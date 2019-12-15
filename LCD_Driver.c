#include "LCD_Driver.h"

void LCD_Init(){
  SYSCTL_RCGCGPIO_R |= (PORTA | PORTB| PORTE);  //Enabling clock for PORTA & PORTB & PORTE
  GPIO_PORTA_DEN_R |= (0xC0);              //Enabling Pins A6,A7
  GPIO_PORTE_DEN_R |= (0x10);              //Enabling Pins E4
  GPIO_PORTB_DEN_R |= 0xFF;              //Enabling all Pins of PORTB
  GPIO_PORTA_DIR_R |= (0xC0);     //Direction of Pins A6,A7 : OUTPUT
  GPIO_PORTE_DIR_R |= (0x10);     // Direction of Pin E4: OUTPUT
  GPIO_PORTB_DIR_R |= 0xFF;              //Direction of PORTB for Data pins : OUTPUT
  Init_Ports();
  
}

void Init_Ports(){
  
  SYSCTL_RCGCTIMER_R |= 0x01;
    SYSCTL_RCGCGPIO_R |= PORTF;
    GPIO_PORTF_LOCK_R = 0x4c4f434b;
    GPIO_PORTF_CR_R = 0xFF;
    GPIO_PORTF_PUR_R |= SW1 | SW2;
    GPIO_PORTF_DIR_R &= ~SW1 & ~SW2;
    GPIO_PORTF_DIR_R |= RED;
    GPIO_PORTF_DEN_R |= SW1 | SW2 | RED;
    
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


void clearScreen(){
  LCD_command(0x1);                                     //command needed to clear the screen
  waitTime(2 , MILLI_SECONDS_SYSTICK);                  //Wait time needed after this command > 1.64 ms
}

void writeNumbersArray(int* array, int count){
  clearScreen();
  for (int i = 0; i < count; i++){
    LCD_Write_Number((array[i]), 0, i);
  }
  LCD_Write_String(".00", 0, count);
}
int getNumber(int* numberCount){
  SYSCTL_RCGCGPIO_R |= PORTF;
    int count = 0;
    int countdown = 0;
    
    int index = 0;
    int numbersSelected[4] = {0};
  
    while(count < 4){
      char key = getPressedKey();
      if (key == 48 & count == 0){
        continue;
      }
      if (key >= 48 && key <= 57){ // key = [0-9]
        count++;
        countdown *= 10;
        countdown += (int)key - 48;
        
        numbersSelected[index] = (int)key - 48;
        index++;
        
        writeNumbersArray(numbersSelected, count);
        
      
      }
      else if (Get_Bit(GPIO_PORTF_DATA_R, 4) == 0){ 
        waitTime(0.1, SECONDS_SYSTICK);
        if (count != 0){
          break;
        }
      }
    
    }
    *numberCount = count;
    return countdown;
}
void LCD_Write_String(char* string, short rowIndex, short columnIndex){
  
  short index = 0;
  unsigned int DDRAM_Address;
  
  if( (rowIndex < LCD_Number_Of_Rows) && (columnIndex < LCD_Number_Of_Columns) ){
    
    DDRAM_Address = (rowIndex * 0x40) + columnIndex;
    DDRAM_Address |= 0x80;
    LCD_command(DDRAM_Address);
    
    while(string[index] != '\0')
    {
      if(DDRAM_Address == 0x90)
      {
        DDRAM_Address = 0xC0;
        LCD_command(DDRAM_Address);
      }else if(DDRAM_Address == 0xD0)
      {
        DDRAM_Address = 0x80;
        LCD_command(DDRAM_Address);
      }
      LCD_data(string[index]);
      index++;
      DDRAM_Address++;
    }
    
  }
}
void swap(char* a, char *b){
  char temp = *a;
  *a = *b;
  *b = temp;
}
void reverse(char* arr, short length){
  short start = 0;
  short end = length - 1;
  while(start < end){
    swap(&arr[start], &arr[end]);
    start++;
    end--;
  }
}
void LCD_Write_Number(unsigned int number, short rowIndex, short columnIndex){
  char arr[20];
  short index = 0, temp;
  if(number == 0){
    arr[index] = '0';
    index++;
  }
  while(number != 0){
    temp = number % 10;
    arr[index] = temp + '0';
    index++;
    number /= 10;
  }
  arr[index] = '\0';
  reverse(arr, index);
  LCD_Write_String(arr,rowIndex,columnIndex);
}


int countDownLCD(int timeMS, int numberCount){
  
  NVIC_ST_CTRL_R = 5;   
  
  const int arraySize = 6; //If you change this, remember to change numbersToPrint array size
  while ((timeMS >= 0)){
    
    NVIC_ST_RELOAD_R = 159999;  
    NVIC_ST_CURRENT_R = 0;
    NVIC_ST_CTRL_R = 5;        
    while (((NVIC_ST_CTRL_R & 0x10000) == 0) && (Get_Bit(GPIO_PORTF_DATA_R, 0) == 1));
    if ((Get_Bit(GPIO_PORTF_DATA_R, 0) == 0)){
      return 1; //Interruption occured
    }
    /*
    Numbers to print where highest significant number is in lowest index
    For example, 314 will be stored like this: [3, 1, 4] where index 0 
    has the value 3
    */
    int numbersToPrint[6] = { 0 };
    int currentTime = timeMS;
  
    for (int i = 0; i < numberCount; i++){
      int numberToPrint = currentTime % 10;
      currentTime = currentTime / 10;
      numbersToPrint[arraySize - 1 - i] = numberToPrint;
    }
  
    bool shouldPrintDot = true;
    for (int i = arraySize - numberCount; i < arraySize; i++){
      if (i == arraySize - 2 && shouldPrintDot){
        LCD_data((char)(46));
        shouldPrintDot = false;
        --i;
      }
      else{
        int extra = 0;
        if (shouldPrintDot == false){
          extra = 1;
        }
        LCD_Write_Number(numbersToPrint[i],0,i - (arraySize - numberCount) + extra);
      }
      

    }
    timeMS -= 1;
  }
  return 0;
  
}

void showEndCountdownMessage(){
  clearScreen();
  LCD_Write_String("Countdown end", 0,0);
  blinkLED(5.0);
}

void blinkLED(double seconds){
  for (int i = 0; i < seconds * 2; i++){
    GPIO_PORTF_DATA_R ^=  RED;
    waitTime(0.5, SECONDS_SYSTICK);
  }
  
}