/* crypto/engine/engine_err.c */
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
 *    openssl-core@OpenSSL.org.
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

/* NOTE: this file was auto generated by the mkerr.pl script: any changes
 * made to it will be overwritten when the script next updates this file,
 * only reason strings will be preserved.
 */

#include <stdio.h>
#include <openssl/err.h>
#include <openssl/engine.h>

/* BEGIN ERROR CODES */
#ifndef NO_ERR
static ERR_STRING_DATA ENGINE_str_functs[]=
	{
{ERR_PACK(0,ENGINE_F_ATALLA_FINISH,0),	"ATALLA_FINISH"},
{ERR_PACK(0,ENGINE_F_ATALLA_INIT,0),	"ATALLA_INIT"},
{ERR_PACK(0,ENGINE_F_ATALLA_MOD_EXP,0),	"ATALLA_MOD_EXP"},
{ERR_PACK(0,ENGINE_F_ATALLA_RSA_MOD_EXP,0),	"ATALLA_RSA_MOD_EXP"},
{ERR_PACK(0,ENGINE_F_CSWIFT_DSA_SIGN,0),	"CSWIFT_DSA_SIGN"},
{ERR_PACK(0,ENGINE_F_CSWIFT_DSA_VERIFY,0),	"CSWIFT_DSA_VERIFY"},
{ERR_PACK(0,ENGINE_F_CSWIFT_FINISH,0),	"CSWIFT_FINISH"},
{ERR_PACK(0,ENGINE_F_CSWIFT_INIT,0),	"CSWIFT_INIT"},
{ERR_PACK(0,ENGINE_F_CSWIFT_MOD_EXP,0),	"CSWIFT_MOD_EXP"},
{ERR_PACK(0,ENGINE_F_CSWIFT_MOD_EXP_CRT,0),	"CSWIFT_MOD_EXP_CRT"},
{ERR_PACK(0,ENGINE_F_CSWIFT_RSA_MOD_EXP,0),	"CSWIFT_RSA_MOD_EXP"},
{ERR_PACK(0,ENGINE_F_ENGINE_ADD,0),	"ENGINE_add"},
{ERR_PACK(0,ENGINE_F_ENGINE_BY_ID,0),	"ENGINE_by_id"},
{ERR_PACK(0,ENGINE_F_ENGINE_CTRL,0),	"ENGINE_ctrl"},
{ERR_PACK(0,ENGINE_F_ENGINE_FINISH,0),	"ENGINE_finish"},
{ERR_PACK(0,ENGINE_F_ENGINE_FREE,0),	"ENGINE_free"},
{ERR_PACK(0,ENGINE_F_ENGINE_GET_BN_MOD_EXP,0),	"ENGINE_get_BN_mod_exp"},
{ERR_PACK(0,ENGINE_F_ENGINE_GET_BN_MOD_EXP_CRT,0),	"ENGINE_get_BN_mod_exp_crt"},
{ERR_PACK(0,ENGINE_F_ENGINE_GET_CTRL_FUNCTION,0),	"ENGINE_get_ctrl_function"},
{ERR_PACK(0,ENGINE_F_ENGINE_GET_DH,0),	"ENGINE_get_DH"},
{ERR_PACK(0,ENGINE_F_ENGINE_GET_DSA,0),	"ENGINE_get_DSA"},
{ERR_PACK(0,ENGINE_F_ENGINE_GET_FINISH_FUNCTION,0),	"ENGINE_get_finish_function"},
{ERR_PACK(0,ENGINE_F_ENGINE_GET_ID,0),	"ENGINE_get_id"},
{ERR_PACK(0,ENGINE_F_ENGINE_GET_INIT_FUNCTION,0),	"ENGINE_get_init_function"},
{ERR_PACK(0,ENGINE_F_ENGINE_GET_NAME,0),	"ENGINE_get_name"},
{ERR_PACK(0,ENGINE_F_ENGINE_GET_NEXT,0),	"ENGINE_get_next"},
{ERR_PACK(0,ENGINE_F_ENGINE_GET_PREV,0),	"ENGINE_get_prev"},
{ERR_PACK(0,ENGINE_F_ENGINE_GET_RAND,0),	"ENGINE_get_RAND"},
{ERR_PACK(0,ENGINE_F_ENGINE_GET_RSA,0),	"ENGINE_get_RSA"},
{ERR_PACK(0,ENGINE_F_ENGINE_INIT,0),	"ENGINE_init"},
{ERR_PACK(0,ENGINE_F_ENGINE_LIST_ADD,0),	"ENGINE_LIST_ADD"},
{ERR_PACK(0,ENGINE_F_ENGINE_LIST_REMOVE,0),	"ENGINE_LIST_REMOVE"},
{ERR_PACK(0,ENGINE_F_ENGINE_LOAD_PRIVATE_KEY,0),	"ENGINE_load_private_key"},
{ERR_PACK(0,ENGINE_F_ENGINE_LOAD_PUBLIC_KEY,0),	"ENGINE_load_public_key"},
{ERR_PACK(0,ENGINE_F_ENGINE_NEW,0),	"ENGINE_new"},
{ERR_PACK(0,ENGINE_F_ENGINE_REMOVE,0),	"ENGINE_remove"},
{ERR_PACK(0,ENGINE_F_ENGINE_SET_BN_MOD_EXP,0),	"ENGINE_set_BN_mod_exp"},
{ERR_PACK(0,ENGINE_F_ENGINE_SET_BN_MOD_EXP_CRT,0),	"ENGINE_set_BN_mod_exp_crt"},
{ERR_PACK(0,ENGINE_F_ENGINE_SET_CTRL_FUNCTION,0),	"ENGINE_set_ctrl_function"},
{ERR_PACK(0,ENGINE_F_ENGINE_SET_DEFAULT_TYPE,0),	"ENGINE_SET_DEFAULT_TYPE"},
{ERR_PACK(0,ENGINE_F_ENGINE_SET_DH,0),	"ENGINE_set_DH"},
{ERR_PACK(0,ENGINE_F_ENGINE_SET_DSA,0),	"ENGINE_set_DSA"},
{ERR_PACK(0,ENGINE_F_ENGINE_SET_FINISH_FUNCTION,0),	"ENGINE_set_finish_function"},
{ERR_PACK(0,ENGINE_F_ENGINE_SET_ID,0),	"ENGINE_set_id"},
{ERR_PACK(0,ENGINE_F_ENGINE_SET_INIT_FUNCTION,0),	"ENGINE_set_init_function"},
{ERR_PACK(0,ENGINE_F_ENGINE_SET_NAME,0),	"ENGINE_set_name"},
{ERR_PACK(0,ENGINE_F_ENGINE_SET_RAND,0),	"ENGINE_set_RAND"},
{ERR_PACK(0,ENGINE_F_ENGINE_SET_RSA,0),	"ENGINE_set_RSA"},
{ERR_PACK(0,ENGINE_F_ENGINE_UNLOAD_KEY,0),	"ENGINE_UNLOAD_KEY"},
{ERR_PACK(0,ENGINE_F_HWCRHK_CTRL,0),	"HWCRHK_CTRL"},
{ERR_PACK(0,ENGINE_F_HWCRHK_FINISH,0),	"HWCRHK_FINISH"},
{ERR_PACK(0,ENGINE_F_HWCRHK_GET_PASS,0),	"HWCRHK_GET_PASS"},
{ERR_PACK(0,ENGINE_F_HWCRHK_INIT,0),	"HWCRHK_INIT"},
{ERR_PACK(0,ENGINE_F_HWCRHK_LOAD_PRIVKEY,0),	"HWCRHK_LOAD_PRIVKEY"},
{ERR_PACK(0,ENGINE_F_HWCRHK_LOAD_PUBKEY,0),	"HWCRHK_LOAD_PUBKEY"},
{ERR_PACK(0,ENGINE_F_HWCRHK_MOD_EXP,0),	"HWCRHK_MOD_EXP"},
{ERR_PACK(0,ENGINE_F_HWCRHK_MOD_EXP_CRT,0),	"HWCRHK_MOD_EXP_CRT"},
{ERR_PACK(0,ENGINE_F_HWCRHK_RAND_BYTES,0),	"HWCRHK_RAND_BYTES"},
{ERR_PACK(0,ENGINE_F_HWCRHK_RSA_MOD_EXP,0),	"HWCRHK_RSA_MOD_EXP"},
{ERR_PACK(0,ENGINE_F_LOG_MESSAGE,0),	"LOG_MESSAGE"},
{0,NULL}
	};

static ERR_STRING_DATA ENGINE_str_reasons[]=
	{
{ENGINE_R_ALREADY_LOADED                 ,"already loaded"},
{ENGINE_R_BIO_WAS_FREED                  ,"bio was freed"},
{ENGINE_R_BN_CTX_FULL                    ,"BN_CTX full"},
{ENGINE_R_BN_EXPAND_FAIL                 ,"bn_expand fail"},
{ENGINE_R_CHIL_ERROR                     ,"chil error"},
{ENGINE_R_CONFLICTING_ENGINE_ID          ,"conflicting engine id"},
{ENGINE_R_CTRL_COMMAND_NOT_IMPLEMENTED   ,"ctrl command not implemented"},
{ENGINE_R_DSO_FAILURE                    ,"DSO failure"},
{ENGINE_R_ENGINE_IS_NOT_IN_LIST          ,"engine is not in the list"},
{ENGINE_R_FAILED_LOADING_PRIVATE_KEY     ,"failed loading private key"},
{ENGINE_R_FAILED_LOADING_PUBLIC_KEY      ,"failed loading public key"},
{ENGINE_R_FINISH_FAILED                  ,"finish failed"},
{ENGINE_R_GET_HANDLE_FAILED              ,"could not obtain hardware handle"},
{ENGINE_R_ID_OR_NAME_MISSING             ,"'id' or 'name' missing"},
{ENGINE_R_INIT_FAILED                    ,"init failed"},
{ENGINE_R_INTERNAL_LIST_ERROR            ,"internal list error"},
{ENGINE_R_MISSING_KEY_COMPONENTS         ,"missing key components"},
{ENGINE_R_NOT_INITIALISED                ,"not initialised"},
{ENGINE_R_NOT_LOADED                     ,"not loaded"},
{ENGINE_R_NO_CALLBACK                    ,"no callback"},
{ENGINE_R_NO_CONTROL_FUNCTION            ,"no control function"},
{ENGINE_R_NO_KEY                         ,"no key"},
{ENGINE_R_NO_LOAD_FUNCTION               ,"no load function"},
{ENGINE_R_NO_REFERENCE			 ,"no reference"},
{ENGINE_R_NO_SUCH_ENGINE                 ,"no such engine"},
{ENGINE_R_NO_UNLOAD_FUNCTION             ,"no unload function"},
{ENGINE_R_PROVIDE_PARAMETERS             ,"provide parameters"},
{ENGINE_R_REQUEST_FAILED                 ,"request failed"},
{ENGINE_R_REQUEST_FALLBACK               ,"request fallback"},
{ENGINE_R_SIZE_TOO_LARGE_OR_TOO_SMALL    ,"size too large or too small"},
{ENGINE_R_UNIT_FAILURE                   ,"unit failure"},
{0,NULL}
	};

#endif

void ERR_load_ENGINE_strings(void)
	{
	static int init=1;

	if (init)
		{
		init=0;
#ifndef NO_ERR
		ERR_load_strings(ERR_LIB_ENGINE,ENGINE_str_functs);
		ERR_load_strings(ERR_LIB_ENGINE,ENGINE_str_reasons);
#endif

		}
	}
