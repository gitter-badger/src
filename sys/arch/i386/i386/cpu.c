/*	$OpenBSD: cpu.c,v 1.1.2.7 2003/04/11 16:12:56 niklas Exp $	*/
/* $NetBSD: cpu.c,v 1.1.2.7 2000/06/26 02:04:05 sommerfeld Exp $ */

/*-
 * Copyright (c) 2000 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by RedBack Networks Inc.
 *
 * Author: Bill Sommerfeld
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *        This product includes software developed by the NetBSD
 *        Foundation, Inc. and its contributors.
 * 4. Neither the name of The NetBSD Foundation nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * Copyright (c) 1999 Stefan Grefen
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *      This product includes software developed by the NetBSD
 *      Foundation, Inc. and its contributors.
 * 4. Neither the name of The NetBSD Foundation nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY AUTHOR AND CONTRIBUTORS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR AND CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include "lapic.h"
#include "ioapic.h"

#include <sys/param.h>
#include <sys/proc.h>
#include <sys/user.h>
#include <sys/systm.h>
#include <sys/device.h>

#include <uvm/uvm_extern.h>

#include <machine/cpu.h>
#include <machine/cpufunc.h>
#include <machine/cpuvar.h>
#include <machine/pmap.h>
#include <machine/vmparam.h>
#include <machine/mpbiosvar.h>
#include <machine/pcb.h>
#include <machine/specialreg.h>
#include <machine/segments.h>

#if NLAPIC > 0
#include <machine/apicvar.h>
#include <machine/i82489reg.h>
#include <machine/i82489var.h>
#endif

#if NIOAPIC > 0
#include <machine/i82093var.h>
#endif

int     cpu_match __P((struct device *, void *, void *));
void    cpu_attach __P((struct device *, struct device *, void *));

/*
 * Statically-allocated CPU info for the primary CPU (or the only
 * CPU, on uniprocessors).  The CPU info list is initialized to
 * point at it.
 */
struct cpu_info cpu_info_primary;
struct cpu_info *cpu_info_list = &cpu_info_primary;

#ifdef MULTIPROCESSOR
/*
 * Array of CPU info structures.  Must be statically-allocated because
 * curproc, etc. are used early.
 */

struct cpu_info *cpu_info[I386_MAXPROCS] = { &cpu_info_primary };

void   	cpu_hatch __P((void *));
void   	cpu_boot_secondary __P((struct cpu_info *));
void	cpu_copy_trampoline __P((void));

/*
 * Runs once per boot once multiprocessor goo has been detected and
 * the local APIC has been mapped.
 * Called from mpbios_scan();
 */
void
cpu_init_first()
{
	int cpunum = cpu_number();

	if (cpunum != 0) {
		cpu_info[0] = NULL;
		cpu_info[cpunum] = &cpu_info_primary;
	}

	cpu_copy_trampoline();
}
#endif

struct cfattach cpu_ca = {
	sizeof(struct cpu_info), cpu_match, cpu_attach
};

struct cfdriver cpu_cd = {
	NULL, "cpu", DV_DULL /* XXX DV_CPU */
};

int
cpu_match(parent, matchv, aux)
    struct device *parent;
    void *matchv;
    void *aux;
{
  	struct cfdata *match = (struct cfdata *)matchv;
	struct cpu_attach_args *caa = (struct cpu_attach_args *)aux;

	if (strcmp(caa->caa_name, match->cf_driver->cd_name) == 0)
		return (1);
	return (0);
}

void
cpu_attach(parent, self, aux)
	struct device *parent, *self;
	void *aux;
{
	struct cpu_info *ci = (struct cpu_info *)self;
	struct cpu_attach_args *caa = (struct cpu_attach_args *)aux;

#ifdef MULTIPROCESSOR
	int cpunum = caa->cpu_number;
	vaddr_t kstack;
	struct pcb *pcb;

	if (caa->cpu_role != CPU_ROLE_AP) {
		if (cpunum != cpu_number()) {
			panic("%s: running cpu is at apic %d"
			    " instead of at expected %d\n",
			    self->dv_xname, cpu_number(), cpunum);
		}

		ci = &cpu_info_primary;
		bcopy(self, &ci->ci_dev, sizeof *self);

		/* special-case boot CPU */			    /* XXX */
		if (cpu_info[cpunum] == &cpu_info_primary) {	    /* XXX */
			cpu_info[cpunum] = NULL; 		    /* XXX */
		}				 		    /* XXX */
	}
	if (cpu_info[cpunum] != NULL)
		panic("cpu at apic id %d already attached?", cpunum);

	cpu_info[cpunum] = ci;
#endif

	ci->ci_cpuid = caa->cpu_number;
	ci->ci_signature = caa->cpu_signature;
	ci->ci_feature_flags = caa->feature_flags;
	ci->ci_func = caa->cpu_func;

#ifdef MULTIPROCESSOR
	/*
	 * Allocate UPAGES contiguous pages for the idle PCB and stack.
	 */

	kstack = uvm_km_alloc (kernel_map, USPACE);
	if (kstack == 0) {
		if (cpunum == 0) { /* XXX */
			panic("cpu_attach: unable to allocate idle stack for"
			    " primary");
		}
		printf("%s: unable to allocate idle stack\n",
		    ci->ci_dev.dv_xname);
		return;
	}
	pcb = ci->ci_idle_pcb = (struct pcb *)kstack;
	memset(pcb, 0, USPACE);

	pcb->pcb_tss.tss_ss0 = GSEL(GDATA_SEL, SEL_KPL);
	pcb->pcb_tss.tss_esp0 = kstack + USPACE - 16 -
	    sizeof (struct trapframe);
	pcb->pcb_tss.tss_esp = kstack + USPACE - 16 -
	    sizeof (struct trapframe);
	pcb->pcb_pmap = pmap_kernel();
	pcb->pcb_cr3 = vtophys(pcb->pcb_pmap->pm_pdir);
	/* pcb->pcb_cr3 = pcb->pcb_pmap->pm_pdir - KERNBASE; XXX ??? */
#endif

	/* further PCB init done later. */

	printf(": ");

	switch (caa->cpu_role) {
	case CPU_ROLE_SP:
		printf("(uniprocessor)\n");
		ci->ci_flags |= CPUF_PRESENT | CPUF_SP | CPUF_PRIMARY;
		identifycpu(ci);
		cpu_init(ci);
		break;

	case CPU_ROLE_BP:
		printf("apid %d (", caa->cpu_number);
		printf("boot processor");
		ci->ci_flags |= CPUF_PRESENT | CPUF_BSP | CPUF_PRIMARY;
		printf(")\n");
		identifycpu(ci);
		cpu_init(ci);

#if NLAPIC > 0
		/*
		 * Enable local apic
		 */
		lapic_enable();
		lapic_calibrate_timer(ci);
#endif
#if NIOAPIC > 0
		ioapic_bsp_id = caa->cpu_number;
#endif
		break;

	case CPU_ROLE_AP:
		/*
		 * report on an AP
		 */
		printf("apid %d (", caa->cpu_number);
		ci->ci_flags |= CPUF_PRESENT | CPUF_AP;
		printf("application processor");
		printf(")\n");
		identifycpu(ci);
		ci->ci_next = cpu_info_list->ci_next;
		cpu_info_list->ci_next = ci;
		break;

	default:
		panic("unknown processor type??\n");
	}

#ifdef MULTIPROCESSOR
	if (mp_verbose) {
		printf("%s: kstack at 0x%lx for %d bytes\n",
		    ci->ci_dev.dv_xname, kstack, USPACE);
		printf("%s: idle pcb at %p, idle sp at 0x%x\n",
		    ci->ci_dev.dv_xname, pcb, pcb->pcb_esp);
	}
#endif
}

/*
 * Initialize the processor appropriately.
 */

void
cpu_init(ci)
	struct cpu_info *ci;
{
	/* configure the CPU if needed */
	if (ci->cpu_setup != NULL)
		(*ci->cpu_setup)(NULL, 0, 0);

#if defined(I486_CPU) || defined(I586_CPU) || defined(I686_CPU)
	/*
	 * On a 486 or above, enable ring 0 write protection.
	 */
	if (ci->cpu_class >= CPUCLASS_486)
		lcr0(rcr0() | CR0_WP);
#endif
	if (cpu_feature & CPUID_PGE)
		lcr4(rcr4() | CR4_PGE);	/* enable global TLB caching */

	ci->ci_flags |= CPUF_RUNNING;
}


#ifdef MULTIPROCESSOR

void
cpu_boot_secondary_processors()
{
	struct cpu_info *ci;
	u_long i;

	for (i = 0; i < I386_MAXPROCS; i++) {
		ci = cpu_info[i];
		if (ci == NULL)
			continue;
		if (ci->ci_idle_pcb == NULL)
			continue;
		if ((ci->ci_flags & CPUF_PRESENT) == 0)
			continue;
		if (ci->ci_flags & (CPUF_BSP|CPUF_SP|CPUF_PRIMARY))
			continue;
		cpu_boot_secondary(ci);
	}
}

void
cpu_init_idle_pcbs()
{
	struct cpu_info *ci;
	u_long i;

	for (i=0; i < I386_MAXPROCS; i++) {
		ci = cpu_info[i];
		if (ci == NULL)
			continue;
		if (ci->ci_idle_pcb == NULL)
			continue;
		if ((ci->ci_flags & CPUF_PRESENT) == 0)
			continue;
		i386_init_pcb_tss_ldt(ci);
	}
}

void
cpu_boot_secondary (ci)
	struct cpu_info *ci;
{
	struct pcb *pcb;
	int i;
	struct pmap *kpm = pmap_kernel();
	extern u_int32_t mp_pdirpa;

	printf("%s: starting\n", ci->ci_dev.dv_xname);

	/* XXX move elsewhere, not per CPU. */
	mp_pdirpa = vtophys(kpm->pm_pdir);

	pcb = ci->ci_idle_pcb;

	printf("%s: init idle stack ptr is 0x%x\n", ci->ci_dev.dv_xname,
	    pcb->pcb_esp);

	CPU_STARTUP(ci);

	/*
	 * wait for it to become ready
	 */
	for (i = 100000; (!(ci->ci_flags & CPUF_RUNNING)) && i > 0; i--) {
		delay(10);
	}
	if (!(ci->ci_flags & CPUF_RUNNING)) {
		printf("cpu failed to become ready\n");
		Debugger();
	}

}

struct cpu_info *first_app_cpu = NULL;

/*
 * The CPU ends up here when its ready to run
 * XXX should share some of this with init386 in machdep.c
 * for now it jumps into an infinite loop.
 */
void
cpu_hatch(void *v)
{
	struct cpu_info *ci = (struct cpu_info *)v;
        struct region_descriptor region;
#if 0
	volatile int i;
#endif
	int s;

	cpu_init_idt();

	lapic_enable();
	lapic_set_lvt();

	cpu_init(ci);

	s = splhigh();		/* XXX prevent softints from running here.. */

	enable_intr();
	printf("%s: CPU %d reporting for duty, Sir!\n",ci->ci_dev.dv_xname,
	    cpu_number());
	printf("%s: stack is %p\n", ci->ci_dev.dv_xname, &region);

#if 0
	if (first_app_cpu == NULL)
		first_app_cpu = ci;
	printf("%s: sending IPI to CPU %d\n", ci->ci_dev.dv_xname,
	    cpu_info_primary.ci_cpuid);
	i386_send_ipi(&cpu_info_primary, I386_IPI_GMTB);

	/* give it a chance to be handled.. */
	for (i = 0; i < 1000000; i++)
		;

	printf("%s: sending another IPI to CPU %d\n", ci->ci_dev.dv_xname,
	    cpu_info_primary.ci_cpuid);
	i386_send_ipi(&cpu_info_primary, I386_IPI_GMTB);
#endif

	splx(s);
	/* XXX Just run and collect IPIs */
	for (;;)
		;
}

void
cpu_copy_trampoline()
{
	/*
	 * Copy boot code.
	 */
	extern u_char cpu_spinup_trampoline[];
	extern u_char cpu_spinup_trampoline_end[];

	pmap_kenter_pa((vaddr_t)MP_TRAMPOLINE,	/* virtual */
	    (paddr_t)MP_TRAMPOLINE,		/* physical */
	    VM_PROT_ALL);			/* protection */
	bcopy(cpu_spinup_trampoline, (caddr_t)MP_TRAMPOLINE,
	    cpu_spinup_trampoline_end - cpu_spinup_trampoline);
}

#endif
