#include <lpc21xx.h>
#include "i2c_defines.h"
#include "types.h"

void i2c_init(void)
{
	PINSEL0|=0x00000050;
	//CFGPIN(PINSEL0,2,FUN2);//PO.2 AS SCL
	//CFGPIN(PINSEL0,3,FUN2);//P0.3 AS SDA
	I2SCLL=LOADVAL;
	I2SCLH=LOADVAL;
	I2CONSET=1<<I2EN;
}

void i2c_start(void)
{
	//start condition
	I2CONSET=1<<STA;
	//wait for SI bit status
	while(((I2CONSET>>SI)&1)==0);
	// clear start condition
	I2CONCLR=1<<STAC;
}

void i2c_stop(void)
{
	// issue stop condition
  	I2CONSET=1<<STO;
  	// clear SI bit status
  	I2CONCLR=1<<SIC;
  	//stop will cleared automatically
  	    
  	//while(((I2CONSET>>STO_BIT)&1));
}

void i2c_restart(void)
{
	//start condition
  	I2CONSET=1<<STA;
  	//clear SI_BIT
  	I2CONCLR=1<<SIC;
  	//wait for SI bit status
  	while(((I2CONSET>>SI)&1)==0);
  	// clear start condition
  		I2CONCLR=1<<STAC;
}

void i2c_write(u8 dat)
{
	//put data into I2DAT
  	I2DAT=dat;
  	//clear SI_BIT
  	I2CONCLR=1<<SIC;
  	//wait for SI bit status
  	while(((I2CONSET>>SI)&1)==0);
}

u8 i2c_nack(void)
{
	//Assert Not of Ack
  	I2CONSET=0<<AA;
  	//Clear SI bit
  	I2CONCLR=1<<SIC;
  	//wait for byte reception
  	while(((I2CONSET>>SI)&1)==0);
  	//read received byte;
  	return I2DAT; 
}

u8 i2c_mack(void)
{
	//Assert Ack
  	I2CONSET=1<<AA;
  	//Clear SI bit
  	I2CONCLR=1<<SIC;
  	//Wait for SI Bit
  	while(((I2CONSET>>SI)&1)==0);
	//Clear Assert Ack
  	I2CONCLR=1<<AAC;
  	//read read byte
  	return I2DAT;
}

