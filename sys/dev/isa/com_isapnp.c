/*	$OpenBSD: com_isapnp.c,v 1.1.4.2 2003/06/07 11:02:29 ho Exp $	*/
/*
 * Copyright (c) 1997 - 1999, Jason Downs.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name(s) of the author(s) nor the name OpenBSD
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR(S) ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR(S) BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
/*-
 * Copyright (c) 1993, 1994, 1995, 1996
 *	Charles M. Hannum.  All rights reserved.
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
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
 *	@(#)com.c	7.5 (Berkeley) 5/16/91
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/tty.h>
#include <sys/device.h>

#include <machine/intr.h>
#include <machine/bus.h>

#include <dev/ic/comreg.h>
#include <dev/ic/comvar.h>

#include <dev/isa/isavar.h>

#if NCOM_ISAPNP
struct cfattach com_isapnp_ca = {
	sizeof(struct com_softc), comprobe, comattach
};
#endif

int com_isapnp_probe(struct device *, void *, void *);
int com_isapnp_attach(struct device *, struct device *, void *);

int
com_isapnp_probe(struct device *parent, void *match, void *aux)
{
	struct isa_attach_args *ia = aux;
	bus_space_tag_t iot;
	bus_space_handle_t ioh;
	int iobase;

	iot = ia->ia_iot;
	iobase = ia->ia_iobase;
	ioh = ia->ia_ioh;

#ifdef KGDB
	if (iobase == com_kgdb_addr)
		return (1);
#endif
	/* if it's in use as console, it's there. */
	if (iobase == comconsaddr && !comconsattached)
		return (1);

	return comprobe1(iot, ioh);
}

int
com_isapnp_attach(struct device *parent, struct device *self, void *aux)
{
	struct com_softc *sc = (void *)self;
	int iobase;
	int irq;
	bus_space_tag_t iot;
	bus_space_handle_t ioh;
	struct isa_attach_args *ia = aux;

	/*
	 * XXX should be broken out into functions for isa attach and
	 * XXX for commulti attach, with a helper function that contains
	 * XXX most of the interesting stuff.
	 */
	sc->sc_hwflags = 0;
	sc->sc_swflags = 0;

	/*
	 * We're living on an isa.
	 */
	iobase = ia->ia_iobase;
	iot = ia->ia_iot;
	/* No console support! */
	ioh = ia->ia_ioh;

	sc->sc_iot = iot;
	sc->sc_ioh = ioh;
	sc->sc_iobase = iobase;
	sc->sc_frequency = COM_FREQ;

	com_attach_subr(sc);

	irq = ia->ia_irq;
        if (irq != IRQUNK) {
#ifdef KGDB     
		if (iobase == com_kgdb_addr) {
			sc->sc_ih = isa_intr_establish(ia->ia_ic, irq,
				IST_EDGE, IPL_HIGH, kgdbintr, sc,
				sc->sc_dev.dv_xname);
		} else {
			sc->sc_ih = isa_intr_establish(ia->ia_ic, irq,
				IST_EDGE, IPL_TTY, comintr, sc,
				sc->sc_dev.dv_xname);
		}
#else   
		sc->sc_ih = isa_intr_establish(ia->ia_ic, irq,
			IST_EDGE, IPL_TTY, comintr, sc,
			sc->sc_dev.dv_xname);
#endif /* KGDB */
	}
}
