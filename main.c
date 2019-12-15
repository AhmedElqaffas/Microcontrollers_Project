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
  int currentState = CLOSED; // currentState represents the state of the door.The door is initially closed
  LCD_Write_String("Type pass. Type", 0 , 0); //initial screen message that shows instructions on how to use
  LCD_Write_String("* to change pass" , 1 , 0);
  waitTime(2.5 , SECONDS_SYSTICK); //initial message disappears after some time
  clearScreen();
  bool newPassFlag = false; //If the user entered his old password correctly then this boolean's value becomes True
  
  /* The system operates in two modes:  

   Type password mode and change password mode */
  
  while(1){
    char pressed = getPressedKey(keys); // Check for the pressed keypad key
    
    // Enter * (E) to change the password. This is the change password mode.
    if(pressed == 'E'){
      LCD_Write_String("Enter old pass: ", 0 , 0);
      LCD_Write_String(">" , 1 , 0);
      while(1){
        char pressed = getPressedKey(keys);
        if(pressed != 'X')//if a key is pressed 
        { LCD_data('*'); // Display on the LCD that a character is pressed
          currentState = oldPasswordState(pressed);// Check which state to go to when entering old password
          if(currentState == TYPE_NEW){ //Old password has been entered correctly
            LCD_Write_String("Enter new pass: ", 0 , 0);
            LCD_Write_String(">", 1 , 0);
            newPassFlag = true;
         while(newPassFlag){ //entering the new password
        char pressed = getPressedKey(keys);
        if(pressed != 'X')//if a key is pressed 
        { LCD_data('*'); // Display on the LCD that a character is pressed
          currentState = newPassState(pressed);// Check which state to go to when entering new password
          if(currentState == CHANGED){ //Old password has been entered correctly
            clearScreen();
            LCD_Write_String("Password changed. " , 0 , 0); //display success message
            newPassFlag = false;
          }
          
          //If a user presses clear
          
         // MISSING CODE HERE
          
        //If a user presses *, the mode should change from change password mode to type password mode
           
        //MISSING CODE HERE
      }
      }
            
          } // If user entered a wrong old password
          else if(currentState == ALARM){
            activateAlarm();
            clearScreen();
            LCD_Write_String("Enter old pass: " , 0 , 0);
            LCD_Write_String(">" , 1 , 0);
          } 
          //If a user pressed the clear button
           else if(currentState == CLEARED){
            LCD_Write_String("Enter old pass: " , 0 , 0);
            LCD_Write_String(">" , 1 , 0);
          }
          //If a user presses *, the mode should change from change password mode to type password mode
           
        //MISSING CODE HERE
        
        }
      }
      
    }// Typing the password mode
    else{
    // If a key is pressed:
     // LCD_Write_String("Enter password:", 0 , 0);
    if(pressed != 'X'){ // ('X' means there is no pressed key on the keypad)
     //clearScreen();
     LCD_data('*'); // Display on the LCD that a character is pressed
     currentState = transit(pressed);  // Check which door state to go to
      // If the user exceeded the maximum range of a password, then he is not authorized to enter.
      if(currentState == ALARM){ 
        LCD_Write_String("Wrong Password" , 0 , 0); // Display error message on the LCD
        activateAlarm(); // Activate the alarm (the function waits for some time and turns the alarm off)
        clearScreen(); // Clear the error message
      }
      // If the correct password is enterd, the door should be opened
      else if(currentState == OPEN){ 
        LCD_Write_String("Door Opened" , 0, 0); // Display a message on the LCD
        openDoor(); // Open the door (the function waits for some time and closes the door again)
        clearScreen(); // Clear the screen again when the door is locked
      } 
    }
    }
  }
    
  return 0;
  }

