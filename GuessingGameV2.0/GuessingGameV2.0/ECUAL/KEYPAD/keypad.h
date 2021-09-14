/*
 * keypad.h
 *
 * Created: 9/14/2021 12:13:06 PM
 *  Author: 20109
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "../../MCAL/DIO/DIO.h"
#include "Keypad_config.h"

#define NO_KEY_PRESSED		0				/*return value if no button is pressed*/

typedef enum {								/*Reading from keypad modes*/
	ONE_PRESS,
	CONTINOUS,
	}EN_KEYPAD_ReadingMode;
/*
*Description: Function to init keypad according to the configuration file (see keypad_config.h)
*Inputs: none
*void return
*Expected Output: configured pins are used as DIO
*======================= make sure you configured the keypad pins in "keypad_config.h"========================
*/
void Keypad_init();

/*
*Function to check the pressed key on the 4*4 keypad
*Inputs: none
*return: Ascii code of the pressed button {'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'o','0','=','+'}
*if no button is pressed it return NO_KEY_PRESSED which is defined in keypad.h
*/
uint8_t Keypad_read(EN_KEYPAD_ReadingMode MODE);

/*
*Function to map the button presses to the return values continuously
*input:Row number to check
*return:
*it checks for pressed button in the selected row
*if no button is pressed in the row it returns 0 ,otherwise it returns the character
*of the pressed button continuously
*This function is designed for 4x4 keypad
*/

uint8_t MapKeyPad4x4_cont(uint8_t row);

/*
*Function to map the button presses to the return values one time only
*input:Row number to check
*return:
*it checks for pressed button in the selected row
*if no button is pressed in the row it returns 0 ,otherwise it returns the character
*of the pressed button one time only and return any other value for the rest of readings
*This function is designed for 4x4 keypad
*/

uint8_t MapKeyPad4x4_OnePress(uint8_t row);

/*Function to return actual pin state one time only
*Input parameters:  EN_PORTS_t PORT (DIO.h)
*					EN_PINS_t pin (DIO.h)
*I/O parameters:	uint8_t* last_value reserves the last pin state
*return:	return pin state one time only and return any other value for the rest of readings
*
*/

uint8_t read_one_press(EN_PORTS_t port,EN_PINS_t pin,uint8_t* last_value);



#endif /* KEYPAD_H_ */