/******************************************************************************
 * File Name    : m_kpm.c
 * Description  : Matrix keypad interfacing functions
 ******************************************************************************/

#include<lpc21xx.h>      
// LPC2148 register definitions

#include"typedef.h"      
// User-defined datatype definitions

#include"defines.h"      
// Bit manipulation macros

#include<string.h>       
// String handling functions

#include "delay.h"       
// Delay functions

#include"kpm_defines.h"  
// Keypad pin definitions

#include "lcd.h"         
// LCD display functions

// Lookup table for keypad buttons
u8 kpmLUT[4][4]={
	{'1','2','3','4'},
	{'5','6','7','8'},
	{'9','0','*','#'},
	{'A','B','C','1'}
};

/******************************************************************************
 * Function Name : Initkpm
 * Description   : Initialize keypad pins
 ******************************************************************************/
void Initkpm(void)
{
	WNIBBLE(IODIR1,ROW0,15);
	// Configure row pins as output
}

/******************************************************************************
 * Function Name : ColScan
 * Description   : Scan keypad columns
 ******************************************************************************/
u32 ColScan(void)
{
	return ((RNIBBLE(IOPIN1,COL0)<15)?0:1);
	// Return 0 if key pressed else 1
}

/******************************************************************************
 * Function Name : RowCheck
 * Description   : Detect active keypad row
 ******************************************************************************/
u32 RowCheck(void)
{
	u32 rno;

	for(rno=0;rno<4;rno++)
	{
		WNIBBLE(IOPIN1,ROW0,~(1<<rno));
		// Activate one row at a time

		if(ColScan()==0)
		{
			break;
			// Stop if key press detected
		}
	}

	WNIBBLE(IOPIN1,ROW0,0X0);
	// Reset all rows

	return rno;
}

/******************************************************************************
 * Function Name : ColCheck
 * Description   : Detect active keypad column
 ******************************************************************************/
u32 ColCheck(void)
{
	u32 cno;

	for(cno=0;cno<4;cno++)
	{
		if(RBIT(IOPIN1,(COL0+cno))==0)
		{
			break;
			// Stop if active column detected
		}
	}

	return cno;
}

/******************************************************************************
 * Function Name : keyScan
 * Description   : Detect pressed keypad key
 ******************************************************************************/
u32 keyScan(void)
{
	u32 rno,cno,keyV;

	while(ColScan());
	// Wait until key press

	rno=RowCheck();
	// Detect row

	cno=ColCheck();
	// Detect column

	keyV=kpmLUT[rno][cno];
	// Get actual key value

	while(!ColScan());
	// Wait until key release

	return keyV;
}

/******************************************************************************
 * Function Name : ReadNum
 * Description   : Read numeric value from keypad
 ******************************************************************************/
u32 ReadNum(void)
{
	u8 key;
	u32 sum=0;

	while(1)
	{
		key=keyScan();

		if(key>='0' && key<='9')
		{
			LCD_Init();

			Write_LCD(key);
			// Display pressed key

			sum=(sum*10)+(key-'0');
			// Convert ASCII to integer
		}
		else if(key=='=')
		{
			break;
			// Exit on '=' key
		}
	}

	return sum;
}