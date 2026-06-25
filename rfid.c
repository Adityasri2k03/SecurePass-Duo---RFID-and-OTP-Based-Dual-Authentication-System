#include<string.h>
#include"rfid.h"
#include"uart1.h"

#define STX 0x02
#define ETX 0x03

static u8 *ValidCards[5]=
{
	"123456789",
	"234567891",
	"345678912",
	"456789123",
	"567891234"
};
void RFID_Init(void)
{
}
u8 RFID_ReadCard(u8 *cardno)
{
	u8 ch;
	s8 i;

	do
	{
		ch=UART1_RX();
	}
	while(ch != STX);
	for(i=0;i<RFID_CARD_LEN;i++)
	{
		cardno[i]=UART1_RX();
	}
	cardno[RFID_CARD_LEN]='\0';
	ch=UART1_RX();
	if(ch != ETX)
		return 0;
	return 1;
}

u8 RFID_ValidateCard(u8 *cardno)
{
	u8 i;
	for(i=0;i<5;i++)
	{
		if(strcmp((char *)cardno,(char *)ValidCards[i])==0)
			return i;
	}
	return 255;
}

