#include "LCD_Driver.h"
void LCD_Init(){
  SYSCTL_RCGCGPIO_R |= (PORTA | PORTB| PORTE);  //Enabling clock for PORTA & PORTB & PORTE
  GPIO_PORTA_DEN_R |= (0xC0);              //Enabling Pins A6,A7
  GPIO_PORTE_DEN_R |= (0x10);              //Enabling Pins E4
  GPIO_PORTB_DEN_R |= 0xFF;              //Enabling all Pins of PORTB
  GPIO_PORTA_DIR_R |= (0xC0);     //Direction of Pins A6,A7 : OUTPUT
  GPIO_PORTE_DIR_R |= (0x10);     // Direction of Pin E4: OUTPUT
  GPIO_PORTB_DIR_R |= 0xFF;              //Direction of PORTB for Data pins : OUTPUT

  
}
void LCD_command(unsigned char command)
{
    Clear_Bit(LCD_CTRL_DATA_RSRW , LCD_RS_PIN);              //RS = 0
    Clear_Bit(LCD_CTRL_DATA_RSRW , LCD_RW_PIN);              //R/W = 0
    LCD_DATA_DATA = command;

    Set_Bit(LCD_CTRL_DATA_EN , LCD_EN_PIN);                //pulse E
    	
    waitTime(1 , MICRO_SECONDS_SYSTICK);                //Enable pulse Width
    
    Clear_Bit(LCD_CTRL_DATA_RSRW , LCD_RS_PIN);              //RS = 0
    Clear_Bit(LCD_CTRL_DATA_RSRW , LCD_RW_PIN);              //R/W = 0
    Clear_Bit(LCD_CTRL_DATA_EN , LCD_EN_PIN);              //EN = 0
   
    if(command < 4){
      waitTime(2 , MILLI_SECONDS_SYSTICK);             //command 1 and 2 needs up to 1.64ms
    }else{
        waitTime(40 , MICRO_SECONDS_SYSTICK);          //all others 40 us
    }
}

void LCD_data(unsigned char data)
{
    Set_Bit(LCD_CTRL_DATA_RSRW , LCD_RS_PIN); // RS = 1
    Clear_Bit(LCD_CTRL_DATA_RSRW , LCD_RW_PIN); //RW = 0
    
    LCD_DATA_DATA = data;

    Set_Bit(LCD_CTRL_DATA_EN , LCD_EN_PIN);                // pulse E
    
    waitTime(1 , MICRO_SECONDS_SYSTICK);
    
    Clear_Bit(LCD_CTRL_DATA_EN , LCD_EN_PIN);              //EN = 0
    
    waitTime(40 , MICRO_SECONDS_SYSTICK);
}

void LCD_start(){
    //Initialization sequence
    
    waitTime(20 , MILLI_SECONDS_SYSTICK);                       // Wait >15 ms after power is applied
    LCD_command(0x30);		                                // command 0x30 = Wake up
    waitTime(5 , MILLI_SECONDS_SYSTICK);			// must wait 5ms, busy flag not available
    LCD_command(0x30);		                                // command 0x30 = Wake up #2
    waitTime(100 , MICRO_SECONDS_SYSTICK);			// must wait 100us, busy flag not available
    LCD_command(0x30);		                                // command 0x30 = Wake up #3
    waitTime(100 , MICRO_SECONDS_SYSTICK);			// must wait 100us, busy flag not available
    
    // Prepare LCD Operation and Function  
    LCD_command(0x38);      /* set 8-bit data, 2-line, 5x7 font */
    LCD_command(0x06);      /* move cursor right */
    LCD_command(0x01);      /* clear screen, move cursor to home */
    LCD_command(0x0F);      /* turn on display, cursor blinking */
}

void write_string(char *string){
  clearScreen();
  short i = 0;
  while(string[i] != '\0'){
    LCD_data(string[i]);
    i++;
  }
}

void clearScreen(){
  LCD_command(0x1);                                     //command needed to clear the screen
  waitTime(2 , MILLI_SECONDS_SYSTICK);                  //Wait time needed after this command > 1.64 ms
}