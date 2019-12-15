#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_
#include "tm4c123gh6pm.h"
#include "BIT_CALC.h"
#include "sysTick.h"
#include "stdbool.h"

#define SW1 (1 << 4)
#define SW2 (1)
#define PORTF (1 << 5)
#define RED (1 << 1)


#define LCD_DATA_DATA GPIO_PORTB_DATA_R //Port has the DATA Pins of LCD
#define LCD_CTRL_DATA_RSRW GPIO_PORTA_DATA_R //Port has the RS/RW CONTROL Pin of LCD
#define LCD_CTRL_DATA_EN GPIO_PORTE_DATA_R //Port has the EN CONTROL Pin of LCD
#define LCD_RS_PIN      6       //Pin index connected to the RS pin
#define LCD_RW_PIN      7       //Pin index connected to the RW  pin
#define LCD_EN_PIN      4       //Pin index connected to the EN pin
#define PORTA   ( 1 << 0 )
#define PORTB   ( 1 << 1 )
#define PORTE   ( 1 << 4 )


#define LCD_Number_Of_Rows 2
#define LCD_Number_Of_Columns 16
/*
Function: LCD_Init
Initalizes the ports and pins used with the LCD
*/
void LCD_Init();
/*
Function: Init_Ports
Initializes ports unrelated to the LCD connections like PORTF
*/
void Init_Ports();
/*
Function: LCD_command
Applies the given command on the LCD
Parameters: command: the command needed to be applied on the LCD
*/
void LCD_start();


/*
Function: clear_screen
clears the entire LCD
*/
void clearScreen();

/*
Function: writeNumbersArray
Shows int array on LCD and concatenates ".00" to it
Parameters: The int array containing values I want to show and it's count
*/
void writeNumbersArray(int* array, int count);

/*
Function: getCountdownNumber
Print the parameter 'description' on the 
LCD and wait for the user to enter a number,
the number will be confirmed if it exceeds 
4 numbers or if the user presses the "*" key 
*/
int getNumber(int* numberCount);

/*
Function: countDownLCD
Displays a countdown on the LCD starting from a given time with precision of 0.01 sec
Parameters: time: 6 Digits number maximum that will start counting down from it (Unit: ms)
Returns: 1: returned through clicking a switch -- 2: returned through finishing the timer
*/
int countDownLCD(int timeMS, int numberCount);


/*
Function: showEndCountdownMessage
Displayes a message indicating that the countdown is done and blinks an LED for 5 seconds
*/
void showEndCountdownMessage();

/*
Function: blinkLED
Blinks red LE
Parameters: seconds: Number of seconds to keep blinking LED for
*/
void blinkLED(double seconds);

void LCD_Write_String(char* string, short rowIndex, short columnIndex);

void LCD_Write_Number(unsigned int number, short rowIndex, short columnIndex);



#endif /* LCD_INTERFACE_H_ */

