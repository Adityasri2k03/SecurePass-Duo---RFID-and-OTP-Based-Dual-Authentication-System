# 🔐 SecurePass Duo – RFID & OTP Based Dual Authentication Smart Door System

A two-factor authentication smart door access system built using the **LPC2148 ARM7 Microcontroller**. The system combines **RFID authentication** with **OTP verification via GSM SMS**, ensuring that access is granted only after both authentication stages are successfully completed.

---

## 📖 Overview

SecurePass Duo is an embedded security system designed to improve access control by implementing **dual-factor authentication**.

Unlike conventional RFID-based door locks, this system requires:

1. **RFID Card Verification**
2. **One-Time Password (OTP) Verification**

After a valid RFID card is detected, the system generates a **4-digit OTP** using the current RTC time and sends it to a registered mobile number through a GSM module. Only when the OTP is entered correctly within the allowed time does the door unlock.

The project also includes an **Admin RTC Edit Mode**, accessible through an external interrupt, allowing secure modification of RTC settings without affecting the authentication workflow.

---

# ✨ Features

- 🔐 RFID + OTP Dual Authentication
- 📱 GSM-based OTP delivery via SMS
- ⏳ OTP expiration (60 seconds)
- 🚫 Maximum 3 OTP verification attempts
- 🕒 Real-Time Clock (RTC) display
- 🔧 Admin RTC Edit Mode using External Interrupt
- 🚪 Automatic door lock control using relay
- 📟 LCD-based user interface
- ⌨️ Matrix keypad for OTP entry

---

# 🎯 Objectives

- Build a secure two-factor authentication system.
- Integrate RFID and GSM communication on LPC2148.
- Generate and validate time-based OTPs.
- Prevent unauthorized access using expiry and retry limits.
- Demonstrate interrupt-driven embedded system design.
- Develop a modular Embedded C application.

---

# 🧩 Hardware Requirements

| Component | Description |
|------------|-------------|
| LPC2148 ARM7 Board | Main Controller |
| RFID Reader Module | User Identification |
| GSM Module | OTP Delivery |
| 16x2 LCD | User Interface |
| 4x4 Matrix Keypad | OTP Input |
| Relay / Solenoid Lock | Door Lock Control |
| External Interrupt Switch | Admin Mode Trigger |

---

# 💻 Software Tools

- Embedded C
- Keil uVision4
- Flash Magic

---

# 🏗️ System Architecture

The LPC2148 acts as the central controller and manages communication between all peripherals.

## Controller

Responsible for:

- RFID authentication
- OTP generation
- GSM communication
- RTC management
- LCD updates
- Keypad input
- Door lock control
- Interrupt handling

---

## RFID Module

- Reads RFID card through UART1
- Validates user identity
- Initiates OTP generation

---

## GSM Module

Communicates through UART0.

Functions:

- Sends OTP using SMS
- Uses AT Commands

Example:

```
AT+CMGF=1
AT+CMGS
```

---

## RTC Module

Provides:

- Current Time
- Date
- Day

Also acts as the seed for OTP generation.

---

## LCD Display

Displays:

- Current time
- Date
- Authentication status
- OTP prompts
- Access results

---

## Matrix Keypad

Used for:

- OTP entry
- Admin menu navigation

Special Keys

| Key | Function |
|------|----------|
| 15 | Backspace |
| 16 | Confirm |

---

# ⚙️ Working Principle

## Step 1 – System Initialization

On power-up the LPC2148 initializes:

- LCD
- UART0 (GSM)
- UART1 (RFID)
- RTC
- Matrix Keypad
- External Interrupt (EINT1)

The LCD continuously displays the current time and date.

---

## Step 2 – RFID Authentication

The system waits for an RFID card.

### Valid Card

- Display **Valid Tag**
- Store current RTC time
- Generate OTP
- Send OTP via GSM

### Invalid Card

Display:

```
Invalid Card
```

Return to standby.

---

## Step 3 – OTP Generation

A 4-digit OTP is generated using the RTC values.

The OTP is sent to the registered mobile number via SMS.

---

## Step 4 – OTP Verification

The user enters the OTP using the keypad.

Rules:

- Maximum 3 attempts
- OTP valid for 60 seconds

### Correct OTP

```
Access Granted
```

- Relay ON
- Door Unlocks
- Delay
- Relay OFF

### Wrong OTP

```
WRONG OTP
```

Attempt counter increments.

### OTP Expired

```
OTP EXPIRED
```

### Three Failed Attempts

```
Access Denied
```

---

## Step 5 – Return to Idle

After authentication completes, the system returns to standby and waits for the next RFID scan.

---

# 🔐 Admin RTC Edit Mode

Admin mode is entered through **External Interrupt (EINT1)**.

### Menu

```
1. RTC Edit
2. Exit
```

The administrator can modify:

- Hour
- Minute
- Second
- Date
- Month
- Year
- Day of Week

Selecting **Exit** returns the system to normal operation.

---

# 📊 System Flow

```
Power ON
      │
      ▼
Initialize Peripherals
      │
      ▼
Display RTC
      │
      ▼
Wait for RFID
      │
      ▼
Is RFID Valid?
      │
 ┌────┴─────┐
 │          │
No         Yes
 │          │
 ▼          ▼
Invalid   Generate OTP
 Card        │
             ▼
         Send SMS
             │
             ▼
      Wait for OTP
             │
             ▼
      OTP Correct?
             │
      ┌──────┴──────┐
      │             │
     No            Yes
      │             │
      ▼             ▼
Attempts++     Check Time
      │             │
      ▼             ▼
3 Attempts?   Expired?
      │             │
      ▼             ▼
Access       OTP Expired
Denied            │
                  ▼
           Access Granted
                  │
                  ▼
             Unlock Door
                  │
                  ▼
              Lock Door
```

---

# 📡 Communication Protocols

| Interface | Purpose |
|------------|----------|
| UART0 | GSM Communication |
| UART1 | RFID Communication |
| EINT1 | Admin RTC Mode |

---

# 🔌 Pin Connections

| LPC2148 Pin | Connection |
|-------------|------------|
| P0.0 | GSM TxD |
| P0.1 | GSM RxD |
| P0.3 | External Interrupt (EINT1) |
| P0.8 | RFID TxD |
| P0.9 | RFID RxD |
| P0.8–P0.15 | LCD Data Lines |
| P0.16 | LCD RS |
| P0.17 | LCD RW |
| P0.18 | LCD EN |
| P0.12 | Relay / Door Lock |
| P1.16–P1.19 | Keypad Rows |
| P1.20–P1.23 | Keypad Columns |

---

# 🛠️ Project Setup

Initialize all peripherals before entering the main loop.

```c
InitUART0();
InitUART1();
InitLCD();
RTC_Init();
gsm_init();
InitKPM();
enable_eint1();
```

Required header files:

```
lpc21xx.h
string.h
lcd.h
lcd_defines.h
delay.h
types.h
uart_interrupt.h
defines.h
kpm.h
rtc.h
admin.h
```

---

# 📂 Project Modules

- LCD Driver
- UART Driver
- RFID Driver
- GSM Driver
- RTC Driver
- Matrix Keypad Driver
- OTP Generation
- OTP Verification
- Door Control
- Admin Mode
- External Interrupt

---

# 🚀 Applications

- Smart Home Security
- Office Access Control
- Server Rooms
- Bank Lockers
- Hostel Security
- Apartment Entry Systems
- Restricted Area Access

---

# ✅ Advantages

- Strong two-factor authentication
- OTP expiration enhances security
- Retry limit prevents brute-force attacks
- Modular Embedded C architecture
- Easy hardware integration
- Low-cost implementation
- Real-time user feedback

---

# 📈 Project Outcomes

- Developed a complete dual-authentication access system
- Integrated RFID and GSM communication
- Implemented RTC-based OTP generation
- Built interrupt-driven Admin Mode
- Improved understanding of ARM7 peripheral interfacing
- Demonstrated multi-UART embedded application design

---

# 📚 Learning Outcomes

This project demonstrates practical knowledge of:

- ARM7 LPC2148 Programming
- Embedded C
- UART Communication
- RFID Interfacing
- GSM AT Commands
- RTC Programming
- LCD Interfacing
- Matrix Keypad Interfacing
- External Interrupt Handling
- Embedded Security Systems

---

# 🔮 Future Improvements

- 🌐 Wi-Fi / Bluetooth connectivity for remote monitoring
- 🔑 TOTP-based OTP generation instead of SMS OTP
- 📁 SD Card or EEPROM access logging
- 📱 Mobile application integration
- ☁️ IoT-based cloud monitoring
- 👆 Fingerprint or Face Recognition as an additional authentication layer

---

# 👨‍💻 Author

**Kurumidde Vinay Kumar**

Embedded Systems Engineer

---

## ⭐ If you found this project useful, consider giving it a Star!
