#include <LPC21xx.H>
#include <string.h>

#include "types.h"
#include "lcd.h"
#include "delay.h"
#include "lcd_defines.h"

#include "KPM.h"

#include "gsm.h"
#include "rfid.h"
#include "otp.h"

#include "uart.h"
#include "uart1.h"

/* RTC Functions */
void RTC_Init(void);
void GetRTCTimeInfo(s32 *,s32 *,s32 *);

extern s32 hour,min,sec;

/* LED Pin */

#define ACCESS_LED 25

/* OTP Timeout */

#define OTP_TIMEOUT 60

/* Registered Mobile Numbers */

u8 *MobileNumbers[5] =
{
	"9876543210",
	"9876543211",
	"9876543212",
	"9876543213",
	"9876543214"
};

void AccessGranted(void);
void AccessDenied(void);

u32 GetTimeSeconds(void);

int main()
{
	u8 CardNo[9];
	u8 OTPString[7];

	u32 GeneratedOTP;
	u32 EnteredOTP;

	u8 CardIndex;

	u32 SentTime;
	u32 CurrentTime;

	/* LED Output */

	IODIR0 |= (1<<ACCESS_LED);

	InitLCD();

	InitKPM();

	InitUart();      /* GSM */

	InitUART1();     /* RFID */

	RTC_Init();

	GSM_Init();

	CmdLCD(CLEAR_LCD);

	while(1)
	{
		CmdLCD(CLEAR_LCD);

		CmdLCD(GOTO_LINE1_POS0);

		StrLCD("SCAN RFID");

		/* Wait For Card */

		if(RFID_ReadCard(CardNo))
		{
			if(RFID_ValidateCard(CardNo))
			{
				CardIndex =
				RFID_ValidateCard(CardNo);

				GeneratedOTP =
				GenerateOTP();

				OTP_ToString(
				GeneratedOTP,
				OTPString);

				GSM_SendSMS(
				MobileNumbers[CardIndex],
				OTPString);

				GetRTCTimeInfo(
				&hour,
				&min,
				&sec);

				SentTime =
				GetTimeSeconds();

				CmdLCD(CLEAR_LCD);

				StrLCD("ENTER OTP");

				CmdLCD(
				GOTO_LINE2_POS0);

				EnteredOTP =
				ReadNum();

				GetRTCTimeInfo(
				&hour,
				&min,
				&sec);

				CurrentTime =
				GetTimeSeconds();

				if((CurrentTime-SentTime)
					> OTP_TIMEOUT)
				{
					CmdLCD(CLEAR_LCD);

					StrLCD(
					"OTP EXPIRED");

					AccessDenied();

					delay_ms(2000);

					continue;
				}

				if(VerifyOTP(
					GeneratedOTP,
					EnteredOTP))
				{
					CmdLCD(CLEAR_LCD);

					StrLCD(
					"ACCESS OK");

					AccessGranted();
				}
				else
				{
					CmdLCD(CLEAR_LCD);

					StrLCD(
					"WRONG OTP");

					AccessDenied();
				}
			}
			else
			{
				CmdLCD(CLEAR_LCD);

				StrLCD(
				"INVALID CARD");

				AccessDenied();
			}
		}
	}
}

u32 GetTimeSeconds(void)
{
	return
	(
		(hour * 3600)
		+
		(min * 60)
		+
		sec
	);
}

void AccessGranted(void)
{
	IOSET0 = (1<<ACCESS_LED);

	delay_ms(5000);

	IOCLR0 = (1<<ACCESS_LED);
}

void AccessDenied(void)
{
	IOCLR0 = (1<<ACCESS_LED);
}
