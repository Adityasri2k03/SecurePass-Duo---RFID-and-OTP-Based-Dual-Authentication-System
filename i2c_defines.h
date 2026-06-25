//pin defines

#define SCL 2 //PORT 0.2 as scl
#define SDA 3 //port 0.3 as sda

//clock speed defines

#define FOSC 12000000
#define CCLK (FOSC*5)
#define PCLK (CCLK/4)
#define I2C_SPEED 100000   //100KHZ i2c freq 
#define LOADVAL ((PCLK/I2C_SPEED)/2)

//SFRs

#define AA 2
#define SI 3
#define STO 4
#define STA 5
#define I2EN 6

#define AAC 2
#define SIC 3
#define STAC 5
