/************************************************************************/
/*    File Version: V1.00                                               */
/*    Date Generated: 08/07/2013                                        */
/************************************************************************/

#include "iodefine.h"
#include "util.h"
#ifdef __cplusplus
extern "C" {
#endif
extern void HardwareSetup(void);
#ifdef __cplusplus
}
#endif

#define PCLK  (48 * 1000 * 1000)
#define TicksForMillis (PCLK / 8 / 1000)

void InitTimer( void )
{

	startModule(MstpIdCMT0);

	CMT.CMSTR0.BIT.STR0 = 0;

	CMT0.CMCNT = 0;
	CMT0.CMCOR = TicksForMillis - 1;

	IPR(CMT0, CMI0) = 1;
	IEN(CMT0, CMI0) = 1;
	IR(CMT0, CMI0) = 0;

	struct st_cmt0_cmcr cmcr;
	cmcr.WORD = 0;
	cmcr.BIT.CKS = 0b00;	// PCLK/8
	cmcr.BIT.CMIE = 1;	// compare match interrupt enable
	cmcr.BIT.b7 = 1;
	CMT0.CMCR.WORD = cmcr.WORD;

	CMT.CMSTR0.BIT.STR0 = 1;
}

void HardwareSetup(void)
{
int i;

    // Protection off
    SYSTEM.PRCR.WORD = 0xA503u;

    // Stop sub-clock
    SYSTEM.SOSCCR.BYTE = 0x01u;

    // Set main oscillator settling time to 10ms (131072 cycles @ 12MHz)
    SYSTEM.MOSCWTCR.BYTE = 0x0Du;

    // Set PLL circuit settling time to 10ms (2097152 cycles @ 192MHz)
    SYSTEM.PLLWTCR.BYTE = 0x0Eu;

    // Set PLL circuit to x16
    SYSTEM.PLLCR.WORD = 0x0F00u;

    // Start the external 12Mhz oscillator
    SYSTEM.MOSCCR.BYTE = 0x00u;

    // Turn on the PLL
    SYSTEM.PLLCR2.BYTE = 0x00u;

    // Wait over 12ms (~2075op/s @ 125KHz)
    for(i = 0; i < 2075u; i++)
    {
        __asm("nop");
    }

    // Configure the clocks as follows -
    //Clock Description              Frequency
    //----------------------------------------
    //PLL Clock frequency...............192MHz
    //System Clock Frequency.............96MHz
    //Peripheral Module Clock B..........48MHz
    //FlashIF Clock......................48MHz
    //External Bus Clock.................48MHz
    SYSTEM.SCKCR.LONG = 0x21021211u;

    // Configure the clocks as follows -
    //Clock Description              Frequency
    //----------------------------------------
    //USB Clock..........................48MHz
    //IEBus Clock........................24MHz
    SYSTEM.SCKCR2.WORD = 0x0033u;

    // Set the clock source to PLL
    SYSTEM.SCKCR3.WORD = 0x0400u;

    // Stop external bus
    SYSTEM.SYSCR0.WORD  = 0x5A01;

    //EtherC, EDMAC
    SYSTEM.MSTPCRB.BIT.MSTPB15 = 0;

#ifndef __RX600__
    // Protection on
    SYSTEM.PRCR.WORD = 0xA500u;
#else
    // Enable the PFSWE midification.
    MPC.PWPR.BIT.B0WI = 0;

    // Disable the PFS register protect.
    MPC.PWPR.BIT.PFSWE = 1;
#endif

/*
 BSC.CS0MOD.WORD = 0x1234;
 BSC.CS7CNT.WORD = 0x5678;
  
 SCI0.SCR.BIT.TE  = 0;
 SCI0.SCR.BIT.RE  = 0;
 SCI0.SCR.BIT.TE  = 1;
 SCI2.SSR.BIT.PER = 0;

 TMR0.TCR.BYTE = 0x12;
 TMR1.TCR.BYTE = 0x12;
 TMR2.TCR.BYTE = 0x12;
 
 P0.DDR.BYTE = 0x12;
 P1.DDR.BYTE = 0x12;
*/
}
