/*	$OpenBSD: intr.h,v 1.4.4.8 2001/12/05 00:39:10 niklas Exp $	*/
/*	$NetBSD: intr.h,v 1.5 1996/05/13 06:11:28 mycroft Exp $	*/

/*
 * Copyright (c) 1996 Charles M. Hannum.  All rights reserved.
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
 *	This product includes software developed by Charles M. Hannum.
 * 4. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _I386_INTR_H_
#define _I386_INTR_H_

/*
 * Intel APICs (advanced programmable interrupt controllers) have
 * bytesized priority registers where the upper nibble is the actual
 * interrupt priority level (a.k.a. IPL).  Interrupt vectors are
 * closely tied to these levels as interrupts whose vectors' upper
 * nibble is lower than or equal to the current level are blocked.
 * Not all 256 possible vectors are available for interrupts in
 * APIC systems, only
 *
 * For systems where instead the older ICU (interrupt controlling
 * unit, a.k.a. PIC or 82C59) is used, the IPL is not directly useful,
 * since the interrupt blocking is handled via interrupt masks instead
 * of levels.  However the IPL is easily used as an offset into arrays
 * of masks.
 */
#define IPLSHIFT 4	/* The upper nibble of vectors is the IPL.	*/
#define NIPL 16		/* Four bits of information gives as much.	*/
#define IPL(level) ((level) >> IPLSHIFT)	/* Extract the IPL.	*/
/* XXX Maybe this IDTVECOFF definition should be elsewhere? */
#define IDTVECOFF 0x20	/* The lower 32 IDT vectors are reserved.	*/

/*
 * This macro is only defined for 0 <= x < 14, i.e. there are fourteen
 * distinct priority levels available for interrupts.
 */
#define MAKEIPL(priority) (IDTVECOFF + ((priority) << IPLSHIFT))

/*
 * Interrupt priority levels.
 * XXX We are somewhat sloppy about what we mean by IPLs, sometimes
 * XXX we refer to the eight-bit value suitable for storing into APICs'
 * XXX priority registers, other times about the four-bit entity found
 * XXX in the former values' upper nibble, which can be used as offsets
 * XXX in various arrays of our implementation.  We are hoping that
 * XXX the context will provide enough information to not make this
 * XXX sloppy naming a real problem.
 */
#define	IPL_NONE	0		/* nothing */
#define	IPL_SOFTCLOCK	MAKEIPL(0)	/* timeouts */
#define	IPL_SOFTNET	MAKEIPL(1)	/* protocol stacks */
#define	IPL_BIO		MAKEIPL(2)	/* block I/O */
#define	IPL_NET		MAKEIPL(3)	/* network */
#define	IPL_SOFTTTY	MAKEIPL(4)	/* delayed terminal handling */
#define	IPL_TTY		MAKEIPL(5)	/* terminal */
#define	IPL_IMP		MAKEIPL(6)	/* memory allocation */
#define	IPL_AUDIO	MAKEIPL(7)	/* audio */
#define	IPL_CLOCK	MAKEIPL(8)	/* clock */
#define	IPL_HIGH	MAKEIPL(9)	/* everything */
#define	IPL_IPI		MAKEIPL(10)	/* interprocessor interrupt */

/* Interrupt sharing types. */
#define	IST_NONE	0	/* none */
#define	IST_PULSE	1	/* pulsed */
#define	IST_EDGE	2	/* edge-triggered */
#define	IST_LEVEL	3	/* level-triggered */

/* Soft interrupt masks. */
#define	SIR_CLOCK	31
#define	SIR_NET		30
#define	SIR_TTY		29

#ifndef _LOCORE

#ifdef MULTIPROCESSOR
#include <machine/i82489reg.h>
#include <machine/i82489var.h>
#endif

extern volatile u_int32_t lapic_tpr;

volatile int cpl;	/* Current interrupt priority level.		*/
volatile u_int32_t ipending;/* Interrupts pending.			*/
#ifndef MULTIPROCESSOR
volatile u_int32_t astpending;/* Async software traps (softints) pending. */
#endif
int imask[NIPL];	/* Bitmasks telling what interrupts are blocked. */
int iunmask[NIPL];	/* Bitmasks telling what interrupts are accepted. */

#define IMASK(level) imask[IPL(level)]
#define IUNMASK(level) iunmask[IPL(level)]

extern void Xspllower __P((void));

static __inline int splraise __P((int));
static __inline int spllower __P((int));
static __inline void splx __P((int));
static __inline void softintr __P((int, int));

/*
 * Raise current interrupt priority level, and return the old one.
 */
static __inline int
splraise(ncpl)
	register int ncpl;
{
	register int ocpl = lapic_tpr;

	if (ncpl > ocpl)
		lapic_tpr = ncpl;
	return (ocpl);
}

/*
 * Restore an old interrupt priority level.  If any thereby unmasked
 * interrupts are pending, call Xspllower() to process them.
 */
static __inline void
splx(ncpl)
	register int ncpl;
{
	lapic_tpr = ncpl;
	if (ipending & IUNMASK(ncpl))
		Xspllower();
}

/*
 * Same as splx(), but we return the old value of spl, for the
 * benefit of some splsoftclock() callers.
 */
static __inline int
spllower(ncpl)
	register int ncpl;
{
	register int ocpl = lapic_tpr;

	splx(ncpl);

/* XXX - instead of splx() call above.
	lapic_tpr = ncpl;
	if (ipending & IUNMASK(ncpl))
		Xspllower();
*/
	return (ocpl);
}

/*
 * Hardware interrupt masks
 */
#define	splbio()	splraise(IPL_BIO)
#define	splnet()	splraise(IPL_NET)
#define	spltty()	splraise(IPL_TTY)
#define	splaudio()	splraise(IPL_AUDIO)
#define	splclock()	splraise(IPL_CLOCK)
#define	splstatclock()	splhigh()

/*
 * Software interrupt masks
 *
 * NOTE: spllowersoftclock() is used by hardclock() to lower the priority from
 * clock to softclock before it calls softclock().
 */
#define	spllowersoftclock()	spllower(IPL_SOFTCLOCK)
#define	splsoftclock()		splraise(IPL_SOFTCLOCK)
#define	splsoftnet()		splraise(IPL_SOFTNET)
#define	splsofttty()		splraise(IPL_SOFTTTY)

/*
 * Miscellaneous
 */
#define	splimp()	splraise(IPL_IMP)
#define	splvm()		splraise(IPL_IMP)
#define	splhigh()	splraise(IPL_HIGH)
#define	spl0()		spllower(IPL_NONE)

/*
 * Software interrupt registration
 *
 * We hand-code this to ensure that it's atomic.
 */
static __inline void
softintr(sir, vec)
	register int sir;
	register int vec;
{
	__asm __volatile("orl %0,_ipending" : : "ir" (sir));
#ifdef MULTIPROCESSOR
	i82489_writereg(LAPIC_ICRLO,
	    vec | LAPIC_DLMODE_FIXED | LAPIC_LVL_ASSERT | LAPIC_DEST_SELF);
#endif
}

#define	setsoftast()	(astpending = 1)
#define	setsoftclock()	softintr(1 << SIR_CLOCK, IPL_SOFTCLOCK)
#define	setsoftnet()	softintr(1 << SIR_NET, IPL_SOFTNET)
#define	setsofttty()	softintr(1 << SIR_TTY, IPL_SOFTTTY)

#define I386_IPI_HALT	0x00000001
#define I386_IPI_TLB	0x00000002
#define I386_IPI_FPSAVE	0x00000004

/* the following are for debugging.. */
#define I386_IPI_GMTB	0x00000010
#define I386_IPI_NYCHI	0x00000020

#define I386_NIPI	6

struct cpu_info;
void i386_send_ipi (struct cpu_info *, int);
void i386_broadcast_ipi (int);
void i386_ipi_handler (void);

#endif /* !_LOCORE */

#endif /* !_I386_INTR_H_ */
