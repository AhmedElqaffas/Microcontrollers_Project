#include "sysTick.h"

void sysTick_Init(int reload,short count){
  NVIC_ST_RELOAD_R = reload;
  NVIC_ST_CURRENT_R = 0;
  NVIC_ST_CTRL_R = 5;
  
  for(short i =0 ; i < count ; i++){
    while((NVIC_ST_CTRL_R & 0x10000) == 0);
  }
  
}
 
void waitTime(float requiredTime, short timeUnit){
  
  if(timeUnit == SECONDS_SYSTICK){
    requiredTime = requiredTime;
  }else if(timeUnit == MILLI_SECONDS_SYSTICK){
    requiredTime = requiredTime/1000;           //Converting Milliseconds to Seconds
  }else if(timeUnit == MICRO_SECONDS_SYSTICK){
    requiredTime = requiredTime/1000000;        //Converting Microseconds to seconds
  }
  
  float Tov = 1.048576;
  int MaxReload = 0xFFFFFF;
  float count = requiredTime/Tov; // How many times I need to fully reload the reload register
  
  int numberOfCompleteReloads = (int)count;
  float numberOfFractionsReloads = count - (int)count;
 
  if(numberOfCompleteReloads != 0){
    sysTick_Init(MaxReload , numberOfCompleteReloads);
  }
  if(numberOfFractionsReloads != 0){
    int numberOfTicksForFraction = (int)(numberOfFractionsReloads * MaxReload); 
    sysTick_Init(numberOfTicksForFraction , 1);
  }
}
