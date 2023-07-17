#include "stm32f10x.h"
#include "gp_driver.h"

#define i2c_FastMode 0x2D
#define i2c_StandardMode 0xB4
#define ACK 0
#define NACK 1

void i2c_init(char i2c, unsigned short speedMode);
void i2c_start(char i2c); /* function to start transaction */
char i2c_address(char i2c, char address, char RW); /* to give slave adress */ /* returns 1 when adress is got */
void i2c_data(char i2c, char data); /* to send data */
void i2c_stop(char i2c);
void i2c_write(char i2c, char address, char data); /* to perform transaction */
char i2c_read(char i2c, char ACK_NACK);
