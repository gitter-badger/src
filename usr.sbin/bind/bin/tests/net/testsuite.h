/*
 * Copyright (C) 2004  Internet Systems Consortium, Inc. ("ISC")
 * Copyright (C) 2000, 2001  Internet Software Consortium.
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
 * OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

/* $ISC: testsuite.h,v 1.4.206.1 2004/03/06 10:21:45 marka Exp $ */

#define SUITENAME "net"

TESTDECL(netaddr_multicast);
TESTDECL(sockaddr_multicast);

static test_t tests[] = {
	{ "isc_netaddr_ismulticast",
	  "Checking to see if multicast addresses are detected properly",
	  netaddr_multicast },
	{ "isc_sockaddr_ismulticast",
	  "Checking to see if multicast addresses are detected properly",
	  sockaddr_multicast },

};
