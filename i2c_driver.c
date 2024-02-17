#include "i2c_driver.h"

/* 
* initiliazes selected I2C port and sets the speed of I2C
*
* @param i2c desired i2c port
* @param speedMode desired speed mode
* @return none
*/
void i2c_init(char i2c, unsigned short speedMode)
{
	RCC->APB2ENR |= 0x01;
	if(i2c == 1)
	{
		RCC->APB1ENR |= 0x200000;
		gpio_init(PB,6,OUT50,OUT_AF_OD);
		gpio_init(PB,7,OUT50,OUT_AF_OD);
		I2C1->CR1 |= 0x8000;
		I2C1->CR1 &= ~0x8000;
		I2C1->CR2 = 0x08;
		I2C1->CCR = speedMode;
		I2C1->TRISE = 0x09;
		I2C1->CR1 |= 0x01;
	}
	else if(i2c == 2)
	{
		RCC->APB1ENR |= 0x400000;
		gpio_init(PB,10,OUT50,OUT_AF_OD);
		gpio_init(PB,11,OUT50,OUT_AF_OD);
		I2C2->CR1 |= 0x8000;
		I2C2->CR1 &= ~0x8000;
		I2C2->CR2 = 0x08;
		I2C2->CCR = speedMode;
		I2C2->TRISE = 0x09;
		I2C2->CR1 |= 0x01;
	}
}

/* 
* starts the transaction
*
* @param i2c port to be communicated
* @return none
*/
void i2c_start(char i2c)
{
	if(i2c==1)
	{
		I2C1->CR1 |= 0x100; /* set start bit 1 */
		while(!(I2C1->SR1 & 1)) /* wait until this bit becomes 0 */
		{}
	}
	else if(i2c==2)
	{
		I2C2->CR1 |= 0x100; /* set start bit 1 */
		while(!(I2C2->SR1 & 1)) /* wait until this bit becomes 0 */
		{}
	}
}

/* 
* sends the adress of the slave device, and tells to device either read data from
* or write data to 
*
* @param i2c port to be communicated
* @param adress is slave adress
* @param RW read/write selection
* @return 1 if the slave is there, 0 if not
*/
char i2c_address(char i2c, char address, char RW)
{
	char ACK_NACK;
	volatile int temp;
	if(i2c==1)
	{
		I2C1->DR = (address | RW);
		while((I2C1->SR1 & 0x02) == 0) /* becomes 1 once address is got */
		{}
		while(I2C1->SR1 & 0x02) /* until it is 0 again, keep reading */
		{
			temp = I2C1->SR1;
			temp = I2C1->SR2;
			if((I2C1->SR1 & 0x02) == 0) /* once it is 0 again, stop */
			{
				return ACK_NACK;
				break;
			}
		}
	}
	else if(i2c==2)
	{
		I2C2->DR = (address | RW);
		while((I2C2->SR1 & 0x02) == 0) /* becomes 1 once address is got */
		{}
		while(I2C2->SR1 & 0x02) /* until it is 0 again, keep reading */
		{
			temp = I2C2->SR1;
			temp = I2C2->SR2;
			if((I2C2->SR1 & 0x02) == 0) /* once it is 0 again, stop */
			{
				return ACK_NACK;
				break;
			}
		}
	}
}

/* 
* sends data bits
*
* @param i2c port to be communicated
* @param data to send
* @return none
*/
void i2c_data(char i2c, char data)
{
	if(i2c==1)
	{
		while((I2C1->SR1 & 0x80) == 0) /* wait until bit7 becomes 1 */
		{}
		I2C1->DR = data; /* put data in DR */
		while((I2C1->SR1 & 0x80) == 0) /* wait until it becomes 1 again */
		{}
	}
	else if(i2c==2)
	{
		while((I2C2->SR1 & 0x80) == 0) /* wait until bit7 becomes 1 */
		{}
		I2C2->DR = data; /* put data in DR */
		while((I2C2->SR1 & 0x80) == 0) /* wait until it becomes 1 again */
		{}
	}
	
}

/* 
* stops the transaction
*
* @param i2c port to be communicated
* @return none
*/
void i2c_stop(char i2c)
{
	volatile int temp;
	if(i2c==1)
	{
		temp = I2C1->SR1; /* just to avoid some errors read like start condition */
		temp = I2C1->SR2;
		I2C1->CR1 |= 0x200; /* set stop bit 1 */
	}
	else if(i2c==2)
	{
		temp = I2C2->SR1;
		temp = I2C2->SR2;
		I2C2->CR1 |= 0x200; 
	}
}

/* 
* Performs all transaction steps in order to write data to I2C
*
* @param i2c port to be communicated
* @param adress is slave adress
* @param data to send
* @return none
*/
void i2c_write(char i2c, char address, char data)
{
	i2c_start(i2c);
	i2c_address(i2c, address, 0);
	i2c_data(i2c, data);
	i2c_stop(i2c);
}

/* 
* Reads data from I2C
*
* @param I2C port to be communicated
* @param ACK_NACK
* @return none
*/
char i2c_read(char i2c, char ACK_NACK)
{
	char temp;
	if(i2c == 1)
	{
		I2C1->CR1 |= 0x400;
		while((I2C1->SR1 & 0x40) == 0)
		{}
		temp = I2C1->DR;
		if(ACK_NACK)
		{
			I2C1->CR1 &= ~0x400;
		}
	}
	else if(i2c == 2)
	{
		I2C2->CR1 |= 0x400;
		while((I2C2->SR1 & 0x40) == 0)
		{}
		temp = I2C2->DR;
		if(ACK_NACK)
		{
			I2C2->CR1 &= ~0x400;
		}
	}
	return temp;
}
