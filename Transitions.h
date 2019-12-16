#include "tm4c123gh6pm.h"
#include "BIT_CALC.h"
#include "EEPROM.h"
#include "LCD_Driver.h"
#include "sysTick.h"
#include "LED.h"
#include "keypad.h"

#define MAX_PASS_LENGTH 15 // Maximum number of characters in the password 
#define CLOSED 0
#define OPEN 1
#define ALARM 2
#define NOT_CHANGED 0
#define TYPE_NEW 1
#define CHANGED 2
#define CLEARED 3
#define MODE_CHANGE 4

int transit(char pressed);
int oldPasswordState(char pressed);
int newPassState(char pressed);
void passwordEntryProcess(char keys[rowsNo][columnsNo]);