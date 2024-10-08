/************************************************************************/
/*    File Version: V1.00                                               */
/*   History    : 1.0A (2013-08-19)  [Hardware Manual Revision : 1.40]  */
/*    Date Generated: 08/19/2013                                        */
/************************************************************************/

#include "interrupt_handlers.h"

#include "iodefine.h"

static volatile unsigned int jiffies = 0;

// Exception(Supervisor Instruction)
void Excep_SuperVisorInst(void) {  }

// Exception(Undefined Instruction)
void Excep_UndefinedInst(void) {  }

// NMI
void NonMaskableInterrupt(void) {  }

// Dummy
void Dummy(void) {  }

// BRK
void Excep_BRK(void) {  }

// BSC BUSERR
void Excep_BSC_BUSERR(void) {  }

// FCU FIFERR
void Excep_FCU_FIFERR(void) {  }

// FCU FRDYI
void Excep_FCU_FRDYI(void) {  }

// ICU SWINT
void Excep_ICU_SWINT(void) {  }

// CMT0 CMI0
void Excep_CMT0_CMI0(void) {
    ++jiffies;
    mrbc_tick();
}

// CMT1 CMI1
void Excep_CMT1_CMI1(void) {  }

// CMT2 CMI2
void Excep_CMT2_CMI2(void) {  }

// CMT3 CMI3
void Excep_CMT3_CMI3(void) {  }

// CAC FERRF
void Excep_CAC_FERRF(void) {  }

// CAC MENDF
void Excep_CAC_MENDF(void) {  }

// CAC OVFF
void Excep_CAC_OVFF(void) {  }

// RSPI0 SPEI0
void Excep_RSPI0_SPEI0(void) {  }

// RSPI0 SPRI0
void Excep_RSPI0_SPRI0(void) {  }

// RSPI0 SPTI0
void Excep_RSPI0_SPTI0(void) {  }

// RSPI0 SPII0
void Excep_RSPI0_SPII0(void) {  }

// DOC DOPCF
void Excep_DOC_DOPCF(void) {  }

// CMPB CMPB0
void Excep_CMPB_CMPB0(void) {  }

// CMPB CMPB1
void Excep_CMPB_CMPB1(void) {  }

// RTC CUP
void Excep_RTC_CUP(void) {  }

// ICU IRQ0
void Excep_ICU_IRQ0(void) {  }

// ICU IRQ1
void Excep_ICU_IRQ1(void) {  }

// ICU IRQ2
void Excep_ICU_IRQ2(void) {  }

// ICU IRQ3
void Excep_ICU_IRQ3(void) {  }

// ICU IRQ4
void Excep_ICU_IRQ4(void) {  }

// ICU IRQ5
void Excep_ICU_IRQ5(void) {  }

// ICU IRQ6
void Excep_ICU_IRQ6(void) {  }

// ICU IRQ7
void Excep_ICU_IRQ7(void) {  }

// LVD LVD1
void Excep_LVD_LVD1(void) {  }

// CMPA CMPA1
//#pragma interrupt _CMPA_CMPA1(vect=88))
//void Excep_CMPA_CMPA1(void) {  }

// LVD LVD2
void Excep_LVD_LVD2(void) {  }

// CMPA CMPA2
//#pragma interrupt _CMPA_CMPA2(vect=89))
//void Excep_CMPA_CMPA2(void) {  }

// RTC ALM
void Excep_RTC_ALM(void) {  }

// RTC PRD
void Excep_RTC_PRD(void) {  }

// S12AD S12ADI0
void Excep_S12AD_S12ADI0(void) {  }

// S12AD GBADI
void Excep_S12AD_GBADI(void) {  }

// ELC ELSR18I
void Excep_ELC_ELSR18I(void) {  }

// ELC ELSR19I
void Excep_ELC_ELSR19I(void) {  }

// MTU0 TGIA0
void Excep_MTU0_TGIA0(void) {  }

// MTU0 TGIB0
void Excep_MTU0_TGIB0(void) {  }

// MTU0 TGIC0
void Excep_MTU0_TGIC0(void) {  }

// MTU0 TGID0
void Excep_MTU0_TGID0(void) {  }

// MTU0 TCIV0
void Excep_MTU0_TCIV0(void) {  }

// MTU0 TGIE0
void Excep_MTU0_TGIE0(void) {  }

// MTU0 TGIF0
void Excep_MTU0_TGIF0(void) {  }

// MTU1 TGIA1
void Excep_MTU1_TGIA1(void) {  }

// MTU1 TGIB1
void Excep_MTU1_TGIB1(void) {  }

// MTU1 TCIV1
void Excep_MTU1_TCIV1(void) {  }

// MTU1 TCIU1
void Excep_MTU1_TCIU1(void) {  }

// MTU2 TGIA2
void Excep_MTU2_TGIA2(void) {  }

// MTU2 TGIB2
void Excep_MTU2_TGIB2(void) {  }

// MTU2 TCIV2
void Excep_MTU2_TCIV2(void) {  }

// MTU2 TCIU2
void Excep_MTU2_TCIU2(void) {  }

// MTU3 TGIA3
void Excep_MTU3_TGIA3(void) {  }

// MTU3 TGIB3
void Excep_MTU3_TGIB3(void) {  }

// MTU3 TGIC3
void Excep_MTU3_TGIC3(void) {  }

// MTU3 TGID3
void Excep_MTU3_TGID3(void) {  }

// MTU3 TCIV3
void Excep_MTU3_TCIV3(void) {  }

// MTU4 TGIA4
void Excep_MTU4_TGIA4(void) {  }

// MTU4 TGIB4
void Excep_MTU4_TGIB4(void) {  }

// MTU4 TGIC4
void Excep_MTU4_TGIC4(void) {  }

// MTU4 TGID4
void Excep_MTU4_TGID4(void) {  }

// MTU4 TCIV4
void Excep_MTU4_TCIV4(void) {  }

// MTU5 TGIU5
void Excep_MTU5_TGIU5(void) {  }

// MTU5 TGIV5
void Excep_MTU5_TGIV5(void) {  }

// MTU5 TGIW5
void Excep_MTU5_TGIW5(void) {  }

// TPU0 TGI0A
void Excep_TPU0_TGI0A(void) {  }

// TPU0 TGI0B
void Excep_TPU0_TGI0B(void) {  }

// TPU0 TGI0C
void Excep_TPU0_TGI0C(void) {  }

// TPU0 TGI0D
void Excep_TPU0_TGI0D(void) {  }

// TPU0 TCI0V
void Excep_TPU0_TCI0V(void) {  }

// TPU1 TGI1A
void Excep_TPU1_TGI1A(void) {  }

// TPU1 TGI1B
void Excep_TPU1_TGI1B(void) {  }

// TPU1 TCI1V
void Excep_TPU1_TCI1V(void) {  }

// TPU1 TCI1U
void Excep_TPU1_TCI1U(void) {  }

// TPU2 TGI2A
void Excep_TPU2_TGI2A(void) {  }

// TPU2 TGI2B
void Excep_TPU2_TGI2B(void) {  }

// TPU2 TCI2V
void Excep_TPU2_TCI2V(void) {  }

// TPU2 TCI2U
void Excep_TPU2_TCI2U(void) {  }

// TPU3 TGI3A
void Excep_TPU3_TGI3A(void) {  }

// TPU3 TGI3B
void Excep_TPU3_TGI3B(void) {  }

// TPU3 TGI3C
void Excep_TPU3_TGI3C(void) {  }

// TPU3 TGI3D
void Excep_TPU3_TGI3D(void) {  }

// TPU3 TCI3V
void Excep_TPU3_TCI3V(void) {  }

// TPU4 TGI4A
void Excep_TPU4_TGI4A(void) {  }

// TPU4 TGI4B
void Excep_TPU4_TGI4B(void) {  }

// TPU4 TCI4V
void Excep_TPU4_TCI4V(void) {  }

// TPU4 TCI4U
void Excep_TPU4_TCI4U(void) {  }

// TPU5 TGI5A
void Excep_TPU5_TGI5A(void) {  }

// TPU5 TGI5B
void Excep_TPU5_TGI5B(void) {  }

// TPU5 TCI5V
void Excep_TPU5_TCI5V(void) {  }

// TPU5 TCI5U
void Excep_TPU5_TCI5U(void) {  }

// POE OEI1
void Excep_POE_OEI1(void) {  }

// POE OEI2
void Excep_POE_OEI2(void) {  }

// TMR0 CMIA0
void Excep_TMR0_CMIA0(void) {  }

// TMR0 CMIB0
void Excep_TMR0_CMIB0(void) {  }

// TMR0 OVI0
void Excep_TMR0_OVI0(void) {  }

// TMR1 CMIA1
void Excep_TMR1_CMIA1(void) {  }

// TMR1 CMIB1
void Excep_TMR1_CMIB1(void) {  }

// TMR1 OVI1
void Excep_TMR1_OVI1(void) {  }

// TMR2 CMIA2
void Excep_TMR2_CMIA2(void) {  }

// TMR2 CMIB2
void Excep_TMR2_CMIB2(void) {  }

// TMR2 OVI2
void Excep_TMR2_OVI2(void) {  }

// TMR3 CMIA3
void Excep_TMR3_CMIA3(void) {  }

// TMR3 CMIB3
void Excep_TMR3_CMIB3(void) {  }

// TMR3 OVI3
void Excep_TMR3_OVI3(void) {  }

// SCI2 ERI2
void Excep_SCI2_ERI2(void) {  }

// SCI2 RXI2
void Excep_SCI2_RXI2(void) {  }

// SCI2 TXI2
void Excep_SCI2_TXI2(void) {  }

// SCI2 TEI2
void Excep_SCI2_TEI2(void) {  }

// SCI3 ERI3
void Excep_SCI3_ERI3(void) {  }

// SCI3 RXI3
void Excep_SCI3_RXI3(void) {  }

// SCI3 TXI3
void Excep_SCI3_TXI3(void) {  }

// SCI3 TEI3
void Excep_SCI3_TEI3(void) {  }

// SCI4 ERI4
void Excep_SCI4_ERI4(void) {  }

// SCI4 RXI4
void Excep_SCI4_RXI4(void) {  }

// SCI4 TXI4
void Excep_SCI4_TXI4(void) {  }

// SCI4 TEI4
void Excep_SCI4_TEI4(void) {  }

// DMAC DMAC0I
void Excep_DMAC_DMAC0I(void) {  }

// DMAC DMAC1I
void Excep_DMAC_DMAC1I(void) {  }

// DMAC DMAC2I
void Excep_DMAC_DMAC2I(void) {  }

// DMAC DMAC3I
void Excep_DMAC_DMAC3I(void) {  }

// SCI7 ERI7
void Excep_SCI7_ERI7(void) {  }

// SCI7 RXI7
void Excep_SCI7_RXI7(void) {  }

// SCI7 TXI7
void Excep_SCI7_TXI7(void) {  }

// SCI7 TEI7
void Excep_SCI7_TEI7(void) {  }

// SCI10 ERI10
void Excep_SCI10_ERI10(void) {  }

// SCI10 RXI10
void Excep_SCI10_RXI10(void) {  }

// SCI10 TXI10
void Excep_SCI10_TXI10(void) {  }

// SCI10 TEI10
void Excep_SCI10_TEI10(void) {  }

// SCI0 ERI0
void Excep_SCI0_ERI0(void) {  }

// SCI0 RXI0
void Excep_SCI0_RXI0(void) {  }

// SCI0 TXI0
void Excep_SCI0_TXI0(void) {  }

// SCI0 TEI0
void Excep_SCI0_TEI0(void) {  }

// SCI1 ERI1
void Excep_SCI1_ERI1(void) {  }

// SCI1 RXI1
void Excep_SCI1_RXI1(void) {  }

// SCI1 TXI1
void Excep_SCI1_TXI1(void) {  }

// SCI1 TEI1
void Excep_SCI1_TEI1(void) {  }

// SCI5 ERI5
void Excep_SCI5_ERI5(void) {  }

// SCI5 RXI5
void Excep_SCI5_RXI5(void) {  }

// SCI5 TXI5
void Excep_SCI5_TXI5(void) {  }

// SCI5 TEI5
void Excep_SCI5_TEI5(void) {  }

// SCI6 ERI6
void Excep_SCI6_ERI6(void) {  }

// SCI6 RXI6
void Excep_SCI6_RXI6(void) {  }

// SCI6 TXI6
void Excep_SCI6_TXI6(void) {  }

// SCI6 TEI6
void Excep_SCI6_TEI6(void) {  }

// SCI8 ERI8
void Excep_SCI8_ERI8(void) {  }

// SCI8 RXI8
void Excep_SCI8_RXI8(void) {  }

// SCI8 TXI8
void Excep_SCI8_TXI8(void) {  }

// SCI8 TEI8
void Excep_SCI8_TEI8(void) {  }

// SCI9 ERI9
void Excep_SCI9_ERI9(void) {  }

// SCI9 RXI9
void Excep_SCI9_RXI9(void) {  }

// SCI9 TXI9
void Excep_SCI9_TXI9(void) {  }

// SCI9 TEI9
void Excep_SCI9_TEI9(void) {  }

// SCI12 ERI12
void Excep_SCI12_ERI12(void) {  }

// SCI12 RXI12
void Excep_SCI12_RXI12(void) {  }

// SCI12 TXI12
void Excep_SCI12_TXI12(void) {  }

// SCI12 TEI12
void Excep_SCI12_TEI12(void) {  }

// SCI12 SCIX0
void Excep_SCI12_SCIX0(void) {  }

// SCI12 SCIX1
void Excep_SCI12_SCIX1(void) {  }

// SCI12 SCIX2
void Excep_SCI12_SCIX2(void) {  }

// SCI12 SCIX3
void Excep_SCI12_SCIX3(void) {  }

// RIIC0 EEI0
void Excep_RIIC0_EEI0(void) {  }

// RIIC0 RXI0
void Excep_RIIC0_RXI0(void) {  }

// RIIC0 TXI0
void Excep_RIIC0_TXI0(void) {  }

// RIIC0 TEI0
void Excep_RIIC0_TEI0(void) {  }

// SCI11 ERI11
void Excep_SCI11_ERI11(void) {  }

// SCI11 RXI11
void Excep_SCI11_RXI11(void) {  }

// SCI11 TXI11
void Excep_SCI11_TXI11(void) {  }

// SCI11 TEI11
void Excep_SCI11_TEI11(void) {  }

delay_ms(int msec)
{
int start;

	start = jiffies;

	while (jiffies < start + msec)
		;
}
