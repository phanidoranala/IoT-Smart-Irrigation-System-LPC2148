/******************************************************************************
 * File Name    : UART_INT.c
 * Description  : UART0 communication with interrupt support
 ******************************************************************************/

#include <LPC21xx.H>           // LPC2148 register definitions
#include <string.h>            // String handling functions

#define UART_INT_ENABLE 1      // Enable UART interrupts

void InitUART0 (void);         // UART initialization prototype
void UART0_Tx(char ch);        // UART transmit prototype
char UART0_Rx(void);           // UART receive prototype

char buff[10],dummy;           // UART receive buffer and dummy variable

unsigned char i=0,ch,r_flag;  // Global variables for UART handling

/******************************************************************************
 * Function Name : UART0_isr
 * Description   : UART0 interrupt service routine
 ******************************************************************************/
void UART0_isr(void) __irq
{
	// Check whether receive interrupt occurred
	if((U0IIR & 0x04))
	{
		ch = U0RBR;	
		// Read received character from UART buffer

		if(i<200)
			buff[i++] = ch; 
			// Store received character into buffer
	}
	else
	{
		dummy=U0IIR; 
		// Read interrupt register to clear transmit interrupt
	}

	VICVectAddr = 0; 
	// End of interrupt
}

/******************************************************************************
 * Function Name : InitUART0
 * Description   : Initialize UART0 communication
 ******************************************************************************/
void InitUART0 (void)
{  
	PINSEL0 = 0x00000005; 
	// Configure P0.0 as TXD0 and P0.1 as RXD0

	U0LCR = 0x83;         
	// 8-bit data, 1 stop bit, no parity, DLAB enabled

	U0DLL = 97;           
	// Set baud rate for 9600

	U0LCR = 0x03;         
	// Disable DLAB

#if UART_INT_ENABLE > 0

	VICIntSelect = 0x00000000; 
	// Configure as IRQ interrupt

	VICVectAddr0 = (unsigned)UART0_isr;
	// Assign ISR address

	VICVectCntl0 = 0x20 | 6; 
	// Enable UART0 interrupt slot

	VICIntEnable = 1 << 6;   
	// Enable UART0 interrupt

	U0IER = 0x03;       
	// Enable RX and THRE interrupts

#endif
}

/******************************************************************************
 * Function Name : UART0_Tx
 * Description   : Transmit single character
 ******************************************************************************/
void UART0_Tx(char ch)
{ 
	while (!(U0LSR & 0x20));
	// Wait until transmitter becomes empty

	U0THR = ch;                
	// Send character
}

/******************************************************************************
 * Function Name : UART0_Rx
 * Description   : Receive single character
 ******************************************************************************/
char UART0_Rx(void)
{                     
	while (!(U0LSR & 0x01));
	// Wait until data is received

	return (U0RBR);
	// Return received character
}

/******************************************************************************
 * Function Name : UART0_Str
 * Description   : Send string through UART
 ******************************************************************************/
void UART0_Str(char *s)
{
	while(*s)
		UART0_Tx(*s++);
	// Send characters one by one
}

/******************************************************************************
 * Function Name : UART0_Int
 * Description   : Send integer through UART
 ******************************************************************************/
void UART0_Int(unsigned int n)
{
	unsigned char a[10]={0,0,0,0,0,0,0,0,0,0};
	int i=0;

	if(n==0)
	{
		UART0_Tx('0');
		return;
	}
	else
	{
		while(n>0)
		{
			a[i++]=(n%10)+48;
			// Convert digit into ASCII

			n=n/10;
		}

		--i;

		for(;i>=0;i--)
		{
			UART0_Tx(a[i]);
			// Send digits one by one
		}
	}
}

/******************************************************************************
 * Function Name : UART0_Float
 * Description   : Send float value through UART
 ******************************************************************************/
void UART0_Float(float f)
{
	int x;
	float temp;

	x=f;
	// Extract integer part

	UART0_Int(x);
	// Send integer part

	UART0_Tx('.');
	// Send decimal point

	temp=(f-x)*100;
	// Extract decimal part

	x=temp;

	UART0_Int(x);
	// Send decimal value
}

/******************************************************************************
 * Function Name : DelayS
 * Description   : Software delay in seconds
 ******************************************************************************/
void DelayS(unsigned int dly)
{
	unsigned int i;

	for(; dly>0; dly--) 
		for(i=1200000; i>0; i--);
}