/*
 *
 */

#include "iodefine.h"
#include "r_typedefs.h"
#include "e2flashdef.h"
#include "mrubyc.h"

#include "xprintf.h"

#define XMODEM_SOH	0x01
#define XMODEM_STX	0x02
#define XMODEM_EOT	0x04
#define XMODEM_ACK	0x06
#define XMODEM_NAK	0x15
#define XMODEM_CAN	0x18
#define XMODEM_EOF	0x1a /* Ctrl-Z */

#define E2_BASE_ADDR	(0x00100000)

#define MEMORY_SIZE (1024*10)
static char memory_pool[MEMORY_SIZE];

extern c_sci5_init();
extern c_sci5_read();
extern c_sci5_write();

mon()
{
unsigned char ch;

	R_FlashDataAreaAccess (0xFFFF, 0xFFFF);
	flash_init();

	for(;;) {
		ch = gchar();
		switch(ch) {
			case 'x':
				xrec();
				break;
			case 'r':
				runmrbc();
				break;
			default:
				break;
		}
	}

}

mrbcopy(unsigned short *src, unsigned short *dst, int size)
{
int i;

	for (i = 0; i < size / 2; ++i)
		dst[i] = src[i];
}

xrec()
{
unsigned char ch;
unsigned char dat[128];
int i, block;

	block = 0;

	xprintf("xmodem start after 10 secs\r\n", block);

#if defined(GRCITRUS)
	EraseE2Flash(E2_BASE_ADDR, 128 * 256);	// 32K
#else
	EraseE2Flash(E2_BASE_ADDR, 128 * 64);	// 8K
#endif

	delay_ms(10000);
	pchar(XMODEM_NAK);

	while(1) {
		ch = gchar();
		if (ch == XMODEM_EOT) {
			pchar(XMODEM_ACK);
			break;
		}
		ch = gchar();
		ch = gchar();
		for(i = 0; i < 128; ++i)
			dat[i] = gchar();
		ch = gchar();

		WriteE2Flash(E2_BASE_ADDR + block * 128, dat, 128);
		++block;
		pchar(XMODEM_ACK);
	}

	xprintf("%d blocks\r\n", block);

}

void runmrbc()
{
unsigned short *e2p;
unsigned short ss;
unsigned char ch;
int i;
int mrbsize;
unsigned char *mrbbuf;

	e2p = E2_BASE_ADDR;
	for (i = 0; i < 8; ++i) {
		ch = *(e2p + i);
		xprintf("%02x ", ch);
		ch = *(e2p + i) >> 8;
		xprintf("%02x ", ch);
	}
	xprintf("\r\n");
	ss = *(e2p + 4);
	mrbsize = (ss & 0xff) << 24 | (ss >> 8) << 16;
	ss = *(e2p + 5);
	mrbsize += (ss & 0xff) << 8 | (ss >> 8);
	mrbsize = ((mrbsize + 1) / 2) * 2;
	xprintf("MRB SIZE %d\r\n", mrbsize);

	mrbbuf = malloc(mrbsize);

	mrbcopy(e2p, mrbbuf, mrbsize);

	mrbc_init(memory_pool, MEMORY_SIZE);
	mrbc_define_method(0, mrbc_class_object, "serial_init",
	    (mrbc_func_t)c_sci5_init);
	mrbc_define_method(0, mrbc_class_object, "serial_read",
	    (mrbc_func_t)c_sci5_read);
	mrbc_define_method(0, mrbc_class_object, "serial_write",
	    (mrbc_func_t)c_sci5_write);

	if (NULL == mrbc_create_task(mrbbuf, 0))
	{
		while(1);
	}

	mrbc_run();

	return 0;
}

