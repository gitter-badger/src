/*	$OpenBSD: mainbus.c,v 1.3.4.2 2002/03/06 02:04:44 niklas Exp $ */
/*  Copyright (c) 1998 Steve Murphree, Jr. */
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/reboot.h>
#include <sys/conf.h>
#include <sys/device.h>
#include <sys/disklabel.h>

#include <machine/cpu.h>
#include <machine/autoconf.h>

void mainbus_attach __P((struct device *, struct device *, void *));
int  mainbus_match __P((struct device *, void *, void *));
int mainbus_print __P((void *, const char *));
int mainbus_scan __P((struct device *, void *, void *));

struct cfattach mainbus_ca = {
	sizeof(struct device), mainbus_match, mainbus_attach
};

struct cfdriver mainbus_cd = {
	NULL, "mainbus", DV_DULL, 0
};

int
mainbus_match(parent, cf, args)
	struct device *parent;
	void *cf;
	void *args;
{
	return (1);
}

int
mainbus_print(args, bus)
	void *args;
	const char *bus;
{
	struct confargs *ca = args;

	if (ca->ca_paddr != (void *)-1)
		printf(" addr 0x%x", (u_int32_t)ca->ca_paddr);
	return (UNCONF);
}

int
mainbus_scan(parent, child, args)
	struct device *parent;
	void *child, *args;
{
	struct cfdata *cf = child;
	struct confargs oca;

	bzero(&oca, sizeof oca);
	oca.ca_paddr = (void *)cf->cf_loc[0];
	oca.ca_vaddr = (void *)-1;
	oca.ca_ipl = -1;
	oca.ca_bustype = BUS_MAIN;
	oca.ca_name = cf->cf_driver->cd_name;
	if ((*cf->cf_attach->ca_match)(parent, cf, &oca) == 0)
		return (0);
	config_attach(parent, cf, &oca, mainbus_print);
	return (1);
}

void
mainbus_attach(parent, self, args)
	struct device *parent, *self;
	void *args;
{
	printf (" machine type MVME%x\n", brdtyp);

	/* XXX
	 * should have a please-attach-first list for mainbus,
	 * to ensure that the pcc/vme2/mcc chips are attached
	 * first.
	 */

	(void)config_search(mainbus_scan, self, args);
}
