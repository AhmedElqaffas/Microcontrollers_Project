#include "tm4c123gh6pm.h"
#include "DIO_interface.h"
#include "Transitions.h"
#include "keypad.h"

int main()
{
    // The matrix of keypad switches which represents the real position of each switch
  // For example: A which is in the 4th column and 1st row on the physical keypad 
                                                           //is also in the last column and first row in this matrix
  // * is represented with E , # is represented with F
char keys[rowsNo][columnsNo]={ 
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'E','0','F','D'}
  
};

  Keypad_Init();
  LED_Init();
  SysTick_Init();
  
  int currentState = CLOSED;
  
  while(1){
    char pressed = getPressedKey(keys);
    if(pressed != 'X'){
      currentState = transit(pressed);

      if(currentState == ALARM){
        activateAlarm();
      }
      else if(currentState == OPEN){
        openDoor();
      }
      
      
    }
  }
  return 0;
}
