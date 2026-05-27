/******************************************************************************
 * File Name    : lcd.h
 * Description  : LCD function declarations
 ******************************************************************************/

void Write_CMD_LCD(char);          
// Send command to LCD

void Write_DAT_LCD(char);          
// Send data to LCD

void Write_LCD(char);              
// General LCD write function

void LCD_Init(void);               
// Initialize LCD

void Write_str_LCD(char *);        
// Display string on LCD

void Write_int_LCD(signed int);    
// Display integer on LCD

void Write_float_LCD(float f,char);
// Display floating point value on LCD