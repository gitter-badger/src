/* $OpenBSD: dsdt.h,v 1.51 2010/07/21 15:07:40 deraadt Exp $ */
/*
 * Copyright (c) 2005 Marco Peereboom <marco@openbsd.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef __DEV_ACPI_DSDT_H__
#define __DEV_ACPI_DSDT_H__

struct aml_scope {
	struct acpi_softc	*sc;
	uint8_t			*pos;
	uint8_t			*end;
	struct aml_node		*node;
	struct aml_scope	*parent;
	struct aml_value	*locals;
	struct aml_value	*args;
	int			nargs;
	int			flags;
	struct aml_value	*retv;
	uint8_t			*start;
	int			type;
};


struct aml_opcode {
	u_int32_t		opcode;
	const char		*mnem;
	const char		*args;
};

const char		*aml_eisaid(u_int32_t);
const char		*aml_mnem(int, uint8_t *);
int64_t			aml_val2int(struct aml_value *);
struct aml_node		*aml_searchname(struct aml_node *, const void *);
struct aml_node		*aml_searchrel(struct aml_node *, const void *);

struct aml_value 	*aml_getstack(struct aml_scope *, int);
struct aml_value	*aml_allocint(uint64_t);
struct aml_value	*aml_allocstr(const char *);
struct aml_value	*aml_allocvalue(int, int64_t, const void *);
void			aml_freevalue(struct aml_value *);
void			aml_notify(struct aml_node *, int);
void			aml_notify_dev(const char *, int);
void			aml_showvalue(struct aml_value *, int);
void			aml_walkroot(void);
void			aml_walktree(struct aml_node *);

int			aml_find_node(struct aml_node *, const char *,
			    int (*)(struct aml_node *, void *), void *);
int			acpi_parse_aml(struct acpi_softc *, u_int8_t *,
			    u_int32_t);
void			aml_register_notify(struct aml_node *, const char *,
			    int (*)(struct aml_node *, int, void *), void *,
			    int);

u_int64_t		aml_getpciaddr(struct acpi_softc *, struct aml_node *);

int			aml_evalnode(struct acpi_softc *, struct aml_node *,
			    int , struct aml_value *, struct aml_value *);
int			aml_evalname(struct acpi_softc *, struct aml_node *,
			    const char *, int, struct aml_value *,
			    struct aml_value *);
int			aml_evalinteger(struct acpi_softc *, struct aml_node *,
                            const char *, int, struct aml_value *, int64_t *);

void			aml_create_defaultobjects(void);

const char		*aml_nodename(struct aml_node *);

#define SR_IRQ			0x04
#define SR_DMA			0x05
#define SR_STARTDEP		0x06
#define SR_ENDDEP		0x07
#define SR_IOPORT		0x08
#define SR_FIXEDPORT		0x09
#define SR_ENDTAG		0x0F

#define LR_24BIT		0x81
#define LR_GENREGISTER		0x82
#define LR_32BIT		0x85
#define LR_32BITFIXED		0x86
#define LR_DWORD		0x87
#define LR_WORD			0x88
#define LR_EXTIRQ		0x89
#define LR_QWORD		0x8A

#define __amlflagbit(v,s,l)
union acpi_resource {
	struct {
		uint8_t  typecode;
		uint16_t length;
	}  __packed hdr;

	/* Small resource structures
	 * format of typecode is: tttttlll, t = type, l = length
	 */
	struct {
		uint8_t  typecode;
		uint16_t irq_mask;
		uint8_t  irq_flags;
	}  __packed sr_irq;
	struct {
		uint8_t  typecode;
		uint8_t  channel;
		uint8_t  flags;
	}  __packed sr_dma;
	struct {
		uint8_t  typecode;
		uint8_t  flags;
		uint16_t _min;
		uint16_t _max;
		uint8_t  _aln;
		uint8_t  _len;
	}  __packed sr_ioport;
	struct {
		uint8_t  typecode;
		uint16_t _bas;
		uint8_t  _len;
	}  __packed sr_fioport;

	/* Large resource structures */
	struct {
		uint8_t  typecode;
		uint16_t length;
		uint8_t  _info;
		uint16_t _min;
		uint16_t _max;
		uint16_t _aln;
		uint16_t _len;
	}  __packed lr_m24;
	struct {
		uint8_t  typecode;
		uint16_t length;
		uint8_t  _info;
		uint32_t _min;
		uint32_t _max;
		uint32_t _aln;
		uint32_t _len;
	}  __packed lr_m32;
	struct {
		uint8_t  typecode;
		uint16_t length;
		uint8_t  flags;
		uint8_t  irq_count;
		uint32_t irq[1];
	} __packed lr_extirq;
	struct {
		uint8_t		typecode;
		uint16_t	length;
		uint8_t		type;
		uint8_t		flags;
		uint8_t		tflags;
		uint16_t	_gra;
		uint16_t	_min;
		uint16_t	_max;
		uint16_t	_tra;
		uint16_t	_len;
		uint8_t		src_index;
		char		src[1];
	} __packed lr_word;
	struct {
		uint8_t		typecode;
		uint16_t	length;
		uint8_t		type;
		uint8_t		flags;
		uint8_t		tflags;
		uint32_t	_gra;
		uint32_t	_min;
		uint32_t	_max;
		uint32_t	_tra;
		uint32_t	_len;
		uint8_t		src_index;
		char		src[1];
	} __packed lr_dword;
	struct {
		uint8_t		typecode;
		uint16_t	length;
		uint8_t		type;
		uint8_t		flags;
		uint8_t		tflags;
		uint64_t	_gra;
		uint64_t	_min;
		uint64_t	_max;
		uint64_t	_tra;
		uint64_t	_len;
		uint8_t		src_index;
		char		src[1];
	} __packed lr_qword;
	uint8_t		pad[64];
} __packed;

#define AML_CRSTYPE(x)	((x)->hdr.typecode & 0x80 ? \
			    (x)->hdr.typecode : (x)->hdr.typecode >> 3)
#define AML_CRSLEN(x)	((x)->hdr.typecode & 0x80 ? \
			    3+(x)->hdr.length : 1+((x)->hdr.typecode & 0x7))

int			aml_print_resource(union acpi_resource *, void *);
int			aml_parse_resource(struct aml_value *,
			    int (*)(union acpi_resource *, void *), void *);

#define ACPI_E_NOERROR   0x00
#define ACPI_E_BADVALUE  0x01

#define AML_MAX_ARG	 7
#define AML_MAX_LOCAL	 8

#define AML_WALK_PRE 0x00
#define AML_WALK_POST 0x01

void			aml_walknodes(struct aml_node *, int,
			    int (*)(struct aml_node *, void *), void *);

void			aml_postparse(void);
void			acpi_poll_notify(void);

void			aml_hashopcodes(void);

void			aml_foreachpkg(struct aml_value *, int,
			    void (*fn)(struct aml_value *, void *), void *);

const char		*aml_val_to_string(const struct aml_value *);

int			valid_acpihdr(void *, int, const char *);
void			aml_disasm(struct aml_scope *scope, int lvl, 
			    void (*dbprintf)(void *, const char *, ...), 
			    void *arg);
int			aml_xgetpci(struct aml_node *, int64_t *);
int			aml_evalhid(struct aml_node *, struct aml_value *);

int			acpi_walkmem(int, const char *);

#define aml_get8(p)    *(uint8_t *)(p)
#define aml_get16(p)   *(uint16_t *)(p)
#define aml_get32(p)   *(uint32_t *)(p)
#define aml_get64(p)   *(uint64_t *)(p)

union amlpci_t {
	uint64_t addr;
	struct {
		uint16_t reg;
		uint16_t fun;
		uint16_t dev;
		uint16_t bus;
	};
};
int			aml_rdpciaddr(struct aml_node *pcidev,
			    union amlpci_t *);

void			acpi_getdevlist(struct acpi_devlist_head *,
			    struct aml_node *, struct aml_value *, int);
void			acpi_freedevlist(struct acpi_devlist_head *);

#endif /* __DEV_ACPI_DSDT_H__ */
