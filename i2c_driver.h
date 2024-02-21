/**
  ******************************************************************************
  * @file    i2c_driver.h
  * @author  Cihan Senyuz
  * @brief   Header for i2c_driver.c file.
  *                 This file contains the common defines of the application.
  *         I2C1 pins           I2C2 pins
  *         PB6     SCL         PB10    SCL
  *         PB7     SDA         PB11    SDA
  *         
  *     notes for I2C initiliaze process;
  *                 I2C is on the ABP1 bus
  *                 
  *                 on APB2 register bit0 -> AFIO EN must be set
  *                 on APB1 register bit21 -> I2C1 EN or bit22 -> I2C2 EN must be set
  * 
  *                 then I2Cx->CR1 , reset using SWRST bit15
  *                 set freq bit0-5 0x08
  *                 on I2Cx CR1 bit0 -> enable peripherial must be set
  * @note   Source code depends on stm32f10x.h and gp_driver.h library
  ******************************************************************************
  */

#include "stm32f10x.h"
#include "gp_driver.h"

#define i2c_FastMode 0x2D
#define i2c_StandardMode 0xB4
#define ACK 0
#define NACK 1

/* 
* initiliazes selected I2C port and sets the speed of I2C
*
* @param i2c desired i2c port
* @param speedMode desired speed mode
* @return none
*/
void i2c_init(char i2c, unsigned short speedMode);

/* 
* starts the transaction
*
* @param i2c port to be communicated
* @return none
*/
void i2c_start(char i2c);

/* 
* sends the adress of the slave device, and tells to device either read data from
* or write data to 
*
* @param i2c port to be communicated
* @param adress is slave adress
* @param RW read/write selection
* @return 1 if the slave is there, 0 if not
*/
char i2c_address(char i2c, char address, char RW);

/* 
* sends data bits
*
* @param i2c port to be communicated
* @param data to send
* @return none
*/
void i2c_data(char i2c, char data);

/* 
* stops the transaction
*
* @param i2c port to be communicated
* @return none
*/
void i2c_stop(char i2c);

/* 
* Performs all transaction steps in order to write data to I2C
*
* @param i2c port to be communicated
* @param adress is slave adress
* @param data to send
* @return none
*/
void i2c_write(char i2c, char address, char data);

/* 
* Reads data from I2C
*
* @param I2C port to be communicated
* @param ACK_NACK
* @return none
*/
char i2c_read(char i2c, char ACK_NACK);
