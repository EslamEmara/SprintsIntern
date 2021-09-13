/*
 * Button.h
 *
 * Created: 9/3/2021 3:23:22 PM
 *  Author: 20109
 */ 

#ifndef BUTTON_H_
#define BUTTON_H_

#include "..\..\MCAL\DIO\DIO.h"

//#define	 DEBOUNCTING_TIME	 50

typedef enum {											/*connection type*/
	PULLUP_RES,
	PULLDOWN_RES,
	INTERNAL_PULLUP,
}EN_CONN_t;

/*
 *	Function to initialize to Button pin
 *	Inputs:  uint8 port,uint8 pin
 *	void return.
 *	Expected Output: PIN of the button is set as input.
 */
void Button_init(EN_PORTS_t port,EN_PINS_t pin,EN_CONN_t conn);
/*
 *	Function to read to Button state
 *	Inputs:  uint8 port,uint8 pin,EN_CONN_t conn (See Button.h for definition)
 *	conn options (PULLUP_RES) or (PULLDOWN_RES) according to your desired connection
 *	Return: 1 if the button is pressed 0 otherwise.
 *	=================PS:: FUNCTION MUST BE CALLED PERIDOCALLY TO AVOID DEBOUNCING EFFECTS======================
 * change DEBOUNCING TIME macro in Button.h according to your app.
 */
uint8_t Button_read(EN_PORTS_t port,EN_PINS_t pin,EN_CONN_t conn);
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
uint8_t Button_read_one_press(EN_PORTS_t port,EN_PINS_t pin,EN_CONN_t conn);


#endif /* BUTTON_H_ */
