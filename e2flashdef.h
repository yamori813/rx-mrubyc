//
void FCUReset(void);
int NotifyPeripheralClock(uint32_t FlashAddr);
void ClearE2FlashStatus(void);
int EnterPEmode(int addr);
int CheckE2flashAddress(int addr,int bytes);
void R_FlashDataAreaAccess (uint16_t read_en_mask, uint16_t write_en_mask);
int EraseE2Flash(int addr,int bytes);
uint8_t CMDE2FlashErase(volatile uint8_t *pErase);
void ExitPeMode (uint32_t FlashAddr);
uint8_t WriteE2Flash(void *pFlashAddr,void *pSrc,int16_t bytes);
uint8_t WriteDataFlash(uint32_t address, uint32_t data);
