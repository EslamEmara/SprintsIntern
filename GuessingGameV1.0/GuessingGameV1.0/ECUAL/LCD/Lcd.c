/*
 * Lcd.c
 *
 * Created: 9/13/2021 1:24:59 PM
 *  Author: Eslam Emara
 */ 

#include "Lcd.h"

ST_TIMER_config_t TimerConfig = {TIMER0,FREQ_1_MHZ,NORMAL_MODE};		/*Set the timer for delay configurations*/


/*
*Description: Function to initalize the connected LCD according to Config file
*Set your desired configuration in "Lcd_config.h"
*Expected Output: Setting the control pins and direction pins as output 
*					and sending config commands for connected lcd
*Void input and return.
*
*/

void Lcd_init(){
	Timer_init(TimerConfig);
	#if LCD_MODE == FOUR_BIT_MODE						/*SET HIGH PINS DIRECTIONS OUT AND SEND 4BIT COMMANDS*/
		DIO_setPinDir(LCD_D4,OUT);
		DIO_setPinDir(LCD_D5,OUT);
		DIO_setPinDir(LCD_D6,OUT);
		DIO_setPinDir(LCD_D7,OUT);
	
		DIO_setPinDir(LCD_RS,OUT);						/*CONTROL PINS*/
		DIO_setPinDir(LCD_EN,OUT);
		DIO_setPinDir(LCD_RW,OUT);
		
		Lcd_SendCommand(LCD_4BIT_MODE);					/*4BIT COMMANDS*/
		Lcd_SendCommand(FOUR_BIT_TWO_LINES_5x7);	

	#else												/*SET PINS DIRECTIONS OUT AND SEND 8BIT COMMANDS*/
		DIO_setPinDir(LCD_D0,OUT);
		DIO_setPinDir(LCD_D1,OUT);
		DIO_setPinDir(LCD_D2,OUT);
		DIO_setPinDir(LCD_D3,OUT);
		DIO_setPinDir(LCD_D4,OUT);
		DIO_setPinDir(LCD_D5,OUT);
		DIO_setPinDir(LCD_D6,OUT);
		DIO_setPinDir(LCD_D7,OUT);
		
		DIO_setPinDir(LCD_RS,OUT);						/*CONTROL PINS*/
		DIO_setPinDir(LCD_EN,OUT);
		DIO_setPinDir(LCD_RW,OUT);
		
		Lcd_SendCommand(LCD_8BIT_MODE);						/*8BIT COMMANDS*/
		Lcd_SendCommand(EIGHT_BIT_TWO_LINES_5x7);			

	#endif

	Lcd_SendCommand(DISPLAY_ON_CURSOR_OFF);              /* Display on cursor off*/
	Lcd_SendCommand(CURSOR_RIGHT);						 /* shift cursor to right*/
	Lcd_SendCommand(CLR_DISPLAY);						 /* Clear screen*/	
	
}
/*
*Description: Function to send a command byte to the LCD (see commands in lcd.h)
*Input: uint8_t command 
*Output: NONE
*return void
*
*/
void Lcd_SendCommand( uint8_t cmnd )
{
	#if LCD_MODE == FOUR_BIT_MODE
		WriteHighNibble(cmnd);

		DIO_clearPin(LCD_RS);						/*Write to control register*/
		ToggleEN();

		WriteLowNibble(cmnd);
		ToggleEN();
	#endif
}
/*
*Description: Function to display a character on the lcd 
*Input: uint8_t ascii code of the character 
*Expected Output: the character is printed on the screen.
*void return.
*/
void Lcd_SendChar( uint8_t data )
{
	#if LCD_MODE == FOUR_BIT_MODE
		WriteHighNibble(data);					
	
		DIO_setPin(LCD_RS);						/*Write to Data register*/
		ToggleEN();
	
		WriteLowNibble(data);
		ToggleEN();
	#endif
}
/*
*Description: Function to print a string on the screen
*Inputs: pointer to a character points to the first character of the string
*Void return.
*EXAMPLE: Lcd_SendString("Hello World");
*/
void Lcd_SendString (sint8_t *str)		/* Send string to LCD function */
{
	uint8_t chars_iterator;
	for(chars_iterator=0;str[chars_iterator]!= '\0';chars_iterator++){		/* Send each char of string till the end of string */
		Lcd_SendChar (str[chars_iterator]);
	}
}
/*
*Description: Function to put the cursor on the screen in a certain position
*inputs: row number , column number , string to be printed
*		row number must be 0 or 1 if using 16*2 LCD
*		column number must be less than maximum character numbers in one row
*void return.
*/
void Lcd_GoToXY(uint8_t row , uint8_t col){
	
	if (col < MAX_CHARS && row <MAX_ROWS){
		if (row == 0){									/*First row , row number 0*/
			Lcd_SendCommand((col & 0x0F)|CURSOR_BEGIN_FIRST_LINE);
		}
		else if(row == 1){								/*Second row , row number 1*/
			Lcd_SendCommand((col & 0x0F)|CURSOR_BEGIN_SECOND_LINE);
		}
	}
}
/*
*Description: Function to print a string on the screen in a certain position
*inputs: row number , column number , string to be printed
*		row number must be 0 or 1 if using 16*2 LCD
*		column number must be less than maximum character numbers in one row
*void return.
*/
void Lcd_SendStringXY (uint8_t row, uint8_t col, sint8_t *str)
{
		Lcd_GoToXY(row,col);
		Lcd_SendString(str);
}
/*
*Description: function to delay until processor is not busy
*inputs: None.
*Return: none.
*Expected Output: Delay the code until the processor of lcd is done from the current instruction
**/
void Lcd_CheckBusyFlag()
{
	DIO_setPinDir(LCD_D7,IN);
	DIO_clearPin(LCD_RS);
	DIO_setPin(LCD_RW);
	
	while(DIO_getPin(LCD_D7) == HIGH);
	
	DIO_setPinDir(LCD_D7,OUT);
	DIO_clearPin(LCD_RW);
}
/*
* Function to clean the LCD screen.
* Inputs: NONE
* void return.
**/
void Lcd_ClrScreen(){
	Lcd_SendCommand(CLR_DISPLAY);
}

/*
Description: Function to write low nibble of number to the connected high pins for 4bit mode
*Input : uint8_t the number to write
*return: None
*/

 void WriteLowNibble( uint8_t n ){
	DIO_write(LCD_D4 , ((n) & (0x01)) );
	DIO_write(LCD_D5 , ((n >> 1) & (0x01)) );
	DIO_write(LCD_D6 , ((n >> 2) & (0x01)) );
	DIO_write(LCD_D7 , ((n >> 3) & (0x01)) );
}

/*
Description: Function to write high nibble of number to the connected high pins for 4bit mode
*Input : uint8_t the number to write
*return: None
*/

 void WriteHighNibble( uint8_t n ){
	DIO_write(LCD_D4 , ((n>>4) & (0x01)) );
	DIO_write(LCD_D5 , ((n >> 5) & (0x01)) );
	DIO_write(LCD_D6 , ((n >> 6) & (0x01)) );
	DIO_write(LCD_D7 , ((n >> 7) & (0x01)) );
}

/*
Description: Function to make a falling edge on the enable pin with delay 1us
*Input : None.
*return: None.
*/
void ToggleEN(void){
	DIO_setPin(LCD_EN);
	Timer_Delay(0.000001,TimerConfig);
	DIO_clearPin(LCD_EN);
}