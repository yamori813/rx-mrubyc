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
//#include "r_smc_entry.h"
//#include "r_sci_rx_if.h"
#include "mrubyc.h"

#define MEMORY_SIZE (1024*40)
static char memory_pool[MEMORY_SIZE];

extern const uint8_t sample_serial_echo_server[];

//sci_hdl_t xSerialSciHandle;

static void c_sci5_init (mrb_vm * vm, mrb_value * v);
static void c_sci5_read (mrb_vm * vm, mrb_value * v);
static void c_sci5_write (mrb_vm * vm, mrb_value * v);

static void c_sci5_init (mrb_vm * vm, mrb_value * v)
{
#if 0
    sci_cfg_t xSerialSciConfig;
    R_SCI_PinSet_SCI5();

    xSerialSciConfig.async.baud_rate    = BSP_CFG_SCI_UART_TERMINAL_BITRATE;
    xSerialSciConfig.async.clk_src      = SCI_CLK_INT;
    xSerialSciConfig.async.data_size    = SCI_DATA_8BIT;
    xSerialSciConfig.async.parity_en    = SCI_PARITY_OFF;
    xSerialSciConfig.async.parity_type  = SCI_EVEN_PARITY;
    xSerialSciConfig.async.stop_bits    = SCI_STOPBITS_1;
    xSerialSciConfig.async.int_priority = 1; /* lowest at first. */
    R_SCI_Open(SCI_CH5, SCI_MODE_ASYNC, &xSerialSciConfig, NULL, &xSerialSciHandle);
#endif
}

static void c_sci5_read(mrb_vm * vm, mrb_value * v)
{
#if 0
    sci_err_t ret;
    uint8_t ch;

    do
    {
        ret = R_SCI_Receive(xSerialSciHandle, &ch, 1);
    } while (SCI_SUCCESS != ret);

    SET_INT_RETURN(ch);
#endif
}

static void c_sci5_write(mrb_vm * vm, mrb_value * v)
{
#if 0
    sci_err_t ret;
    uint8_t ch = GET_INT_ARG(1);

    do
    {
        ret = R_SCI_Send(xSerialSciHandle, &ch, 1);
    } while (SCI_SUCCESS != ret);
#endif
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
	mrbc_init(memory_pool, MEMORY_SIZE);
	mrbc_define_method(0, mrbc_class_object, "serial_init", (mrbc_func_t)c_sci5_init);
	mrbc_define_method(0, mrbc_class_object, "serial_read", (mrbc_func_t)c_sci5_read);
	mrbc_define_method(0, mrbc_class_object, "serial_write", (mrbc_func_t)c_sci5_write);

	if (NULL == mrbc_create_task(sample_serial_echo_server, 0))
	{
		while(1);
	}

	mrbc_run();

	while(1)
	{
		/* do nothing */
	}

    return 0;
}

