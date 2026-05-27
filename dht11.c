/******************************************************************************
 * File Name    : dht11.c
 * Description  : DHT11 sensor interfacing functions
 ******************************************************************************/

#include <lpc214x.h>         // LPC2148 register definitions

#include "delay.h"           // Delay function declarations

#include "defines.h"         // Bit manipulation macro definitions

#define input 0              // Input direction definition

#define output 1             // Output direction definition

#define DHT11 4              
// DHT11 data pin connected to P0.4

/******************************************************************************
 * Function Name : dht11_request
 * Description   : Send start signal to DHT11 sensor
 ******************************************************************************/
void dht11_request(void)
{
	WRITEBIT(IODIR0,DHT11,output);
	// Configure DHT11 pin as output

	WRITEBIT(IOPIN0,DHT11,0);
	// Pull DHT11 pin LOW

	delay_ms(20);
	// Keep pin LOW for minimum 18ms

	WRITEBIT(IOPIN0,DHT11,1);
	// Pull DHT11 pin HIGH
}

/******************************************************************************
 * Function Name : dht11_response
 * Description   : Wait for DHT11 response sequence
 ******************************************************************************/
void dht11_response(void)
{
	WRITEBIT(IODIR0,DHT11,input);
	// Configure DHT11 pin as input

	while(READBIT(IOPIN0,DHT11) == 1);
	// Wait until DHT11 pulls line LOW

	while(READBIT(IOPIN0,DHT11) == 0);
	// Wait until DHT11 pulls line HIGH

	while(READBIT(IOPIN0,DHT11) == 1);
	// Wait until DHT11 response ends
}

/******************************************************************************
 * Function Name : dht11_data
 * Description   : Read 8-bit data from DHT11 sensor
 ******************************************************************************/
unsigned char dht11_data(void)
{
	unsigned char count;
	// Variable for bit counter

	unsigned char data = 0;
	// Variable to store received data

	for(count = 0; count<8 ; count++)
	// Loop to receive 8 bits
	{
		while(READBIT(IOPIN0,DHT11) == 0);
		// Wait until line becomes HIGH

		delay_us(30);
		// Wait 30 microseconds

		if (READBIT(IOPIN0,DHT11))
		// Check whether received bit is 1
		{
			data = ((data<<1) | 0x01);
			// Shift left and store logic 1
		}
		else
		{
			data = (data<<1);
			// Shift left and store logic 0
		}

		while(READBIT(IOPIN0,DHT11));
		// Wait until signal becomes LOW
	}

	return data;
	// Return received byte
}