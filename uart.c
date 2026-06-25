#include "pin_connect_block.h"
#include "types.h"
#include <lpc21xx.h>
#include "uart_defines.h"
void InitUart(void)
{
	//cfg p0.0 as TXD, p0.1 as RXD
	cfgportpinfunc(0,TXD,1);
	cfgportpinfunc(0,RXD,1);
	//PINSEL0|=0x00000005;
	//select 8bit WL and set DLAB
	U0LCR=1<<DLAB_BIT|WL_8BIT;
	//set baudrate by placing DIVISOR
	U0DLL=DIVISOR;
	U0DLM=DIVISOR>>8;
	//clear DLAB_BIT 
	U0LCR&=~(1<<DLAB_BIT);
}

void Uart_TX(u8 Sdat)
{
	U0THR=Sdat;
	while(((U0LSR>>TEMT_BIT)&1)==0);				
}

u8 Uart_RX(void)
{
	while(((U0LSR>>RDR_BIT)&1)==0)
	{
	}
		return U0RBR;
}

void StrTx(s8* str)
{
	while(*str)
	{
		Uart_TX(*str++);
	}
}
