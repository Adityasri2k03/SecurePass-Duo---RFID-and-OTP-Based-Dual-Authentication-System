#include <LPC214X.H>

#include "types.h"
#include "defines.h"
#include "pin_connect_block.h"
#include "uart1.h"

#define UART1_DIVISOR 97

void InitUART1(void)
{
	/* P0.8 -> TXD1
	   P0.9 -> RXD1 */

	PINSEL0 |= 0x00050000;

	U1LCR = 0x83;

	U1DLL = UART1_DIVISOR;
	U1DLM = 0;

	U1LCR = 0x03;
}

void UART1_TX(u8 data)
{
	U1THR = data;

	while(!(U1LSR & (1<<5)));
}

u8 UART1_RX(void)
{
	while(!(U1LSR & 0x01));

	return U1RBR;
}

void UART1_StrTx(u8 *str)
{
	while(*str)
	{
		UART1_TX(*str++);
	}
}
