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
