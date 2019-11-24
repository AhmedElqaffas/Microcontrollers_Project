#include "tm4c123gh6pm.h"
#include "BIT_CALC.h"
#include "sysTick.h"

// Definitions for ports numbers in the SYSCTL_RCGCGPIO_R
#define PORTA 0
#define PORTE 4
// Definitions for pin numbers of rows
#define ROW0 0x4 // A2
#define ROW1 0x8 // A3
#define ROW2 0x10 // A4
#define ROW3 0x20 // A5
// Definitions for pin numbers of columns
#define COL0 0x1 // E0
#define COL1 0x2 // E1
#define COL2 0x4 // E2
#define COL3 0x8 // E3

// Number of columns and rows in the keypad
#define columnsNo 4
#define rowsNo 4

// Prototypes for the keypad.c functions
char getPressedKey(char keys[][columnsNo]);
void Keypad_Init();