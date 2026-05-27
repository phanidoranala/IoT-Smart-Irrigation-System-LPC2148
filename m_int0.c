/******************************************************************************
 * File Name    : m_int0.c
 * Description  : External interrupt handling using EINT0
 ******************************************************************************/

#include<lpc21xx.h>      
// LPC2148 register definitions

#include"typedef.h"      
// User-defined datatype definitions

#include"delay.h"        
// Delay functions

// Configuration value for EINT0 pin selection
#define EINT0_INPUT_PIN 0x000000C5

// VIC channel number for EINT0
#define EINT0_VIC_CHNO 15

// Global interrupt flag variable
volatile int flag=0;

// ISR function declaration
void eint0_isr(void) __irq;

/******************************************************************************
 * Function Name : init_int
 * Description   : Initialize external interrupt INT0
 ******************************************************************************/
void init_int(void)
{
	// Configure interrupt pin function
	PINSEL0|=EINT0_INPUT_PIN;

	// Enable EINT0 interrupt in VIC
	VICIntEnable=1<<EINT0_VIC_CHNO;

	// Enable vector slot and assign interrupt channel
	VICVectCntl1=(1<<5)|EINT0_VIC_CHNO;

	// Assign ISR address
	VICVectAddr1=(u32)eint0_isr;

	// Configure interrupt as edge triggered
	EXTMODE|=1<<1;
}

/******************************************************************************
 * Function Name : eint0_isr
 * Description   : External interrupt service routine
 ******************************************************************************/
void eint0_isr(void) __irq
{
	delay_ms(20);
	// Debounce delay

	flag=1;
	// Set interrupt flag

	EXTINT=1<<1;
	// Clear external interrupt flag

	VICVectAddr=0;
	// End of interrupt
}