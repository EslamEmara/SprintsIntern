/*
 * Lcd.h
 *
 * Created: 9/13/2021 1:25:22 PM
 *  Author: 20109
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "../../MCAL/TIMER/Timer.h"
#include "Lcd_config.h"

/*AVAILABLE COMMANDS FOR THE CONTROL REGISTER*/
#define LCD_ON_CURSOR_ON			0x0F
#define CLR_DISPLAY					0x01
#define RETURN_HOME					0x02
#define CURSOR_LEFT					0x04
#define CURSOR_RIGHT				0x06
#define DISPLAY_LEFT				0x07
#define DISPLAY_RIGHT				0x05
#define	DISPLAY_ON_CURSOR_BLINK		0x0E
#define CURSOR_BEGIN_FIRST_LINE		0x80
#define CURSOR_BEGIN_SECOND_LINE	0xC0
#define EIGHT_BIT_TWO_LINES_5x7		0x38
#define FOUR_BIT_TWO_LINES_5x7		0x28
#define ACTIVATE_SECOND_LINE		0x3C
#define	DISPLAY_OFF_CURSOR_OFF		0x08
#define	DISPLAY_ON_CURSOR_OFF		0x0C
#define LCD_8BIT_MODE				0x38
#define LCD_4BIT_MODE				0x02
#define JUMP_SECOND_POS1			0xC1

/*LCD TYPE*/
#define MAX_ROWS					2
#define MAX_CHARS					16

/*
*Description: Function to initalize the connected LCD according to Config file
*Set your desired configuration in "Lcd_config.h"
*Expected Output: Setting the control pins and direction pins as output
*					and sending config commands for connected lcd
*Void input and return.
*/
void Lcd_init();
/*
*Description: Function to send a command byte to the LCD (see commands in lcd.h)
*Input: uint8_t command
*Output: NONE
*return void
*/
void Lcd_SendCommand( unsigned char cmnd );

/*
*Description: Function to print a string on the screen
*Inputs: pointer to a character points to the first character of the string
*Void return.
*EXAMPLE: Lcd_SendString("Hello World");
*/

void Lcd_SendString (sint8_t *str);

/*
*Description: Function to put the cursor on the screen in a certain position
*inputs: row number , column number , string to be printed
*		row number must be 0 or 1 if using 16*2 LCD
*		column number must be less than maximum character numbers in one row
*void return.
*/
void Lcd_GoToXY(uint8_t row , uint8_t col);

/*
*Description: Function to print a string on the screen in a certain position
*inputs: row number , column number , string to be printed
*		row number must be 0 or 2 if using 16*2 LCD
*		column number must be less than maximum character numbers in one row
*void return.
*/

void Lcd_SendStringXY (uint8_t row, uint8_t col, sint8_t *str);
/*
*Description: Function to display a character on the lcd
*Input: uint8_t ascii code of the character
*Expected Output: the characted is printed on the screen.
*void return.
*/
void Lcd_SendChar( uint8_t data );
/*
*Description: function to delay until processor is not busy
*inputs: None.
*Return: none.
*Expected Output: Delay the code until the processor of lcd is done from the current instruction
**/
void Lcd_CheckBusyFlag();
/*
* Function to clean the LCD screen.
* Inputs: NONE
* void return.
**/
void Lcd_ClrScreen();
/*
Description: Function to write low nibble of number to the connected high pins for 4bit mode
*Input : uint8_t the number to write
*return: None
*/

void WriteLowNibble(uint8_t);
/*
Description: Function to write high nibble of number to the connected high pins for 4bit mode
*Input : uint8_t the number to write
*return: None
*/

void WriteHighNibble(uint8_t);
/*
Description: Function to make a falling edge on the enable pin with delay 1us
*Input : None.
*return: None.
*/
void ToggleEN();


#endif /* LCD_H_ */