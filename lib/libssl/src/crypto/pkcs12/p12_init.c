/* p12_init.c */
/* Written by Dr Stephen N Henson (shenson@bigfoot.com) for the OpenSSL
 * project 1999.
 */
/* ====================================================================
 * Copyright (c) 1999 The OpenSSL Project.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer. 
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. All advertising materials mentioning features or use of this
 *    software must display the following acknowledgment:
 *    "This product includes software developed by the OpenSSL Project
 *    for use in the OpenSSL Toolkit. (http://www.OpenSSL.org/)"
 *
 * 4. The names "OpenSSL Toolkit" and "OpenSSL Project" must not be used to
 *    endorse or promote products derived from this software without
 *    prior written permission. For written permission, please contact
 *    licensing@OpenSSL.org.
 *
 * 5. Products derived from this software may not be called "OpenSSL"
 *    nor may "OpenSSL" appear in their names without prior written
 *    permission of the OpenSSL Project.
 *
 * 6. Redistributions of any form whatsoever must retain the following
 *    acknowledgment:
 *    "This product includes software developed by the OpenSSL Project
 *    for use in the OpenSSL Toolkit (http://www.OpenSSL.org/)"
 *
 * THIS SOFTWARE IS PROVIDED BY THE OpenSSL PROJECT ``AS IS'' AND ANY
 * EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE OpenSSL PROJECT OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 * ====================================================================
 *
 * This product includes cryptographic software written by Eric Young
 * (eay@cryptsoft.com).  This product includes software written by Tim
 * Hudson (tjh@cryptsoft.com).
 *
 */

#include <stdio.h>
#include "cryptlib.h"
#include <openssl/pkcs12.h>

/* Initialise a PKCS12 structure to take data */

PKCS12 *PKCS12_init (int mode)
{
	PKCS12 *pkcs12;
	if (!(pkcs12 = PKCS12_new())) {
		PKCS12err(PKCS12_F_PKCS12_INIT,ERR_R_MALLOC_FAILURE);
		return NULL;
	}
	if (!(pkcs12->version = M_ASN1_INTEGER_new ())) {
		PKCS12err(PKCS12_F_PKCS12_INIT,ERR_R_MALLOC_FAILURE);
		return NULL;
	}
	ASN1_INTEGER_set(pkcs12->version, 3);
	if (!(pkcs12->authsafes = PKCS7_new())) {
		PKCS12err(PKCS12_F_PKCS12_INIT,ERR_R_MALLOC_FAILURE);
		return NULL;
	}
	pkcs12->authsafes->type = OBJ_nid2obj(mode);
	switch (mode) {
		case NID_pkcs7_data:
			if (!(pkcs12->authsafes->d.data =
				 M_ASN1_OCTET_STRING_new())) {
			PKCS12err(PKCS12_F_PKCS12_INIT,ERR_R_MALLOC_FAILURE);
			return NULL;
		}
		break;
		default:
			PKCS12err(PKCS12_F_PKCS12_INIT,PKCS12_R_UNSUPPORTED_PKCS12_MODE);
			PKCS12_free(pkcs12);
			return NULL;
		break;
	}
		
	return pkcs12;
}
