/**
  ******************************************************************************
  * @file    1602_i2c_driver.h
  * @author  Cihan Senyuz
  * @brief   Header for 1602_i2c_driver.c file.
  *                 This file contains the common defines of the application.
  *     
  *     --- pin configuration ---
  *     P0	RS
  *     P1	RW
  *     P2	E
  *     P3	Screen light (always 1)
  *
  *     P4	Data4
  *     P5	Data5
  *     P6	Data6
  *     P7	Data7
  *     
  *     --- write operation ---
  *     RS goes 1 or 0 according to data type
  *     at the same time RW goes 0
  *     then wait a bit and E goes 1 (keep RS, RW as is)
  *     then wait a bit and push data (keep RS, RW, E as is)
  *     then wait a bit and E goes 0 (keep RS, RW as is)
  *     
  *     --- read operation ---
  *     RS goes 1 or 0 according to data type
  *     at the same time RW goes 1
  *     then wait a bit and E goes 1 (keep RS, RW as is)
  *     then wait a bit and push data (keep RS, RW, E as is)
  *     then wait a bit and E goes 0 (keep RS, RW as is)
  * 	
  * 
  * @note   Source code depends on i2c_driver.h and systick_delay.h libraries
  ******************************************************************************
  */

#include "i2c_driver.h"
#include "systick_delay.h"

#define i2c 2
#define displayAddress 0x44

void displayWrite(char type, char data);
void displayInit(void);
void displayClear(void);
void displayOnOff(char D, char C, char B);
void displayMessage(char message[]);
void displayNewLine(void);
void displayShiftCursor(int step);
