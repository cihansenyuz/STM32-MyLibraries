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

/* 
* Sends given byte to the display. It may be both data(char) or instruction.
*
* @param registerType 0: instruction, 1: char/data
* @param input byte to be send. Either instruction or char data
* @return none
*/
void displayWrite(char registerType, char input);

/* 
* Configurates display registers to initiliaze it. Displays "All is well!" once it is successfully initiliazed.
*
* @param none
* @return none
* @note sets communication mode 4 bits and display line 2 rows.
*/
void displayInit(void);

/* 
* Clears display content and moves cursor to the first position
*
* @param none
* @return none
*/
void displayClear(void);

/* 
* Sets on or off display screen, cursor and cursor blinking)
*
* @param D 1: display screen on, 0: off
* @param C 1: cursor on, 0: off
* @param B 1: blinking cursor on, 0: off
* @return none
*/
void displayOnOff(char D, char C, char B);

/* 
* Sends given string to be shown on the display where cursor rests.
*
* @param message string to be shown on the display
* @return none
*/
void displayMessage(char message[]);

/* 
* Moves cursor to the beginning of second line
*
* @param none
* @return none
*/
void displayNewLine(void);

/* 
* Moves cursor given number to the right from the current position 
*
* @param step number of position to the right
* @return none
*/
void displayShiftCursor(int step);
