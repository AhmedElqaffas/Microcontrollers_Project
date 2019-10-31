#include "tm4c123gh6pm.h"
#include "DIO_interface.h"

#define MAX_PASS_LENGTH 15 // Maimum number of characters in the password 
#define CLOSED 0
#define OPEN 1
#define ALARM 2

int transit(char pressed);