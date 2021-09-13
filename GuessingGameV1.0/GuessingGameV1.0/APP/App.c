/*
 * App.c
 *
 * Created: 9/13/2021 7:09:48 PM
 *  Author: 20109
 */ 

#include <stdlib.h>
#include "../ECUAL/LCD/Lcd.h"
#include "../ECUAL/BUTTON/Button.h"


#define BUTTON				PORTA,PIN0,INTERNAL_PULLUP
#define DELAY_TIME			2
#define MAX					15
#define MIN					0

ST_TIMER_config_t Timer1Config = {TIMER1 , FREQ_1_MHZ , CTC_MODE};


void convert_2DigitInt_to_str(unsigned char number,char* arr);
void CheckForPassedTime(void);

uint8_t Time_Passed;
uint8_t user_number;
uint8_t rand_number;
uint8_t button_pressed;
uint8_t counter;

void printLayoutMsg(void){
	sint8_t str_number[2];
	Lcd_ClrScreen();
	Lcd_SendString("Guess the number ");
	convert_2DigitInt_to_str(user_number,str_number);
	Lcd_SendStringXY (1,0, str_number);
}

void printGreaterThanMin(void){
	sint8_t min_number[2];
	Lcd_ClrScreen();
	Lcd_SendStringXY(0,0,"Enter number");
	Lcd_SendStringXY(1,0,"Greater than");		
	convert_2DigitInt_to_str(MIN,min_number);
	Lcd_SendStringXY (1,13, min_number);

}
void printLessThanMax(void){
	sint8_t max_number[2];
	Lcd_ClrScreen();
	Lcd_SendStringXY(0,0,"Enter number");
	Lcd_SendStringXY(1,0,"less than");
	convert_2DigitInt_to_str(MAX,max_number);
	Lcd_SendStringXY (1,13, max_number);

}
void printWinMsg()
{
	Lcd_SendCommand(CLR_DISPLAY);
	Lcd_SendStringXY (0,1, "YOU WIN!!!");
}
void printLoseMsg()
{
	sint8_t str_rand_number[2];
	Lcd_SendCommand(CLR_DISPLAY);
	Lcd_SendStringXY (0,1, "YOU LOSE");
	Lcd_SendStringXY (1,0, "Number is ");

	convert_2DigitInt_to_str(rand_number,str_rand_number);
	Lcd_SendStringXY (1,12, str_rand_number);
}
void printStrFromInt(uint8_t number)
{	
	sint8_t str_number[2];
	convert_2DigitInt_to_str(user_number,str_number);
	Lcd_SendStringXY (1,0, str_number);
}

void app_init()
{	
	Lcd_init();
	Timer_init(Timer1Config);
	Button_init(BUTTON);
	Timer_Schedule_Fun(DELAY_TIME,Timer1Config,CheckForPassedTime);
	
	counter = 0;
	user_number=0;
	button_pressed=0;
	Time_Passed = 0;
	rand_number = 0;
	
	printLayoutMsg();
	
}
void app()
{

		//rand_number = (rand()%14) +1;
		rand_number = 5;
		
		if (counter > 1 && button_pressed == 0){
			printGreaterThanMin();
			counter = 0;
		}
		if(Button_read_one_press(BUTTON) == HIGH){
			
			if (button_pressed == 0){
				button_pressed = 1;
				printLayoutMsg();
			}
			
			Time_Passed = 0;
			user_number ++;
			
			if(user_number > 15)
			{
				printLessThanMax();
				user_number = 0;
				button_pressed = 0;
				return;
			}
			
			counter = 0;
			printStrFromInt(user_number);

		}
		else if(Time_Passed > 1){
			if (rand_number == user_number){
				printWinMsg();
			}
			else
			{
				printLoseMsg();
			}
			button_pressed = 0;
			user_number =0;
			Time_Passed =0;
			counter = 0;
		}

}

void convert_2DigitInt_to_str(unsigned char number,char* arr){
	arr[0] = (number / 10);
	
	if (arr[0] == 0){
		arr[0] = number + '0';
		arr[1] = '\0';
		return;
	}
	else{
		arr[1]= (number - (arr[0]*10));
		arr[0]+= '0';
		arr[1]+='0';
		arr[2]= '\0';
	}
}

void CheckForPassedTime(){
	if (button_pressed == 1)
		Time_Passed++;
	
	counter++;
}