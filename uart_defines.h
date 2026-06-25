//uart_defines.h
#define FOSC 12000000
#define CCLK (5*FOSC)
#define PCLK (CCLK/4)
#define BAUD 9600
#define DIVISOR (PCLK/(16*BAUD))

//U0LCR
#define WL_8BIT 3
#define DLAB_BIT 7

//U0LSR
#define TEMT_BIT 6
#define RDR_BIT 0

//pin_defines
#define TXD 0
#define RXD 1
