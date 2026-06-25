#ifndef _OTP_H_
#define _OTP_H_

#include "types.h"
u32 GenerateOTP(void);
u8 VerifyOTP(u32 GenerateOTP,u32 EnteredOTP);
void OTP_ToString(u32 otp,u8 *str);

#endif
