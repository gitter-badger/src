/*	$OpenBSD: tgets.c,v 1.1.12.1 2003/06/07 11:11:35 ho Exp $	*/
/*	$NetBSD: tgets.c,v 1.4 1994/10/26 07:28:05 cgd Exp $	*/

/*-
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
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
 *	@(#)gets.c	8.1 (Berkeley) 6/11/93
 */

int
tgets(buf)
    char *buf;
{
    register int c;
    int i;
    register char *lp = buf;

    for (i = 240000; i > 0; i--) {
        c = tgetchar() & 0177;
        if (c) {
            for (;;) {
                switch (c) {
                case '\n':
                case '\r':
                    *lp = '\0';
                    putchar('\n');
                    return (1);
                case '\b':
                case '\177':
                    if (lp > buf) {
                        lp--;
                        putchar('\b');
                        putchar(' ');
                        putchar('\b');
                    }
                    break;
                case '#':
                    if (lp > buf)
                        --lp;
                    break;
                case 'r'&037: {
                    register char *p;

                    putchar('\n');
                    for (p = buf; p < lp; ++p)
                        putchar(*p);
                    break;
                }
                case '@':
                case 'u'&037:
                case 'w'&037:
                    lp = buf;
                    putchar('\n');
                    break;
                default:
                    *lp++ = c;
                    putchar(c);
                }
                c = getchar() & 0177;
            }
        }
    }
    return (0);
}
