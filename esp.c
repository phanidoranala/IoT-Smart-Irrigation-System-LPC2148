/******************************************************************************
 * File Name    : esp01.c
 * Description  : ESP8266 WiFi communication using AT commands
 * Purpose      : Connect ESP8266 to WiFi and send sensor data to ThingSpeak
 ******************************************************************************/

#include <string.h>              // Header file for string handling functions

#include "uart0.h"               // UART communication function declarations

#include "delay.h"               // Delay function declarations

#include "lcd.h"                 // LCD function declarations

extern char buff[200];           // External UART receive buffer

extern unsigned char i;          // UART buffer index variable

/******************************************************************************
 * Function Name : esp01_connectAP
 * Description   : Connect ESP8266 module to WiFi Access Point
 ******************************************************************************/
void esp01_connectAP()
{
	Write_CMD_LCD(0x01);                 // Clear LCD display
	Write_CMD_LCD(0x80);                 // Move cursor to first line first position
	Write_str_LCD("AT");                 // Display AT command on LCD
	delay_ms(1000);                      // Wait for 1 second

	UART0_Str("AT\r\n");                 // Send AT command to ESP8266

	i=0;                                 // Reset UART receive index
	memset(buff,'\0',200);               // Clear UART receive buffer

	while(i<4);                          // Wait until response received

	delay_ms(500);                       // Small stabilization delay

	buff[i] = '\0';                      // Add null terminator to string

	Write_CMD_LCD(0x01);                 // Clear LCD display
	Write_CMD_LCD(0x80);                 // Move cursor to first line
	Write_str_LCD(buff);                 // Display ESP8266 response

	delay_ms(2000);                      // Wait for 2 seconds

	if(strstr(buff,"OK"))                // Check whether response contains OK
	{
		Write_CMD_LCD(0xC0);             // Move cursor to second line
		Write_str_LCD("OK");             // Display success message
		delay_ms(1000);                  // Wait for 1 second
	}
	else
	{
		Write_CMD_LCD(0xC0);             // Move cursor to second line
		Write_str_LCD("ERROR");          // Display error message
		delay_ms(1000);                  // Wait for 1 second
		return;                          // Exit function
	}

	Write_CMD_LCD(0x01);                 // Clear LCD
	Write_CMD_LCD(0x80);                 // Move cursor to first line
	Write_str_LCD("ATE0");               // Display ATE0 command
	delay_ms(1000);                      // Wait for 1 second

	UART0_Str("ATE0\r\n");               // Disable command echo from ESP8266

	i=0;                                 // Reset receive index
	memset(buff,'\0',200);               // Clear buffer

	while(i<4);                          // Wait for response

	delay_ms(500);                       // Small delay

	buff[i] = '\0';                      // Add string terminator

	Write_CMD_LCD(0x01);                 // Clear LCD
	Write_CMD_LCD(0x80);                 // Move cursor to first line
	Write_str_LCD(buff);                 // Display response

	delay_ms(2000);                      // Wait for 2 seconds

	if(strstr(buff,"OK"))                // Check whether echo disabled successfully
	{
		Write_CMD_LCD(0xC0);             // Move cursor to second line
		Write_str_LCD("OK");             // Display success
		delay_ms(1000);                  // Wait for 1 second
	}
	else
	{
		Write_CMD_LCD(0xC0);             // Move cursor to second line
		Write_str_LCD("ERROR");          // Display error
		delay_ms(1000);                  // Wait
		return;                          // Exit function
	}

	Write_CMD_LCD(0x01);                 // Clear LCD
	Write_CMD_LCD(0x80);                 // Move cursor
	Write_str_LCD("AT+CIPMUX");          // Display connection mode command
	delay_ms(1000);                      // Wait

	UART0_Str("AT+CIPMUX=0\r\n");        // Configure ESP8266 for single connection mode

	i=0;                                 // Reset buffer index
	memset(buff,'\0',200);               // Clear buffer

	while(i<4);                          // Wait for response

	delay_ms(500);                       // Small delay

	buff[i] = '\0';                      // Add null terminator

	Write_CMD_LCD(0x01);                 // Clear LCD
	Write_CMD_LCD(0x80);                 // Move cursor
	Write_str_LCD(buff);                 // Display response

	delay_ms(2000);                      // Wait

	if(strstr(buff,"OK"))                // Check command execution status
	{
		Write_CMD_LCD(0xC0);             // Move cursor
		Write_str_LCD("OK");             // Display success
		delay_ms(1000);                  // Wait
	}
	else
	{
		Write_CMD_LCD(0xC0);             // Move cursor
		Write_str_LCD("ERROR");          // Display failure
		delay_ms(1000);                  // Wait
		return;                          // Exit function
	}

	Write_CMD_LCD(0x01);                 // Clear LCD
	Write_CMD_LCD(0x80);                 // Move cursor
	Write_str_LCD("AT+CWQAP");           // Display disconnect command
	delay_ms(1000);                      // Wait

	UART0_Str("AT+CWQAP\r\n");           // Disconnect previously connected WiFi network

	i=0;                                 // Reset buffer index
	memset(buff,'\0',200);               // Clear buffer

	while(i<4);                          // Wait for response

	delay_ms(1500);                      // Wait for disconnection

	buff[i] = '\0';                      // Add string terminator

	Write_CMD_LCD(0x01);                 // Clear LCD
	Write_CMD_LCD(0x80);                 // Move cursor
	Write_str_LCD(buff);                 // Display response

	delay_ms(2000);                      // Wait

	if(strstr(buff,"OK"))                // Check disconnection status
	{
		Write_CMD_LCD(0xC0);             // Move cursor
		Write_str_LCD("OK");             // Display success
		delay_ms(1000);                  // Wait
	}
	else
	{
		Write_CMD_LCD(0xC0);             // Move cursor
		Write_str_LCD("ERROR");          // Display failure
		delay_ms(1000);                  // Wait
		return;                          // Exit function
	}

	Write_CMD_LCD(0x01);                 // Clear LCD
	Write_CMD_LCD(0x80);                 // Move cursor
	Write_str_LCD("AT+CWJAP");           // Display WiFi join command
	delay_ms(1000);                      // Wait

	UART0_Str("AT+CWJAP=\"AK\",\"123456789\"\r\n");
	// Connect ESP8266 to WiFi network using SSID and password

	i=0;                                 // Reset buffer index
	memset(buff,'\0',200);               // Clear receive buffer

	while(i<4);                          // Wait for response

	delay_ms(2500);                      // Wait for WiFi connection

	buff[i] = '\0';                      // Add string terminator

	Write_CMD_LCD(0x01);                 // Clear LCD
	Write_CMD_LCD(0x80);                 // Move cursor
	Write_str_LCD(buff);                 // Display WiFi response

	delay_ms(2000);                      // Wait

	if(strstr(buff,"WIFI CONNECTED"))    // Check WiFi connection status
	{
		Write_CMD_LCD(0xC0);             // Move cursor
		Write_str_LCD("OK");             // Display connection success
		delay_ms(1000);                  // Wait
	}
	else
	{
		Write_CMD_LCD(0xC0);             // Move cursor
		Write_str_LCD("ERROR");          // Display connection failure
		delay_ms(1000);                  // Wait
		return;                          // Exit function
	}
}

/******************************************************************************
 * Function Name : esp01_sendToThingspeak1
 * Description   : Send temperature and humidity data to ThingSpeak
 ******************************************************************************/
void esp01_sendToThingspeak1(float val1,float val2)
{
	delay_ms(1000);                               // Wait before communication starts

	UART0_Str("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");
	// Open TCP connection with ThingSpeak server

	i=0;                                          // Reset UART receive index
	memset(buff,'\0',200);                        // Clear UART receive buffer

	while(i<5);                                   // Wait for response

	delay_ms(2500);                               // Wait for connection establishment

	buff[i] = '\0';                               // Add null terminator

	delay_ms(2000);                               // Stabilization delay

	if(strstr(buff,"CONNECT") || strstr(buff,"ALREADY CONNECTED"))
	{
		delay_ms(1000);                           // Small delay

		UART0_Str("AT+CIPSEND=64\r\n");
		// Enable data sending mode

		i=0;                                      // Reset UART index
		memset(buff,'\0',200);                    // Clear buffer

		delay_ms(500);                            // Wait for prompt

		UART0_Str("GET /update?api_key=HWVLM0FXWP9G7IAM&field1=");
		// Send HTTP GET request with API key

		UART0_Float(val2);                        // Send temperature value

		UART0_Str("&field2=");                    // Move to field2

		UART0_Float(val1);                        // Send humidity value

		UART0_Str("\r\n\r\n");                    // End HTTP request

		delay_ms(5000);                           // Wait for upload
		delay_ms(5000);                           // Additional wait

		buff[i] = '\0';                           // Add string terminator

		delay_ms(2000);                           // Wait for response

		if(strstr(buff,"SEND OK"))                // Check upload success
		{
			delay_ms(1000);                       // Wait for 1 second
		}
		else
		{
			Write_CMD_LCD(0x01);                 // Clear LCD
			Write_str_LCD("TEMP NOT UPDATED");   // Display failure
			delay_ms(1000);                      // Wait
			Write_CMD_LCD(0x01);                 // Clear LCD
		}
	}
	else
	{
		Write_CMD_LCD(0xC0);                     // Move cursor
		Write_str_LCD("ERROR1");                 // Display error
		delay_ms(1000);                          // Wait
		Write_CMD_LCD(0x01);                     // Clear LCD
		return;                                  // Exit function
	}
}