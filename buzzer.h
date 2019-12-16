#include "tm4c123gh6pm.h"
#include "BIT_CALC.h"
#include "sysTick.h"

#define PORTE     (1 << 4)
#define PE5       (1 << 5) // The buzzer is connected to Port E pin 5

void buzzer_Init();
void alarm();