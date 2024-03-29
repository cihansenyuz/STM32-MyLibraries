#include "1602_i2c_driver.h"

/* 
* Sends given byte to the display. It may be both data(char) or instruction.
*
* @param registerType 0: instruction, 1: char/data
* @param input byte to be send. Either instruction or char data
* @return none
*/
void displayWrite(char registerType, char input)
{
	/* setting RS and RW */
	if(registerType==0) /* instruction register */
	{
		i2c_write(i2c, displayAddress, 0x08);
		delayMS(1);
		/* E high */
		i2c_write(i2c, displayAddress, 0x0C); /* to get ready to give data */
		delayMS(1);
		/* data part1 */
		i2c_write(i2c, displayAddress, ((input & 0xF0) | 0x0C)); /* to take first half of data and keep control regs the same */
		delayMS(1);
		/* E low */
		i2c_write(i2c, displayAddress, ((input & 0xF0) | 0x08)); /* to make data to be read and not to lose data*/
		delayMS(1);
		/* E high */
		i2c_write(i2c, displayAddress, 0x0C); /* to get ready to give second part data */
		/* data part2 */
		i2c_write(i2c, displayAddress, (((input << 4) & 0xF0) | 0x0C)); /* second part of data */
		delayMS(1);
		/* E low */
		i2c_write(i2c, displayAddress, (((input << 4) & 0xF0) | 0x08));
		delayMS(1);
	}
	else if(registerType==1) /* data register */
	{	
		i2c_write(i2c, displayAddress, 0x09);
		delayMS(1);
		/* E high */
		i2c_write(i2c, displayAddress, 0x0D); /* to get ready to give data */
		delayMS(1);
		/* data part1 */
		i2c_write(i2c, displayAddress, ((input & 0xF0) | 0x0D)); /* to take first half of data and keep control regs the same */
		delayMS(1);
		/* E low */
		i2c_write(i2c, displayAddress, ((input & 0xF0) | 0x09)); /* to make data to be read and not to lose data*/
		delayMS(1);
		/* E high */
		i2c_write(i2c, displayAddress, 0x0D); /* to get ready to give second part data */
		/* data part2 */
		i2c_write(i2c, displayAddress, (((input << 4) & 0xF0) | 0x0D)); /* second part of data */
		delayMS(1);
		/* E low */
		i2c_write(i2c, displayAddress, (((input << 4) & 0xF0) | 0x09));
		delayMS(1);
	}
		
}

/* 
* Configurates display registers to initiliaze it. Displays "All is well!" once it is successfully initiliazed.
*
* @param none
* @return none
* @note sets communication mode 4 bits and display line 2 rows.
*/
void displayInit(void)
{

	{/* switching to 4 bit mode */
	/* RS low, RW low */
	i2c_write(i2c, displayAddress, 0x08);
	delayMS(1);
	/* E high */
	i2c_write(i2c, displayAddress, 0x0C);
	delayMS(1);
	/* set 8 bit communication mode */
	i2c_write(i2c, displayAddress, 0x3C);
	delayMS(1);
	/* E low */
	i2c_write(i2c, displayAddress, 0x38);
	delayMS(10);
	
	i2c_write(i2c, displayAddress, 0x08);
	delayMS(1);
	/* E high */
	i2c_write(i2c, displayAddress, 0x0C);
	delayMS(1);
	/* set 8 bit communication mode */
	i2c_write(i2c, displayAddress, 0x3C);
	delayMS(1);
	/* E low */
	i2c_write(i2c, displayAddress, 0x38);
	delayMS(1);
	
	i2c_write(i2c, displayAddress, 0x08);
	delayMS(1);
	/* E high */
	i2c_write(i2c, displayAddress, 0x0C);
	delayMS(1);
	/* set 8 bit communication mode */
	i2c_write(i2c, displayAddress, 0x3C);
	delayMS(1);
	/* E low */
	i2c_write(i2c, displayAddress, 0x38);
	delayMS(1);
	
	i2c_write(i2c, displayAddress, 0x08);
	delayMS(1);
	/* E high */
	i2c_write(i2c, displayAddress, 0x0C);
	delayMS(1);
	/* set 4 bit communication mode */
	i2c_write(i2c, displayAddress, 0x2C);
	delayMS(1);
	/* E low */
	i2c_write(i2c, displayAddress, 0x28);
	delayMS(1);
	}
	
	
	displayWrite(0, 0x2C); /* 4 bit communication mode / 2 lines */
	delayMS(5);
	displayWrite(0, 0x0C); /* display ON */
	delayMS(5);
	displayWrite(0, 0x01); /* clear display */
	delayMS(5);
	displayWrite(0, 0x02); /* go to initial position address */
	delayMS(5);
	displayMessage("All is well!");
	delayMS(3000);
	displayClear();
	displayOnOff(0,0,0);
}

/* 
* Clears display content and moves cursor to the first position
*
* @param none
* @return none
*/
void displayClear(void) 
{
	displayWrite(0, 0x01);
	delayMS(2);
}

/* 
* Sets on or off display screen, cursor and cursor blinking)
*
* @param D 1: display screen on, 0: off
* @param C 1: cursor on, 0: off
* @param B 1: blinking cursor on, 0: off
* @return none
*/
void displayOnOff(char D, char C, char B) 
{
	if(D == '0' && C == '0' && B == '0')
		displayWrite(0, 0x08);
	else if(D == '0' && C == '0' && B == '1')
		displayWrite(0, 0x09);
	else if(D == '0' && C == '1' && B == '0')
		displayWrite(0, 0x0A);
	else if(D == '0' && C == '1' && B == '1')
		displayWrite(0, 0x0B);
	else if(D == '1' && C == '0' && B == '0')
		displayWrite(0, 0x0C);
	else if(D == '1' && C == '0' && B == '1')
		displayWrite(0, 0x0D);
	else if(D == '1' && C == '1' && B == '0')
		displayWrite(0, 0x0E);
	else if(D == '1' && C == '1' && B == '1')
		displayWrite(0, 0x0F);
	delayMS(1);
}

/* 
* Sends given string to be shown on the display where cursor rests.
*
* @param message string to be shown on the display
* @return none
*/
void displayMessage(char message[])
{
	int i = 0;
	while(message[i] != '\0')
	{
		displayWrite(1, message[i]);
		i++;
	}
}

/* 
* Moves cursor to the beginning of second line
*
* @param none
* @return none
*/
void displayNewLine(void)
{
	displayWrite(0, 0xC0); /* to go begining of second line */
	delayMS(1);
}

/* 
* Moves cursor given number to the right from the current position 
*
* @param step number of position to the right
* @return none
*/
void displayShiftCursor(int step) 
{
	int i = 0;
	for ( ; i<step; i++)
	{
		displayWrite(0, 0x14); /* shifts the cursor to the right */
		delayMS(1);
	}
}
