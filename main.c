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

extern const uint8_t hoge[];

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

/**
 * @brief mruby/c initialize routine
 *
 */
int main (void)
{
	xfunc_out=pchar;

	xprintf("start\r\n");

	mrbc_init(memory_pool, MEMORY_SIZE);
	mrbc_define_method(0, mrbc_class_object, "serial_init",
	    (mrbc_func_t)c_sci5_init);
	mrbc_define_method(0, mrbc_class_object, "serial_read",
	    (mrbc_func_t)c_sci5_read);
	mrbc_define_method(0, mrbc_class_object, "serial_write",
	    (mrbc_func_t)c_sci5_write);

	if (NULL == mrbc_create_task(hoge, 0))
	{
		while(1);
	}

	mrbc_run();

	return 0;
}

