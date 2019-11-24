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
    return CLOSED;
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
