/*
 * Button.c
 *
 * Created: 9/3/2021 3:23:04 PM
 *  Author: Eslam Emara
 */

#include "Button.h"

/*
 *	Function to initialize to Button pin
 *	Inputs:  uint8 port,uint8 pin
 *	void return.
 *	Expected Output: PIN of the button is set as input.
 */
void Button_init(EN_PORTS_t port,EN_PINS_t pin,EN_CONN_t conn)
{
	if (conn == INTERNAL_PULLUP)
		DIO_setPinDir(port ,pin ,INTERNAL_PULLUP);
	else 
		DIO_setPinDir(port ,pin ,IN);
}

/*
 *	Function to read to Button state
 *	Inputs:  uint8 port,uint8 pin,EN_CONN_t conn (See Button.h for definition)
 *	conn options (PULLUP_RES) or (PULLDOWN_RES) according to your desired connection
 *	Return: 1 if the button is pressed 0 otherwise.
 *	=================PS:: FUNCTION MUST BE CALLED PERIDOCALLY TO AVOID DEBOUNCING EFFECTS======================
 * change DEBOUNCING TIME macro in Button.h according to your app.
 */
uint8_t Button_read(EN_PORTS_t port,EN_PINS_t pin,EN_CONN_t conn)
{
	if (conn == PULLDOWN_RES){
		return DIO_getPin(port,pin);
	}
	else{
		return !DIO_getPin(port,pin);
	}

}
/*
 *	Function to read the state of the button in one press
 * INPUTS:uint8 Button port, uint8 Button Pin , EN_CONN_t connection type
 * return the current value of the button one time only otherwise return 2
 *EX:: if you want to increase variable one time in every press
 *	while(1){
		if(Button_read_one_press(portA,0,PULLUP_RES) == HIGH){
			variable ++;
		}
	}
 */

uint8_t Button_read_one_press(EN_PORTS_t port,EN_PINS_t pin,EN_CONN_t conn)
{
	uint8_t current_value =0;
	static uint8_t last_value = 0;
	uint8_t return_value = 0;
	
	current_value = Button_read(port,pin,conn);
	
	if (current_value!=last_value){
		return_value = current_value;					/*return pressed value */
	}
	else return_value = 2;								/*return any other value*/
	
	last_value = current_value;							/*update variables*/
	
	return return_value;
}

