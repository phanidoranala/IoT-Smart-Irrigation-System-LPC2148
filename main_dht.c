/******************************************************************************
 * File Name    : main_dht11.c
 * Description  : Main control logic for Smart Irrigation System
 ******************************************************************************/

#include <lpc214x.h>             // LPC2148 register definitions

#include "uart0.h"               // UART communication functions

#include "delay.h"               // Delay functions

#include "lcd.h"                 // LCD display functions

#include "esp01.h"               // ESP8266 WiFi functions

#include "dht11.h"               // DHT11 sensor functions

#include "kpm.h"                 // Keypad functions

#define FOSC      12000000       // Crystal frequency

#define CCLK  	  5*FOSC         // CPU clock frequency

#define PCLK  	  CCLK/4         // Peripheral clock frequency

#define PREINT_VAL  ((PCLK/32768)-1)
// RTC integer divider value

#define PREFRAC_VAL  (PCLK - ((PREINT_VAL + 1) * 32768))
// RTC fractional divider value

/******************************************************************************
 * Function Name : rtc_init
 * Description   : Initialize RTC timing values
 ******************************************************************************/
void rtc_init()
{
	SEC=20;                        // Initialize seconds

	MIN=21;                        // Initialize minutes

	HOUR=12;                       // Initialize hour
}

extern char buff[100],dummy;     // UART receive buffer variables

extern unsigned char i,ch,r_flag;
// UART variables

char I_t1,I_t2,I_t3;             
// Irrigation timings for different conditions

char T_t1,H_t1,T_t2,H_t2,T_t3,H_t3;
// Temperature and humidity threshold values

extern volatile int flag;        
// External interrupt flag

unsigned char humidity_integer, humidity_decimal;
unsigned char temp_integer, temp_decimal, checksum;
// DHT11 sensor data variables

extern int humidity,temperature;
// Global humidity and temperature values

int flag1=0,flag2=0;
// Flags for configuration completion

/******************************************************************************
 * Function Name : SetIrrigationTiming
 * Description   : Set irrigation motor timings
 ******************************************************************************/
void SetIrrigationTiming(void)
{
	int val;                       // Variable for keypad input

	flag1=1;                      // Set irrigation timing flag

	Write_CMD_LCD(0x01);          // Clear LCD

	Write_str_LCD("Set Motor Time");
	// Display menu title

	delay_ms(800);                // Delay for readability

	val = Get1DigitValue("Enter HighTem LowHum:");
	// Get irrigation time for high temp low humidity

	if(val != -1) I_t1 = val;
	// Store timing value

	Write_CMD_LCD(0x01);          // Clear LCD

	val = Get1DigitValue("Enter ModTem ModHum:");
	// Get irrigation time for moderate condition

	if(val != -1) I_t2 = val;
	// Store timing

	Write_CMD_LCD(0x01);          // Clear LCD

	val = Get1DigitValue("Enter LowTemp HighHum:");
	// Get irrigation time for low temp high humidity

	if(val != -1) I_t3 = val;
	// Store timing

	Write_CMD_LCD(0x01);          // Clear LCD

	Write_CMD_LCD(0x80);          // Move cursor

	Write_str_LCD("Saved Successfully");
	// Display success message

	delay_ms(1000);               // Wait

	Write_CMD_LCD(0X01);          // Clear LCD
}

/******************************************************************************
 * Function Name : Set_Temp_Humidity
 * Description   : Set temperature and humidity thresholds
 ******************************************************************************/
void Set_Temp_Humidity(void)
{
	int val;                      // Variable for keypad input

	flag2=1;                     // Set threshold configuration flag

	Write_CMD_LCD(0x01);         // Clear LCD

	Write_str_LCD("Set Temp & Hum");
	// Display title

	delay_ms(800);               // Delay

	Write_str_LCD("Temp Range (0-50)");
	// Display valid temperature range

	val = Get2DigitValue("ENTER TEMPRATURE1:");
	// Read first temperature threshold

	if(val != -1) T_t1 = val;
	// Store threshold

	Write_str_LCD("Humrange is (0-99)");
	// Display humidity range

	val = Get2DigitValue("ENTER HUMIDITY1:");
	// Read first humidity threshold

	if(val != -1) H_t1 = val;
	// Store humidity threshold

	Write_str_LCD("Temp Range (0-50)");
	// Display range

	val = Get2DigitValue("ENTER TEMPRATURE2:");
	// Read second temperature threshold

	if(val != -1) T_t2 = val;
	// Store value

	Write_str_LCD("Humrange is (0-100)");
	// Display range

	val = Get2DigitValue("ENTER HUMIDITY2:");
	// Read second humidity threshold

	if(val != -1) H_t2 = val;
	// Store value

	Write_str_LCD("Temp Range (0-50)");
	// Display range

	val = Get2DigitValue("ENTER TEMPRATURE3:");
	// Read third temperature threshold

	if(val != -1) T_t3 = val;
	// Store value

	Write_str_LCD("Humrange is (0-100)");
	// Display range

	val = Get2DigitValue("ENTER HUMIDITY3:");
	// Read third humidity threshold

	if(val != -1) H_t3 = val;
	// Store value

	Write_CMD_LCD(0x01);         // Clear LCD

	Write_str_LCD("Saved");
	// Display saved message

	delay_ms(1000);              // Wait

	Write_CMD_LCD(0X01);         // Clear LCD
}