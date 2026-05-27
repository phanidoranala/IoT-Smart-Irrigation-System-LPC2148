/******************************************************************************
 * File Name    : defines.h
 * Description  : Common bit manipulation macros
 ******************************************************************************/

#ifndef __DEFINES_H__          // Prevent multiple inclusion
#define __DEFINES_H__

#define SETBIT(WORD,BITPOS) (WORD|=1<<BITPOS) 
// Set particular bit

#define CLRBIT(WORD,BITPOS) (WORD&=~(1<<BITPOS)) 
// Clear particular bit

#define SSETBIT(WORD,BITPOS) (WORD=1<<BITPOS) 
// Set only selected bit

#define SCLRBIT(WORD,BITPOS) (WORD=1<<BITPOS) 
// Clear operation macro

#define CPLBIT(WORD,BITPOS) (WORD^=1<<BITPOS) 
// Toggle particular bit

#define WBYTE(WORD,SBITPOS,BYTE) \
WORD=(WORD&~(0XFF<<SBITPOS))|(BYTE<<SBITPOS) 
// Write byte into register

#define WNIBBLE(WORD,SBITPOS,NIBBLE) \
WORD=(WORD&~(0XF<<SBITPOS))|(NIBBLE<<SBITPOS) 
// Write nibble into register

#define WBIT(WORD,BITPOS,BIT) \
WORD=(WORD&~(1<<BITPOS))|(BIT<<BITPOS) 
// Write single bit

#define RBIT(WORD,BITPOS) ((WORD>>BITPOS)&1) 
// Read single bit

#define RNIBBLE(WORD,SBITPOS) ((WORD>>SBITPOS)&15) 
// Read nibble

#define RBYTE(WORD,SBITPOS) ((WORD>>SBITPOS)&255) 
// Read byte

#define READWRITEBIT(DWORD,DBIT,SBIT) DWORD=(DWORD&~(1<<DBIT))|\
(((DWORD>>SBIT)&1)<<DBIT)
// Copy source bit into destination bit

#define READWRITEBIT2(DWORD,DBIT,SWORD,SBIT) DWORD=(DWORD&~(1<<DBIT))|(((SWORD>>SBIT)&1)<<DBIT)
// Copy bit from another register

#endif