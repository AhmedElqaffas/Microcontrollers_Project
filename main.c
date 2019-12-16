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
  

  /*char password[] = {'3','2','5','1'};
  savePasswordLength((sizeof(password) / sizeof(char)));
  // BLOCK 0 IS RESERVED FOR PASSWORD LENGTH SO WRITING SHOULD BEGIN FROM BLOCK 1 , HENCE i=1
  for(int i=1;i<= (sizeof(password) / sizeof(char)); i++){
     EEPROM_Write(password[i-1],i);
  }*/
  
  // Start entering the password  or changing it
  passwordEntryProcess(keys);
    
  return 0;
  }

