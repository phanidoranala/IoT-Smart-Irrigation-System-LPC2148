/******************************************************************************
 * File Name    : m_lcd.h
 * Description  : LCD pin definitions, command macros and function declarations
 ******************************************************************************/

#ifndef __M_LCD_H__
#define __M_LCD_H__

#include "typedef.h"

// ================= LCD DATA PIN DEFINITIONS ================= //

// LCD data pins connected from P0.8 onwards
#define LCD_DATA 8

// ================= LCD CONTROL PIN DEFINITIONS ================= //

// Register Select pin connected to P0.16
#define RS 16

// Read/Write pin connected to P0.17
#define RW 17

// Enable pin connected to P0.18
#define EN 18

// ================= LCD COMMAND DEFINITIONS ================= //

// Clear LCD screen
#define CLEAR_LCD 0X01

// Return cursor to home position
#define RET_CUR_HOME 0x02

// Display OFF
#define DISP_OFF 0x08

// Display ON without cursor
#define DISP_ON 0x0C

// Display ON with cursor enabled
#define DISP_ON_CUR_ON 0x0E

// Display ON with blinking cursor
#define DISP_ON_CUR_BLINK 0x0F

// 8-bit mode with 1 line
#define MODE_8BIT_1LINE 0X30

// 8-bit mode with 2 lines
#define MODE_8BIT_2LINE 0X38

// 4-bit mode with 1 line
#define MODE_4BIT_1LINE 0X20

// 4-bit mode with 2 lines
#define MODE_4BIT_2LINE 0X28

// Move cursor to line 1 position 0
#define GOTO_LINE1_POS0 0X80

// Move cursor to line 2 position 0
#define GOTO_LINE2_POS0 0XC0

// Move cursor to line 3 position 0
#define GOTO_LINE3_POS0 0X94

// Move cursor to line 4 position 0
#define GOTO_LINE4_POS0 0XD4

// Shift cursor right
#define SHIFT_CUR_RIGHT 0X06

// Shift display left
#define SHIFT_DISP_LEFT 0x10

// Shift display right
#define SHIFT_DISP_RIGHT 0X14

// Access CGRAM memory
#define GOTO_CGRAM 0x40

// ================= LCD FUNCTION DECLARATIONS ================= //

// Write raw data to LCD
void WriteLCD(u8 data);

// Send command to LCD
void CmdLCD(u8 cmd);

// Display single character on LCD
void CharLCD(u8 ascii);

// Initialize LCD module
void InitLCD(void);

// Display string on LCD
void StrLCD(s8* p);

// Display unsigned integer on LCD
void U32LCD(u32 n);

// Display floating point value on LCD
void F32LCD(f32 data,u32 nd);

// Create custom character in CGRAM
void BuildCGRAM(u8* p, u8 nb);

// Display binary value on LCD
void BinLCD(u8 data,u8 nb);

// Display hexadecimal value on LCD
void HEXLCD(u32 n);

#endif