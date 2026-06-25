#ifndef _UART1_H_
#define _UART1_H_

#include"types.h"

void InitUART1(void);
void UART1_TX(u8 data);
u8 UART1_RX(void);
void UART1_StrTx(u8 *str);

#endif
