#ifndef _GSM_H_
#define _GSM_H_
#include"types.h"

void GSM_Init(void);
void GSM_SendCommand(u8 *msg);
void GSM_SendSMS(u8 *number,u8 *msg);
u8 GSM_WaitForResponse(u8 *response);

#endif
