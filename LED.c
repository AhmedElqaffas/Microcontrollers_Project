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
  waitTime(5,SECONDS_SYSTICK); // Keep it on for 5 seconds
  GPIO_PORTF_DATA_R &= ~GREEN; // turn off the green LED
}

void activateAlarm(){
  GPIO_PORTF_DATA_R |= RED; // light the red LED 
  waitTime(5,SECONDS_SYSTICK);// Keep it on for 5 seconds
  GPIO_PORTF_DATA_R &= ~RED; // turn off the green LED
}


