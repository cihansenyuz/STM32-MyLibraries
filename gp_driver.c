#include "gp_driver.h"


void gpio_init (unsigned short port, unsigned short pin, unsigned dir, unsigned short opt)
{
	volatile unsigned long* ClockReg;
	unsigned short tPIN = pin;
	unsigned short offset = 0x00;
	
	if (pin > 7)
	{
		tPIN -= 8;
		offset = 0x01;
	}
	
	if (port == 1) /* means port A */
	{
		gpioClockEnable |= 0x04; /* enable port A */
		ClockReg = (volatile unsigned long*) (&gpioA + offset);
	}
	
		if (port == 2) /* means port B */
	{
		gpioClockEnable |= 0x08; /* enable port B */
		ClockReg = (volatile unsigned long*) (&gpioB + offset);
	}
	
			if (port == 3) /* means port C */
	{
		gpioClockEnable |= 0x10; /* enable port C */
		ClockReg = (volatile unsigned long*) (&gpioC + offset);
	}
	*ClockReg &= ~(0x0F << (tPIN*4)); /* reset the target pin */
	*ClockReg |= ((dir << (tPIN*4)) | (opt << (tPIN*4+2))); /* set up the direction & option */
	
	
}

int read_GP (unsigned short port, unsigned short pin)
{
	volatile unsigned long * IDR;
	unsigned long offset = 0x02;
	int state;
	
	if (port == 1)
	{
		IDR = (volatile unsigned long*) (&gpioA + offset);
	}
	else if (port == 2)
	{
		IDR = (volatile unsigned long*) (&gpioB + offset);
	}
	else if (port == 3)
	{
		IDR = (volatile unsigned long*) (&gpioC + offset);
	}
	state = ((*IDR & (1<<pin)) >>pin);
	return state;
}


void write_GP (unsigned short port, unsigned short pin, unsigned short state)
{
	volatile unsigned long * ODR;
	unsigned long offset = 0x03;
	
	if (port == 1)
	{
		ODR = (volatile unsigned long*) (&gpioA + offset);
	}
	else if (port == 2)
	{
		ODR = (volatile unsigned long*) (&gpioB + offset);
	}
	else if (port == 3)
	{
		ODR = (volatile unsigned long*) (&gpioC + offset);
	}
	state ? (*ODR |= (state<<pin)) : (*ODR &= ~(1<<pin));
	
}

void toggle_GP (unsigned short port, unsigned short pin)
{
	if (read_GP(port,pin))
	{
		write_GP(port,pin,0);
	}
	else
	{
		write_GP(port,pin,1);
	}
}


