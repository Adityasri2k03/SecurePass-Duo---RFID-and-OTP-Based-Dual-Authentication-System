#ifndef _RFID_H_
#define _RFID_H_

#include"types.h"
#define RFID_CARD_LEN 0
void RFID_Init(void);
u8 RFID_ReadCard(u8 *cardno);
u8 RFID_ValidateCard(u8 *cardno);
u8 RFID_GetCardIndex(u8 *cardno);

#endif
