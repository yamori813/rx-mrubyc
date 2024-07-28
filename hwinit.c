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

void InitClock( void )
{
    // プロテクト解除（クロック発生回路関連 / 動作モード、消費電力低減機能、ソフトウェアリセット関連 / VRCR）
    SYSTEM.PRCR.WORD = 0xA507;

    // 電圧レギュレータ制御レジスタ(システムクロックを変更するため、"00h"を書き込む）
    //SYSTEM.VRCR = 0x00;

    // メインクロック発振動作開始
    SYSTEM.MOSCWTCR.BYTE = 0x0D;        // メインクロック発振安定時間：131072サイクル
    SYSTEM.MOSCCR.BIT.MOSTP = 0;        // メインクロック発振動作開始
    while( SYSTEM.MOSCCR.BIT.MOSTP != 0 );  // 設定完了待ち

    // PLL発振動作開始
    SYSTEM.PLLCR.WORD = 0x0901;     // 20HMz / 2 * 10 = 100MHz
    SYSTEM.PLLWTCR.BYTE = 0x0D;     // PLL発振安定時間：1048576サイクル
    SYSTEM.PLLCR2.BIT.PLLEN = 0;        // PLL発振動作開始
    while( SYSTEM.PLLCR2.BIT.PLLEN != 0 );  // 設定完了待ち

    // 高速動作モードに遷移
    SYSTEM.OPCCR.BIT.OPCM = 0;      // 高速動作モード
    while( SYSTEM.OPCCR.BIT.OPCMTSF != 0 ); // 遷移完了まで待つ

    // 周辺モジュールクロック(PCLKD)：50MHz(100MHz / 2)
    // 周辺モジュールクロック(PCLKB)：25MHz(100MHz / 4)
    // 外部バスクロック(BCLK)       ：25MHz(100Mhz / 4)
    // システムクロック(ICLK)       ：50MHz(100MHz / 2)
    // FlashIFクロック(FCLK)        ：25MHz(100MHz / 4)
    SYSTEM.SCKCR.LONG = 0x21021211;
    while( SYSTEM.SCKCR.LONG != 0x21021211 ); // 設定完了待ち

    // PLL回路選択
    SYSTEM.SCKCR3.WORD = 0x0400;        // PLL回路選択
    while( SYSTEM.SCKCR3.WORD != 0x0400 );  // 設定完了待ち

    // 高速オンチップオシレータ停止
    SYSTEM.HOCOCR.BYTE = 0x01;      // HOCO停止
    while( SYSTEM.HOCOCR.BYTE != 0x01 );    // 設定完了待ち

    // 低速オンチップオシレータ停止
    SYSTEM.LOCOCR.BYTE = 0x01;      // LOCO停止
    while( SYSTEM.LOCOCR.BYTE != 0x01 );    // 設定完了待ち

    // サブクロック発振器停止
    SYSTEM.SOSCCR.BYTE = 0x01;      // サブクロック発振器停止
    while( SYSTEM.SOSCCR.BYTE != 0x01 );    // 設定完了待ち
    RTC.RCR3.BYTE = 0x0C;           // RTC[サブクロック発振器停止, 標準CL用ドライブ能力]
    while( RTC.RCR3.BYTE != 0x0C );     // 設定完了待ち

    // プロテクト設定
    SYSTEM.PRCR.WORD = 0xA500;
}

void InitBCLK( void )
{
    // PORT53をBCLK出力に切り替える
    PORT5.PMR.BIT.B3 = 1;

    // プロテクト解除（クロック発生回路関連 / 動作モード、消費電力低減機能、ソフトウェアリセット関連）
    SYSTEM.PRCR.WORD = 0xA503;

    // BCLK端子出力停止
    SYSTEM.SCKCR.BIT.PSTOP1 = 1;        // BCLK端子出力停止
    while( SYSTEM.SCKCR.BIT.PSTOP1 != 1 );  // 設定完了待ち

    // BCLK端子出力選択：12.5MHz(25MHz / 2)
    SYSTEM.BCKCR.BYTE = 0x01;       // BCLKの2分周
    while( SYSTEM.BCKCR.BYTE != 0x01 ); // 設定完了待ち

    // 外部バスを有効にする
    SYSTEM.SYSCR0.WORD = 0x5A03;        // 外部バス有効
    while( SYSTEM.SYSCR0.BIT.EXBE != 1 );   // 設定完了待ち

    // BCLK端子出力動作
    SYSTEM.SCKCR.BIT.PSTOP1 = 0;        // BCLK端子出力動作
    while( SYSTEM.SCKCR.BIT.PSTOP1 != 0 );  // 設定完了待ち

    // プロテクト設定
    SYSTEM.PRCR.WORD = 0xA500;
}

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

void
HardwareSetup (void)
{
  R_INIT_Clock();
  SCI_Init();
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
