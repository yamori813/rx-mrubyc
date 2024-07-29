/************************************************************************/
/*    File Version: V1.00                                               */
/*    Date Generated: 08/07/2013                                        */
/************************************************************************/

#include "iodefine.h"
#ifdef __cplusplus
extern "C"
{
#endif
  extern void HardwareSetup (void);
#ifdef __cplusplus
}
#endif

#ifndef MRBC_NO_TIMER
void InitTimer( void )
{
    // プロテクト解除（動作モード、消費電力低減機能、ソフトウェアリセット関連）
    SYSTEM.PRCR.WORD = 0xA502;

    // コンペアマッチタイマ(ユニット0)モジュールストップ設定ビット
    MSTP(CMT0) = 0;             // 状態解除

    // CMI0割込み要求許可
    IEN( CMT0, CMI0 ) = 1;

    // CMI0割込みの割込み優先レベルを1に設定
    IPR( CMT0, CMI0 ) = 1;

    // プロテクト設定
    SYSTEM.PRCR.WORD = 0xA500;


    CMT0.CMCR.WORD = 0x00C0;    // コンペアマッチ割込み許可, クロック選択ビット(PCLKB(25MHz) / 8)
    CMT0.CMCOR = 3125 - 1;      // 1msのカウント
    CMT0.CMCNT = 0;         // コンペアマッチタイマカウンタ初期化
    CMT.CMSTR0.BIT.STR0 = 1;    // CMT0.CMCNTカウンタのカウント動作開始
}
#endif

void
HardwareSetup (void)
{
  R_INIT_Clock();
  SCI_Init();

#ifndef MRBC_NO_TIMER
  InitTimer();
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
