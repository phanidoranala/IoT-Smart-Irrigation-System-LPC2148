/******************************************************************************
 * File Name    : kpm.h
 * Description  : Keypad module function declarations
 ******************************************************************************/

#ifndef __KPM_H__
#define __KPM_H__

#include "typedef.h"    
// Include user-defined datatypes

// Initialize keypad module
void Initkpm(void);

// Scan keypad columns
u32 ColScan(void);

// Check active row
u32 RowCheck(void);

// Check active column
u32 ColCheck(void);

// Scan pressed key
u32 keyScan(void);

// Read numeric value from keypad
u32 ReadNum(void);

// Read 2-digit input value
int Get2DigitValue(char *);

// Read 1-digit input value
int Get1DigitValue(char *);

#endif