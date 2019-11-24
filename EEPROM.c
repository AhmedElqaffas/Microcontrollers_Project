#include "EEPROM.h"

/*
  DESCRIPTION:
              This function initializes the EEPROM module by enabling the clock and waiting for 3 clock cycles 
              It also makes sure there are no errors as it keeps waiting for the EEDONE (register which contains flags for errors) to be 0
              If this register is equal 0 then there are no flags raised and therefore no errors
*/
void EEPROM_Init(){
  SYSCTL_RCGCEEPROM_R |= EEPROM_ENABLE;
  
  /*There must be a delay of 3 system clocks after the EEPROM module clock is enabled
  before any EEPROM module registers are accessed. In addition, after enabling or resetting the
  EEPROM module, software must wait until the WORKING bit in the EEDONE register is clear before
  accessing any EEPROM registers.*/
  
  // Each count takes 62.5ns so 1ms would be enough to wait 3 system clocks
   waitTime(1,MILLI_SECONDS_SYSTICK);
   
   // Wait for WORKING bit in EEDONE to be zero
   while(EEPROM_EEDONE_R != 0); 
   
}

/*
  PARAMETERS:
              - char number: a character representing the number that should be stored in the memory block
              - short block: The number of the block that the number should be stored in. The function caller 
                             is responsible for keeping track of where he stored his data in order not to overwrite it.
                             The caller is also responsible for not saving in block 0 as it is reserved for storing password length
                             using savePasswordLength() method.
  
  DESCRIPTION:
              This function chooses the desired block of EEPROM to store the data and write the value specified by the user. 
              It terminates when there are no error (EEDONE register = 0)
*/

void EEPROM_Write(char number, short block){
  // Choose the block to use
   EEPROM_EEBLOCK_R &= ~(BLOCK_ZERO);
   EEPROM_EEBLOCK_R |= block;

   // Select the word offset within the block
   EEPROM_EEOFFSET_R &= ~(0xF); // No offset (word 0)
   
   // Write the value
   EEPROM_EERDWR_R &= ~(0xFFFFFFFF); // Need to clear the old values first
   EEPROM_EERDWR_R |= number;  
   
   // If EEDONE Register = 0 then no error
   while(EEPROM_EEDONE_R != 0);   
   
}


/*
  PARAMETERS:
              - short block: The block number that contains the desired data
  
  OUTPUT:
             - char value: The data contained in the selected block

  DESCRIPTION:
              This function accesses a block in the EEPROM specified by the user, and returns the value that block contains
*/
  
char EEPROM_Read(short block){
   // Choose the block to use
   EEPROM_EEBLOCK_R &= ~(BLOCK_ZERO);
   EEPROM_EEBLOCK_R |= block;
   // Begin reading from the first word
   EEPROM_EEOFFSET_R &= ~(0xF) ;
  
   // Read the block value
   char value = EEPROM_EERDWR_R;
   return value;  
}

/*
  PARAMETERS:
              - int number: The length of the password array (The length of the password that the user enters when changing an old password to a new one)
  
  DESCRIPTION:
              This function saves the length of the password in block 0 in the EEPROM
              The difference between this function and EEPROM_Write is that it saves a number not a character in order to retrieve it from
              getPasswordLength() method as a number as well, it's desired to retrieve at as a number to be able to do some operations on it that
              won't work if the retrieved data was 'char' represented. 
*/

void savePasswordLength(int number){
  // Always use Block zero to save the length of the password
   EEPROM_EEBLOCK_R &= ~(BLOCK_ZERO);

   // Select the word offset within the block
   EEPROM_EEOFFSET_R &= ~(0xF); // No offset (word 0)

   
   // Write the value
   EEPROM_EERDWR_R &= ~(0xFFFFFFFF); // Delete old value first
   EEPROM_EERDWR_R |= number;
   // If EEDONE Register = 0 then no error
   while(EEPROM_EEDONE_R != 0);   
   
}

/*
  OUTPUT:
              - int length: The length of the password array (The length of the password that the user enters when changing an old password to a new one)
                            Which was stored in block 0 in the EEPROM
  
  DESCRIPTION:
              This function retrieves the length of the password from block 0 in the EEPROM, the function returns the data as int not as a character  
              as EEPROM_Read does.
*/
int getPasswordLength(){
  // The length is always in block 0
   EEPROM_EEBLOCK_R &= ~(BLOCK_ZERO);
   // Begin reading from the first word 
   EEPROM_EEOFFSET_R &= ~(0xF) ; // no offset
   // retrieve the length
   int length = EEPROM_EERDWR_R;
   return length;  
}