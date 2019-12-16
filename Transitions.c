#include "Transitions.h"
  
/*
  PARAMETERS:
              - char pressed: a character representing the switch pressed on the keypad
  
  OUTPUT:
             - an int representing the state that the system is now in
                  OPEN: The door is open as the password is entered correctly
                  ALARM: Wrong password and an alarm should be activated
                  CLOSED: The correct password is not inserted yet and the door is still closed

  DESCRIPTION:
              The function transits the system to a new state based on the character pressed on the keypad
*/
int transit(char pressed){
  int length = getPasswordLength(); // The number of characters of the password

  static volatile int current = 0; // Indicates which character in the password is the program expecting (first character, second character, etc...)
  static volatile int wrong = 0;
  // The maximum length of password is 15 characters
  // If the user enters a wrong character, the 'wrong' variable is incremented
  // Once 'wrong' is greater than 0, it will keep incrementing with each press until the user resets and starts entering characters from the start or reaches the-
  // maximum length of 15 characters and an alarm will be activated
  if(pressed=='F'){ // Reset if # is pressed
    clearScreen();
    wrong = 0;
    current = 0;
    return CLEARED;
  }
  
  if(wrong>0){ // if wrong > 0, keep incrementing it with each character pressed
    wrong++;
    if(wrong== MAX_PASS_LENGTH){ // if the characters entered reached the max length of password, alarm will be activated
      wrong = 0; // reset to zero for the next time the function is entered
      return ALARM;
    }
    return CLOSED;
  }
  
  if(pressed == EEPROM_Read(current+1)){ // If the pressed key is the one expected
    if(current == length -1){ // If the whole password is now entered correctly, the door should be opened and the "current" reset to zero
      current = 0;
      return OPEN;
    }
    current++; // The system will now expect the next character in the array to be pressed
    return CLOSED; // The door isn't open yet
  }
  
  else{ // The entered key is wrong, door will keep locked , and 'wrong' will be equal to the length of the characters currently inserted
    // If the user entered 3 characters correctly then the 4th one wrong, 'wrong' will be set to 4
        wrong = current +1;
        current = 0;
        return CLOSED;
      
  }
    
}
/* Function to change the state based on typing old password */
int oldPasswordState(char pressed){
  int length = getPasswordLength(); // The number of characters of the password

  static volatile int current = 0; // Indicates which character in the password is the program expecting (first character, second character, etc...)
  static volatile int wrong = 0;
  // The maximum length of password is 15 characters
  // If the user enters a wrong character, the 'wrong' variable is incremented
  // Once 'wrong' is greater than 0, it will keep incrementing with each press until the user resets and starts entering characters from the start or reaches the-
  // maximum length of 15 characters and an alarm will be activated
  if(pressed=='F'){ // Reset if # is pressed
    clearScreen();
    wrong = 0;
    current = 0;
    return CLEARED;
  }
 //If * button is pressed then the mode should be changed to type password mode
  if(pressed == 'E'){
    clearScreen();
    wrong = 0;
    current = 0;
    return MODE_CHANGE;
  } 
  
  if(wrong>0){ // if wrong > 0, keep incrementing it with each character pressed
    wrong++;
    if(wrong== MAX_PASS_LENGTH){ // if the characters entered reached the max length of password, alarm will be activated
      wrong = 0; // reset to zero for the next time the function is entered
      return ALARM;
    }
    return CLOSED;
  }
  
  if(pressed == EEPROM_Read(current+1)){ // If the pressed key is the one expected
    if(current == length -1){ // If the whole password is now entered correctly, the door should be opened and the "current" reset to zero
      current = 0;
      clearScreen();
      return TYPE_NEW;
    }
    current++; // The system will now expect the next character in the array to be pressed
    return CLOSED; // The door isn't open yet
  }
  
  else{ // The entered key is wrong, door will keep locked , and 'wrong' will be equal to the length of the characters currently inserted
    // If the user entered 3 characters correctly then the 4th one wrong, 'wrong' will be set to 4
        wrong = current +1;
        current = 0;
        return CLOSED;
  
}
}
int newPassState(char pressed){
  /* This function handles the states when typing a new password */
  
  static volatile int lengthNew = 0; //Length of new password
  static volatile char newPassword[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}; //initial empty array to store the password in it
  
  //If clear button is pressed then the screen should be cleared
  if(pressed == 'F'){
    clearScreen();
    lengthNew = 0;
    return CLEARED;
  } 
  //If * button is pressed then the mode should be changed to type password mode
  if(pressed == 'E'){
    clearScreen();
    lengthNew = 0;
    return MODE_CHANGE;
  } 
  //Typing the new password and increasing the length of password on each press
  else if(pressed != 'D' && lengthNew <MAX_PASS_LENGTH){ //'D' is the okay button that determines if I finished typing the password
    newPassword[lengthNew] = pressed;
    lengthNew++;
    
    return NOT_CHANGED;
  }
  
  // Saving the new password once the D button is clicked or length exceeds max length
  else if( pressed == 'D' || lengthNew >= MAX_PASS_LENGTH){
    
 savePasswordLength(lengthNew);
  // BLOCK 0 IS RESERVED FOR PASSWORD LENGTH SO WRITING SHOULD BEGIN FROM BLOCK 1 , HENCE i=1
  for(int i=1;i<= lengthNew; i++){
     EEPROM_Write(newPassword[i-1],i);
  }
    lengthNew = 0;
    return CHANGED;
  }
    
}
