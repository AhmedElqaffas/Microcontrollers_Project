#include "keypad.h"

/*
  Description: 
              This function initializes the keypad to work on ports A and E
              Bits 0 -> 3 on port E are used as ouput bits (keypad columns)
              Bits 2 -> 5 on port A are used as input bits (keypad rows)

*/
void Keypad_Init(){
     Set_Bit(SYSCTL_RCGCGPIO_R,PORTE); // Enable port E
     GPIO_PORTE_DEN_R |= (COL0 | COL1 | COL2 | COL3); // Set digital enable 
     GPIO_PORTE_DIR_R |= (COL0 | COL1 | COL2 | COL3); // set pins E 0->3 as output
     GPIO_PORTE_ODR_R |= (COL0 | COL1 | COL2 | COL3); // Open Drain Mode
     GPIO_PORTE_DATA_R |= (COL0 | COL1 | COL2 | COL3); // Set all output bits as 1 initially 

     
     Set_Bit(SYSCTL_RCGCGPIO_R,PORTA); // Enable port A
     GPIO_PORTA_DEN_R |= (ROW0| ROW1| ROW2| ROW3); // Set digital enable
     GPIO_PORTA_DIR_R &= ~(ROW0| ROW1| ROW2| ROW3); // Set pins A 2->5 as input
     GPIO_PORTA_PUR_R |= (ROW0| ROW1| ROW2| ROW3); // Pull up resistor
         
}



/*
  PARAMETERS:
            - char keys[][columnsNo]: a char array instance of the matrix representing the keypad switches

  OUTPUT:
           - A character 
                The character either represents the key pressed (from the elements inside the keys[][] array) and is called "pressedKey"
                or 'X' meaning no key is pressed

  DESCRIPTION:
             We are using pull up resistors so all inputs are 1 if not pressed
             Setting the output bits (columns) as 1s will lead to the input pins keep having 1 on them even if they are pressed
             We will then keep setting each column to 0 and check if the rows changed to 0 or are they still 1 
             If a row became zero that means that it was pressed and connected to the column currently set to 0 and we know have the location of the pressed switch
             If we found that all rows are still 1s then we will reset the current column to 1 and set the next column to zero and so on 

            There is a short delay between setting each column to zero and checking the rows to avoid bouncing effect 

*/
char getPressedKey(char keys[][columnsNo]){

  char pressedKey;
  
  for(int c = 0; c< columnsNo; c++){ // Check each column
    Clear_Bit(GPIO_PORTE_DATA_R,c); // Set the current column as 0
   // Short delay to avoid bouncing effect
    waitTime(20, MILLI_SECONDS_SYSTICK);
    for(int r =0; r<rowsNo;r++){ //Check each input row 
      if(Get_Bit(GPIO_PORTA_DATA_R,r+2)==0){ // if it's 0 not 1 (as we are using pull up so 0 means pressed)                                   
                                             // Input begins from PORTA 2 so we should add 2
        pressedKey = keys[r][c]; // The pressed switch is the one connecting this row to the current column
        while(Get_Bit(GPIO_PORTA_DATA_R,r+2)==0); // Keep stuck until the user removes his finger from the switch
        Set_Bit(GPIO_PORTE_DATA_R,c); // Reset the column to 1 so the next time we enter this functions all the columns will be 1s
        return pressedKey;
      }
    
    }
    Set_Bit(GPIO_PORTE_DATA_R,c); // The switch is not in this column , reset the column to 1


  }
  return 'X'; // No key is pressed
}