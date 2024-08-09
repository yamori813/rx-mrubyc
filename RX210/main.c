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
#include "r_typedefs.h"
#include "e2flashdef.h"
#include "mrubyc.h"

#include "xprintf.h"

#define E2_BASE_ADDR	(0x00100000)

int statcon()
{
	if(SCI1.SSR.BYTE & 0x38)
	{
		SCI1.SSR.BYTE = (SCI1.SSR.BYTE & 1) | 0xC0;
	}
	return ICU.IR[IR_SCI1_RXI1].BIT.IR;
}

int gchar()
{
	while(ICU.IR[IR_SCI1_RXI1].BIT.IR == 0)
	{
		if(SCI1.SSR.BYTE & 0x38)
		{
			SCI1.SSR.BYTE = (SCI1.SSR.BYTE & 1) | 0xC0;
		}
	}
	ICU.IR[IR_SCI1_RXI1].BIT.IR = 0;
	return(SCI1.RDR);
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

void c_sci5_init (mrb_vm * vm, mrb_value * v)
{
}

void c_sci5_read(mrb_vm * vm, mrb_value * v)
{
	uint8_t ch;

	ch = gchar();
	SET_INT_RETURN(ch);
}

void c_sci5_write(mrb_vm * vm, mrb_value * v)
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
unsigned char ch;

	xfunc_out=pchar;

	xprintf("start\r\n");

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

