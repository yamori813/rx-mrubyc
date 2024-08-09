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
* File Name    : r_init_clock.c
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

/*******************************************************************************
Includes <System Includes> , "Project Includes"
*******************************************************************************/
#include <stdint.h>
#include "iodefine.h"
#include "r_init_clock.h"

/*******************************************************************************
Macro definitions
*******************************************************************************/
#define MAIN_CLOCK_CYCLE (1000000000L/MAIN_CLOCK_Hz)
#define SUB_CLOCK_CYCLE  (1000000000L/SUB_CLOCK_Hz)

/* Time for one count of CMT0 is approximately 232727 ns
   when the count source is LOCO divided by 32 (max. of LOCO = 137.5 kHz) */
#define FOR_CMT0_TIME    (232727)

/*******************************************************************************
Private variables and functions
*******************************************************************************/
static void oscillation_subclk(void);
static void no_use_subclk_as_sysclk(void);
static void resetting_wtcr_subclk(void);
static void enable_RTC(void);
static void cmt0_wait(uint32_t);


/*******************************************************************************
* Outline      : Clock initialization
* Header       : r_init_clock.h
* Function Name: R_INIT_Clock
* Description  : Initialize the clock.
* Arguments    : none
* Return Value : none
*******************************************************************************/
void R_INIT_Clock(void)
{

    /* ---- Enable write protection ---- */
    /* PRCR - Protect Register
    b15:b8 PRKEY - PRC Key Code - A5h
                  (The write value should be A5h to permission writing PRCi bit)
    b2     PRC2 - Protect Bit 2 - Write enabled
    b1     PRC1 - Protect Bit 1 - Write enabled
    b0     PRC0 - Protect Bit 0 - Write enabled */
    SYSTEM.PRCR.WORD = 0xA507;

    /* ---- Set the VRCR register ---- */
    SYSTEM.VRCR = 0x00;

    /* ---- Turn off the HOCO power supply ---- */
#if (SEL_HOCO == B_NOT_USE)
    /* HOCOPCR - High-Speed On-Chip Oscillator Power Supply Control Register
    b7:b1   Reserved - The write value should be 0.
    b0      HOCOPCNT - High-Speed On-Chip Oscillator Power Supply Control
                     - HOCO power supply is turned off. */
    SYSTEM.HOCOPCR.BYTE = 0x01;
#endif

    /* ---- Turn off the PLL power supply ---- */
#if (SEL_PLL == B_NOT_USE) && (SEL_CHIP == VERSION_B)
    /* PLLPCR - PLL Power Control Register
    b7:b1   Reserved - The write value should be 0.
    b0      PLLPCNT  - PLL Power Control - Powered off */
    SYSTEM.PLLPCR.BYTE = 0x01;
#endif

    /* ---- Set the sub-clock ---- */
#if (SEL_SUB == B_USE) || (SEL_RTC == B_USE)
    CGC_oscillation_sub();
#else
    CGC_disable_subclk();
#endif

    /* ---- Set the main clock ---- */
#if (SEL_MAIN == B_USE) || (SEL_PLL == B_USE)
    CGC_oscillation_main();
#endif

    /* ---- Set the PLL clock ---- */
#if (SEL_PLL == B_USE)
    CGC_oscillation_PLL();
#endif

    /* ---- Set the HOCO clock ---- */
#if (SEL_HOCO == B_USE)
    CGC_oscillation_HOCO();
#endif


#if (REG_OPCCR == OPCM_HIGH)
    /* ---- Set the operating power control mode ---- */
    /* OPCCR - Operating Power Control Register
    b7:b5   Reserved - The write value should be 0.
    b4      OPCMTSF  - Operating Power Control Mode Transition Status Flag
    b3      Reserved - The write value should be 0.
    b2:b0   OPCM     - Operating Power Control Mode Select - High-speed operating mode */
    SYSTEM.OPCCR.BYTE = REG_OPCCR;
    while (0 != SYSTEM.OPCCR.BIT.OPCMTSF)
    {
        /* Confirm that the operation power control mode transition completed. */
    }
#endif

    /* ---- Set the internal clock division ratio ---- */
    /* SCKCR - System Clock Control Register
    b31:b28 FCK      - FlashIF Clock(FCLK) Select - divide-by-4
    b27:b24 ICK      - System Clock (ICLK) Select - divide-by-2
    b23     PSTOP1   - BCLK Pin Output Control    - disabled. (Fixed high)
    b22:b20 Reserved - The write value should be 0.
    b19:b16 BCK      - External Bus Clock (BCLK) Select - divide-by-4
    b15:b12 Reserved - The write value should be 0001b.
    b10:b8  PCLKB    - Peripheral Module Clock B(PCLKB) Select - divide-by-4
    b7:b4   Reserved - The write value should be 0001b.
    b3:b0   PCLKD    - Peripheral Module Clock D(PCLKD) Select - divide-by-2 */
    SYSTEM.SCKCR.LONG = REG_SCKCR;
    while (REG_SCKCR != SYSTEM.SCKCR.LONG)
    {
         /* Confirm that the written value can be read correctly. */
    }

    /* ---- Set the BCLK pin output ---- */
    /* BCKCR - External Bus Clock Control Register
    b7:b1    Reserved - The write value should be 0.
    b0       BCLKDIV  - BCLK Pin Output Select - divide-by-2 */
    SYSTEM.BCKCR.BYTE = 0x01;
    while (0x01 != SYSTEM.BCKCR.BYTE)
    {
        /* Confirm that the written value can be read correctly. */
    }

    /* ---- Set the internal clock source ---- */
    /* SCKCR3 - System Clock Control Register 3
    b10:b8  CKSEL    - Clock Source Select - PLL circuit is selected. */
    SYSTEM.SCKCR3.WORD = SEL_SYSCLK;
    while (SEL_SYSCLK != SYSTEM.SCKCR3.WORD)
    {
        /* Confirm that the written value can be read correctly. */
    }

#if (REG_OPCCR > OPCM_MID_1A)
    /* ---- Set the operating power control mode ---- */
    /* OPCCR - Operating Power Control Register
    b7:b5   Reserved - The write value should be 0.
    b4      OPCMTSF  - Operating Power Control Mode Transition Status Flag
    b3      Reserved - The write value should be 0.
    b2:b0   OPCM     - Operating Power Control Mode Select - High-speed operating mode */
    SYSTEM.OPCCR.BYTE = REG_OPCCR;
    while (0 != SYSTEM.OPCCR.BIT.OPCMTSF)
    {
        /* Confirm that the operation power control mode transition completed. */
    }
#endif

    /* ---- Disable write protection ---- */
    /* PRCR - Protect Register
    b15:b8 PRKEY - PRC Key Code - A5h
                  (The write value should be A5h to permission writing PRCi bit)
    b2     PRC2 - Protect Bit 2 - Write disabled
    b1     PRC1 - Protect Bit 1 - Write disabled
    b0     PRC0 - Protect Bit 0 - Write disabled */
    SYSTEM.PRCR.WORD = 0xA500;

}

/*******************************************************************************
* Outline      : Configure main clock oscillation
* Header       : r_init_clock.h
* Function Name: CGC_oscillation_main
* Description  : Set the drive capability and the MOSCWTCR register,
*                then enable main clock oscillation.
*                Wait for the main clock oscillation stabilization
*                wait time by a software.
* Arguments    : none
* Return Value : none
*******************************************************************************/
void CGC_oscillation_main(void)
{

    /* ----  Set the main clock oscillator drive capability ---- */
    /* MOFCR - Main Clock Oscillator Forced Oscillation Control Register
    b7       Reserved - The write value should be 0.
    b6       MOSEL    - Main Clock Oscillator Switch - Resonator
    b5:b4    MODRV2   - Main Clock Oscillator Drive Capability Switch 2
                      - 16 MHz to 20 MHz
    b3:b1    MODRV    - Main Clock Oscillator Drive Capability Switch
                      - 16 MHz to 20 MHz non-lead type ceramic resonator
    b0       Reserved - The write value should be 0. */
    SYSTEM.MOFCR.BYTE = REG_MOFCR;

    /* ---- Set wait time until the main clock oscillator stabilizes ---- */
    /* MOSCWTCR - Main Clock Oscillator Wait Control Register
    b7:b5    Reserved - The write value should be 0.
    b4:b0    MSTS     - Main Clock Oscillator Waiting Time
                      - Wait time is 131072 cycles (approx. 6.55 ms). */
    SYSTEM.MOSCWTCR.BYTE = REG_MOSCWTCR;

    /* ---- Operate the main clock oscillator ---- */
    /* MOSCCR   - Main Clock Oscillator Control Register
    b7:b1    Reserved - The write value should be 0.
    b0       MOSTP    - Main Clock Oscillator Stop - Main clock oscillator is operating. */
    SYSTEM.MOSCCR.BYTE = 0x00;
    while (0x00 != SYSTEM.MOSCCR.BYTE)
    {
        /* Confirm that the written value can be read correctly. */
    }

    /* ---- Wait processing for the clock oscillation stabilization ---- */
    cmt0_wait((WAIT_TIME_FOR_MAIN_OSCILLATION/FOR_CMT0_TIME)+1);        /* oscillation stabilize (13.1 ms). */ 

}

/*******************************************************************************
* Outline      : Configure PLL clock oscillation
* Header       : r_init_clock.h
* Function Name: CGC_oscillation_PLL
* Description  : Set the PLL input frequency division ratio and 
*                frequency multiplication factor, set the PLLWTCR, 
*                then enable PLL clock oscillation.
*                Wait for the PLL clock oscillation stabilization time.
* Arguments    : none
* Return Value : none
*******************************************************************************/
void CGC_oscillation_PLL(void)
{

    /* ---- Set the PLL division ratio and multiplication factor ---- */
    /* PLLCR - PLL Control Register
    b15:b13  Reserved - The write value should be 0.
    b12:b8   STC      - Frequency Multiplication Factor Select
                      - Frequency multiplication factor is multiply-by-10.
    b7:b2    Reserved - The write value should be 0.
    b1:b0    PLIDIV   - PLL Input Frequency Division Ratio Select
                      - PLL input division ratio is divide-by-2. */
    SYSTEM.PLLCR.WORD = REG_PLLCR;

    /* ---- Set wait time until the PLL clock oscillator stabilizes ---- */
    /* PLLWTCR - PLL Wait Control Register
    b7:b5    Reserved - The write value should be 0.
    b4:b0    PSTS     - PLL Waiting Time
                      - Wait time is 65536 cycles (approx. 655.36 us). */
    SYSTEM.PLLWTCR.BYTE = REG_PLLWTCR;

    /* ---- Operate the PLL clock oscillator ---- */
    /* PLLCR2 - PLL Control Register 2
    b7:b1    Reserved - The write value should be 0.
    b0       PLLEN    - PLL Stop Control - PLL is operating. */
    SYSTEM.PLLCR2.BYTE = 0x00;

    /* ---- Wait processing for the clock oscillation stabilization ---- */
    cmt0_wait((WAIT_TIME_FOR_PLL_OSCILLATION/FOR_CMT0_TIME)+1); /* oscillation stabilize (1.50 ms). */

}

/*******************************************************************************
* Outline      : Configure the HOCO clock oscillation
* Header       : r_init_clock.h
* Function Name: CGC_oscillation_HOCO
* Description  : Set the frequency and the HOCOWTCR2 register,
*                then enable the HOCO.
*                Wait for the HOCO stabilization wait time by a software.
* Arguments    : none
* Return Value : none
*******************************************************************************/
void CGC_oscillation_HOCO(void)
{

    /* ---- Set the HOCO frequency ---- */
    /* HOCOCR2 - High-Speed On-Chip Oscillator Control Register 2
    b7:b2    Reserved - The write value should be 0.
    b1:b0    HCFRQ    - HOCO Frequency Setting - 50 MHz */
    SYSTEM.HOCOCR2.BYTE = REG_HOCOCR2;

    /* ---- Set wait time until the HOCO oscillator stabilizes ---- */
    /* HOCOWTCR2 - HOCO Wait Control Register 2
    b7:b4    Reserved - The write value should be 0.
    b3:b0    HSTS2    - HOCO Wait Time Select 2
                      - Wait time is 9216 cycles (approx. 184.32 us). */
    SYSTEM.HOCOWTCR2.BYTE = REG_HOCOWTCR2;

    /* ---- Operate the HOCO clock ---- */
    /* HOCOCR - High-Speed On-Chip Oscillator Control Register
    b7:b1    Reserved   - The write value should be 0.
    b0       HCSTP      - the HOCO is operating. */
    SYSTEM.HOCOCR.BYTE = 0x00;

    /* ---- Wait processing for the clock oscillation stabilization ---- */
    cmt0_wait((WAIT_TIME_FOR_HOCO_OSCILLATION/FOR_CMT0_TIME)+1);    /* oscillation stabilize (350 us). */

}

/*******************************************************************************
* Outline      : Configure the Sub-clock oscillation
* Header       : r_init_clock.h
* Function Name: CGC_oscillation_sub
* Description  : Configure the setting when the sub-clock is used
*                as the system clock or RTC count source.
* Arguments    : none
* Return Value : none
*******************************************************************************/
void CGC_oscillation_sub(void)
{

    /* ---- Setting of the sub-clock oscillation  ---- */
    oscillation_subclk();

    /* ---- When using the RTC ---- */
    enable_RTC();

    /* ---- Resetting the wait control register ---- */
    resetting_wtcr_subclk();

    /* ---- Setting of the sub-clock do not use the system clock ---- */
    no_use_subclk_as_sysclk();

}

/*******************************************************************************
* Outline      : Configure the Sub-clock stop
* Header       : r_init_clock.h
* Function Name: CGC_disable_subclk
* Description  : Configure the setting when the sub-clock is not used
*                as the system clock or RTC count source.
* Arguments    : none
* Return Value : none
*******************************************************************************/
void CGC_disable_subclk(void)
{

    uint8_t i;
    volatile uint8_t dummy;

    /* ---- Stop the sub-clock oscillator ---- */
    /* SOSCCR - Sub-Clock Oscillator Control Register
    b7:b1    Reserved - The write value should be 0.
    b0       SOSTP    - Sub-clock oscillator Stop - Sub-clock oscillator is stopped. */
    SYSTEM.SOSCCR.BYTE = 0x01;
    while (0x01 != SYSTEM.SOSCCR.BYTE)
    {
        /* Confirm that the written value can be read correctly. */
    }

    /* RCR3 - RTC Control Register 3
    b0       RTCEN    - Sub-clock oscillator is stopped. */
    RTC.RCR3.BIT.RTCEN = 0;

    /* dummy read three times */
    for (i = 0; i < 3; i++)
    {
        dummy = RTC.RCR3.BIT.RTCEN;
    }

}

/*******************************************************************************
* Outline      : Sub-clock oscillation
* Header       : none
* Function Name: oscillation_subclk
* Description  : Configure the sub-clock oscillation setting.
* Arguments    : none
* Return Value : none
*******************************************************************************/
static void oscillation_subclk(void)
{

    uint8_t i;
    volatile uint8_t dummy;

#if (SEL_SUB == B_USE) && (SEL_RTC == B_USE)
    /* ---- Wait processing for the clock oscillation stabilization ---- */
    cmt0_wait((WAIT_TIME_FOR_SUB_OSCILLATION/FOR_CMT0_TIME)+1);    /* Oscillation stabilize (4.0s). */
#endif

    /* ---- Stop the Sub-clock oscillator ---- */
    /* SOSCCR - Sub-Clock Oscillator Control Register
    b0       SOSTP    - Sub-clock oscillator Stop - Sub-clock oscillator is stopped. */
    SYSTEM.SOSCCR.BYTE = 0x01;
    while (0x01 != SYSTEM.SOSCCR.BYTE)
    {
        /* Confirm that the written value can be read correctly. */
    }
    /* RCR3 - RTC Control Register 3
    b0       RTCEN    - Sub-clock oscillator is stopped. */
    RTC.RCR3.BIT.RTCEN = 0;

    /* dummy read three times */
    for (i = 0; i < 3; i++)
    {
        dummy = RTC.RCR3.BIT.RTCEN;
    }

    while (0 != RTC.RCR3.BIT.RTCEN)
    {
        /* Confirm that the written */
    }

    /* ---- Wait for five sub-clock cycles ---- */
    cmt0_wait((SUB_CLOCK_CYCLE*5/FOR_CMT0_TIME)+1);        /* Wait time is 5 sub-clock cycles (approx. 152 us). */

    /* ---- Setting of the sub-clock drive strength ---- */
    /* RCR3 - RTC Control Register 3
    b7:b4    Reserved - The write value should be 0.
    b3:b1    RTCDV    - Sub-clock Oscillator Drive Ability Control
                      - Drive ability for low CL
    b0       RTCEN    - Sub-clock Control
                      - Sub-clock oscillator is stopped. */
    RTC.RCR3.BYTE = REG_RCR3;

    /* dummy read three times */
    for (i = 0; i < 3; i++)
    {
        dummy = RTC.RCR3.BYTE;
    }

    while (REG_RCR3 != RTC.RCR3.BYTE)
    {
        /* Confirm that the written */
    }

    /* ---- Set wait time until the sub-clock oscillator stabilizes ---- */
    /* SOSCWTCR - Sub-Clock Oscillator Wait Control Register
    b7:b5    Reserved - The write value should be 0.
    b4:b0    SSTS - Sub-Clock Oscillator Waiting Time - Waiting time is 2 s + 2 cycles. */
    SYSTEM.SOSCWTCR.BYTE = REG_SOSCWTCR;    /* Wait time is 2 s + 2 sub-clock cycles (approx. 2 s). */

    /* ---- Operate the Sub-clock oscillator ---- */
    /* SOSCCR - Sub-Clock Oscillator Control Register
    b0       SOSTP    - Sub-clock oscillator Stop - Sub-clock oscillator is running. */
    SYSTEM.SOSCCR.BYTE = 0x00;
    while (0x00 != SYSTEM.SOSCCR.BYTE)
    {
        /* Confirm that the written */
    }

    /* ---- Wait processing for the clock oscillation stabilization ---- */
    cmt0_wait(WAIT_TIME_FOR_SUB_OSCILLATION/FOR_CMT0_TIME+1);      /* oscillation stabilize (4.0s). */

}

/*******************************************************************************
* Outline      : Configure when not using the sub-clock as the system clock
* Header       : none
* Function Name: no_use_subclk_as_sysclk
* Description  : Set the SOSTP bit to 1 (sub-clock stops)
*                when the sub-clock is used only as the RTC count source.
* Arguments    : none
* Return Value : none
*******************************************************************************/
static void no_use_subclk_as_sysclk(void)
{

#if (SEL_RTC == B_USE) && (SEL_SUB != B_USE)

    /* ---- Stop the Sub-clock oscillator ---- */
    /* SOSCCR - Sub-Clock Oscillator Control Register
    b0       SOSTP    - Sub-clock oscillator Stop - Sub-clock oscillator is stopped. */
    SYSTEM.SOSCCR.BYTE = 0x01;
    while (0x01 != SYSTEM.SOSCCR.BYTE)
    {
        /* Confirm that the written value can be read correctly. */
    }

#endif

}

/*******************************************************************************
* Outline      : Set the wait control register
*                (the sub-clock is used as the RTC count source.)
* Header       : none
* Function Name: resetting_wtcr_subclk
* Description  : Set the wait control register when exiting 
*                from the software standby mode.
* Arguments    : none
* Return Value : none
*******************************************************************************/
static void resetting_wtcr_subclk(void)
{

#if (SEL_RTC == B_USE) && (SEL_SUB == B_USE)

    /* ---- Stop the Sub-clock oscillator ---- */
    /* SOSCCR - Sub-Clock Oscillator Control Register
    b0       SOSTP    - Sub-clock oscillator Stop - Sub-clock oscillator is stopped. */
    SYSTEM.SOSCCR.BYTE = 0x01;
    while (0x01 != SYSTEM.SOSCCR.BYTE)
    {
        /* Confirm that the written value can be read correctly. */
    }

    /* ---- Wait for five sub-clock cycles ---- */
    cmt0_wait((SUB_CLOCK_CYCLE*5/FOR_CMT0_TIME)+1);       /* Wait time is five sub-clock cycles (approx. 152 us).*/

    /* ---- Set wait time until the sub-clock oscillator stabilizes ---- */
    /* SOSCWTCR - Sub-Clock Oscillator Wait Control Register
    b4:b0    SSTS - Sub-Clock Oscillator Waiting Time - Waiting time is 2 cycles. */
    SYSTEM.SOSCWTCR.BYTE = 0x00;            /* Wait time is two sub-clock cycles (approx. 61 us).*/

    /* ---- Operate the sub-clock oscillator ---- */
    /* SOSCCR - Sub-Clock Oscillator Control Register
    b0       SOSTP    - Sub-clock oscillator Stop - Sub-clock oscillator is running. */
    SYSTEM.SOSCCR.BYTE = 0x00;              /* Sub-clock oscillator is operating. */
    while (0x00 != SYSTEM.SOSCCR.BYTE)
    {
        /* Confirm that the written value can be read correctly. */
    }

    /* ---- Wait processing for the clock oscillation stabilization ---- */
    cmt0_wait((SUB_CLOCK_CYCLE*2/FOR_CMT0_TIME)+1 );    /* Wait time is two sub-clock cycles (approx. 61 us).*/

#endif

}

/*******************************************************************************
* Outline      : Initialization when using the RTC
* Header       : none
* Function Name: enable_RTC
* Description  : Configure the initialization when using the RTC.
* Arguments    : none
* Return Value : none
*******************************************************************************/
static void enable_RTC(void)
{

#if (SEL_RTC == B_USE)

    uint8_t i;
    volatile uint8_t dummy;

    /* ---- Set RCR3 register ---- */
    /* RCR3 - RTC Control Register 3
    b0       RTCEN    - Sub-clock oscillator is running. */
    RTC.RCR3.BIT.RTCEN = 1;

    /* dummy read three times */
    for (i = 0; i < 3; i++)
    {
         dummy = RTC.RCR3.BIT.RTCEN;
    }

    while (1 != RTC.RCR3.BIT.RTCEN)
    {
         /* Confirm that the written value can be read correctly. */
    }

    /* ---- Wait for six the sub-clock cycles ---- */
    cmt0_wait((SUB_CLOCK_CYCLE*6/FOR_CMT0_TIME)+1);

    /* ---- Stop prescaler and counter ---- */
    /* RCR2 - RTC Control Register 2
    b7       Reserved - The write value should be 0.
    b0       START    - start - Prescaler is stopped. */
    RTC.RCR2.BYTE &= 0x7E;
    while (0 != RTC.RCR2.BIT.START)
    {
        /* Confirm that the written value can be read correctly. */
    }

    /* ---- RTC Software Reset ---- */
    /* RCR2 - RTC Control Register 2
    b1       RESET     - RTC Software Reset
                       - The prescaler and target registers are reset by RTC software reset.*/
    RTC.RCR2.BIT.RESET = 1;
    while (0 != RTC.RCR2.BIT.RESET)
    {
        /* Confirm that the written value can be read correctly. */
    }

#endif

}

/*******************************************************************************
* Outline      : Software wait with CMT0
* Header       : none
* Function Name: cmt0_wait
* Description  : This function is to wait for the oscillation stabilization wait time.
* Arguments    : cnt : Wait for the time specified by an argument multiplied 
*                      by FOR_CMT0_TIME (us).
* Return Value : none
*******************************************************************************/
static void cmt0_wait(uint32_t cnt)
{

    /* ---- Exit the module stop state ---- */
    MSTP(CMT0) = 0;                         /* CMT0 and CMT1 exit the module stop state. */

    /* ---- Stop CMT0 counting ---- */
    /* CMSTR0 - Compare Match Timer Start Register 0
    b15:b2  Reserved  - The write value should be 0.
    b1      STR1      - Count Start 1 - CMT1.CMCNT count is stopped.
    b0      STR0      - Count Start 0 - CMT0.CMCNT count is stopped. */
    CMT.CMSTR0.BIT.STR0 = 0;                /* CMT0 count is stopped. */

    /* ---- Set the CMT0 count source and Enable the CMT0 compare match interrupt ---- */
    /* CMCR - Compare Match Timer Control Register
    b15:b8   Reserved  - The write value should be 0.
    b7       Reserved  - The write value should be 1.
    b6       CMIE      - Compare Match Interrupt Enable - Compare match interrupt enable.
    b5:b2    Reserved  - The write value should be 0.
    b1:b0    CKS       - Clock Select - PCLK/32 */
    CMT0.CMCR.WORD = 0x00C1;

    /* ---- Clear the CMT0 count ---- */
    /* CMCNT - Compare Match Timer Counter */
    CMT0.CMCNT = 0x0000;

    /* ---- Wait time set is other than 0 ? ---- */
    if (0 != cnt)
    {
        /* ---- Decrement the wait time ---- */
        cnt = cnt - 1;
    }

    /* ---- Set the CMT0 wait time ---- */
    /* CMCOR - Compare Match Timer Constant Register */
    CMT0.CMCOR = cnt;

    /* ---- Clear the CMT0 interrupt request ---- */
    while (1 == IR(CMT0,CMI0))
    {
        IR(CMT0,CMI0) = 0;                  /* CMT0.CMI0 interrupt request is cleared. */
    }

    /* ---- Start CMT0 counting ---- */
    /* CMSTR0 - Compare Match Timer Start Register 0
    b0      STR0      - Count Start 0 - CMT0.CMCNT count is started. */
    CMT.CMSTR0.BIT.STR0 = 1;

    /* ---- CMI0 interrupt request generated? ---- */
    while (0 == IR(CMT0,CMI0))
    {

    }

    /* ---- Stop CMT0 counting ---- */
    /* CMSTR0 - Compare Match Timer Start Register 0
    b0      STR0      - Count Start 0 - CMT0.CMCNT count is stopped. */
    CMT.CMSTR0.BIT.STR0 = 0;

    /* ---- Initialize CMT0 ---- */
    /* CMCR - Compare Match Timer Control Register
    b15:b8   Reserved  - The write value should be 0.
    b7       Reserved  - The write value should be 1.
    b6       CMIE      - Compare Match Interrupt Enable - Compare match interrupt disable.
    b5:b2    Reserved  - The write value should be 0.
    b1:b0    CKS       - Clock Select - PCLK/8 */
    CMT0.CMCR.WORD = 0x0080;

    /* CMCNT - Compare Match Timer Counter */
    CMT0.CMCNT = 0x0000;

    /* CMCOR - Compare Match Timer Constant Register */
    CMT0.CMCOR = 0x0000;

    /* Clear IR flag */
    IR(CMT0,CMI0) = 0;

    /* ----Transfer the module stop state ---- */
    MSTP(CMT0) = 1;

}

/* End of File */
