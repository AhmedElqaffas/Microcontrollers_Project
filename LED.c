#include "LED.h"

// These functions are prototypes for what should happen when the door should be opened or the alarm should be activated
// Code using LED to show the user that the door is opened or alarm is activated should be replaced with actual systems
void LED_Init(){
  SYSCTL_RCGCGPIO_R |= PORTF; // Enables the clock for port F
  GPIO_PORTF_DEN_R |= (RED | GREEN); 
  GPIO_PORTF_DIR_R |= (RED | GREEN);
}

void openDoor(){
  GPIO_PORTF_DATA_R |= GREEN; // light the green LED
  
  // This delay should be replaced with SysTick for accuracy
  /*int counter = 0;
  while (counter< 10000000){
    ++counter;
  }*/
  delay10ms(500);
  
  GPIO_PORTF_DATA_R &= ~GREEN; // turn off the green LED
}

void activateAlarm(){
  GPIO_PORTF_DATA_R |= RED; // light the red LED
  
  // This delay should be replaced with SysTick for accuracy
  /*int counter = 0;
  while (counter< 10000000){
    ++counter;
  }*/
  delay10ms(500);
  
  GPIO_PORTF_DATA_R &= ~RED; // turn off the green LED
}


