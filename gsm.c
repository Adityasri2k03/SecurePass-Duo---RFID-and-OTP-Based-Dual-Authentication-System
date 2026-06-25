#include<LPC214x.h>
#include<string.h>
#include"gsm.h"
#include"uart.h"
#include"delay.h"

#define CTRL_Z 0x1A
static u8 GSM_RxBuffer[200];

void GSM_SendCommand(u8 *cmd)
{
	StrTx(cmd);
	Uart_TX('\r');
	Uart_TX('\n');
	delay_ms(1000);
}
u8 GSM_WaitForResponse(u8 *response)
{
	u32 i=0;
	u32 timeout=0;
	memset(GSM_RxBuffer,0,sizeof(GSM_RxBuffer));
	while(timeout<5000)
	{
 		if(U0LSR & 0x01)
		{
			GSM_RxBuffer[i]=Uart_RX();
			if(i<1999)
				i++;
			if(strstr((char *)GSM_RxBuffer,(char *)response))
			{
				return 1;
			}
		}
		delay_ms(1);
		timeout++;
	}
	return 0;
}

void GSM_Init(void)
{
	GSM_SendCommand("AT");
	if(GSM_WaitForResponse("OK"))
		return;
	delay_ms(1000);
	GSM_SendCommand("ATE0");
	if(!GSM_WaitForResponse("OK"))
		return;
	delay_ms(1000);
	GSM_SendCommand("AT+CMGF=1");
	if(!GSM_WaitForResponse("OK"))
		return;
	delay_ms(1000);
}

void GSM_SendSMS(u8 *number,u8 *msg)
{
	u8 cmd[40];
	strcpy((char *)cmd,"AT+CMGS=\"");
	strcat((char *)cmd,(char *)number);
	strcat((char *)cmd,"\"");

	GSM_SendCommand(cmd);
	if(GSM_WaitForResponse(">"))
	{
		StrTx(msg);
		delay_ms(100);
		Uart_TX(CTRL_Z);
		GSM_WaitForResponse("OK");
	}
}
