/*	$OpenBSD: cache.c,v 1.1.4.2 2004/02/19 10:49:04 niklas Exp $	*/
#define CACHELINESIZE   32                      /* For now              XXX */

void
syncicache(void *from, int len)
{
	int l = len;
	void *p = from;

	do {
		asm volatile ("dcbf %1,%0" :: "r"(p), "r"(0));
		p += CACHELINESIZE;
	} while ((l -= CACHELINESIZE) > 0);
	asm volatile ("sync");
	do {
		asm volatile ("icbi %1,%0" :: "r"(from), "r"(0));
		from += CACHELINESIZE;
	} while ((len -= CACHELINESIZE) > 0);
	asm volatile ("isync");
}
