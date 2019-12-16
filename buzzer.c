#include "buzzer.h"


/*
  DESCRIPTION:
              This function initializes the buzzer component 
              The buzzer is connected to PE5
              This function sets the GPIO clock, enables PE5 and sets its direction as output 
*/
void buzzer_Init(){
  SYSCTL_RCGCGPIO_R |= PORTE; // Enables the clock for port E
  GPIO_PORTE_DEN_R |= (PE5); // Enable the pin 
  GPIO_PORTE_DIR_R |= (PE5); // Set the direction as output
}


/*
  DESCRIPTION:
              This function controls the alarm by using the buzzer
              It buzzes 3 times, 1 second each, and waits for a 0.5 second pause in between
*/
void alarm(){
  for(int i=0; i<3 ; i++){
    // Buzz
    GPIO_PORTE_DATA_R |= PE5; // Supply voltage to the buzzer
    waitTime(1,SECONDS_SYSTICK); // Keep buzzing for 1 second
    GPIO_PORTE_DATA_R &= ~PE5; // Stop voltage
    
    // A small pause, don't pause after last buzz
    if(i<2){
      waitTime(500,MILLI_SECONDS_SYSTICK);
    }
  }
  GPIO_PORTE_DATA_R &= ~PE5; // Stop voltage
}