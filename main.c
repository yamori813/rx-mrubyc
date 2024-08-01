/**
 * @file main.c
 * @author nizuki926
 * @brief main program
 * @version 1.0
 * @date 2019-02-03
 *
 * @copyright Copyright (c) 2019, nizuki926 All rights reserved.
 *
 */
#include "iodefine.h"
#include "mrubyc.h"

#include "xprintf.h"

#define MEMORY_SIZE (1024*10)
static char memory_pool[MEMORY_SIZE];

static void c_sci5_init (mrb_vm * vm, mrb_value * v);
static void c_sci5_read (mrb_vm * vm, mrb_value * v);
static void c_sci5_write (mrb_vm * vm, mrb_value * v);

static void c_sci5_init (mrb_vm * vm, mrb_value * v)
{
}

static void c_sci5_read(mrb_vm * vm, mrb_value * v)
{
	uint8_t ch;

	while(ICU.IR[IR_SCI1_RXI1].BIT.IR == 0)
	{
		if(SCI1.SSR.BYTE & 0x38)
		{
			SCI1.SSR.BYTE = (SCI1.SSR.BYTE & 1) | 0xC0;
		}
	}
	ICU.IR[IR_SCI1_RXI1].BIT.IR = 0;
	ch = SCI1.RDR;
	SET_INT_RETURN(ch);
}

void pchar(unsigned char);
void pchar(unsigned char ch)
{
	while (ICU.IR[IR_SCI1_TXI1].BIT.IR == 0)
	{
		;
	}
	ICU.IR[IR_SCI1_TXI1].BIT.IR = 0;
	SCI1.TDR = ch;
}

static void c_sci5_write(mrb_vm * vm, mrb_value * v)
{
	uint8_t ch = GET_INT_ARG(1);

	pchar(ch);
}

int hal_write(int fd, const void * buf, int nbytes)
{
	return 0;
}

int hal_flush(int fd)
{
	return 0;
}

mrbcopy(unsigned short *src, unsigned short *dst, int size)
{
int i;

	for (i = 0; i < size / 2; ++i)
		dst[i] = src[i];
}

/**
 * @brief mruby/c initialize routine
 *
 */
int main (void)
{
unsigned short *e2p;
unsigned short ss;
unsigned char ch;
int i;
int mrbsize;
unsigned char *mrbbuf;

	xfunc_out=pchar;

	xprintf("start\r\n");

	FLASH.DFLRE0.WORD = 0x2D00 | 0x0F;

	e2p = 0x00100000;
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

	FLASH.DFLRE0.WORD = 0x2D00 | 0x00;

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

