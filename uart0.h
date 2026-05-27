/******************************************************************************
 * File Name    : uart0.h
 * Description  : UART0 function declarations and baud rate configuration
 ******************************************************************************/

#ifndef _UART0_H_              // Prevent multiple inclusion
#define _UART0_H_

#define UART_INT_ENABLE 1      // Enable UART interrupt

// ---------------- UART Baud Rate Calculation ---------------- //

#define FOSC      12000000     // Crystal oscillator frequency = 12MHz

#define CCLK  	  5*FOSC       // CPU clock frequency

#define PCLK  	  CCLK/4       // Peripheral clock frequency

#define BAUD  	  9600         // UART baud rate

#define DIVISOR   (PCLK/(16 * BAUD)) 
// Baud rate divisor calculation

// ---------------- Function Declarations ---------------- //

void InitUART0(void);          
// Initialize UART0 communication

void UART0_Tx(char ch);        
// Transmit single character

char UART0_Rx(void);           
// Receive single character

void UART0_Str(char *);        
// Transmit string

void UART0_Int(unsigned int);  
// Transmit integer value

void UART0_Float(float);       
// Transmit float value

#endif