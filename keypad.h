#include "tm4c123gh6pm.h"
#include "DIO_interface.h"

// Definitions for ports numbers in the SYSCTL_RCGCGPIO_R
#define PORTA 0
#define PORTE 4

// Number of columns and rows in the keypad
#define columnsNo 4
#define rowsNo 4

// Prototypes for the keypad.c functions
char getPressedKey(char keys[][columnsNo]);
void Keypad_Init();