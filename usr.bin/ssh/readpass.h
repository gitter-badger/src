/*	$OpenBSD: readpass.h,v 1.2.6.2 2002/03/09 00:20:44 miod Exp $	*/

/*
 * Author: Tatu Ylonen <ylo@cs.hut.fi>
 * Copyright (c) 1995 Tatu Ylonen <ylo@cs.hut.fi>, Espoo, Finland
 *                    All rights reserved
 *
 * As far as I am concerned, the code I have written for this software
 * can be used freely for any purpose.  Any derived versions of this
 * software must be clearly marked as such, and if the derived work is
 * incompatible with the protocol description in the RFC file, it must be
 * called by a name other than "ssh" or "Secure Shell".
 */

#define RP_ECHO			0x0001
#define RP_ALLOW_STDIN		0x0002

char	*read_passphrase(const char *, int);
