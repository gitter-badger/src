/*	$OpenBSD: param.h,v 1.31 2008/05/21 19:23:15 kettenis Exp $	*/
/*	$NetBSD: param.h,v 1.25 2001/05/30 12:28:51 mrg Exp $ */

/*
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Lawrence Berkeley Laboratory.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)param.h	8.1 (Berkeley) 6/11/93
 */

/*
 * Copyright (c) 1996-1999 Eduardo Horvath
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR  ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR  BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

#ifndef _SPARC64_PARAM_H_
#define _SPARC64_PARAM_H_

#define	_MACHINE	sparc64
#define	MACHINE		"sparc64"
#define	_MACHINE_ARCH	sparc64
#define	MACHINE_ARCH	"sparc64"
#define	MID_MACHINE	MID_SPARC64

/*
 * Round p (pointer or byte index) up to a correctly-aligned value for
 * the machine's strictest data type.  The result is u_int and must be
 * cast to any desired pointer type.
 *
 * ALIGNED_POINTER is a boolean macro that checks whether an address
 * is valid to fetch data elements of type t from on this architecture.
 * This does not reflect the optimal alignment, just the possibility
 * (within reasonable limits). 
 *
 */
#define	ALIGNBYTES		0xf
#define	ALIGN(p)		(((u_long)(p) + ALIGNBYTES) & ~ALIGNBYTES)
#define ALIGNED_POINTER(p,t)	((((u_long)(p)) & (sizeof(t)-1)) == 0)

#define	DEV_BSHIFT	9		/* log2(DEV_BSIZE) */
#define	DEV_BSIZE	(1 << DEV_BSHIFT)
#define	BLKDEV_IOSIZE	2048
#define	MAXPHYS		(64 * 1024)

/* We get stack overflows w/8K stacks in 64-bit mode */
#define	UPAGES		2		/* initial stack size in pages */
#define	USPACE		(UPAGES*8192)
#define	USPACE_ALIGN	(0)		/* u-area alignment 0-none */


/*
 * Here are all the magic kernel virtual addresses and how they're allocated.
 * 
 * First, the PROM is usually a fixed-sized block from 0x00000000f0000000 to
 * 0x00000000f0100000.  It also uses some space around 0x00000000fff00000 to
 * map in device registers.  The rest is pretty much ours to play with.
 *
 * The kernel starts at KERNBASE.  Here's the layout.  We use macros to set
 * the addresses so we can relocate everything easily.  We use 4MB locked TTEs
 * to map in the kernel text and data segments.  Any extra pages are recycled,
 * so they can potentially be double-mapped.  This shouldn't really be a
 * problem since they're unused, but wild pointers can cause silent data
 * corruption if they are in those segments.
 *
 * 0x0000000000000000:	64K NFO page zero
 * 0x0000000000010000:	Userland or PROM
 * KERNBASE:		4MB kernel text and read only data
 *				This is mapped in the ITLB and 
 *				Read-Only in the DTLB
 * KERNBASE+0x400000:	4MB kernel data and BSS -- not in ITLB
 *				Contains context table, kernel pmap,
 *				and other important structures.
 * KERNBASE+0x800000:	Unmapped page -- redzone
 * KERNBASE+0x802000:	Process 0 stack and u-area
 * KERNBASE+0x806000:	2 pages for pmap_copy_page and /dev/mem
 * KERNBASE+0x80a000:	Start of kernel VA segment
 * KERNEND:		End of kernel VA segment
 * KERNEND+0x02000:	Auxreg_va (unused?)
 * KERNEND+0x04000:	TMPMAP_VA (unused?)
 * KERNEND+0x06000:	message buffer.
 * KERNEND+0x010000:	64K locked TTE -- different for each CPU
 *			Contains interrupt stack, cpu_info structure,
 *			and 32KB kernel TSB.
 *
 */
#define	KERNBASE	0x001000000	/* start of kernel virtual space */
#define	KERNEND		0x0e0000000	/* end of kernel virtual space */
#define	VM_MAX_KERNEL_BUF	((KERNEND-KERNBASE)/4)

#define _MAXNBPG	8192	/* fixed VAs, independent of actual NBPG */

#define	AUXREG_VA	(      KERNEND + _MAXNBPG) /* 1 page REDZONE */
#define	TMPMAP_VA	(    AUXREG_VA + _MAXNBPG)
#define	MSGBUF_VA	(    TMPMAP_VA + _MAXNBPG)
/*
 * Here's the location of the interrupt stack and CPU structure.
 */
#define INTSTACK	(      KERNEND + 8*_MAXNBPG)/* 64K after kernel end */
#define	EINTSTACK	(     INTSTACK + 2*USPACE)	/* 32KB */
#define	CPUINFO_VA	(    EINTSTACK)

/*
 * Constants related to network buffer management.
 */
#define	NMBCLUSTERS	4096		/* map size, max cluster allocation */

#define MSGBUFSIZE	NBPG

/*
 * Minimum and maximum sizes of the kernel malloc arena in PAGE_SIZE-sized
 * logical pages.
 */
#define	NKMEMPAGES_MIN_DEFAULT	((8 * 1024 * 1024) >> PAGE_SHIFT)
#define	NKMEMPAGES_MAX_DEFAULT	((128 * 1024 * 1024) >> PAGE_SHIFT)

/* pages ("clicks") to disk blocks */
#define	ctod(x)		((x) << (PGSHIFT - DEV_BSHIFT))
#define	dtoc(x)		((x) >> (PGSHIFT - DEV_BSHIFT))

/* bytes to disk blocks */
#define	btodb(x)	((x) >> DEV_BSHIFT)
#define	dbtob(x)	((x) << DEV_BSHIFT)

/*
 * dvmamap manages a range of DVMA addresses intended to create double
 * mappings of physical memory. In a way, `dvmamap' is a submap of the
 * VM map `phys_map'. The difference is the use of the `resource map'
 * routines to manage page allocation, allowing DVMA addresses to be
 * allocated and freed from within interrupt routines.
 *
 * Note that `phys_map' can still be used to allocate memory-backed pages
 * in DVMA space.
 */
#ifdef _KERNEL
#ifndef _LOCORE

extern void	delay(unsigned int);
#define	DELAY(n)	delay(n)

extern int cputyp;

#if defined (SUN4US) || defined (SUN4V)
#define CPU_ISSUN4U	(cputyp == CPU_SUN4U)
#define CPU_ISSUN4US	(cputyp == CPU_SUN4US)
#define CPU_ISSUN4V	(cputyp == CPU_SUN4V)
#else
#define CPU_ISSUN4U	(1)
#define CPU_ISSUN4US	(0)
#define CPU_ISSUN4V	(0)
#endif

#endif /* _LOCORE */
#endif /* _KERNEL */

/*
 * Values for the cputyp variable.
 */
#define CPU_SUN4	0
#define CPU_SUN4C	1
#define CPU_SUN4M	2
#define CPU_SUN4U	3
#define CPU_SUN4US	4
#define CPU_SUN4V	5 

/*
 * On a sun4u machine, the page size is 8192.
 */

#define	NBPG		8192		/* bytes/page */
#define	PGOFSET		(NBPG-1)	/* byte offset into page */
#define	PGSHIFT		13		/* log2(NBPG) */

#define PAGE_SHIFT	13
#define PAGE_SIZE	(1 << PAGE_SHIFT)
#define PAGE_MASK	(PAGE_SIZE - 1)

#ifdef _KERNEL
#ifndef _LOCORE
#include <machine/cpu.h>
#endif
#endif

#endif	/* _SPARC64_PARAM_H_ */
