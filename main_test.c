/******************************************************************************
 * File Name    : main_test.c
 * Description  : Main program for Smart Irrigation System
 ******************************************************************************/

#include<lpc21xx.h>          // LPC2148 register definitions

#include "lcd.h"             // LCD function declarations

#include "kpm.h"             // Keypad module functions

#include "uart0.h"           // UART communication functions

#include "esp01.h"           // ESP8266 WiFi module functions

#include "rtc.h"             // RTC related functions

#include "delay.h"           // Delay functions

#include "m_int0.h"          // External interrupt functions

#include "uart0.h"           // UART header included again

#include "dht11.h"           // DHT11 sensor functions

#include "main_dht11.h"      // Main DHT11 related functions

#include "main_code.h"       // Additional project functions

#define SEND_INTERVAL 3      
// Send data to ThingSpeak every 3 minutes

extern int flag;             
// External interrupt flag variable

int humidity,temperature;    
// Variables to store humidity and temperature

int last_sent_min=-1;        
// Stores last sent minute value

/******************************************************************************
 * Function Name : main
 * Description   : Main execution function
 ******************************************************************************/
int main()
{
	unsigned char humidity_integer, humidity_decimal;
	// Variables for humidity data

	unsigned char temp_integer, temp_decimal;
	// Variables for temperature data

	unsigned char checksum;
	// Variable for checksum verification

	IODIR0=1<<20;
	// Configure P0.20 as output for motor control

	IODIR0&=~(1<<21);
	// Configure P0.21 as input for soil moisture sensor

	InitUART0();
	// Initialize UART communication

	LCD_Init();
	// Initialize LCD display

	Write_str_LCD("SMART IRRIGATION");
	// Display project title

	delay_ms(1000);
	// Wait for 1 second

	Write_CMD_LCD(0x01);
	// Clear LCD

	Initkpm();
	// Initialize keypad module

	init_int();
	// Initialize external interrupt

	rtc_init();
	// Initialize RTC

	esp01_connectAP();
	// Connect ESP8266 to WiFi

	delay_ms(1000);
	// Wait for connection stability

	Write_CMD_LCD(0x01);
	// Clear LCD

	while(1)
	// Infinite loop
	{
		delay_s(3);
		// Wait for 3 seconds

		dht11_request();
		// Send start signal to DHT11

		dht11_response();
		// Wait for DHT11 response

		humidity_integer = dht11_data();
		// Read humidity integer value

		humidity_decimal = dht11_data();
		// Read humidity decimal value

		temp_integer = dht11_data();
		// Read temperature integer value

		temp_decimal = dht11_data();
		// Read temperature decimal value

		checksum = dht11_data();
		// Read checksum byte

		humidity=humidity_integer+humidity_decimal;
		// Calculate total humidity

		temperature=temp_integer+temp_decimal;
		// Calculate total temperature

		if((humidity_integer + humidity_decimal + temp_integer + temp_decimal) != checksum)
		// Verify checksum
		{
			Write_str_LCD("Checksum Error\r\n");
			// Display checksum error
		}
		else
		{
			Write_CMD_LCD(0x80);
			// Move cursor to first line

			Write_str_LCD("Humidity : ");
			// Display humidity label

			Write_int_LCD(humidity_integer);
			// Display humidity integer value

			Write_DAT_LCD('.');
			// Display decimal point

			Write_int_LCD(humidity_decimal);
			// Display humidity decimal value

			Write_str_LCD(" % RH ");
			// Display humidity unit

			Write_CMD_LCD(0xC0);
			// Move cursor to second line

			Write_str_LCD("Temprature : ");
			// Display temperature label

			Write_int_LCD(temp_integer);
			// Display temperature integer value

			Write_DAT_LCD('.');
			// Display decimal point

			Write_int_LCD(temp_decimal);
			// Display temperature decimal value

			Write_DAT_LCD(223);
			// Display degree symbol

			Write_str_LCD("C");
			// Display Celsius symbol

			Write_CMD_LCD(0xD4);
			// Move cursor to fourth line

			Write_str_LCD("Checksum : ");
			// Display checksum label

			Write_int_LCD(checksum);
			// Display checksum value

			delay_ms(3000);
			// Wait for 3 seconds

			if((MIN%SEND_INTERVAL==0) && (MIN!=last_sent_min))
			// Check whether data should be sent
			{
				esp01_sendToThingspeak1(humidity,temperature);
				// Send humidity and temperature to ThingSpeak

				last_sent_min=MIN;
				// Update last sent minute
			}
		}

		menu_base_int();
		// Handle interrupt based menu

		compare_temp_hum();
		// Compare sensor values and control motor
	}
}