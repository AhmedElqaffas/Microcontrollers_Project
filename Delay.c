#include "Delay.h"

void SysTick_Init(){
  NVIC_ST_CTRL_R = 0;               // disable SysTick during setup
  NVIC_ST_CTRL_R = 0x00000005;      // enable SysTick with core clock
}

/*
  PARAMETERS:
            - int value: the value to put in the reload register

  DESCRPTION:
            - This function is only accessed from delay10ms() 
              It puts the required value in the reload register and waits until the flag becomes 1

*/
void delay(unsigned long value){
  NVIC_ST_RELOAD_R = value;
  NVIC_ST_CURRENT_R = 0;
  while ((NVIC_ST_CTRL_R & 0x10000) == 0);
}

/*
  PARAMETERS:
            - int numberOfTimes: how many 10ms should the program wait

  DESCRIPTION:
            - The function calls the delay() function for each 10 ms that the program needs to wait
*/
void delay10ms(int numberOfTimes){
  for(int i=0; i< numberOfTimes; i++){
      delay(RELOAD_TEN_MS);
      
  }
  /*double temp = ((CLOCK_SPEED * numberOfTimes * TENms)-1);
  printf("%lf \n",temp);
  unsigned long value =  79999999;//(unsigned long) ((CLOCK_SPEED*numberOfTimes*TENms)-1);
  printf("%lu",value);
  if( value <= MAX_CAPACITY){ // The value fits in the reload register
    //printf("%value first if is:   lu \n",value);
    delay(value);
      
  }
  else{ // The value doesn't fit
    while(value>MAX_CAPACITY){ // Keep putting the max capacity in the reload register as long as the value is more than the max capacity
   //    printf("value before is:   %lu \n",value);
      value = value - MAX_CAPACITY;  
      delay(MAX_CAPACITY);
     // printf("value after is:   %lu \n",value);
    }     
    delay(value); // put the remaining value in the reload register
  }*/
}