/************************************************************************/
/*    File Version: V1.00                                               */
/*    History    : 1.0A (2013-08-19)  [Hardware Manual Revision : 1.40]  */
/*    Date Generated: 08/19/2013                                        */
/************************************************************************/

#ifndef INTERRUPT_HANDLERS_H
#define INTERRUPT_HANDLERS_H

// Exception(Supervisor Instruction)
void Excep_SuperVisorInst(void) __attribute__ ((interrupt));

// Exception(Undefined Instruction)
void Excep_UndefinedInst(void) __attribute__ ((interrupt));

// NMI
void NonMaskableInterrupt(void) __attribute__ ((interrupt));

// Dummy
void Dummy(void) __attribute__ ((interrupt));

// BRK
void Excep_BRK(void) __attribute__ ((interrupt));

// BSC BUSERR
void Excep_BSC_BUSERR(void) __attribute__ ((interrupt));

// FCU FIFERR
void Excep_FCU_FIFERR(void) __attribute__ ((interrupt));

// FCU FRDYI
void Excep_FCU_FRDYI(void) __attribute__ ((interrupt));

// ICU SWINT
void Excep_ICU_SWINT(void) __attribute__ ((interrupt));

// CMT0 CMI0
void Excep_CMT0_CMI0(void) __attribute__ ((interrupt));

// CMT1 CMI1
void Excep_CMT1_CMI1(void) __attribute__ ((interrupt));

// CMT2 CMI2
void Excep_CMT2_CMI2(void) __attribute__ ((interrupt));

// CMT3 CMI3
void Excep_CMT3_CMI3(void) __attribute__ ((interrupt));

// CAC FERRF
void Excep_CAC_FERRF(void) __attribute__ ((interrupt));

// CAC MENDF
void Excep_CAC_MENDF(void) __attribute__ ((interrupt));

// CAC OVFF
void Excep_CAC_OVFF(void) __attribute__ ((interrupt));

// RSPI0 SPEI0
void Excep_RSPI0_SPEI0(void) __attribute__ ((interrupt));

// RSPI0 SPRI0
void Excep_RSPI0_SPRI0(void) __attribute__ ((interrupt));

// RSPI0 SPTI0
void Excep_RSPI0_SPTI0(void) __attribute__ ((interrupt));

// RSPI0 SPII0
void Excep_RSPI0_SPII0(void) __attribute__ ((interrupt));

// DOC DOPCF
void Excep_DOC_DOPCF(void) __attribute__ ((interrupt));

// CMPB CMPB0
void Excep_CMPB_CMPB0(void) __attribute__ ((interrupt));

// CMPB CMPB1
void Excep_CMPB_CMPB1(void) __attribute__ ((interrupt));

// RTC CUP
void Excep_RTC_CUP(void) __attribute__ ((interrupt));

// ICU IRQ0
void Excep_ICU_IRQ0(void) __attribute__ ((interrupt));

// ICU IRQ1
void Excep_ICU_IRQ1(void) __attribute__ ((interrupt));

// ICU IRQ2
void Excep_ICU_IRQ2(void) __attribute__ ((interrupt));

// ICU IRQ3
void Excep_ICU_IRQ3(void) __attribute__ ((interrupt));

// ICU IRQ4
void Excep_ICU_IRQ4(void) __attribute__ ((interrupt));

// ICU IRQ5
void Excep_ICU_IRQ5(void) __attribute__ ((interrupt));

// ICU IRQ6
void Excep_ICU_IRQ6(void) __attribute__ ((interrupt));

// ICU IRQ7
void Excep_ICU_IRQ7(void) __attribute__ ((interrupt));

// LVD LVD1
void Excep_LVD_LVD1(void) __attribute__ ((interrupt));

// CMPA CMPA1
//void Excep_CMPA_CMPA1(void) __attribute__ ((interrupt));

// LVD LVD2
void Excep_LVD_LVD2(void) __attribute__ ((interrupt));

// CMPA CMPA2
//void Excep_CMPA_CMPA2(void) __attribute__ ((interrupt));

// RTC ALM
void Excep_RTC_ALM(void) __attribute__ ((interrupt));

// RTC PRD
void Excep_RTC_PRD(void) __attribute__ ((interrupt));

// S12AD S12ADI0
void Excep_S12AD_S12ADI0(void) __attribute__ ((interrupt));

// S12AD GBADI
void Excep_S12AD_GBADI(void) __attribute__ ((interrupt));

// ELC ELSR18I
void Excep_ELC_ELSR18I(void) __attribute__ ((interrupt));

// ELC ELSR19I
void Excep_ELC_ELSR19I(void) __attribute__ ((interrupt));

// MTU0 TGIA0
void Excep_MTU0_TGIA0(void) __attribute__ ((interrupt));

// MTU0 TGIB0
void Excep_MTU0_TGIB0(void) __attribute__ ((interrupt));

// MTU0 TGIC0
void Excep_MTU0_TGIC0(void) __attribute__ ((interrupt));

// MTU0 TGID0
void Excep_MTU0_TGID0(void) __attribute__ ((interrupt));

// MTU0 TCIV0
void Excep_MTU0_TCIV0(void) __attribute__ ((interrupt));

// MTU0 TGIE0
void Excep_MTU0_TGIE0(void) __attribute__ ((interrupt));

// MTU0 TGIF0
void Excep_MTU0_TGIF0(void) __attribute__ ((interrupt));

// MTU1 TGIA1
void Excep_MTU1_TGIA1(void) __attribute__ ((interrupt));

// MTU1 TGIB1
void Excep_MTU1_TGIB1(void) __attribute__ ((interrupt));

// MTU1 TCIV1
void Excep_MTU1_TCIV1(void) __attribute__ ((interrupt));

// MTU1 TCIU1
void Excep_MTU1_TCIU1(void) __attribute__ ((interrupt));

// MTU2 TGIA2
void Excep_MTU2_TGIA2(void) __attribute__ ((interrupt));

// MTU2 TGIB2
void Excep_MTU2_TGIB2(void) __attribute__ ((interrupt));

// MTU2 TCIV2
void Excep_MTU2_TCIV2(void) __attribute__ ((interrupt));

// MTU2 TCIU2
void Excep_MTU2_TCIU2(void) __attribute__ ((interrupt));

// MTU3 TGIA3
void Excep_MTU3_TGIA3(void) __attribute__ ((interrupt));

// MTU3 TGIB3
void Excep_MTU3_TGIB3(void) __attribute__ ((interrupt));

// MTU3 TGIC3
void Excep_MTU3_TGIC3(void) __attribute__ ((interrupt));

// MTU3 TGID3
void Excep_MTU3_TGID3(void) __attribute__ ((interrupt));

// MTU3 TCIV3
void Excep_MTU3_TCIV3(void) __attribute__ ((interrupt));

// MTU4 TGIA4
void Excep_MTU4_TGIA4(void) __attribute__ ((interrupt));

// MTU4 TGIB4
void Excep_MTU4_TGIB4(void) __attribute__ ((interrupt));

// MTU4 TGIC4
void Excep_MTU4_TGIC4(void) __attribute__ ((interrupt));

// MTU4 TGID4
void Excep_MTU4_TGID4(void) __attribute__ ((interrupt));

// MTU4 TCIV4
void Excep_MTU4_TCIV4(void) __attribute__ ((interrupt));

// MTU5 TGIU5
void Excep_MTU5_TGIU5(void) __attribute__ ((interrupt));

// MTU5 TGIV5
void Excep_MTU5_TGIV5(void) __attribute__ ((interrupt));

// MTU5 TGIW5
void Excep_MTU5_TGIW5(void) __attribute__ ((interrupt));

// TPU0 TGI0A
void Excep_TPU0_TGI0A(void) __attribute__ ((interrupt));

// TPU0 TGI0B
void Excep_TPU0_TGI0B(void) __attribute__ ((interrupt));

// TPU0 TGI0C
void Excep_TPU0_TGI0C(void) __attribute__ ((interrupt));

// TPU0 TGI0D
void Excep_TPU0_TGI0D(void) __attribute__ ((interrupt));

// TPU0 TCI0V
void Excep_TPU0_TCI0V(void) __attribute__ ((interrupt));

// TPU1 TGI1A
void Excep_TPU1_TGI1A(void) __attribute__ ((interrupt));

// TPU1 TGI1B
void Excep_TPU1_TGI1B(void) __attribute__ ((interrupt));

// TPU1 TCI1V
void Excep_TPU1_TCI1V(void) __attribute__ ((interrupt));

// TPU1 TCI1U
void Excep_TPU1_TCI1U(void) __attribute__ ((interrupt));

// TPU2 TGI2A
void Excep_TPU2_TGI2A(void) __attribute__ ((interrupt));

// TPU2 TGI2B
void Excep_TPU2_TGI2B(void) __attribute__ ((interrupt));

// TPU2 TCI2V
void Excep_TPU2_TCI2V(void) __attribute__ ((interrupt));

// TPU2 TCI2U
void Excep_TPU2_TCI2U(void) __attribute__ ((interrupt));

// TPU3 TGI3A
void Excep_TPU3_TGI3A(void) __attribute__ ((interrupt));

// TPU3 TGI3B
void Excep_TPU3_TGI3B(void) __attribute__ ((interrupt));

// TPU3 TGI3C
void Excep_TPU3_TGI3C(void) __attribute__ ((interrupt));

// TPU3 TGI3D
void Excep_TPU3_TGI3D(void) __attribute__ ((interrupt));

// TPU3 TCI3V
void Excep_TPU3_TCI3V(void) __attribute__ ((interrupt));

// TPU4 TGI4A
void Excep_TPU4_TGI4A(void) __attribute__ ((interrupt));

// TPU4 TGI4B
void Excep_TPU4_TGI4B(void) __attribute__ ((interrupt));

// TPU4 TCI4V
void Excep_TPU4_TCI4V(void) __attribute__ ((interrupt));

// TPU4 TCI4U
void Excep_TPU4_TCI4U(void) __attribute__ ((interrupt));

// TPU5 TGI5A
void Excep_TPU5_TGI5A(void) __attribute__ ((interrupt));

// TPU5 TGI5B
void Excep_TPU5_TGI5B(void) __attribute__ ((interrupt));

// TPU5 TCI5V
void Excep_TPU5_TCI5V(void) __attribute__ ((interrupt));

// TPU5 TCI5U
void Excep_TPU5_TCI5U(void) __attribute__ ((interrupt));

// POE OEI1
void Excep_POE_OEI1(void) __attribute__ ((interrupt));

// POE OEI2
void Excep_POE_OEI2(void) __attribute__ ((interrupt));

// TMR0 CMIA0
void Excep_TMR0_CMIA0(void) __attribute__ ((interrupt));

// TMR0 CMIB0
void Excep_TMR0_CMIB0(void) __attribute__ ((interrupt));

// TMR0 OVI0
void Excep_TMR0_OVI0(void) __attribute__ ((interrupt));

// TMR1 CMIA1
void Excep_TMR1_CMIA1(void) __attribute__ ((interrupt));

// TMR1 CMIB1
void Excep_TMR1_CMIB1(void) __attribute__ ((interrupt));

// TMR1 OVI1
void Excep_TMR1_OVI1(void) __attribute__ ((interrupt));

// TMR2 CMIA2
void Excep_TMR2_CMIA2(void) __attribute__ ((interrupt));

// TMR2 CMIB2
void Excep_TMR2_CMIB2(void) __attribute__ ((interrupt));

// TMR2 OVI2
void Excep_TMR2_OVI2(void) __attribute__ ((interrupt));

// TMR3 CMIA3
void Excep_TMR3_CMIA3(void) __attribute__ ((interrupt));

// TMR3 CMIB3
void Excep_TMR3_CMIB3(void) __attribute__ ((interrupt));

// TMR3 OVI3
void Excep_TMR3_OVI3(void) __attribute__ ((interrupt));

// SCI2 ERI2
void Excep_SCI2_ERI2(void) __attribute__ ((interrupt));

// SCI2 RXI2
void Excep_SCI2_RXI2(void) __attribute__ ((interrupt));

// SCI2 TXI2
void Excep_SCI2_TXI2(void) __attribute__ ((interrupt));

// SCI2 TEI2
void Excep_SCI2_TEI2(void) __attribute__ ((interrupt));

// SCI3 ERI3
void Excep_SCI3_ERI3(void) __attribute__ ((interrupt));

// SCI3 RXI3
void Excep_SCI3_RXI3(void) __attribute__ ((interrupt));

// SCI3 TXI3
void Excep_SCI3_TXI3(void) __attribute__ ((interrupt));

// SCI3 TEI3
void Excep_SCI3_TEI3(void) __attribute__ ((interrupt));

// SCI4 ERI4
void Excep_SCI4_ERI4(void) __attribute__ ((interrupt));

// SCI4 RXI4
void Excep_SCI4_RXI4(void) __attribute__ ((interrupt));

// SCI4 TXI4
void Excep_SCI4_TXI4(void) __attribute__ ((interrupt));

// SCI4 TEI4
void Excep_SCI4_TEI4(void) __attribute__ ((interrupt));

// DMAC DMAC0I
void Excep_DMAC_DMAC0I(void) __attribute__ ((interrupt));

// DMAC DMAC1I
void Excep_DMAC_DMAC1I(void) __attribute__ ((interrupt));

// DMAC DMAC2I
void Excep_DMAC_DMAC2I(void) __attribute__ ((interrupt));

// DMAC DMAC3I
void Excep_DMAC_DMAC3I(void) __attribute__ ((interrupt));

// SCI7 ERI7
void Excep_SCI7_ERI7(void) __attribute__ ((interrupt));

// SCI7 RXI7
void Excep_SCI7_RXI7(void) __attribute__ ((interrupt));

// SCI7 TXI7
void Excep_SCI7_TXI7(void) __attribute__ ((interrupt));

// SCI7 TEI7
void Excep_SCI7_TEI7(void) __attribute__ ((interrupt));

// SCI10 ERI10
void Excep_SCI10_ERI10(void) __attribute__ ((interrupt));

// SCI10 RXI10
void Excep_SCI10_RXI10(void) __attribute__ ((interrupt));

// SCI10 TXI10
void Excep_SCI10_TXI10(void) __attribute__ ((interrupt));

// SCI10 TEI10
void Excep_SCI10_TEI10(void) __attribute__ ((interrupt));

// SCI0 ERI0
void Excep_SCI0_ERI0(void) __attribute__ ((interrupt));

// SCI0 RXI0
void Excep_SCI0_RXI0(void) __attribute__ ((interrupt));

// SCI0 TXI0
void Excep_SCI0_TXI0(void) __attribute__ ((interrupt));

// SCI0 TEI0
void Excep_SCI0_TEI0(void) __attribute__ ((interrupt));

// SCI1 ERI1
void Excep_SCI1_ERI1(void) __attribute__ ((interrupt));

// SCI1 RXI1
void Excep_SCI1_RXI1(void) __attribute__ ((interrupt));

// SCI1 TXI1
void Excep_SCI1_TXI1(void) __attribute__ ((interrupt));

// SCI1 TEI1
void Excep_SCI1_TEI1(void) __attribute__ ((interrupt));

// SCI5 ERI5
void Excep_SCI5_ERI5(void) __attribute__ ((interrupt));

// SCI5 RXI5
void Excep_SCI5_RXI5(void) __attribute__ ((interrupt));

// SCI5 TXI5
void Excep_SCI5_TXI5(void) __attribute__ ((interrupt));

// SCI5 TEI5
void Excep_SCI5_TEI5(void) __attribute__ ((interrupt));

// SCI6 ERI6
void Excep_SCI6_ERI6(void) __attribute__ ((interrupt));

// SCI6 RXI6
void Excep_SCI6_RXI6(void) __attribute__ ((interrupt));

// SCI6 TXI6
void Excep_SCI6_TXI6(void) __attribute__ ((interrupt));

// SCI6 TEI6
void Excep_SCI6_TEI6(void) __attribute__ ((interrupt));

// SCI8 ERI8
void Excep_SCI8_ERI8(void) __attribute__ ((interrupt));

// SCI8 RXI8
void Excep_SCI8_RXI8(void) __attribute__ ((interrupt));

// SCI8 TXI8
void Excep_SCI8_TXI8(void) __attribute__ ((interrupt));

// SCI8 TEI8
void Excep_SCI8_TEI8(void) __attribute__ ((interrupt));

// SCI9 ERI9
void Excep_SCI9_ERI9(void) __attribute__ ((interrupt));

// SCI9 RXI9
void Excep_SCI9_RXI9(void) __attribute__ ((interrupt));

// SCI9 TXI9
void Excep_SCI9_TXI9(void) __attribute__ ((interrupt));

// SCI9 TEI9
void Excep_SCI9_TEI9(void) __attribute__ ((interrupt));

// SCI12 ERI12
void Excep_SCI12_ERI12(void) __attribute__ ((interrupt));

// SCI12 RXI12
void Excep_SCI12_RXI12(void) __attribute__ ((interrupt));

// SCI12 TXI12
void Excep_SCI12_TXI12(void) __attribute__ ((interrupt));

// SCI12 TEI12
void Excep_SCI12_TEI12(void) __attribute__ ((interrupt));

// SCI12 SCIX0
void Excep_SCI12_SCIX0(void) __attribute__ ((interrupt));

// SCI12 SCIX1
void Excep_SCI12_SCIX1(void) __attribute__ ((interrupt));

// SCI12 SCIX2
void Excep_SCI12_SCIX2(void) __attribute__ ((interrupt));

// SCI12 SCIX3
void Excep_SCI12_SCIX3(void) __attribute__ ((interrupt));

// RIIC0 EEI0
void Excep_RIIC0_EEI0(void) __attribute__ ((interrupt));

// RIIC0 RXI0
void Excep_RIIC0_RXI0(void) __attribute__ ((interrupt));

// RIIC0 TXI0
void Excep_RIIC0_TXI0(void) __attribute__ ((interrupt));

// RIIC0 TEI0
void Excep_RIIC0_TEI0(void) __attribute__ ((interrupt));

// SCI11 ERI11
void Excep_SCI11_ERI11(void) __attribute__ ((interrupt));

// SCI11 RXI11
void Excep_SCI11_RXI11(void) __attribute__ ((interrupt));

// SCI11 TXI11
void Excep_SCI11_TXI11(void) __attribute__ ((interrupt));

// SCI11 TEI11
void Excep_SCI11_TEI11(void) __attribute__ ((interrupt));

//;<<VECTOR DATA START (POWER ON RESET)>>
//;Power On Reset PC
extern void PowerON_Reset(void) __attribute__ ((interrupt));
//;<<VECTOR DATA END (POWER ON RESET)>>

#endif
