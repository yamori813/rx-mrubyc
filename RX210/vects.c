/************************************************************************/
/*    File Version: V1.00                                               */
/*    History    : 1.0A (2013-08-19)  [Hardware Manual Revision : 1.40]  */
/*    Date Generated: 08/19/2013                                        */
/************************************************************************/

#include "interrupt_handlers.h"

typedef void (*fp) (void);
extern void PowerON_Reset (void);
extern void stack (void);

#define FVECT_SECT __attribute__ ((section (".fvectors")))

const void *HardwareVectors[] FVECT_SECT  = {
//;0xffffff80  MDES  Endian Select Register
#ifdef __RX_LITTLE_ENDIAN__ 
(fp)0xffffffff,
#endif
#ifdef __RX_BIG_ENDIAN__ 
(fp)0xfffffff8,
#endif
//;0xffffff84  Reserved
    (fp)0,
//;0xffffff88  OFS1
    (fp)0xffffffff,
//;0xffffff8C  OFS0
    (fp)0xffffffff,
//;0xffffff90  Reserved
    (fp)0,
//;0xffffff94  Reserved
    (fp)0,
//;0xffffff98  Reserved
    (fp)0,
//;0xffffff9C  Reserved
    (fp)0,
//;0xffffffA0  Reserved
    (fp)0xffffffff,
//;0xffffffA4  Reserved
    (fp)0xffffffff,
//;0xffffffA8  Reserved
    (fp)0xffffffff,
//;0xffffffAC  Reserved
    (fp)0xffffffff,
//;0xffffffB0  Reserved
    (fp)0,
//;0xffffffB4  Reserved
    (fp)0,
//;0xffffffB8  Reserved
    (fp)0,
//;0xffffffBC  Reserved
    (fp)0,
//;0xffffffC0  Reserved
    (fp)0,
//;0xffffffC4  Reserved
    (fp)0,
//;0xffffffC8  Reserved
    (fp)0,
//;0xffffffCC  Reserved
    (fp)0,
//;0xffffffd0  Exception(Supervisor Instruction)
    Excep_SuperVisorInst,
//;0xffffffd4  Reserved
    (fp)0,
//;0xffffffd8  Reserved
    (fp)0,
//;0xffffffdc  Exception(Undefined Instruction)
    Excep_UndefinedInst,
//;0xffffffe0  Reserved
    (fp)0,
//;0xffffffe4  Reserved
    (fp)0,
//;0xffffffe8  Reserved
    (fp)0,
//;0xffffffec  Reserved
    (fp)0,
//;0xfffffff0  Reserved
    (fp)0,
//;0xfffffff4  Reserved
    (fp)0,
//;0xfffffff8  NMI
    NonMaskableInterrupt,
//;0xfffffffc  RESET
//;<<VECTOR DATA START (POWER ON RESET)>>
//;Power On Reset PC
    /*(void*)*/ PowerON_Reset
//;<<VECTOR DATA END (POWER ON RESET)>>
};

#define RVECT_SECT          __attribute__ ((section (".rvectors")))

const fp RelocatableVectors[] RVECT_SECT  = {
//;0x0000  Reserved
    (fp)0,
//;0x0004  Reserved
    (fp)0,
//;0x0008  Reserved
    (fp)0,
//;0x000C  Reserved
    (fp)0,
//;0x0010  Reserved
    (fp)0,
//;0x0014  Reserved
    (fp)0,
//;0x0018  Reserved
    (fp)0,
//;0x001C  Reserved
    (fp)0,
//;0x0020  Reserved
    (fp)0,
//;0x0024  Reserved
    (fp)0,
//;0x0028  Reserved
    (fp)0,
//;0x002C  Reserved
    (fp)0,
//;0x0030  Reserved
    (fp)0,
//;0x0034  Reserved
    (fp)0,
//;0x0038  Reserved
    (fp)0,
//;0x003C  Reserved
    (fp)0,
//;0x0040  BUSERR
    Excep_BSC_BUSERR,
//;0x0044  Reserved
    (fp)0,
//;0x0048  Reserved
    (fp)0,
//;0x004C  Reserved
    (fp)0,
//;0x0050  Reserved
    (fp)0,
//;0x0054  FCU FIFERR
    Excep_FCU_FIFERR,
//0x0058  Reserved
    (fp)0,
//;0x005C FCU FRDYI
    Excep_FCU_FRDYI,
//;0x0060  Reserved
    (fp)0,
//;0x0064  Reserved
    (fp)0,    
//;0x0068  Reserved
    (fp)0,
//;0x006C ICU SWINT
    Excep_ICU_SWINT,
//;0x0070 CMT0 CMI0
    Excep_CMT0_CMI0,
//;0x0074 CMT1 CMI1
    Excep_CMT1_CMI1,
//;0x0078 CMT2 CMI2
    Excep_CMT2_CMI2,
//;0x007C CMT3 CMI3
    Excep_CMT3_CMI3,
//;0x0080 CAC FERRF
    Excep_CAC_FERRF,
//;0x0084 CAC MENDF
    Excep_CAC_MENDF,
//;0x0088 CAC OVFF
    Excep_CAC_OVFF,
//;0x008C  Reserved
    (fp)0,
//;0x0090  Reserved
    (fp)0,
//;0x0094  Reserved
    (fp)0,
//;0x0098  Reserved
    (fp)0,
//;0x009C  Reserved
    (fp)0,
//;0x00A0  Reserved
    (fp)0,
//;0x00A4  Reserved
    (fp)0,
//;0x00A8  Reserved
    (fp)0,
//;0x00AC  Reserved
    (fp)0,
//;0x00B0 RSPI0 SPEI0
    Excep_RSPI0_SPEI0,
//;0x00B4 RSPI0 SPRI0
    Excep_RSPI0_SPRI0,
//;0x00B8 RSPI0 SPTI0
    Excep_RSPI0_SPTI0,
//;0x00BC RSPI0 SPII0
    Excep_RSPI0_SPII0,
//;0x00A0  Reserved
    (fp)0,
//;0x00A4  Reserved
    (fp)0,
//;0x00A8  Reserved
    (fp)0,
//;0x00AC  Reserved
    (fp)0,
//;0x00A0  Reserved
    (fp)0,
//;0x00A4  Reserved
    (fp)0,
//;0x00A8  Reserved
    (fp)0,
//;0x00AC  Reserved
    (fp)0,
//;0x00AC  Reserved
    (fp)0,
//;0x00E4 DOC DOPCF
    Excep_DOC_DOPCF,

// CMPB CMPB0
    Excep_CMPB_CMPB0,

// CMPB CMPB1
    Excep_CMPB_CMPB1,
//;0x00F0  Reserved
    (fp)0,
//;0x00F4  Reserved
    (fp)0,
//;0x00F8  Reserved
    (fp)0,
// RTC CUP
    Excep_RTC_CUP,

// ICU IRQ0
    Excep_ICU_IRQ0,

// ICU IRQ1
    Excep_ICU_IRQ1,

// ICU IRQ2
    Excep_ICU_IRQ2,

// ICU IRQ3
    Excep_ICU_IRQ3,

// ICU IRQ4
    Excep_ICU_IRQ4,

// ICU IRQ5
    Excep_ICU_IRQ5,

// ICU IRQ6
    Excep_ICU_IRQ6,

// ICU IRQ7
    Excep_ICU_IRQ7,
//;0x0120  Reserved
    (fp)0,
//;0x0124  Reserved
    (fp)0,
//;0x0128  Reserved
    (fp)0,
//;0x012C  Reserved
    (fp)0,
//;0x0130  Reserved
    (fp)0,
//;0x0134  Reserved
    (fp)0,
//;0x0138  Reserved
    (fp)0,
//;0x013C  Reserved
    (fp)0,
//;0x0140  Reserved
    (fp)0,
//;0x0144  Reserved
    (fp)0,
//;0x0148  Reserved
    (fp)0,
//;0x014C  Reserved
    (fp)0,
//;0x0150  Reserved
    (fp)0,
//;0x0154  Reserved
    (fp)0,
//;0x0158  Reserved
    (fp)0,
//;0x015C  Reserved
    (fp)0,    
// LVD LVD1
    Excep_LVD_LVD1,
// LVD LVD2
    Excep_LVD_LVD2,
//;0x00A8  Reserved
    (fp)0,
//;0x00AC  Reserved
    (fp)0,
 // RTC ALM
    Excep_RTC_ALM,

// RTC PRD
    Excep_RTC_PRD,
 //;0x0178  Reserved
    (fp)0,
//;0x017C  Reserved
    (fp)0,
//;0x0180  Reserved
    (fp)0,
//;0x0184  Reserved
    (fp)0,
//;0x0188  Reserved
    (fp)0,
//;0x018C  Reserved
    (fp)0,
//;0x0190  Reserved
    (fp)0,
//;0x0194  Reserved
    (fp)0,
// S12AD S12ADI0
    Excep_S12AD_S12ADI0,

// S12AD GBADI
    Excep_S12AD_GBADI,
//104;0x01A0  Reserved 
    (fp)0,
//105;0x01A4  Reserved 
    (fp)0,
// ELC ELSR18I
    Excep_ELC_ELSR18I,

// ELC ELSR19I
    Excep_ELC_ELSR19I,
//;0x01B0  Reserved
    (fp)0,
//;0x01B4  Reserved
    (fp)0,
//;0x01B8  Reserved
    (fp)0,
//;0x01BC  Reserved
    (fp)0,
//;0x01C0  Reserved
    (fp)0,
//;0x01C4  Reserved
    (fp)0, 
// MTU0 TGIA0
    Excep_MTU0_TGIA0,

// MTU0 TGIB0
    Excep_MTU0_TGIB0,

// MTU0 TGIC0
    Excep_MTU0_TGIC0,

// MTU0 TGID0
    Excep_MTU0_TGID0,

// MTU0 TCIV0
    Excep_MTU0_TCIV0,

// MTU0 TGIE0
    Excep_MTU0_TGIE0,

// MTU0 TGIF0
    Excep_MTU0_TGIF0,

// MTU1 TGIA1
    Excep_MTU1_TGIA1,

// MTU1 TGI1B
    Excep_MTU1_TGIB1,

// MTU1 TCI1V
    Excep_MTU1_TCIV1,

// MTU1 TCI1U
    Excep_MTU1_TCIU1,

// MTU2 TGI2A
    Excep_MTU2_TGIA2,

// MTU2 TGI2B
    Excep_MTU2_TGIB2,

// MTU2 TCI2V
    Excep_MTU2_TCIV2,

// MTU2 TCI2U
    Excep_MTU2_TCIU2,

// MTU3 TGI3A
    Excep_MTU3_TGIA3,

// MTU3 TGI3B
    Excep_MTU3_TGIB3,

// MTU3 TGI3C
    Excep_MTU3_TGIC3,

// MTU3 TGI3D
    Excep_MTU3_TGID3,

// MTU3 TCI3V
    Excep_MTU3_TCIV3,

// MTU4 TGI4A
    Excep_MTU4_TGIA4,

// MTU4 TGI4B
    Excep_MTU4_TGIB4,

// MTU4 TGI4C
    Excep_MTU4_TGIC4,

// MTU4 TGI4D
    Excep_MTU4_TGID4,

// MTU4 TCI4V
    Excep_MTU4_TCIV4,

// MTU5 TGI5U
    Excep_MTU5_TGIU5,

// MTU5 TGI5V
    Excep_MTU5_TGIV5,

// MTU5 TGI5W
    Excep_MTU5_TGIW5,

// TPU0 TGI0A
    Excep_TPU0_TGI0A,

// TPU0 TGI0B
    Excep_TPU0_TGI0B,

// TPU0 TGI0C
    Excep_TPU0_TGI0C,

// TPU0 TGI0D
    Excep_TPU0_TGI0D,

// TPU0 TCI0V
    Excep_TPU0_TCI0V,

// TPU1 TGI1A
    Excep_TPU1_TGI1A,

// TPU1 TGI1B
    Excep_TPU1_TGI1B,

// TPU1 TCI1V
    Excep_TPU1_TCI1V,

// TPU1 TCI1U
    Excep_TPU1_TCI1U,

// TPU2 TGI2A
    Excep_TPU2_TGI2A,

// TPU2 TGI2B
    Excep_TPU2_TGI2B,

// TPU2 TCI2V
    Excep_TPU2_TCI2V,

// TPU2 TCI2U
    Excep_TPU2_TCI2U,

// TPU3 TGI3A
    Excep_TPU3_TGI3A,

// TPU3 TGI3B
    Excep_TPU3_TGI3B,

// TPU3 TGI3C
    Excep_TPU3_TGI3C,

// TPU3 TGI3D
    Excep_TPU3_TGI3D,

// TPU3 TCI3V
    Excep_TPU3_TCI3V,

// TPU4 TGI4A
    Excep_TPU4_TGI4A,

// TPU4 TGI4B
    Excep_TPU4_TGI4B,

// TPU4 TCI4V
    Excep_TPU4_TCI4V,

// TPU4 TCI4U
    Excep_TPU4_TCI4U,

// TPU5 TGI5A
    Excep_TPU5_TGI5A,

// TPU5 TGI5B
    Excep_TPU5_TGI5B,

// TPU5 TCI5V
    Excep_TPU5_TCI5V,

// TPU5 TCI5U
    Excep_TPU5_TCI5U,
//;0x02A0  Reserved
    (fp)0,
//;0x02A4  Reserved
    (fp)0,

// POE OEI1
    Excep_POE_OEI1,

// POE OEI2
    Excep_POE_OEI2,
 //;0x02B0  Reserved
    (fp)0,
//;0x02B4  Reserved
    (fp)0,

// TMR0 CMIA0
    Excep_TMR0_CMIA0,

// TMR0 CMIB0
    Excep_TMR0_CMIB0,

// TMR0 OVI0
    Excep_TMR0_OVI0,

// TMR1 CMIA1
    Excep_TMR1_CMIA1,

// TMR1 CMIB1
    Excep_TMR1_CMIB1,

// TMR1 OVI1
    Excep_TMR1_OVI1,

// TMR2 CMIA2
    Excep_TMR2_CMIA2,

// TMR2 CMIB2
    Excep_TMR2_CMIB2,

// TMR2 OVI2
    Excep_TMR2_OVI2,

// TMR3 CMIA3
    Excep_TMR3_CMIA3,

// TMR3 CMIB3
    Excep_TMR3_CMIB3,

// TMR3 OVI3
    Excep_TMR3_OVI3,

// SCI2 ERI2
    Excep_SCI2_ERI2,

// SCI2 RXI2
    Excep_SCI2_RXI2,

// SCI2 TXI2
    Excep_SCI2_TXI2,

// SCI2 TEI2
    Excep_SCI2_TEI2,

// SCI3 ERI3
    Excep_SCI3_ERI3,

// SCI3 RXI3
    Excep_SCI3_RXI3,

// SCI3 TXI3
    Excep_SCI3_TXI3,

// SCI3 TEI3
    Excep_SCI3_TEI3,

// SCI4 ERI4
    Excep_SCI4_ERI4,

// SCI4 RXI4
    Excep_SCI4_RXI4,

// SCI4 TXI4
    Excep_SCI4_TXI4,

// SCI4 TEI4
    Excep_SCI4_TEI4,

// DMAC DMAC0I
    Excep_DMAC_DMAC0I,

// DMAC DMAC1I
    Excep_DMAC_DMAC1I,

// DMAC DMAC2I
    Excep_DMAC_DMAC2I,

// DMAC DMAC3I
    Excep_DMAC_DMAC3I,
//;0x0328  Reserved
    (fp)0,
//;0x032C  Reserved
    (fp)0,
//;0x0330  Reserved
    (fp)0,
//;0x0334  Reserved
    (fp)0,

// SCI7 ERI7
    Excep_SCI7_ERI7,

// SCI7 RXI7
    Excep_SCI7_RXI7,

// SCI7 TXI7
    Excep_SCI7_TXI7,

// SCI7 TEI7
    Excep_SCI7_TEI7,

// SCI10 ERI10
    Excep_SCI10_ERI10,

// SCI10 RXI10
    Excep_SCI10_RXI10,

// SCI10 TXI10
    Excep_SCI10_TXI10,

// SCI10 TEI10
    Excep_SCI10_TEI10,

// SCI0 ERI0
    Excep_SCI0_ERI0,

// SCI0 RXI0
    Excep_SCI0_RXI0,

// SCI0 TXI0
    Excep_SCI0_TXI0,

// SCI0 TEI0
    Excep_SCI0_TEI0,

// SCI1 ERI1
    Excep_SCI1_ERI1,

// SCI1 RXI1
    Excep_SCI1_RXI1,

// SCI1 TXI1
    Excep_SCI1_TXI1,

// SCI1 TEI1
    Excep_SCI1_TEI1,

// SCI5 ERI5
    Excep_SCI5_ERI5,

// SCI5 RXI5
    Excep_SCI5_RXI5,

// SCI5 TXI5
    Excep_SCI5_TXI5,

// SCI5 TEI5
    Excep_SCI5_TEI5,

// SCI6 ERI6
    Excep_SCI6_ERI6,

// SCI6 RXI6
    Excep_SCI6_RXI6,

// SCI6 TXI6
    Excep_SCI6_TXI6,

// SCI6 TEI6
    Excep_SCI6_TEI6,

// SCI8 ERI8
    Excep_SCI8_ERI8,

// SCI8 RXI8
    Excep_SCI8_RXI8,

// SCI8 TXI8
    Excep_SCI8_TXI8,

// SCI8 TEI8
    Excep_SCI8_TEI8,

// SCI9 ERI9
    Excep_SCI9_ERI9,

// SCI9 RXI9
    Excep_SCI9_RXI9,

// SCI9 TXI9
    Excep_SCI9_TXI9,

// SCI9 TEI9
    Excep_SCI9_TEI9,

// SCI12 ERI12
    Excep_SCI12_ERI12,

// SCI12 RXI12
    Excep_SCI12_RXI12,

// SCI12 TXI12
    Excep_SCI12_TXI12,

// SCI12 TEI12
    Excep_SCI12_TEI12,

// SCI12 SCIX0
    Excep_SCI12_SCIX0,

// SCI12 SCIX1
    Excep_SCI12_SCIX1,

// SCI12 SCIX2
    Excep_SCI12_SCIX2,

// SCI12 SCIX3
    Excep_SCI12_SCIX3,

// RIIC0 EEI0
    Excep_RIIC0_EEI0,

// RIIC0 RXI0
    Excep_RIIC0_RXI0,

// RIIC0 TXI0
    Excep_RIIC0_TXI0,

// RIIC0 TEI0
    Excep_RIIC0_TEI0,

// SCI11 ERI11
    Excep_SCI11_ERI11,

// SCI11 RXI11
    Excep_SCI11_RXI11,

// SCI11 TXI11
    Excep_SCI11_TXI11,

// SCI11 TEI11
    Excep_SCI11_TEI11,
//;0x03F0  Reserved
    (fp)0,
//;0x03FC  Reserved
    (fp)0,
};
