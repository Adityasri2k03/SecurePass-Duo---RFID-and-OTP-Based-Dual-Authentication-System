#include"otp.h"
extern u8 hour;
extern u8 min;
extern u8 sec;
u32 GenerateOTP(void)
{
	u32 otp;
	otp=((hour * 3600)+(min*60)+sec);
	otp+=100000;
	return otp;
}
u8 VerifyOTP(u32 GeneratedOTP,u32 EnteredOTP)
{
	if(GeneratedOTP==EnteredOTP)
		return 1;
	return 0;
}

void OTP_ToString(u32 otp,u8 *str)
{
	u8 i;
	for(i=0;i<6;i++)
	{
		str[5-i]=(otp%10)+'\0';
		otp/=10;
	}
	str[6]='\0';
}
