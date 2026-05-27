/******************************************************************************
 * File Name    : esp01.c
 * Description  : ESP8266 WiFi communication using AT commands
 ******************************************************************************/

#include <string.h>              // Header file for string handling functions

#include "uart0.h"               // UART communication function declarations

#include "delay.h"               // Delay function declarations

#include "lcd.h"                 // LCD function declarations

extern char buff[200];           // External UART receive buffer

extern unsigned char i;          // External UART buffer index variable

/******************************************************************************
 * Function Name : esp01_connectAP
 * Description   : Connect ESP8266 module to WiFi Access Point
 ******************************************************************************/
void esp01_connectAP()
{
	Write_CMD_LCD(0x01);                 // Clear LCD display

	Write_CMD_LCD(0x80);                 // Move cursor to first line first position

	Write_str_LCD("AT");                 // Display "AT" on LCD

	delay_ms(1000);                      // Wait for 1 second

	UART0_Str("AT\r\n");                 // Send AT command to ESP8266

	i=0;                                 // Reset UART receive index

	memset(buff,'\0',200);               // Clear UART receive buffer

	while(i<4);                          // Wait until response received

	delay_ms(500);                       // Small delay

	buff[i] = '\0';                      // Add null character to end string

	Write_CMD_LCD(0x01);                 // Clear LCD

	Write_CMD_LCD(0x80);                 // Move cursor to first line

	Write_str_LCD(buff);                 // Display ESP response on LCD

	delay_ms(2000);                      // Wait for 2 seconds

	if(strstr(buff,"OK"))                // Check whether response contains "OK"
	{
		Write_CMD_LCD(0xC0);             // Move cursor to second line

		Write_str_LCD("OK");             // Display OK message

		delay_ms(1000);                  // Wait for 1 second
	}
	else
	{
		Write_CMD_LCD(0xC0);             // Move cursor to second line

		Write_str_LCD("ERROR");          // Display ERROR message

		delay_ms(1000);                  // Wait for 1 second

		return;                          // Exit function
	}

	Write_CMD_LCD(0x01);                 // Clear LCD

	Write_CMD_LCD(0x80);                 // Move cursor to first line

	Write_str_LCD("ATE0");               // Display ATE0 command

	delay_ms(1000);                      // Wait for 1 second

	UART0_Str("ATE0\r\n");               // Send ATE0 command to disable echo

	i=0;                                 // Reset buffer index

	memset(buff,'\0',200);               // Clear receive buffer

	while(i<4);                          // Wait for response

	delay_ms(500);                       // Small delay

	buff[i] = '\0';                      // Add string terminator

	Write_CMD_LCD(0x01);                 // Clear LCD

	Write_CMD_LCD(0x80);                 // Move cursor to first line

	Write_str_LCD(buff);                 // Display response on LCD

	delay_ms(2000);                      // Wait for 2 seconds

	if(strstr(buff,"OK"))                // Check whether echo disabled
	{
		Write_CMD_LCD(0xC0);             // Move cursor to second line

		Write_str_LCD("OK");             // Display OK

		delay_ms(1000);                  // Wait for 1 second
	}
	else
	{
		Write_CMD_LCD(0xC0);             // Move cursor to second line

		Write_str_LCD("ERROR");          // Display ERROR

		delay_ms(1000);                  // Wait for 1 second

		return;                          // Exit function
	}

	Write_CMD_LCD(0x01);                 // Clear LCD

	Write_CMD_LCD(0x80);                 // Move cursor to first line

	Write_str_LCD("AT+CIPMUX");          // Display CIPMUX command

	delay_ms(1000);                      // Wait for 1 second

	UART0_Str("AT+CIPMUX=0\r\n");        // Enable single connection mode

	i=0;                                 // Reset index

	memset(buff,'\0',200);               // Clear buffer

	while(i<4);                          // Wait for response

	delay_ms(500);                       // Small delay

	buff[i] = '\0';                      // Add null terminator

	Write_CMD_LCD(0x01);                 // Clear LCD

	Write_CMD_LCD(0x80);                 // Move cursor to first line

	Write_str_LCD(buff);                 // Display response

	delay_ms(2000);                      // Wait for 2 seconds

	if(strstr(buff,"OK"))                // Check command status
	{
		Write_CMD_LCD(0xC0);             // Move cursor to second line

		Write_str_LCD("OK");             // Display OK

		delay_ms(1000);                  // Wait for 1 second
	}
	else
	{
		Write_CMD_LCD(0xC0);             // Move cursor to second line

		Write_str_LCD("ERROR");          // Display ERROR

		delay_ms(1000);                  // Wait for 1 second

		return;                          // Exit function
	}
}