/*	$OpenBSD: cpu.h,v 1.3 2005/05/25 23:17:47 niklas Exp $	*/

/*
 * Copyright (c) 2005 Michael Shalayeff
 * All rights reserved.
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF MIND, USE, DATA OR PROFITS, WHETHER IN
 * AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
 * OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
/* 
 * Copyright (c) 1988-1994, The University of Utah and
 * the Computer Systems Laboratory at the University of Utah (CSL).
 * All rights reserved.
 *
 * Permission to use, copy, modify and distribute this software is hereby
 * granted provided that (1) source code retains these copyright, permission,
 * and disclaimer notices, and (2) redistributions including binaries
 * reproduce the notices in supporting documentation, and (3) all advertising
 * materials mentioning features or use of this software display the following
 * acknowledgement: ``This product includes software developed by the
 * Computer Systems Laboratory at the University of Utah.''
 *
 * THE UNIVERSITY OF UTAH AND CSL ALLOW FREE USE OF THIS SOFTWARE IN ITS "AS
 * IS" CONDITION.  THE UNIVERSITY OF UTAH AND CSL DISCLAIM ANY LIABILITY OF
 * ANY KIND FOR ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 *
 * CSL requests users of this software to return to csl-dist@cs.utah.edu any
 * improvements that they make and grant CSL redistribution rights.
 *
 * 	Utah $Hdr: cpu.h 1.19 94/12/16$
 */

#ifndef	_MACHINE_CPU_H_
#define	_MACHINE_CPU_H_

#include <machine/trap.h>
#include <machine/frame.h>

/*
 * COPR/SFUs
 */
#define	HPPA_FPUS	0xc0
#define	HPPA_FPUVER(w)	(((w) & 0x003ff800) >> 11)
#define	HPPA_FPU_OP(w)	((w) >> 26)
#define	HPPA_FPU_UNMPL	0x01	/* exception reg, the rest is << 1 */
#define	HPPA_FPU_ILL	0x80	/* software-only */
#define	HPPA_FPU_I	0x01
#define	HPPA_FPU_U	0x02
#define	HPPA_FPU_O	0x04
#define	HPPA_FPU_Z	0x08
#define	HPPA_FPU_V	0x10
#define	HPPA_FPU_D	0x20
#define	HPPA_FPU_T	0x40
#define	HPPA_FPU_XMASK	0x7f
#define	HPPA_FPU_T_POS	25	/* 32bit reg! */
#define	HPPA_FPU_RM	0x00000600
#define	HPPA_FPU_CQ	0x00fff800
#define	HPPA_FPU_C	0x04000000
#define	HPPA_FPU_FLSH	27
#define	HPPA_FPU_INIT	(0)
#define	HPPA_FPU_FORK(s) ((s) & ~((u_int64_t)(HPPA_FPU_XMASK)<<32))
#define	HPPA_PMSFUS	0x20	/* ??? */

/*
 * Interrupts stuff
 */
#define	IPL_NONE	0
#define	IPL_SOFTCLOCK	1   
#define	IPL_SOFTNET	2
#define	IPL_BIO		3
#define	IPL_NET		4
#define	IPL_SOFTTTY	5
#define	IPL_TTY		6
#define	IPL_VM		7
#define	IPL_AUDIO	8
#define	IPL_CLOCK	9
#define	IPL_STATCLOCK	10
#define	IPL_SCHED	IPL_STATCLOCK
#define	IPL_HIGH	11

#define	NIPL		12

#define	IST_NONE        0
#define	IST_PULSE       1
#define	IST_EDGE        2
#define	IST_LEVEL       3

#define	splsoftclock()	splraise(IPL_SOFTCLOCK)
#define	splsoftnet()	splraise(IPL_SOFTNET)
#define	splbio()	splraise(IPL_BIO)
#define	splnet()	splraise(IPL_NET)
#define	splsofttty()	splraise(IPL_SOFTTTY)
#define	spltty()	splraise(IPL_TTY)
#define	splvm()		splraise(IPL_VM)
#define	splimp()	splvm()
#define	splaudio()	splraise(IPL_AUDIO)
#define	splclock()	splraise(IPL_CLOCK)
#define	splsched()	splraise(IPL_SCHED)
#define	splstatclock()	splraise(IPL_STATCLOCK)
#define	splhigh()	splraise(IPL_HIGH)
#define	spl0()		spllower(IPL_NONE)
#define	splx(c)		spllower(c)

#define	setsoftast()		(astpending = 1)
#define	setsoftclock()		/* TODO */
#define	setsoftnet()		/* TODO */
#define	setsofttty()		/* TODO */

#ifndef _LOCORE
#include <sys/time.h>
#include <sys/sched.h>

struct cpu_info {
	struct proc	*ci_curproc;
	struct pcb	*ci_cpcb;
	struct cpu_info	*ci_next;

	struct proc	*ci_fpproc;
	int		ci_number;
	struct schedstate_percpu ci_schedstate;	/* scheduler state */

	/* DEBUG/DIAGNOSTIC stuff */
	u_long		ci_spin_locks;  /* # of spin locks held */
	u_long		ci_simple_locks;/* # of simple locks held */

	/* Spinning up the CPU */
	void		(*ci_spinup)(void); /* spinup routine */
	void		*ci_initstack;
};

struct cpu_info *curcpu(void);
#define	cpu_number()	(curcpu()->ci_number)
#define	CPU_IS_PRIMARY(ci)	((ci)->ci_number == 0)
#define	CPU_INFO_ITERATOR	int
#define	CPU_INFO_FOREACH(cii,ci) \
	cii = 0, ci = curcpu(); ci != NULL; ci = ci->ci_next
#define	CPU_INFO_UNIT(ci)	((ci)->ci_number)

#ifdef DIAGNOSTIC   
void splassert_fail(int, int, const char *);
extern int splassert_ctl;
void splassert_check(int, const char *);
#define splassert(__wantipl) do {			\
	if (__predict_false(splassert_ctl > 0)) {	\
		splassert_check(__wantipl, __func__);	\
	}						\
} while (0)
#else
#define splassert(__wantipl)	do { /* nada */ } while (0)
#endif /* DIAGNOSTIC */

/* types */
enum hppa_cpu_type {
	hpcxu, hpcxu2, hpcxw
};
extern enum hppa_cpu_type cpu_type;
extern const char *cpu_typename;
extern int cpu_hvers;
#endif

/*
 * Exported definitions unique to hp700/PA-RISC cpu support.
 */

#define	HPPA_PGALIAS	0x0000000000100000UL
#define	HPPA_PGAMASK	0xfffffffffff00000UL
#define	HPPA_PGAOFF	0x00000000000fffffUL

#define	HPPA_PHYSMAP	0x000001ffffffffffUL
#define	HPPA_IOBEGIN	0xfffffff000000000UL
#define	HPPA_IOLEN	0x0000001000000000UL
#define	HPPA_PHYSEND	0xffffffffffffffffUL
#define	HPPA_IOADDR	0xfffffff100000000UL
#define	HPPA_IOBCAST	0xfffffffffffc0000UL
#define	HPPA_LBCAST	0xfffffffffffc0000UL
#define	HPPA_GBCAST	0xfffffffffffe0000UL
#define	HPPA_FPADDR	0xfffffffffff80000UL
#define	HPPA_FLEX_MASK	0xfffffffffffc0000UL
#define	HPPA_DMA_ENABLE	0x00000001
#define	HPPA_SPA_ENABLE	0x00000020
#define	HPPA_NMODSPBUS	64

#define	clockframe		trapframe
#define	CLKF_PC(framep)		((framep)->tf_iioq[0])
#define	CLKF_INTR(framep)	((framep)->tf_flags & TFF_INTR)
#define	CLKF_USERMODE(framep)	((framep)->tf_flags & T_USER)
#define	CLKF_SYSCALL(framep)	((framep)->tf_flags & TFF_SYS)

#define	signotify(p)		(setsoftast())
#define	need_resched(ci)	(want_resched = 1, setsoftast())
#define	need_proftick(p)	((p)->p_flag |= P_OWEUPC, setsoftast())

#ifndef _LOCORE
#ifdef _KERNEL

extern int want_resched, astpending;

#define DELAY(x) delay(x)

int	splraise(int cpl);
int	spllower(int cpl);

void	delay(u_int us);
void	hppa_init(paddr_t start);
void	trap(int type, struct trapframe *frame);
int	spcopy(pa_space_t ssp, const void *src,
		    pa_space_t dsp, void *dst, size_t size);
int	spstrcpy(pa_space_t ssp, const void *src,
		      pa_space_t dsp, void *dst, size_t size, size_t *rsize);
int	copy_on_fault(void);
void	switch_trampoline(void);
int	cpu_dumpsize(void);
int	cpu_dump(void);

#ifdef USELEDS
#define	PALED_NETSND	0x01
#define	PALED_NETRCV	0x02
#define	PALED_DISK	0x04
#define	PALED_HEARTBEAT	0x08
#define	PALED_LOADMASK	0xf0

#define	PALED_DATA	0x01
#define	PALED_STROBE	0x02

extern volatile u_int8_t *machine_ledaddr;
extern int machine_ledword, machine_leds;

static __inline void
ledctl(int on, int off, int toggle)
{
	if (machine_ledaddr) {
		int r;

		if (on)
			machine_leds |= on;
		if (off)
			machine_leds &= ~off;
		if (toggle)
			machine_leds ^= toggle;
			
		r = ~machine_leds;	/* it seems they should be reversed */

		if (machine_ledword)
			*machine_ledaddr = r;
		else {
			register int b;
			for (b = 0x80; b; b >>= 1) {
				*machine_ledaddr = (r & b)? PALED_DATA : 0;
				DELAY(1);
				*machine_ledaddr = ((r & b)? PALED_DATA : 0) |
				    PALED_STROBE;
			}
		}
	}
}
#endif

void fpu_save(vaddr_t va);
void fpu_exit(void);
void ficache(pa_space_t sp, vaddr_t va, vsize_t size);
void fdcache(pa_space_t sp, vaddr_t va, vsize_t size);
void pdcache(pa_space_t sp, vaddr_t va, vsize_t size);
void ficacheall(void);
void fdcacheall(void);
void pitlb(pa_space_t sp, vaddr_t va);
void pdtlb(pa_space_t sp, vaddr_t va);
void ptlball(void);
void mtctl(register_t val, int reg);
register_t mfctl(int reg);
hppa_hpa_t cpu_gethpa(int n);
void sync_caches(void);
#endif

/*
 * Boot arguments stuff
 */

#define	BOOTARG_LEN	(NBPG)
#define	BOOTARG_OFF	(0x10000)

/*
 * CTL_MACHDEP definitions.
 */
#define	CPU_CONSDEV		1	/* dev_t: console terminal device */
#define	CPU_MAXID		1	/* number of valid machdep ids */

#define CTL_MACHDEP_NAMES { \
	{ 0, 0 }, \
	{ "console_device", CTLTYPE_STRUCT }, \
}
#endif

#endif /* _MACHINE_CPU_H_ */
