/*	$OpenBSD: vector.s,v 1.1.2.3 2004/03/23 08:02:55 niklas Exp $	*/
/*	$NetBSD: vector.s,v 1.32 1996/01/07 21:29:47 mycroft Exp $	*/

/*
 * Copyright (c) 1993, 1994, 1995 Charles M. Hannum.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *	notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *	notice, this list of conditions and the following disclaimer in the
 *	documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *	must display the following acknowledgement:
 *	This product includes software developed by Charles M. Hannum.
 * 4. The name of the author may not be used to endorse or promote products
 *	derived from this software without specific prior written permission.
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

#include <machine/i8259.h>
#include <dev/isa/isareg.h>

#define MY_COUNT _C_LABEL(uvmexp)

/*
 * Macros for interrupt entry, call to handler, and exit.
 *
 * XXX
 * The interrupt frame is set up to look like a trap frame.  This may be a
 * waste.  The only handler which needs a frame is the clock handler, and it
 * only needs a few bits.  Xdoreti() needs a trap frame for handling ASTs, but
 * it could easily convert the frame on demand.
 *
 * The direct costs of setting up a trap frame are two pushl's (error code and
 * trap number), an addl to get rid of these, and pushing and popping the
 * callee-saved registers %esi, %edi, %ebx, and %ebp twice.
 *
 * If the interrupt frame is made more flexible,  INTR can push %eax first and
 * decide the ipending case with less overhead, e.g., by avoiding loading the
 * segment registers.
 *
 * XXX
 * Should we do a cld on every system entry to avoid the requirement for
 * scattered cld's?
 */

	.globl	_C_LABEL(isa_strayintr)

#ifdef MULTIPROCESSOR
#define LOCK_KERNEL	call _C_LABEL(i386_intlock)
#define UNLOCK_KERNEL	call _C_LABEL(i386_intunlock)
#else
#define LOCK_KERNEL
#define UNLOCK_KERNEL
#endif

/*
 * Normal vectors.
 *
 * We cdr down the intrhand chain, calling each handler with its appropriate
 * argument (0 meaning a pointer to the frame, for clock interrupts).
 *
 * The handler returns one of three values:
 *   0 - This interrupt wasn't for me.
 *   1 - This interrupt was for me.
 *  -1 - This interrupt might have been for me, but I don't know.
 * If there are no handlers, or they all return 0, we flags it as a `stray'
 * interrupt.  On a system with level-triggered interrupts, we could terminate
 * immediately when one of them returns 1; but this is a PC.
 *
 * On exit, we jump to Xdoreti(), to process soft interrupts and ASTs.
 */
#define	INTR(irq_num, ack) \
IDTVEC(recurse/**/irq_num)						;\
	pushfl								;\
	pushl	%cs							;\
	pushl	%esi							;\
	cli								;\
_C_LABEL(Xintr)/**/irq_num/**/:						;\
	pushl	$0			/* dummy error code */		;\
	pushl	$T_ASTFLT		/* trap # for doing ASTs */	;\
	INTRENTRY							;\
	MAKE_FRAME							;\
	i8259_asm_mask(irq_num)		/* mask it in hardware */	;\
	ack(irq_num)			/* and allow other intrs */	;\
	incl	MY_COUNT+V_INTR		/* statistical info */		;\
	movl	_C_LABEL(iminlevel) + (irq_num) * 4, %eax		;\
	movl	CPL,%ebx						;\
	cmpl	%eax,%ebx						;\
	jae	_C_LABEL(Xhold/**/irq_num)/* currently masked; hold it */;\
Xresume/**/irq_num/**/:						;\
	movl	CPL,%eax		/* cpl to restore on exit */	;\
	pushl	%eax							;\
	movl	_C_LABEL(imaxlevel) + (irq_num) * 4,%eax		;\
	movl	%eax,CPL		/* block enough for this irq */	;\
	sti				/* safe to take intrs now */	;\
	movl	_C_LABEL(intrhand) + (irq_num) * 4,%ebx	/* head of chain */ ;\
	testl	%ebx,%ebx						;\
	jz	_C_LABEL(Xstray)/**/irq_num	/* no handlears; we're stray */	;\
	STRAY_INITIALIZE		/* nobody claimed it yet */	;\
	LOCK_KERNEL							;\
7:	movl	IH_ARG(%ebx),%eax	/* get handler arg */		;\
	testl	%eax,%eax						;\
	jnz	4f							;\
	movl	%esp,%eax		/* 0 means frame pointer */	;\
4:	pushl	%eax							;\
	call	*IH_FUN(%ebx)		/* call it */			;\
	addl	$4,%esp			/* toss the arg */		;\
	STRAY_INTEGRATE			/* maybe he claimed it */	;\
	orl	%eax,%eax		/* should it be counted? */	;\
	jz	5f			/* no, skip it */		;\
	incl	IH_COUNT(%ebx)		/* count the intrs */		;\
5:	movl	IH_NEXT(%ebx),%ebx	/* next handler in chain */	;\
	testl	%ebx,%ebx						;\
	jnz	7b							;\
	UNLOCK_KERNEL							;\
	STRAY_TEST			/* see if it's a stray */	;\
6:	i8259_asm_unmask(irq_num)	/* unmask it in hardware */	;\
	jmp	_C_LABEL(Xdoreti)	/* lower spl and do ASTs */	;\
IDTVEC(stray/**/irq_num)						;\
	pushl	$irq_num						;\
	call	_C_LABEL(isa_strayintr)					;\
	addl	$4,%esp							;\
	jmp	6b							;\
IDTVEC(hold/**/irq_num)							;\
	orb	$IRQ_BIT(irq_num),_C_LABEL(ipending) + IRQ_BYTE(irq_num)	;\
	INTRFASTEXIT

#if defined(DEBUG) && defined(notdef)
#define	STRAY_INITIALIZE \
	xorl	%esi,%esi
#define	STRAY_INTEGRATE \
	orl	%eax,%esi
#define	STRAY_TEST \
	testl	%esi,%esi						;\
	jz	_C_LABEL(Xstray)/**/irq_num
#else /* !DEBUG */
#define	STRAY_INITIALIZE
#define	STRAY_INTEGRATE
#define	STRAY_TEST
#endif /* DEBUG */

#ifdef DDB
#define	MAKE_FRAME \
	leal	-8(%esp),%ebp
#else /* !DDB */
#define	MAKE_FRAME
#endif /* DDB */

#define ICUADDR IO_ICU1

INTR(0, i8259_asm_ack1)
INTR(1, i8259_asm_ack1)
INTR(2, i8259_asm_ack1)
INTR(3, i8259_asm_ack1)
INTR(4, i8259_asm_ack1)
INTR(5, i8259_asm_ack1)
INTR(6, i8259_asm_ack1)
INTR(7, i8259_asm_ack1)

#undef ICUADDR
#define ICUADDR IO_ICU2

INTR(8, i8259_asm_ack2)
INTR(9, i8259_asm_ack2)
INTR(10, i8259_asm_ack2)
INTR(11, i8259_asm_ack2)
INTR(12, i8259_asm_ack2)
INTR(13, i8259_asm_ack2)
INTR(14, i8259_asm_ack2)
INTR(15, i8259_asm_ack2)

/*
 * These tables are used by the ISA configuration code.
 */
/* interrupt service routine entry points */
IDTVEC(intr)
	.long   _C_LABEL(Xintr0), _C_LABEL(Xintr1), _C_LABEL(Xintr2)
	.long	_C_LABEL(Xintr3), _C_LABEL(Xintr4), _C_LABEL(Xintr5)
	.long	_C_LABEL(Xintr6), _C_LABEL(Xintr7), _C_LABEL(Xintr8)
	.long	_C_LABEL(Xintr9), _C_LABEL(Xintr10), _C_LABEL(Xintr11)
	.long	_C_LABEL(Xintr12), _C_LABEL(Xintr13)
	.long	_C_LABEL(Xintr14), _C_LABEL(Xintr15)

/*
 * These tables are used by Xdoreti() and Xspllower().
 */
/* resume points for suspended interrupts */
IDTVEC(resume)
	.long	_C_LABEL(Xresume0), _C_LABEL(Xresume1)
	.long	_C_LABEL(Xresume2), _C_LABEL(Xresume3)
	.long	_C_LABEL(Xresume4), _C_LABEL(Xresume5)
	.long	_C_LABEL(Xresume6), _C_LABEL(Xresume7)
	.long	_C_LABEL(Xresume8), _C_LABEL(Xresume9)
	.long	_C_LABEL(Xresume10), _C_LABEL(Xresume11)
	.long	_C_LABEL(Xresume12), _C_LABEL(Xresume13)
	.long	_C_LABEL(Xresume14), _C_LABEL(Xresume15)
	/* for soft interrupts */
	.long	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	.long	_C_LABEL(Xsofttty), _C_LABEL(Xsoftnet)
	.long	_C_LABEL(Xsoftclock)
	.long	0, 0
/* fake interrupts to resume from splx() */
IDTVEC(recurse)
	.long	_C_LABEL(Xrecurse0), _C_LABEL(Xrecurse1)
	.long	_C_LABEL(Xrecurse2), _C_LABEL(Xrecurse3)
	.long	_C_LABEL(Xrecurse4), _C_LABEL(Xrecurse5)
	.long	_C_LABEL(Xrecurse6), _C_LABEL(Xrecurse7)
	.long	_C_LABEL(Xrecurse8), _C_LABEL(Xrecurse9)
	.long	_C_LABEL(Xrecurse10), _C_LABEL(Xrecurse11)
	.long	_C_LABEL(Xrecurse12), _C_LABEL(Xrecurse13)
	.long	_C_LABEL(Xrecurse14), _C_LABEL(Xrecurse15)
	/* for soft interrupts */
	.long	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	.long	_C_LABEL(Xsofttty), _C_LABEL(Xsoftnet)
	.long	_C_LABEL(Xsoftclock)
	.long	0, 0

/* Some bogus data, to keep vmstat happy, for now. */
	.globl	_C_LABEL(intrnames), _C_LABEL(eintrnames)
	.globl	_C_LABEL(intrcnt), _C_LABEL(eintrcnt)
_C_LABEL(intrnames):
	.long	0
_C_LABEL(eintrnames):
_C_LABEL(intrcnt):
	.long	0
_C_LABEL(eintrcnt):
