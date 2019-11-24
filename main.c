#include "Transitions.h"
#include "keypad.h"
#include "LCD_Driver.h"
#include "EEPROM.h"
#include "sysTick.h"
#include "LED.h"

int main()
{
    // The matrix of keypad switches which represents the real position of each switch
  // For example: 'A' which is in the 4th column and 1st row on the physical keypad 
                                                           //is also in the last column and first row in this matrix
  // * is represented with E , # is represented with F
char keys[rowsNo][columnsNo]={ 
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'E','0','F','D'}
  
};

  // Initialize interfaces
  Keypad_Init();
  LED_Init();
  EEPROM_Init();
  LCD_Init();
  LCD_start();

  /*char password[] = {'3','2','5','1','4','7','0','0','0','2','3','5'};
  savePasswordLength((sizeof(password) / sizeof(char)));
  // BLOCK 0 IS RESERVED FOR PASSWORD LENGTH SO WRITING SHOULD BEGIN FROM BLOCK 1 , HENCE i=1
  for(int i=1;i<= (sizeof(password) / sizeof(char)); i++){
     EEPROM_Write(password[i-1],i);
  }*/
  int currentState = CLOSED; // currentState represents the state of the door.The door is initially closed
  
  while(1){
    char pressed = getPressedKey(keys); // Check for the pressed keypad key
    // If a key is pressed:
    if(pressed != 'X'){ // ('X' means there is no pressed key on the keypad)
      LCD_data('*'); // Display on the LCD that a character is pressed
      currentState = transit(pressed);  // Check which door state to go to
      // If the user exceeded the maximum range of a password, then he is not authorized to enter.
      if(currentState == ALARM){ 
        write_string("Wrong Password"); // Display error message on the LCD
        activateAlarm(); // Activate the alarm (the function waits for some time and turns the alarm off)
        clearScreen(); // Clear the error message
      }
      // If the correct password is enterd, the door should be opened
      else if(currentState == OPEN){ 
        write_string("Door Opened"); // Display a message on the LCD
        openDoor(); // Open the door (the function waits for some time and closes the door again)
        clearScreen(); // Clear the screen again when the door is locked
      } 
    }
  }
  return 0;
}
