/*	$OpenBSD: fils.c,v 1.22 2000/11/14 18:56:31 aaron Exp $	*/

/*
 * Copyright (C) 1993-1998 by Darren Reed.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that this notice is preserved and due credit is given
 * to the original author and the contributors.
 */
#ifdef  __FreeBSD__
# include <osreldate.h>
#endif
#include <stdio.h>
#include <string.h>
#if !defined(__SVR4) && !defined(__svr4__)
# include <strings.h>
#endif
#include <sys/types.h>
#include <sys/time.h>
#include <sys/param.h>
#include <sys/file.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stddef.h>
#include <nlist.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <net/if.h>
#if __FreeBSD_version >= 300000
# include <net/if_var.h>
#endif
#include <netdb.h>
#include <arpa/nameser.h>
#include <resolv.h>
#include <netinet/tcp.h>
#include <netinet/ip_fil_compat.h>
#include <netinet/ip_fil.h>
#include "ipf.h"
#include <netinet/ip_proxy.h>
#include <netinet/ip_nat.h>
#include <netinet/ip_frag.h>
#include <netinet/ip_state.h>
#include <netinet/ip_auth.h>
#include "kmem.h"
#if defined(__NetBSD__) || (__OpenBSD__)
# include <paths.h>
#endif

#if !defined(lint)
static const char sccsid[] = "@(#)fils.c	1.21 4/20/96 (C) 1993-1996 Darren Reed";
static const char rcsid[] = "@(#)$IPFilter: fils.c,v 2.2.2.7 2000/05/24 20:34:56 darrenr Exp $";
#endif

#define	F_IN	0
#define	F_OUT	1
#define	F_AC	2
static	char	*filters[4] = { "ipfilter(in)", "ipfilter(out)",
				"ipacct(in)", "ipacct(out)" };

int	opts = 0;

char *nlistf = NULL, *memf = NULL;

extern	int	main __P((int, char *[]));
static	void	showstats __P((int, friostat_t *));
static	void	showfrstates __P((int, ipfrstat_t *));
static	void	showlist __P((friostat_t *));
static	void	showipstates __P((int, ips_stat_t *));
static	void	showauthstates __P((int, fr_authstat_t *));
static	void	showgroups __P((friostat_t *));
static	void	Usage __P((char *));
static	void	printlist __P((frentry_t *));
static	char	*get_ifname __P((void *));


static void Usage(name)
char *name;
{
	fprintf(stderr,
	    "usage: %s [-aAfghIinosv] [-d device] [-M core]\n", 
		name);
	exit(1);
}


int main(argc,argv)
int argc;
char *argv[];
{
	fr_authstat_t	frauthst;
	friostat_t fio;
	ips_stat_t ipsst;
	ipfrstat_t ifrst;
	char	*name = NULL, *device = IPL_NAME;
	int	c, fd;

	while ((c = getopt(argc, argv, "AafhgIinosvd:M:")) != -1)
	{
		switch (c)
		{
		case 'a' :
			opts |= OPT_ACCNT|OPT_SHOWLIST;
			break;
		case 'A' :
			opts |= OPT_AUTHSTATS;
			break;
		case 'd' :
			device = optarg;
			break;
		case 'f' :
			opts |= OPT_FRSTATES;
			break;
		case 'g' :
			opts |= OPT_GROUPS;
			break;
		case 'h' :
			opts |= OPT_HITS;
			break;
		case 'i' :
			opts |= OPT_INQUE|OPT_SHOWLIST;
			break;
		case 'I' :
			opts |= OPT_INACTIVE;
			break;
		case 'n' :
			opts |= OPT_SHOWLINENO;
			break;
		case 'o' :
			opts |= OPT_OUTQUE|OPT_SHOWLIST;
			break;
		case 's' :
			opts |= OPT_IPSTATES;
			break;
		case 'v' :
			opts |= OPT_VERBOSE;
			break;
		case 'M':
			memf = optarg;
			break;
		default :
			Usage(argv[0]);
			break;
		}
	}

	if (nlistf != NULL || memf != NULL) {
		(void)setuid(getuid());
		(void)setgid(getgid());
	}

	if (openkmem(nlistf, memf) == -1)
		exit(-1);

	(void)setuid(getuid());
	(void)setgid(getgid());

	if ((fd = open(device, O_RDONLY)) < 0) {
		perror("open");
		exit(-1);
	}

	bzero((char *)&fio, sizeof(fio));
	bzero((char *)&ipsst, sizeof(ipsst));
	bzero((char *)&ifrst, sizeof(ifrst));

	if (ioctl(fd, SIOCGETFS, &fio) == -1) {
		perror("ioctl(SIOCGETFS)");
		exit(-1);
	}
	if ((opts & OPT_IPSTATES)) {
		int	sfd = open(IPL_STATE, O_RDONLY);

		if (sfd == -1) {
			perror("open");
			exit(-1);
		}
		if ((ioctl(sfd, SIOCGIPST, &ipsst) == -1)) {
			perror("ioctl(SIOCGIPST)");
			exit(-1);
		}
		close(sfd);
	}
	if ((opts & OPT_FRSTATES) && (ioctl(fd, SIOCGFRST, &ifrst) == -1)) {
		perror("ioctl(SIOCGFRST)");
		exit(-1);
	}

	if (opts & OPT_VERBOSE)
		printf("opts %#x name %s\n", opts, name ? name : "<>");

	if ((opts & OPT_AUTHSTATS) &&
	    (ioctl(fd, SIOCATHST, &frauthst) == -1)) {
		perror("ioctl(SIOCATHST)");
		exit(-1);
	}

	if (opts & OPT_SHOWLIST) {
		showlist(&fio);
		if ((opts & OPT_OUTQUE) && (opts & OPT_INQUE)){
			opts &= ~OPT_OUTQUE;
			showlist(&fio);
		}
	} else {
		if (opts & OPT_IPSTATES)
			showipstates(fd, &ipsst);
		else if (opts & OPT_FRSTATES)
			showfrstates(fd, &ifrst);
		else if (opts & OPT_AUTHSTATS)
			showauthstates(fd, &frauthst);
		else if (opts & OPT_GROUPS)
			showgroups(&fio);
		else
			showstats(fd, &fio);
	}
	return 0;
}


/*
 * read the kernel stats for packets blocked and passed
 */
static	void	showstats(fd, fp)
int	fd;
struct	friostat	*fp;
{
	u_32_t	frf = 0;

	if (ioctl(fd, SIOCGETFF, &frf) == -1)
		perror("ioctl(SIOCGETFF)");

#if SOLARIS
	printf("dropped packets:\tin %lu\tout %lu\n",
			fp->f_st[0].fr_drop, fp->f_st[1].fr_drop);
	printf("non-data packets:\tin %lu\tout %lu\n",
			fp->f_st[0].fr_notdata, fp->f_st[1].fr_notdata);
	printf("no-data packets:\tin %lu\tout %lu\n",
			fp->f_st[0].fr_nodata, fp->f_st[1].fr_nodata);
	printf("non-ip packets:\t\tin %lu\tout %lu\n",
			fp->f_st[0].fr_notip, fp->f_st[1].fr_notip);
	printf("   bad packets:\t\tin %lu\tout %lu\n",
			fp->f_st[0].fr_bad, fp->f_st[1].fr_bad);
	printf("copied messages:\tin %lu\tout %lu\n",
			fp->f_st[0].fr_copy, fp->f_st[1].fr_copy);
#endif
	printf(" input packets:\t\tblocked %lu passed %lu nomatch %lu",
			fp->f_st[0].fr_block, fp->f_st[0].fr_pass,
			fp->f_st[0].fr_nom);
	printf(" counted %lu short %lu\n", 
			fp->f_st[0].fr_acct, fp->f_st[0].fr_short);
	printf("output packets:\t\tblocked %lu passed %lu nomatch %lu",
			fp->f_st[1].fr_block, fp->f_st[1].fr_pass,
			fp->f_st[1].fr_nom);
	printf(" counted %lu short %lu\n", 
			fp->f_st[1].fr_acct, fp->f_st[1].fr_short);
	printf(" input packets logged:\tblocked %lu passed %lu\n",
			fp->f_st[0].fr_bpkl, fp->f_st[0].fr_ppkl);
	printf("output packets logged:\tblocked %lu passed %lu\n",
			fp->f_st[1].fr_bpkl, fp->f_st[1].fr_ppkl);
	printf(" packets logged:\tinput %lu output %lu\n",
			fp->f_st[0].fr_pkl, fp->f_st[1].fr_pkl);
	printf(" log failures:\t\tinput %lu output %lu\n",
			fp->f_st[0].fr_skip, fp->f_st[1].fr_skip);
	printf("fragment state(in):\tkept %lu\tlost %lu\n",
			fp->f_st[0].fr_nfr, fp->f_st[0].fr_bnfr);
	printf("fragment state(out):\tkept %lu\tlost %lu\n",
			fp->f_st[1].fr_nfr, fp->f_st[1].fr_bnfr);
	printf("packet state(in):\tkept %lu\tlost %lu\n",
			fp->f_st[0].fr_ads, fp->f_st[0].fr_bads);
	printf("packet state(out):\tkept %lu\tlost %lu\n",
			fp->f_st[1].fr_ads, fp->f_st[1].fr_bads);
	printf("ICMP replies:\t%lu\tTCP RSTs sent:\t%lu\n",
			fp->f_st[0].fr_ret, fp->f_st[1].fr_ret);
	printf("Result cache hits(in):\t%lu\t(out):\t%lu\n",
			fp->f_st[0].fr_chit, fp->f_st[1].fr_chit);
	printf("IN Pullups succeeded:\t%lu\tfailed:\t%lu\n",
			fp->f_st[0].fr_pull[0], fp->f_st[0].fr_pull[1]);
	printf("OUT Pullups succeeded:\t%lu\tfailed:\t%lu\n",
			fp->f_st[1].fr_pull[0], fp->f_st[1].fr_pull[1]);
	printf("Fastroute successes:\t%lu\tfailures:\t%lu\n",
			fp->f_froute[0], fp->f_froute[1]);
	printf("TCP cksum fails(in):\t%lu\t(out):\t%lu\n",
			fp->f_st[0].fr_tcpbad, fp->f_st[1].fr_tcpbad);

	printf("Packet log flags set: (%#x)\n", frf);
	if (frf & FF_LOGPASS)
		printf("\tpackets passed through filter\n");
	if (frf & FF_LOGBLOCK)
		printf("\tpackets blocked by filter\n");
	if (frf & FF_LOGNOMATCH)
		printf("\tpackets not matched by filter\n");
	if (!frf)
		printf("\tnone\n");
}


static void printlist(fp)
frentry_t *fp;
{
	struct	frentry	fb;
	int	n;

	for (n = 1; fp; n++) {
		if (kmemcpy((char *)&fb, (u_long)fp, sizeof(fb)) == -1) {
			perror("kmemcpy");
			return;
		}
		fp = &fb;
		if (opts & OPT_OUTQUE)
			fp->fr_flags |= FR_OUTQUE;
		if (opts & (OPT_HITS|OPT_VERBOSE))
#ifdef	USE_QUAD_T
			printf("%qu ", fp->fr_hits);
#else
			printf("%lu ", fp->fr_hits);
#endif
		if (opts & (OPT_ACCNT|OPT_VERBOSE))
#ifdef	USE_QUAD_T
			printf("%qu ", fp->fr_bytes);
#else
			printf("%lu ", fp->fr_bytes);
#endif
		if (opts & OPT_SHOWLINENO)
			printf("@%d ", n);
		printfr(fp);
		if (opts & OPT_VERBOSE)
			binprint(fp);
		if (fp->fr_grp)
			printlist(fp->fr_grp);
		fp = fp->fr_next;
	}
}

/*
 * print out filter rule list
 */
static	void	showlist(fiop)
struct	friostat	*fiop;
{
	struct	frentry	*fp = NULL;
	int	i, set;

	set = fiop->f_active;
	if (opts & OPT_INACTIVE)
		set = 1 - set;
	if (opts & OPT_ACCNT) {
		i = F_AC;
		if (opts & OPT_OUTQUE) {
			fp = (struct frentry *)fiop->f_acctout[set];
			i++;
		} else if (opts & OPT_INQUE)
			fp = (struct frentry *)fiop->f_acctin[set];
		else {
			fprintf(stderr, "No -i or -o given with -a\n");
			return;
		}
	} else if (opts & OPT_OUTQUE) {
		i = F_OUT;
		fp = (struct frentry *)fiop->f_fout[set];
	} else if (opts & OPT_INQUE) {
		i = F_IN;
		fp = (struct frentry *)fiop->f_fin[set];
	} else
		return;
	if (opts & OPT_VERBOSE)
		fprintf(stderr, "showlist:opts %#x i %d\n", opts, i);

	if (opts & OPT_VERBOSE)
		printf("fp %p set %d\n", fp, set);
	if (!fp) {
		fprintf(stderr, "empty list for %s%s\n",
			(opts & OPT_INACTIVE) ? "inactive " : "", filters[i]);
		return;
	}
	printlist(fp);
}


static void showipstates(fd, ipsp)
int fd;
ips_stat_t *ipsp;
{
	ipstate_t *istab[IPSTATE_SIZE], ips;
	int i;

	printf("IP states added:\n\t%lu TCP\n\t%lu UDP\n\t%lu ICMP\n",
		ipsp->iss_tcp, ipsp->iss_udp, ipsp->iss_icmp);
	printf("\t%lu hits\n\t%lu misses\n", ipsp->iss_hits, ipsp->iss_miss);
	printf("\t%lu maximum\n\t%lu no memory\n\tbuckets in use\t%lu\n",
		ipsp->iss_max, ipsp->iss_nomem, ipsp->iss_inuse);
	printf("\t%lu active\n\t%lu expired\n\t%lu closed\n",
		ipsp->iss_active, ipsp->iss_expire, ipsp->iss_fin);
	if (kmemcpy((char *)istab, (u_long)ipsp->iss_table, sizeof(istab)))
		return;
	for (i = 0; i < IPSTATE_SIZE; i++) {
		while (istab[i]) {
			if (kmemcpy((char *)&ips, (u_long)istab[i],
				    sizeof(ips)) == -1)
				break;
			printf("%s -> ", inet_ntoa(ips.is_src));
			printf("%s ttl %ld pass %#x pr %d state %d/%d\n",
				inet_ntoa(ips.is_dst), ips.is_age,
				ips.is_pass, ips.is_p, ips.is_state[0],
				ips.is_state[1]);
#ifdef	USE_QUAD_T
			printf("\tpkts %qd bytes %qd",
				ips.is_pkts, ips.is_bytes);
#else
			printf("\tpkts %ld bytes %ld",
				ips.is_pkts, ips.is_bytes);
#endif
			if (ips.is_p == IPPROTO_TCP)
#if defined(NetBSD) && (NetBSD >= 199905) && (NetBSD < 1991011) || \
    (__FreeBSD_version >= 220000) || defined(__OpenBSD__)
				printf("\t%hu -> %hu %x:%x %hu:%hu",
					ntohs(ips.is_sport),
					ntohs(ips.is_dport),
					ips.is_send, ips.is_dend,
					ips.is_maxswin, ips.is_maxdwin);
#else
				printf("\t%hu -> %hu %lx:%lx %hu:%hu",
					ntohs(ips.is_sport),
					ntohs(ips.is_dport),
					ips.is_send, ips.is_dend,
					ips.is_maxswin, ips.is_maxdwin);
#endif
			else if (ips.is_p == IPPROTO_UDP)
				printf(" %hu -> %hu", ntohs(ips.is_sport),
					ntohs(ips.is_dport));
			else if (ips.is_p == IPPROTO_ICMP)
				printf(" %hu %hu %d", ips.is_icmp.ics_id,
					ips.is_icmp.ics_seq,
					ips.is_icmp.ics_type);

			printf("\n\t");

			if (ips.is_pass & FR_PASS) {
				printf("pass");
			} else if (ips.is_pass & FR_BLOCK) {
				printf("block");
				switch (ips.is_pass & FR_RETMASK)
				{
				case FR_RETICMP :
					printf(" return-icmp");
					break;
				case FR_FAKEICMP :
					printf(" return-icmp-as-dest");
					break;
				case FR_RETRST :
					printf(" return-rst");
					break;
				default :
					break;
				}
			} else if ((ips.is_pass & FR_LOGMASK) == FR_LOG) {
					printf("log");
				if (ips.is_pass & FR_LOGBODY)
					printf(" body");
				if (ips.is_pass & FR_LOGFIRST)
					printf(" first");
			} else if (ips.is_pass & FR_ACCOUNT)
				printf("count");

			if (ips.is_pass & FR_OUTQUE)
				printf(" out");
			else
				printf(" in");

			if ((ips.is_pass & FR_LOG) != 0) {
				printf(" log");
				if (ips.is_pass & FR_LOGBODY)
					printf(" body");
				if (ips.is_pass & FR_LOGFIRST)
					printf(" first");
				if (ips.is_pass & FR_LOGORBLOCK)
					printf(" or-block");
			}
			if (ips.is_pass & FR_QUICK)
				printf(" quick");
			if (ips.is_pass & FR_KEEPFRAG)
				printf(" keep frags");
			/* a given; no? */
			if (ips.is_pass & FR_KEEPSTATE)
				printf(" keep state");
			printf("\n");

			printf("\tpkt_flags & %x(%x) = %x,\t",
				ips.is_flags & 0xf, ips.is_flags,
				ips.is_flags >> 4);
			printf("\tpkt_options & %x = %x\n", ips.is_optmsk,
				ips.is_opt);
			printf("\tpkt_security & %x = %x, pkt_auth & %x = %x\n",
				ips.is_secmsk, ips.is_sec, ips.is_authmsk,
				ips.is_auth);
			istab[i] = ips.is_next;
			printf("interfaces: in %s[%p] ",
			       get_ifname(ips.is_ifpin), ips.is_ifpin);
			printf("out %s[%p]\n",
			       get_ifname(ips.is_ifpout), ips.is_ifpout);
		}
	}
}


static void showfrstates(fd, ifsp)
int fd;
ipfrstat_t *ifsp;
{
	struct ipfr *ipfrtab[IPFT_SIZE], ifr;
	frentry_t fr;
	int i;

	printf("IP fragment states:\n\t%lu new\n\t%lu expired\n\t%lu hits\n",
		ifsp->ifs_new, ifsp->ifs_expire, ifsp->ifs_hits);
	printf("\t%lu no memory\n\t%lu already exist\n",
		ifsp->ifs_nomem, ifsp->ifs_exists);
	printf("\t%lu inuse\n", ifsp->ifs_inuse);
	if (kmemcpy((char *)ipfrtab, (u_long)ifsp->ifs_table, sizeof(ipfrtab)))
		return;
	for (i = 0; i < IPFT_SIZE; i++)
		while (ipfrtab[i]) {
			if (kmemcpy((char *)&ifr, (u_long)ipfrtab[i],
				    sizeof(ifr)) == -1)
				break;
			printf("%s -> ", inet_ntoa(ifr.ipfr_src));
			if (kmemcpy((char *)&fr, (u_long)ifr.ipfr_rule,
				    sizeof(fr)) == -1)
				break;
			printf("%s %d %d %d %#02x = %#x\n",
				inet_ntoa(ifr.ipfr_dst), ifr.ipfr_id,
				ifr.ipfr_ttl, ifr.ipfr_p, ifr.ipfr_tos,
				fr.fr_flags);
			ipfrtab[i] = ifr.ipfr_next;
		}
}


static void showauthstates(fd, asp)
int fd;
fr_authstat_t *asp;
{
	frauthent_t *frap, fra;

#ifdef	USE_QUAD_T
	printf("Authorisation hits: %qd\tmisses %qd\n", asp->fas_hits,
		asp->fas_miss);
#else
	printf("Authorisation hits: %ld\tmisses %ld\n", asp->fas_hits,
		asp->fas_miss);
#endif
	printf("nospace %ld\nadded %ld\nsendfail %ld\nsendok %ld\n",
		asp->fas_nospace, asp->fas_added, asp->fas_sendfail,
		asp->fas_sendok);
	printf("queok %ld\nquefail %ld\nexpire %ld\n",
		asp->fas_queok, asp->fas_quefail, asp->fas_expire);

	frap = asp->fas_faelist;
	while (frap) {
		if (kmemcpy((char *)&fra, (u_long)frap, sizeof(fra)) == -1)
			break;

		printf("age %ld\t", fra.fae_age);
		printfr(&fra.fae_fr);
		frap = fra.fae_next;
	}
}


static char *get_ifname(ptr)
void *ptr;
{
#if SOLARIS
	char *ifname;
	ill_t ill;

	if (ptr == (void *)-1)
		return "!";
	if (ptr == NULL)
		return "-";

	if (kmemcpy((char *)&ill, (u_long)ptr, sizeof(ill)) == -1)
		return "X";
	ifname = malloc(ill.ill_name_length + 1);
	if (kmemcpy(ifname, (u_long)ill.ill_name,
		    ill.ill_name_length) == -1)
		return "X";
	return ifname;
#else
# if defined(NetBSD) && (NetBSD >= 199905) && (NetBSD < 1991011) || \
    defined(__OpenBSD__)
#else
	char buf[32];
	int len;
# endif
	struct ifnet netif;

	if (ptr == (void *)-1)
		return "!";
	if (ptr == NULL)
		return "-";

	if (kmemcpy((char *)&netif, (u_long)ptr, sizeof(netif)) == -1)
		return "X";
# if defined(NetBSD) && (NetBSD >= 199905) && (NetBSD < 1991011) || \
    defined(__OpenBSD__)
	return strdup(netif.if_xname);
# else
	if (kstrncpy(buf, (u_long)netif.if_name, sizeof(buf)) == -1)
		return "X";
	if (netif.if_unit < 10)
		len = 2;
	else if (netif.if_unit < 1000)
		len = 3;
	else if (netif.if_unit < 10000)
		len = 4;
	else
		len = 5;
	buf[sizeof(buf) - len] = '\0';
	sprintf(buf + strlen(buf), "%d", netif.if_unit % 10000);
	return strdup(buf);
# endif
#endif
}


static void showgroups(fiop)
struct friostat	*fiop;
{
	static char *gnames[3] = { "Filter", "Accounting", "Authentication" };
	frgroup_t *fp, grp;
	int on, off, i;

	on = fiop->f_active;
	off = 1 - on;

	for (i = 0; i < 3; i++) {
		printf("%s groups (active):\n", gnames[i]);
		for (fp = fiop->f_groups[i][on]; fp; fp = grp.fg_next)
			if (kmemcpy((char *)&grp, (u_long)fp, sizeof(grp)))
				break;
			else
				printf("%hu\n", grp.fg_num);
		printf("%s groups (inactive):\n", gnames[i]);
		for (fp = fiop->f_groups[i][off]; fp; fp = grp.fg_next)
			if (kmemcpy((char *)&grp, (u_long)fp, sizeof(grp)))
				break;
			else
				printf("%hu\n", grp.fg_num);
	}
}
