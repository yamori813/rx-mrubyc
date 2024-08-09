/*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized. This
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2013 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/
/*******************************************************************************
* System Name  : RX210 initialization example
* File Name    : r_init_clock.h
* Version      : Ver 2.00
* Device       : R5F52108ADFP(RX210 Group)
* Abstract     : Program example of RX210 initialization
* Tool-Chain   : High-performance Embedded Workshop (Version 4.09.01.007)
*              : C/C++ Compiler Package for RX Family (V.1.02 Release 01)
* OS           : not use
* H/W Platform : Renesas Starter Kit for RX210
* Description  : Initialize the clock.
* Limitation   : none
*******************************************************************************/
/*******************************************************************************
* History      : DD.MM.YYYY Version  Description
*              : 01.03.2013 2.00     First Release
*******************************************************************************/

/* Guards against multiple inclusion */
#ifndef R_INIT_CLOCK_H
#define R_INIT_CLOCK_H

/*******************************************************************************
Macro definitions
*******************************************************************************/
/* ==== Please select the Chip Version ==== */
/* This sample code uses the Chip Version C.
   Please change the following settings as necessary. */
#define VERSION_A       (1)
#define VERSION_B       (2)
#define VERSION_C       (3)
#define SEL_CHIP        VERSION_A

/* The value to select whether to use */
#define B_NOT_USE       (0)
#define B_USE           (1)

/* ==== Please set the main clock ==== */
/* This sample code uses the main clock with the following settings.
   Please change the following settings as necessary. */
#define SEL_MAIN        B_USE
/* Frequency : 20 MHz */
#define MAIN_CLOCK_Hz   (20000000L)
/* Drive capability : 20 MHz crystal resonator */
#define REG_MOFCR       (0x30)
/* Wait control register : 131072 cycles (approx. 6.55 ms) */
#define REG_MOSCWTCR    (0x0D)
/* Wait time for the clock oscillation stabilization : 13.1072 ms */
#define WAIT_TIME_FOR_MAIN_OSCILLATION  (13107200L)

/* ==== Please set the sub-clock ==== */
/* This sample code does not use the sub-clock.
   Please change the following settings as necessary. */
#define SEL_SUB         B_NOT_USE       /* Please select whether to use sub-clock as the system clock */
#define SEL_RTC         B_NOT_USE       /* Please select whether to use sub-clock as the RTC count source */
/* Frequency : 32.768 kHz */
#define SUB_CLOCK_Hz    (32768L)
/* Wait control register : 2 s + 2 cycles (approx. 2 s) */
#define REG_SOSCWTCR    (0x00)
/* Wait time for the clock oscillation stabilization : 4 s */
#define WAIT_TIME_FOR_SUB_OSCILLATION   (4000000000L)
/* ---- Please select the drive capability ---- */
#define CL_LOW          (0x02)          /* Low CL */
#define CL_STD          (0x0C)          /* Standard CL */
#define REG_RCR3        CL_LOW

/* ==== Please set the PLL clock ==== */
/* This sample code uses the PLL clock with the following settings.
   Please change the following settings as necessary. */
#define SEL_PLL         B_USE
/* Division ratio and multiplication factor : divide-by-2, multiply-by-10 */
#define REG_PLLCR       (0x0901)
/* Wait control register : 65536 cycles (approx. 655.36 us) */
#define REG_PLLWTCR     (0x09)
/* Wait time for the clock oscillation stabilization : 1.50 ms */
#define WAIT_TIME_FOR_PLL_OSCILLATION   (1500000L)

/* ==== Please set the HOCO clock ==== */
/* This sample code does not use the HOCO clock.
   Please change the following settings as necessary. */
#define SEL_HOCO        B_NOT_USE
/* ---- Please select the HOCO frequency ---- */
#define FREQ_32MHz      (0x00)          /* 32 MHz */
#define FREQ_36MHz      (0x01)          /* 36.864 MHz */
#define FREQ_40MHz      (0x02)          /* 40 MHz */
#define FREQ_50MHz      (0x03)          /* 50 MHz */
#define REG_HOCOCR2     FREQ_50MHz
/* Wait control register */
#if (REG_HOCOCR2 == FREQ_50MHz)
    #define REG_HOCOWTCR2   (0x03)      /* 50 MHz : 9216 cycles */
#else
    #define REG_HOCOWTCR2   (0x02)      /* 32 MHz, 36.864 MHz, 40 MHz : 7168 cycles */
#endif
/* Wait time for the clock oscillation stabilization : 350 us */
#define WAIT_TIME_FOR_HOCO_OSCILLATION  (350000L)

/* ==== Please select the source of the system clock ==== */
#if (SEL_PLL == B_USE)
    #define CLK_PLL     (0x0400)        /* PLL */
#endif
#if (SEL_HOCO == B_USE)
    #define CLK_HOCO    (0x0100)        /* HOCO */
#endif
#if (SEL_SUB == B_USE)
    #define CLK_SUB     (0x0300)        /* Sub-clock */
#endif
#if (SEL_CHIP == VERSION_B) || (SEL_CHIP == VERSION_C)
    #if (SEL_MAIN == B_USE)
    #define CLK_MAIN    (0x0200)        /* Main clock */
    #endif
#endif
/* This sample code uses PLL as the system clock.
   Please change the following settings as necessary. */
#define SEL_SYSCLK      CLK_PLL

/* ==== Please select the internal clock division ratio ==== */
/* This sample code uses the following internal clock division ratio.
   Please change the following settings as necessary. */
#if (SEL_SYSCLK == CLK_PLL)
    #define REG_SCKCR   (0x21821211)    /* ICLK,PCLKD: divide-by-2
                                           PCLKB,BCLK,FCLK: divide-by-4 */
#elif (SEL_SYSCLK == CLK_HOCO)
    #define REG_SCKCR   (0x10811110)    /* ICLK,PCLKD: no division
                                           PCLKB,BCLK,FCLK: divide-by-2 */
#else
    #define REG_SCKCR   (0x00801010)    /* ICLK,PCLKD,PCLKB,BCLK,FCLK: no division */
#endif

/* ==== Please select the operating power control mode ==== */
#define OPCM_HIGH       (0x00)          /* High-speed operating mode */
#define OPCM_MID_1A     (0x02)          /* Middle-speed operating mode 1A */
#define OPCM_MID_1B     (0x03)          /* Middle-speed operating mode 1B */
#if (SEL_CHIP == VERSION_B)
    #define OPCM_MID_2A (0x04)          /* Middle-speed operating mode 2A */
    #define OPCM_MID_2B (0x05)          /* Middle-speed operating mode 2B */
#endif
#if (SEL_PLL == B_NOT_USE)
    #define OPCM_LOW_1  (0x06)          /* Low-speed operating mode 1 */
#endif
#if (SEL_PLL == B_NOT_USE) && (SEL_HOCO == B_NOT_USE)
    #define OPCM_LOW_2  (0x07)          /* Low-speed operating mode 2 */
#endif
/* This sample code uses the High-speed operating mode.
   Please change the following settings as necessary. */
#define REG_OPCCR       OPCM_HIGH


/*******************************************************************************
Exported global variables and functions (to be accessed by other files)
*******************************************************************************/
void R_INIT_Clock(void);
void CGC_oscillation_main(void);
void CGC_oscillation_PLL(void);
void CGC_oscillation_HOCO(void);
void CGC_oscillation_sub(void);
void CGC_disable_subclk(void);

#endif /* R_INIT_CLOCK_H */

/* End of File */
