#include "tm4c123gh6pm.h"
#include "BIT_CALC.h"
#include "sysTick.h"

#define EEPROM_ENABLE 1
#define BLOCK_ZERO 0x0000FFFF

void EEPROM_Init();
void EEPROM_Write(char number, short offset);
char EEPROM_Read(short block);
void savePasswordLength(int number);
int getPasswordLength();