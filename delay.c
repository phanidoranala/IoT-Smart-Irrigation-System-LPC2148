/******************************************************************************
 * File Name    : delay.c
 * Description  : Software delay functions
 ******************************************************************************/

#include "typedef.h"      // Include datatype definitions

void delay_us(u32 dlys)
{
	for(dlys*=12;dlys>0;dlys--);
	// Generate microsecond delay
}

void delay_ms(u32 dlys)
{
	for(dlys*=12000;dlys>0;dlys--);
	// Generate millisecond delay
}

void delay_s(u32 dlys)
{
	for(dlys*=12000000;dlys>0;dlys--);
	// Generate second delay
}