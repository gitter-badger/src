/*	$OpenBSD: rpb.h,v 1.4 1996/07/29 22:59:15 niklas Exp $	*/
/*	$NetBSD: rpb.h,v 1.7 1996/04/29 16:23:11 cgd Exp $	*/

/*
 * Copyright (c) 1994, 1995 Carnegie-Mellon University.
 * All rights reserved.
 *
 * Author: Keith Bostic, Chris G. Demetriou
 * 
 * Permission to use, copy, modify and distribute this software and
 * its documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS" 
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND 
 * FOR ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 *
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 *
 * any improvements or extensions that they make and grant Carnegie the
 * rights to redistribute these changes.
 */

/*
 * From DEC 3000 300/400/500/600/700/800/900 System Programmer's Manual,
 * EK-D3SYS-PM.B01.
 */

/*
 * HWRPB (Hardware Restart Parameter Block).
 */
#define	HWRPB_ADDR	0x10000000		/* virtual address, at boot */

#ifndef	ASSEMBLER
struct rpb {
	struct restart_blk *rpb;		/*   0: HWRPB phys. address. */
	char		rpb_magic[8];		/*   8: "HWRPB" (in ASCII) */
	u_int64_t	rpb_version;		/*  10 */
	u_int64_t	rpb_size;		/*  18: HWRPB size in bytes */
	u_int64_t	rpb_primary_cpu_id;	/*  20 */
	u_int64_t	rpb_page_size;		/*  28: (8192) */
	u_int64_t	rpb_phys_addr_size;	/*  30:   (34) */
	u_int64_t	rpb_max_asn;		/*  38:   (16) */
	char		rpb_ssn[16];		/*  40: only first 10 valid */

#define	ST_ADU			1		/* Alpha Demo. Unit (?) */
#define	ST_DEC_4000		2		/* "Cobra" (?) */
#define	ST_DEC_7000		3		/* "Ruby" (?) */
#define	ST_DEC_3000_500		4		/* "Flamingo" family (TC) */
#define	ST_DEC_2000_300		6		/* "Jensen" (EISA/ISA) */
#define	ST_DEC_3000_300		7		/* "Pelican" (TC) */
#define	ST_DEC_2100_A500	9		/* "Sable" (?) */
#define	ST_DEC_APXVME_64	10		/* "AXPvme" (VME?) */
#define	ST_DEC_AXPPCI_33	11		/* "NoName" (PCI/ISA?) */
#define	ST_DEC_21000		12		/* "TurboLaser" (?) */
#define	ST_DEC_2100_A50		13		/* "Avanti" (PCI/ISA) */
#define	ST_DEC_MUSTANG		14		/* "Mustang" (?) */
#define	ST_DEC_KN20AA		15		/* kn20aa (PCI/EISA) */
#define	ST_DEC_1000		17		/* "Mikasa" (PCI/ISA?) */

	u_int64_t	rpb_type;		/*  50: */

#define	SV_MPCAP		0x00000001	/* multiprocessor capable */

#define	SV_CONSOLE		0x0000001e	/* console hardware mask */
#define	SV_CONSOLE_DETACHED	0x00000002
#define	SV_CONSOLE_EMBEDDED	0x00000004

#define	SV_POWERFAIL		0x000000e0	/* powerfail mask */
#define	SV_PF_UNITED		0x00000020
#define	SV_PF_SEPARATE		0x00000040
#define	SV_PF_BBACKUP		0x00000060
#define	SV_PF_ACTION		0x00000100	/* powerfail restart */

#define	SV_GRAPHICS		0x00000200	/* graphic engine present */

#define	SV_ST_MASK		0x0000fc00	/* system type mask */
#define	SV_ST_RESERVED		0x00000000	/* RESERVED */

/*
 * System types for the DEC 3000/500 (Flamingo) Family
 */
#define	SV_ST_SANDPIPER		0x00000400	/* Sandpiper;	3000/400 */
#define	SV_ST_FLAMINGO		0x00000800	/* Flamingo;	3000/500 */
#define	SV_ST_HOTPINK		0x00000c00	/* "Hot Pink";	3000/500X */
#define	SV_ST_FLAMINGOPLUS	0x00001000	/* Flamingo+;	3000/800 */
#define	SV_ST_ULTRA		0x00001400	/* "Ultra", aka Flamingo+ */
#define	SV_ST_SANDPLUS		0x00001800	/* Sandpiper+;	3000/600 */
#define	SV_ST_SANDPIPER45	0x00001c00	/* Sandpiper45;	3000/700 */
#define	SV_ST_FLAMINGO45	0x00002000	/* Flamingo45;	3000/900 */

/*
 * System types for ???
 */
#define	SV_ST_SABLE		0x00000400	/* Sable (???) */

/*
 * System types for the DEC 3000/300 (Pelican) Family
 */
#define	SV_ST_PELICAN		0x00000000	/* Pelican;	 3000/300 */
#define	SV_ST_PELICA		0x00000400	/* Pelica;	 3000/300L */
#define	SV_ST_PELICANPLUS	0x00000800	/* Pelican+;	 3000/300X */
#define	SV_ST_PELICAPLUS	0x00000c00	/* Pelica+;	 3000/300LX */

/*
 * System types for the AlphaStation Family
 */
#define	SV_ST_AVANTI		0x00000000	/* Avanti;	400 4/233 */
#define	SV_ST_MUSTANG2_4_166	0x00000800	/* Mustang II;	200 4/166 */
#define	SV_ST_MUSTANG2_4_233	0x00001000	/* Mustang II;	200 4/233 */
#define	SV_ST_AVANTI_XXX	0x00001400	/* also Avanti;	400 4/233 */
#define	SV_ST_MUSTANG2_4_100	0x00002400	/* Mustang II;	200 4/100 */

	u_int64_t	rpb_variation;		/*  58 */

	char		rpb_revision[8];	/*  60; only first 4 valid */
	u_int64_t	rpb_intr_freq;		/*  68; scaled by 4096 */
	u_int64_t	rpb_cc_freq;		/*  70: cycle cntr frequency */
	vm_offset_t	rpb_vptb;		/*  78: */
	u_int64_t	rpb_reserved_arch;	/*  80: */
	vm_offset_t	rpb_tbhint_off;		/*  88: */
	u_int64_t	rpb_pcs_cnt;		/*  90: */
	u_int64_t	rpb_pcs_size;		/*  98; pcs size in bytes */
	vm_offset_t	rpb_pcs_off;		/*  A0: offset to pcs info */ 
	u_int64_t	rpb_ctb_cnt;		/*  A8: console terminal */
	u_int64_t	rpb_ctb_size;		/*  B0: ctb size in bytes */
	vm_offset_t	rpb_ctb_off;		/*  B8: offset to ctb */
	vm_offset_t	rpb_crb_off;		/*  C0: offset to crb */
	vm_offset_t	rpb_memdat_off;		/*  C8: memory data offset */
	vm_offset_t	rpb_condat_off;		/*  D0: config data offset */
	vm_offset_t	rpb_fru_off;		/*  D8: FRU table offset */
	long		(*rpb_save_term)();	/*  E0: terminal save */
	long		rpb_save_term_val;	/*  E8: */
	long		(*rpb_rest_term)();	/*  F0: terminal restore */
	long		rpb_rest_term_val;	/*  F8: */
	long		(*rpb_restart)();	/* 100: restart */
	long		rpb_restart_val;	/* 108: */
	u_int64_t	rpb_reserve_os;		/* 110: */
	u_int64_t	rpb_reserve_hw;		/* 118: */
	u_int64_t	rpb_checksum;		/* 120: HWRPB checksum */
	u_int64_t	rpb_rxrdy;		/* 128: receive ready */
	u_int64_t	rpb_txrdy;		/* 130: transmit ready */
	vm_offset_t	rpb_dsrdb_off;		/* 138: HWRPB + DSRDB offset */
	u_int64_t	rpb_tbhint[8];		/* 149: TB hint block */
};

#ifdef _KERNEL
extern struct rpb *hwrpb;
#endif

/*
 * PCS: Per-CPU information.
 */
struct pcs {
	u_int8_t	pcs_hwpcb[128];		/*   0: PAL dependent */

#define	PCS_BIP			0x000001	/* boot in progress */
#define	PCS_RC			0x000002	/* restart possible */
#define	PCS_PA			0x000004	/* processor available */
#define	PCS_PP			0x000008	/* processor present */
#define	PCS_OH			0x000010	/* user halted */
#define	PCS_CV			0x000020	/* context valid */
#define	PCS_PV			0x000040	/* PALcode valid */
#define	PCS_PMV			0x000080	/* PALcode memory valid */
#define	PCS_PL			0x000100	/* PALcode loaded */

#define	PCS_HALT_REQ		0xff0000	/* halt request mask */
#define	PCS_HALT_DEFAULT	0x000000
#define	PCS_HALT_SAVE_EXIT	0x010000
#define	PCS_HALT_COLD_BOOT	0x020000
#define	PCS_HALT_WARM_BOOT	0x030000
#define	PCS_HALT_STAY_HALTED	0x040000
#define	PCS_mbz	      0xffffffffff000000	/* 24:63 -- must be zero */
	u_int64_t	pcs_flags;		/*  80: */

	u_int64_t	pcs_pal_memsize;	/*  88: PAL memory size */
	u_int64_t	pcs_pal_scrsize;	/*  90: PAL scratch size */
	vm_offset_t	pcs_pal_memaddr;	/*  98: PAL memory addr */	
	vm_offset_t	pcs_pal_scraddr;	/*  A0: PAL scratch addr */
	struct {
		u_int64_t
			pcs_alpha	: 8,	/* alphabetic char 'a' - 'z' */
#define	PAL_TYPE_STANDARD	0
#define	PAL_TYPE_VMS		1
#define	PAL_TYPE_OSF1		2
			pcs_pal_type	: 8,	/* PALcode type:
						 * 0 == standard
						 * 1 == OpenVMS
						 * 2 == OSF/1
						 * 3-127 DIGITAL reserv.
						 * 128-255 non-DIGITAL reserv.
						 */
			sbz1		: 16,
			pcs_proc_cnt	: 7,	/* Processor count */
			sbz2		: 25;
	} pcs_pal_rev;				/*  A8: */
#define	pcs_alpha	pcs_pal_rev.alpha
#define	pcs_pal_type	pcs_pal_rev.pal_type
#define	pcs_proc_cnt	pcs_pal_rev.proc_cnt

	u_int64_t	pcs_proc_type;		/*  B0: processor type */

#define	PCS_PROC_MAJOR		0x00000000ffffffff
#define	PCS_PROC_MAJORSHIFT	0
#define	PCS_PROC_EV3		1			/* EV3 */
#define	PCS_PROC_EV4		2			/* EV4: 21064 */
#define	PCS_PROC_SIMULATOR	3			/* simulation */
#define	PCS_PROC_LCA4		4			/* LCA4: 2106[68] */
#define	PCS_PROC_EV5		5			/* EV5: 21164 */
#define	PCS_PROC_EV45		6			/* EV45: 21064A */

#define	PCS_PROC_MINOR		0xffffffff00000000
#define	PCS_PROC_MINORSHIFT	32
#define	PCS_PROC_PASS2		0			/* pass 2 or 2.1 */
#define	PCS_PROC_PASS3		1			/* pass 3 */
				/* 4 == ev4s?  or 1 == ... ? */
	/* minor on the LCA appears to be pass number */

	u_int64_t	pcs_proc_var;		/* B8: processor variation. */

#define	PCS_VAR_VAXFP		0x0000000000000001	/* VAX FP support */
#define	PCS_VAR_IEEEFP		0x0000000000000002	/* IEEE FP support */
#define	PCS_VAR_PE		0x0000000000000004	/* Primary Eligible */
#define	PCS_VAR_RESERVED	0xfffffffffffffff8	/* Reserved */

	char		pcs_proc_revision[8];	/*  C0: only first 4 valid */
	char		pcs_proc_sn[16];	/*  C8: only first 10 valid */
	vm_offset_t	pcs_machcheck;		/*  D8: mach chk phys addr. */
	u_int64_t	pcs_machcheck_len;	/*  E0: length in bytes */
	vm_offset_t	pcs_halt_pcbb;		/*  E8: phys addr of halt PCB */
	vm_offset_t	pcs_halt_pc;		/*  F0: halt PC */
	u_int64_t	pcs_halt_ps;		/*  F8: halt PS */
	u_int64_t	pcs_halt_r25;		/* 100: halt argument list */
	u_int64_t	pcs_halt_r26;		/* 108: halt return addr list */
	u_int64_t	pcs_halt_r27;		/* 110: halt procedure value */

#define	PCS_HALT_RESERVED		0
#define	PCS_HALT_POWERUP		1
#define	PCS_HALT_CONSOLE_HALT		2
#define	PCS_HALT_CONSOLE_CRASH		3
#define	PCS_HALT_KERNEL_MODE		4
#define	PCS_HALT_KERNEL_STACK_INVALID	5
#define	PCS_HALT_DOUBLE_ERROR_ABORT	6
#define	PCS_HALT_SCBB			7
#define	PCS_HALT_PTBR			8	/* 9-FF: reserved */
	u_int64_t	pcs_halt_reason;	/* 118: */

	u_int64_t	pcs_reserved_soft;	/* 120: preserved software */
	u_int64_t	pcs_buffer[21];		/* 128: console buffers */

#define	PALvar_reserved	0
#define	PALvar_OpenVMS	1
#define	PALvar_OSF1	2
	u_int64_t	pcs_palrevisions[16];	/* 1D0: PALcode revisions */

	u_int64_t	pcs_reserved_arch[6];	/* 250: reserved arch */
};

/*
 * CTB: Console Terminal Block
 */
struct ctb {
	u_int64_t	ctb_type;		/*   0: always 4 */
	u_int64_t	ctb_unit;		/*   8: */
	u_int64_t	ctb_reserved;		/*  16: */
	u_int64_t	ctb_len;		/*  24: bytes of info */
	u_int64_t	ctb_ipl;		/*  32: console ipl level */
	vm_offset_t	ctb_tintr_vec;		/*  40: transmit vec (0x800) */
	vm_offset_t	ctb_rintr_vec;		/*  48: receive vec (0x800) */

#define	CTB_GRAPHICS	   3			/* graphics device */
#define	CTB_NETWORK	0xC0			/* network device */
#define	CTB_PRINTERPORT	   2			/* printer port on the SCC */
	u_int64_t	ctb_term_type;		/*  56: terminal type */

	u_int64_t	ctb_keybd_type;		/*  64: keyboard nationality */
	vm_offset_t	ctb_keybd_trans;	/*  72: trans. table addr */
	vm_offset_t	ctb_keybd_map;		/*  80: map table addr */
	u_int64_t	ctb_keybd_state;	/*  88: keyboard flags */
	u_int64_t	ctb_keybd_last;		/*  96: last key entered */
	vm_offset_t	ctb_font_us;		/* 104: US font table addr */
	vm_offset_t	ctb_font_mcs;		/* 112: MCS font table addr */
	u_int64_t	ctb_font_width;		/* 120: font width, height */
	u_int64_t	ctb_font_height;	/* 128:		in pixels */
	u_int64_t	ctb_mon_width;		/* 136: monitor width, height */
	u_int64_t	ctb_mon_height;		/* 144:		in pixels */
	u_int64_t	ctb_dpi;		/* 152: monitor dots per inch */
	u_int64_t	ctb_planes;		/* 160: # of planes */
	u_int64_t	ctb_cur_width;		/* 168: cursor width, height */
	u_int64_t	ctb_cur_height;		/* 176:		in pixels */
	u_int64_t	ctb_head_cnt;		/* 184: # of heads */
	u_int64_t	ctb_opwindow;		/* 192: opwindow on screen */
	vm_offset_t	ctb_head_offset;	/* 200: offset to head info */
	vm_offset_t	ctb_putchar;		/* 208: output char to TURBO */
	u_int64_t	ctb_io_state;		/* 216: I/O flags */
	u_int64_t	ctb_listen_state;	/* 224: listener flags */
	vm_offset_t	ctb_xaddr;		/* 232: extended info addr */
	u_int64_t	ctb_turboslot;		/* 248: TURBOchannel slot # */
	u_int64_t	ctb_server_off;		/* 256: offset to server info */
	u_int64_t	ctb_line_off;		/* 264: line parameter offset */
	u_int8_t	ctb_csd;		/* 272: console specific data */
};

/* 
 * CRD: Console Routine Descriptor
 */
struct crd {
	int64_t	descriptor;
	int	(*code)();
};

/*
 * CRB: Console Routine Block
 */
struct crb {
	struct crd	*crb_v_dispatch;	/*   0: virtual dispatch addr */
	vm_offset_t	 crb_p_dispatch;	/*   8: phys dispatch addr */
	struct crd	*crb_v_fixup;		/*  10: virtual fixup addr */
	vm_offset_t	 crb_p_fixup;		/*  18: phys fixup addr */
	u_int64_t	 crb_map_cnt;		/*  20: phys/virt map entries */
	u_int64_t	 crb_page_cnt;		/*  28: pages to be mapped */
};

/*
 * MDDT: Memory Data Descriptor Table
 */
struct mddt {
	int64_t	 	mddt_cksum;		/*   0: 7-N checksum */
	vm_offset_t	mddt_physaddr;		/*   8: bank config addr
						 * IMPLEMENTATION SPECIFIC
						 */
	u_int64_t	mddt_cluster_cnt;	/*  10: memory cluster count */
	struct {
		vm_offset_t	mddt_pfn;	/*   0: starting PFN */
		u_int64_t	mddt_pg_cnt;	/*   8: 8KB page count */
		u_int64_t	mddt_pg_test;	/*  10: tested page count */
		vm_offset_t	mddt_v_bitaddr;	/*  18: bitmap virt addr */
		vm_offset_t	mddt_p_bitaddr;	/*  20: bitmap phys addr */
		int64_t		mddt_bit_cksum;	/*  28: bitmap checksum */

#define	MDDT_PALCODE			0x01	/* console and PAL only */
#define	MDDT_SYSTEM			0x00	/* system software only */
#define	MDDT_mbz	  0xfffffffffffffffe	/* 1:63 -- must be zero */
		int64_t		mddt_usage;	/*  30: bitmap permissions */
	} mddt_clusters[1];			/* variable length array */
};
#endif /* ASSEMBLER */
