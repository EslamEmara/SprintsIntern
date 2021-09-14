/*
 * App.h
 *
 * Created: 9/14/2021 3:03:28 PM
 *  Author: 20109
 */ 


#ifndef APP_H_
#define APP_H_

#include "../ECUAL/KEYPAD/keypad.h"
#include "../ECUAL/LCD/Lcd.h"
#include <stdlib.h>
#include <time.h>

/*
*Function that contains the logic of the application
*void input and return.
*
*
*/
void app();
/*
*Function to initailze the app according to configurations
*void return.
*inputs: None;
*/
void app_init();
/*
*function to check if the character is digit or not
*return 1 if digit and 0 otherwise
*/
uint8_t isDigit(uint8_t number);

/*
*function to check if the number is within the limits
*return 1 if within limits 0 otherwise
*
**/
uint8_t checkLimits(uint8_t number);
	
/*function to print game layout to lcd screen*/
void printLayout();
/*function to print win message to lcd screen*/
void printWinMsg();

/*
*Function to convert 2 digit array into uint8 integer
*inputs: character array contains the number in chaar format
*return : the number in array in integer form
*no changes to inputs
*/

uint8_t Char_Arr_ToInt(uint8_t* arr);

#endif /* APP_H_ */