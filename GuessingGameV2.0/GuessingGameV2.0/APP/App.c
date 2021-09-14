/*
 * App.c
 *
 * Created: 9/14/2021 3:03:40 PM
 *  Author: 20109
 */ 
#include "App.h"

#define MAX_NUMBER					15
#define MAX_ENTER_DIGIT				2
#define MIN_NUMBER					0

uint8_t keypad_reading ;			/*return of keypad press*/
uint8_t number[MAX_ENTER_DIGIT+1] ={0};				/*array of characters contain user inputs*/
uint8_t digit_count;				/*number of digits entered*/
uint8_t num_int;					/*number in integer format*/
uint8_t rand_number;				/*generated random number*/
	
/*
*Function to convert 2 digit array into uint8 integer 
*inputs: character array contains the number in chaar format
*return : the number in array in integer form
*no changes to inputs
*/

uint8_t Char_Arr_ToInt(uint8_t* arr){

	if (arr[1] == 0){
		return (arr[0] - '0');
	}
	else{
		return (arr[0]-'0')*10 + (arr[1]-'0');
	}
}
/*
*Function to initailze the app according to configurations
*void return.
*inputs: None;
*/
void app_init()
{
		Keypad_init();
		Lcd_init();
		srand(time(0));					/*generate new number every runtime*/
		
		keypad_reading = 0;
		digit_count = 0;
		num_int = 0;
		rand_number = ((rand()%14)+1);
		
		printLayout();
		
}
/*
*Function that contains the logic of the application 
*void input and return.
*
*
*/
void app(){	
	
	keypad_reading = Keypad_read(ONE_PRESS);					/*read from keypad in ONE_PRESS mode*/
	if (keypad_reading != NO_KEY_PRESSED){						/*check if button is pressed*/
		if(isDigit(keypad_reading)){							
			if (digit_count <= (MAX_ENTER_DIGIT - 1)){			/*check if input digits is less than maximum digits*/
				number[digit_count] = keypad_reading;
				number[digit_count+1] = '\0';					/*terminate string after input character*/
				printLayout();
				Lcd_GoToXY(1,0);
				Lcd_SendString((char*)number);
				digit_count++;
			}
		}
		if(keypad_reading == '='){
			num_int = Char_Arr_ToInt(number);					/*get integer number from array*/
			
			if(!checkLimits(num_int)){
				Lcd_ClrScreen();
				Lcd_SendString("Not Valid");
			}
			else{
				if (num_int == rand_number){
					printWinMsg();
					rand_number = ((rand()%14)+1);				/*generate new random number*/
				}
				else{
					Lcd_ClrScreen();
					Lcd_SendString("Try Again!!");
				}
			}
			num_int = 0;										/*Reset variables*/
			number[0] = 0;									/*reset number array in case of 2 digits inputs only (our limit)*/
			number[1]=0;		
			digit_count = 0;
		}
	}
}

/*function to check if the character is digit or not
*return 1 if digit and 0 otherwise
*/
uint8_t isDigit(uint8_t number){
	return (number >='0' && number <= '9')? 1:0;
}

/*
*function to check if the number is within the limits
*return 1 if within limits 0 otherwise
*
**/
uint8_t checkLimits(uint8_t number){
	return (number > MAX_NUMBER || number <= MIN_NUMBER)? 0:1;
}

/*function to print game layout to lcd screen*/
void printLayout(){
	
	Lcd_ClrScreen();	
	Lcd_SendString("Guess!");
}

/*function to print win message to lcd screen*/
void printWinMsg(){
	Lcd_ClrScreen();
	Lcd_SendString("You Win!!");
	Lcd_GoToXY(1,0);
	Lcd_SendString("Press to play!!");
}