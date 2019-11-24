#ifndef sysTick_H
#define sysTick_H
#include "tm4c123gh6pm.h"

//Units to be used as an indication for the unit of the sent time
#define SECONDS_SYSTICK       0
#define MILLI_SECONDS_SYSTICK 1
#define MICRO_SECONDS_SYSTICK 2

/*Function: waitTime
  calculates needed Reload value for the sysTick Timer
  then calls a sysTick_Init Function to start counting

  Parameters:
  requiredTime: float value representing amount of time we need to delay
  timeUnit: represesnts the unit of the entered requiredTime
*/
void waitTime(float requiredTime, short timeUnit);


#endif