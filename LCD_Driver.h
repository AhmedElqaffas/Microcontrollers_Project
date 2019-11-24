#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_
#include "tm4c123gh6pm.h"
#include "BIT_CALC.h"
#include "sysTick.h"


#define LCD_DATA_DATA GPIO_PORTB_DATA_R //Port has the DATA Pins of LCD
#define LCD_CTRL_DATA_RSRW GPIO_PORTA_DATA_R //Port has the RS/RW CONTROL Pin of LCD
#define LCD_CTRL_DATA_EN GPIO_PORTE_DATA_R //Port has the EN CONTROL Pin of LCD
#define LCD_RS_PIN      6       //Pin index connected to the RS pin
#define LCD_RW_PIN      7       //Pin index connected to the RW  pin
#define LCD_EN_PIN      4       //Pin index connected to the EN pin
#define PORTA   ( 1 << 0 )
#define PORTB   ( 1 << 1 )
#define PORTE   ( 1 << 4 )

/*
Function: LCD_Init
Initalizes the ports and pins used with the LCD
*/
void LCD_Init();
/*
Function: LCD_command
Applies the given command on the LCD
Parameters: command: the command needed to be applied on the LCD
*/
void LCD_start();
/*
Function: write_string
Takes a certain string and show it on the LCD
Parameters: data: the string to be written on the LCD
*/
void writeString(char *string);
/*
Function: clear_screen
clears the entire LCD
*/
void clearScreen();





#endif /* LCD_INTERFACE_H_ */

