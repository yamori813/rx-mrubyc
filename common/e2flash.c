// 以下は、an_r01an0544ju0240_rx_flash\Source\r_flash_api_rx\src\r_flash_api_rx.c　からコピー、変更
// 
/******************************************************************************
* Function Name: flash_init
* Description  : Initializes the FCU peripheral block.
*                NOTE: This function does not have to execute from in RAM.
* Arguments    : none
* Return Value : FLASH_SUCCESS -
*                    Operation Successful
*                FLASH_FAILURE -
*                    Operation Failed
******************************************************************************/
#include "iodefine.h"
#include "r_typedefs.h"
#include "e2flashdef.h"
/**** Function Return Values ****/
/* Operation was successful */
#define FLASH_SUCCESS           (0x00)
/* Flash area checked was blank, making this 0x00 as well to keep existing
   code checking compatibility */
#define FLASH_BLANK             (0x00)
/* The address that was supplied was not on aligned correctly for ROM or DF */
#define FLASH_ERROR_ALIGNED     (0x01)
/* Flash area checked was not blank, making this 0x01 as well to keep existing
   code checking compatibility */
#define FLASH_NOT_BLANK         (0x01)
/* The number of bytes supplied to write was incorrect */
#define FLASH_ERROR_BYTES       (0x02)
/* The address provided is not a valid ROM or DF address */
#define FLASH_ERROR_ADDRESS     (0x03)
/* Writes cannot cross the 1MB boundary on some parts */
#define FLASH_ERROR_BOUNDARY    (0x04)
/* Flash is busy with another operation */
#define FLASH_BUSY              (0x05)
/* Operation failed */
#define FLASH_FAILURE           (0x06)
/* Lock bit was set for the block in question */
#define FLASH_LOCK_BIT_SET      (0x07)
/* Lock bit was not set for the block in question */
#define FLASH_LOCK_BIT_NOT_SET  (0x08)

#if   (DF_PROGRAM_SIZE_SMALL == 8)
    /* 'size' parameter for R_FlashDataAreaBlankCheck */
    #define BLANK_CHECK_8_BYTE       0  
#elif (DF_PROGRAM_SIZE_SMALL == 2)
    /* 'size' parameter for R_FlashDataAreaBlankCheck */
    #define BLANK_CHECK_2_BYTE       0
#endif
/* 'size' parameter for R_FlashDataAreaBlankCheck */
#define BLANK_CHECK_ENTIRE_BLOCK     1  

#define FLASH_FENTRYR_TIMEOUT   (4)
#define FCU_RAM_INIT_REQUIRED

// an_r01an0544ju0240_rx_flash\Source\r_flash_api_rx\src\r_flash_api_rx_private.h
/* FCU-RAM address define */
/* FCU F/W Store Address */
#define FCU_PRG_TOP     0xFEFFE000	
/* FCU RAM Address */
#define FCU_RAM_TOP     0x007F8000
/* FCU RAM Size */
#define FCU_RAM_SIZE    0x2000
//extern void cprintf();
int WAITERASE    =    ((int32_t)(60000 * (32.0/(25)))*(50000/1000));

//
uint8_t        g_fcu_transfer_complete = 0;
uint8_t	flagNotifyPeripheralClock;
//
uint8_t flash_init (void)
{
//#if defined(FCU_RAM_INIT_REQUIRED)    
    /* Declare source and destination pointers */
    uint32_t * src, * dst;  
    /* Declare iteration counter variable */
    uint16_t i;
//#endif    
    /* Timeout counter. */
    volatile int32_t  wait_cnt;
        
    /* Disable FCU interrupts in FCU block */
    FLASH.FAEINT.BIT.ROMAEIE = 0;
    FLASH.FAEINT.BIT.CMDLKIE = 0;
    FLASH.FAEINT.BIT.DFLAEIE = 0;
    FLASH.FAEINT.BIT.DFLRPEIE = 0;
    FLASH.FAEINT.BIT.DFLWPEIE = 0;
    
    /* Disable FCU interrupts in ICU */
    
    /* Disable flash interface error (FIFERR) */
    IPR(FCU, FIFERR) = 0;
    IEN(FCU, FIFERR) = 0;
        
//#if defined(FLASH_API_RX_CFG_DATA_FLASH_BGO) || defined(FLASH_API_RX_CFG_ROM_BGO)
    /* Enable flash ready interrupt (FRDYI) */    
    /* Make sure IPL is high enough that interrupt will trigger */
//    IPR(FCU, FRDYI) = FLASH_API_RX_CFG_FLASH_READY_IPL;
//    IEN(FCU, FRDYI) = 1;
//#else        
    /* Disable flash ready interrupt (FRDYI) */
    IPR(FCU, FRDYI) = 0;
    IEN(FCU, FRDYI) = 0;
//#endif    

    /* Transfer Firmware to the FCU RAM. To use FCU commands, the FCU firmware
        must be stored in the FCU RAM. */
    
    /* Before writing data to the FCU RAM, clear FENTRYR to stop the FCU. */
    if(FLASH.FENTRYR.WORD != 0x0000)
    {
        /* Disable the FCU from accepting commands - Clear both the
           FENTRY0(ROM) and FENTRYD(Data Flash) bits to 0 */
        FLASH.FENTRYR.WORD = 0xAA00;

        /* Initialize timeout for FENTRYR being written. */
        wait_cnt = FLASH_FENTRYR_TIMEOUT;

        /* Read FENTRYR to ensure it has been set to 0. Note that the top byte
           of the FENTRYR register is not retained and is read as 0x00. */
        while(0x0000 != FLASH.FENTRYR.WORD)
        {
            /* Wait until FENTRYR is 0 unless timeout occurs. */
            if (wait_cnt-- <= 0)
            {
                /* This should not happen. FENTRYR getting written to 0 should
                   only take 2-4 PCLK cycles. */
                return FLASH_FAILURE;
            }
        }
    }

#if defined(FCU_RAM_INIT_REQUIRED)
    /* Enable the FCU RAM */
    FLASH.FCURAME.WORD = 0xC401;
    
    /* Copies the FCU firmware to the FCU RAM.
       Source: H'FEFFE000 to H'FF00000 (FCU firmware area)
       Destination: H'007F8000 to H'007FA000 (FCU RAM area) */
    /* Set source pointer */
    src = (uint32_t *)FCU_PRG_TOP;
    
    /* Set destination pointer */
    dst = (uint32_t *)FCU_RAM_TOP;
    
    /* Iterate for loop to copy the FCU firmware */
    for( i=0; i<(FCU_RAM_SIZE/4); i++)
    {
        /* Copy data from the source to the destination pointer */
        *dst = *src;
        
        /* Increment the source and destination pointers */
        src++;
        dst++;
    }
#endif

    /* FCU firmware transfer complete, set the flag to 1 */
    g_fcu_transfer_complete = 1;
				flagNotifyPeripheralClock = 0;

    /* Return no errors */
    return FLASH_SUCCESS;
}
/******************************************************************************
* Function Name: R_FlashDataAreaAccess
* Description  : This function is used to allow read and program permissions 
*                to the Data Flash areas. 
*                NOTE1: This function does not have to execute from in RAM. It
*                       must be in RAM though if FLASH_API_RX_CFG_ROM_BGO is 
*                       enabled and this function is called during a ROM P/E 
*                       operation.
* Arguments    : read_en_mask - 
*                    Bitmasked value. Bits 0-3 represents each Data 
*                    Blocks 0-3 (respectively).
*                    '0'=no Read access. 
*                    '1'=Allows Read by CPU
*                write_en_mask - 
*                    Bitmasked value. Bits 0-3 represents each Data 
*                    Blocks 0-3 (respectively).
*                    '0'=no Erase/Write access. 
*                    '1'=Allows Erase/Write by FCU
* Return Value : none
******************************************************************************/
void R_FlashDataAreaAccess (uint16_t read_en_mask, uint16_t write_en_mask)
{
    /* Used for making sure select bits are not set. */
    uint16_t temp_mask;

//#if   defined(BSP_MCU_RX610)
    
//    temp_mask = 0x00FF;
    /* Set Read access for the Data Flash blocks */
//    FLASH.DFLRE.WORD = (uint16_t)(0x2D00 | (read_en_mask & 0x00FF));

    /* Set Erase/Program access for the Data Flash blocks */
//    FLASH.DFLWE.WORD = (uint16_t)(0x1E00 | (write_en_mask & 0x00FF));
        
//#else

//    #if BSP_DATA_FLASH_SIZE_BYTES == 8192
#if defined(GRCITRUS)
    temp_mask = 0x00FF;
#else
    /* Mask off bits 4-7 to make sure they are 0. */
    temp_mask = 0x000F;
#endif
//    #endif

    /* Set Read access for the Data Flash blocks DB0-DB7 */
    FLASH.DFLRE0.WORD = (uint16_t)(0x2D00 | (read_en_mask & temp_mask));

    /* Set Erase/Program access for the Data Flash blocks DB0-DB7 */
    FLASH.DFLWE0.WORD = (uint16_t)(0x1E00 |  (write_en_mask & temp_mask));

//    #if BSP_DATA_FLASH_SIZE_BYTES > 16384
#if defined(GRCITRUS)
    /* Set Read access for the Data Flash blocks DB8-DB15 */
    FLASH.DFLRE1.WORD = (uint16_t)(0xD200 | ((read_en_mask >> 8) & 0x00FF));

    /* Set Erase/Program access for the Data Flash blocks DB8-DB15 */
    FLASH.DFLWE1.WORD = (uint16_t)(0xE100 |  ((write_en_mask >> 8) & 0x00FF));
#endif
//    #endif
    
//#endif
}
/******************************************************************************
End of function  R_FlashDataAreaAccess
******************************************************************************/

/*********************************************/
// アドレスチェック
//		CheckAddress(int addr,int bytes);
//対象アドレス: addr,  長さ: bytes
//return: 0 no error, 1:error
/**********************************************/
int CheckE2flashAddress(int addr,int bytes)
{
	if(bytes & 1)// odd address
		return 1;
	if(bytes < 0)
		return 1;
	if(addr < 0x100000)// out of erea
			return 1;
	if((addr + bytes) > 0x102000)
		return 1;
	return 0;
}
/*********************************************/
// 消去 E2 flash
//		EraseE2Flash(int addr,int bytes);
//対象アドレス: addr,  長さ: bytes
//return: 0 no error, 1:error
/**********************************************/
int EraseE2Flash(int FlashAddr,int bytes)
{
uint32_t	faddr = (uint32_t)FlashAddr;
	int ret;
/* NOT USE
	ret = CheckE2flashAddress(faddr,bytes);
	if(ret)
		return ret;
*/
	if(EnterPEmode(faddr))
	{
//		cprintf("\r\nEnterPEmode error");
		return 1;
	}

	while(bytes)
	{
			// 消去
		ret = CMDE2FlashErase((uint8_t *)faddr);
		// 正常か
		if (ret == 0) {
#if defined(GRCITRUS)
			// アドレスUP
			faddr += 0x20;
			// 総数ブロックカウントダウン
			bytes -= 0x20;
#else
			// アドレスUP
			faddr += 0x80;
			// 総数ブロックカウントダウン
			bytes -= 0x80;
#endif
		} else {
//			cprintf("\r\nCMDE2FlashErase ret=error");
			break;
		}
	}
	// 読み出しモード
	ExitPeMode(faddr);

	return ret;
}
/*********************************************/
// P/E モードに移行
//		EraseE2Flash(int addr,int bytes);
//対象アドレス: addr,  長さ: bytes
//return: 0 no error, 1:error
/**********************************************/
int EnterPEmode(int addr)
{
	volatile int32_t timeout;
	int ret;

	ret = 0;
	// ＰＥモードから抜ける
	FLASH.FENTRYR.WORD = 0xAA00;

	timeout = 10;

	// 遷移完了まで待つ
	while(FLASH.FENTRYR.WORD != 0x0000)
	{
		if (timeout-- <= 0){
			ret = 1;
			break;
		}
	}

	if (ret == 0){
		// P/Eモードに移行。B7=1
		FLASH.FENTRYR.WORD = 0xAA80;

		// E2flash ステータスクリア
		ClearE2FlashStatus();
		// 周辺クロックの通知
		ret = NotifyPeripheralClock(addr);
//		cprintf("\r\nNotifyPeripheralClock ret = %d",ret);
		if (ret == 0){
			// プログラム/イレーズ可能
			FLASH.FWEPROR.BYTE = 0x01;
		}
	}

	return ret;
}
/*******************************************/
/* E2データフラッシュリードモードに移行     */
/* FlashAddr : E2データフラッシュアドレス   */
/*******************************************/
void ExitPeMode (uint32_t FlashAddr)
{
volatile int32_t	timeout;
uint8_t			*pAddr;

	pAddr = (uint8_t *)FlashAddr;

	timeout = WAITERASE*10;//DEF_FCU_WAIT_MAX_ERASE;

	while(FLASH.FSTATR0.BIT.FRDY == 0){
		timeout--;

		if(timeout == 0){
			FCUReset();
			break;
		}
	}

	// エラーが発生しているか
	if(  (FLASH.FSTATR0.BIT.ILGLERR == 1)
	  || (FLASH.FSTATR0.BIT.ERSERR  == 1)
	  || (FLASH.FSTATR0.BIT.PRGERR  == 1)){
		// FCUは不正なコマンドやE2データフラッシュアクセスを検出しているか
		if(FLASH.FSTATR0.BIT.ILGLERR == 1){
			// アクセス違反も検出しているか
			if(FLASH.FASTAT.BYTE != 0x10){
				// アクセス違反を解除
				FLASH.FASTAT.BYTE = 0x10;
			}
		}

		// ステータスクリア
		*pAddr = 0x50;
	}

	// データフラッシュリードモードへ移行
	FLASH.FENTRYR.WORD = 0xAA00;

	timeout = 10;

	// 移行待ち
	while(0x0000 != FLASH.FENTRYR.WORD){
		timeout--;
		if (timeout <= 0){
			break;
		}
	}

	// プログラム/イレーズ禁止
	FLASH.FWEPROR.BYTE = 0x02;
}

/**************************************************/
/* E2flash ステータスクリア                       */
/**************************************************/
void ClearE2FlashStatus(void)
{
	volatile char	*pflash ;
	
	// データフラッシュ先頭アドレスを設定
	pflash = (volatile char *)0x100000;

	// FCUはエラーを検出しているか
	if(FLASH.FSTATR0.BIT.ILGLERR == 1){
		// アクセス違反を検出しているか
		if(FLASH.FASTAT.BYTE != 0x10){
			// アクセス違反を解除
			FLASH.FASTAT.BYTE = 0x10;
		}
	}

	// ステータスレジスタクリア
	*pflash = 0x50;
}
/***********************************************/
// 周辺クロック通知         
//  FlashAddr :  E2データフラッシュアドレス 
/**********************************************/
int NotifyPeripheralClock(uint32_t FlashAddr)
{
	volatile uint8_t	*pFlashAddr;
	volatile long	timeout;
int		ret = 0;
	pFlashAddr = (volatile uint8_t *)FlashAddr;
	
	// 周辺クロック未通知
	if (flagNotifyPeripheralClock == 0){
		// 周辺クロック通知(MHz単位)
		FLASH.PCKAR.WORD = 25;
// ハードウエアユーザースマニュアル r01uh0037jj0150-rx210.pdf の　1385 ページ参照

		*pFlashAddr = 0xE9;

		*pFlashAddr = 0x03;

		*(volatile uint16_t *)pFlashAddr = 0x0F0F;

		*(volatile uint16_t *)pFlashAddr = 0x0F0F;

		*(volatile uint16_t *)pFlashAddr = 0x0F0F;

		*pFlashAddr = 0xD0;

		timeout = 50*60*2;

		// 通知完了待ち
		while(FLASH.FSTATR0.BIT.FRDY == 0)
		{
			timeout--;
			if(timeout == 0){
				ret = 1;
				break;
    		}
		}

		if (ret == 0)
		{
			// 正常か
 			if(FLASH.FSTATR0.BIT.ILGLERR == 0)
			{
				// 周辺クロック通知フラグを１
				flagNotifyPeripheralClock = 1;
			}
			else
			{
//				cprintf("\r\nFLASH.FSTATR0.BYTE = %02X",FLASH.FSTATR0.BYTE);
				ret = 1;
			}
		}
		else
		{
			// FCUリセット
//			cprintf("\r\nTimeout 周辺クロック通知完了");
			FCUReset();
		}
	}

	return ret;
}

/*****************************************
// FCUリセット        
*****************************************/
void FCUReset(void)
{
volatile int32_t	timeout;

	// FCUリセット
	FLASH.FRESETR.WORD = 0xCC01;

	timeout = 50*32;

	// リセット待ち
	while(timeout != 0)
	{
		timeout--;
	}

	// FCUリセット解除
	FLASH.FRESETR.WORD = 0xCC00;

	// リードモードへ移行
	FLASH.FENTRYR.WORD = 0xAA00;

	timeout = 10;

	// 移行完了待ち
	while(0x0000 != FLASH.FENTRYR.WORD)
	{
		timeout--;
		if (timeout <= 0){
			break;
		}
	}

	// P/E 禁止
	FLASH.FWEPROR.BYTE = 0x02;

	// 周辺クロック未通知
	flagNotifyPeripheralClock = 0;
}

/*****************************************/
/* E2データフラッシュブロック消去実行  */
/* pErase : 消去を始めるE2データフラッシュアドレス   */
/* @note    備考                        */
/*******************************************/
uint8_t CMDE2FlashErase(volatile uint8_t *pErase)
{
volatile int32_t	wait_cnt;
uint8_t				result = 0;

	// 消去開始
	*pErase = 0x20;
	*pErase = 0xD0;

	wait_cnt = 30000000;//

	// 消去待ち
	while(FLASH.FSTATR0.BIT.FRDY == 0){
		wait_cnt--;

		if(wait_cnt == 0){
			// FCU リセット
			FCUReset();
			result = 1;
        }
    }

	if (result == 0){
		// エラー発生したか
		if(   (FLASH.FSTATR0.BIT.ILGLERR == 1)
		   || (FLASH.FSTATR0.BIT.ERSERR  == 1)){
			result = 2;
		}
 	}

    return result;
}

/*****************************************/
/* E2データフラッシュ書き込み                     */
/* pFlashAddr : 書き込みE2データフラッシュアドレス*/
/* pSrc       : 書き込みデータアドレス           */
/* bytes      : 書き込みサイズ(2バイト単位)      */
/******************************************/
uint8_t WriteE2Flash(void *pFlashAddr,void *pSrc,int16_t bytes)
{
uint32_t			dstaddr = (uint32_t)pFlashAddr;
uint32_t			srcaddr = (uint32_t)pSrc;
uint8_t				ret = 0;

// フラッシュ先頭と、長さがあっているか？
	ret = CheckE2flashAddress((uint32_t)pFlashAddr,bytes);
	if(ret)
		return ret;

		// PEモードに移行
	EnterPEmode(dstaddr);
//		fEnterPeMode(start_addr);

		while(0 < bytes){
			ret = WriteDataFlash(dstaddr,srcaddr);
			// 正常か
			if (ret == 0){
				dstaddr += 2;
				srcaddr += 2;
				bytes -= 2;
			}
			else{
				break;
			}
		}

		// 読み出しモードに移行
		ExitPeMode((uint32_t)pFlashAddr);

	return ret;
}

/***************************************************/
/* E2データフラッシュ書き込み実行 */
/* address     : 書き込みE2データフラッシュアドレス */
/* data        : 書き込みデータアドレス             */
/****************************************************/
uint8_t WriteDataFlash(uint32_t address, uint32_t data)
{
volatile int32_t	wait_cnt;
uint8_t				result = 0;

	// 
	*(volatile uint8_t *)(0x100000) = 0xE8;

	// 書き込みワード数を通知
	*(volatile uint8_t *)(0x100000) = 1;    
	// データフラッシュにデータ書き込み
	*(volatile uint16_t *)address = *(uint16_t *)data;

	// 4
	*(volatile uint8_t *)(0x100000) = 0xD0;

	wait_cnt = 25*3200;//

	// 書き込み待ち
	while(FLASH.FSTATR0.BIT.FRDY == 0){
		wait_cnt--;

		if(wait_cnt == 0){
			// FCU リセット
			FCUReset();
			result = 1;
		}
	}

	if (result == 0){
		// エラー発生？
		if(   (FLASH.FSTATR0.BIT.ILGLERR == 1)
		   || (FLASH.FSTATR0.BIT.PRGERR == 1)){
			result = 1;
		}
	}

    return result;
}
