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

void i2c_init(char i2c, unsigned short speedMode);
void i2c_start(char i2c);
char i2c_address(char i2c, char address, char RW);
void i2c_data(char i2c, char data);
void i2c_stop(char i2c);
void i2c_write(char i2c, char address, char data);
char i2c_read(char i2c, char ACK_NACK);
