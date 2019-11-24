#include "tm4c123gh6pm.h"
#include "BIT_CALC.h"
#include "sysTick.h"

#define PORTF     (1 << 5)
#define RED       (1 << 1) // pin 1 in port F lights the LED red
#define GREEN     (1 << 3) // pin 3 in port F lights the LED GREEN

// Prototypes for functions in LED.c
void LED_Init();
void activateAlarm();
void openDoor();
