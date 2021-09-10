/*
 * main.c
 *
 * Created: 9/4/2021 6:15:39 AM
 *  Author: Eslam Emara
 */ 

#include ".\MCAL\TIMER\Timer.h"
#include ".\ECUAL\LED\Led.h"


ST_LED_CONFIG_t LEDconfig = {PORTA,PIN0,ACTIVE_HIGH};
ST_LED_CONFIG_t LED2config = {PORTA,PIN1,ACTIVE_HIGH};

ST_TIMER_config_t TIMERconfig = {TIMER1,FREQ_1_MHZ,CTC_MODE};
ST_TIMER_config_t TIMER2config = {TIMER0,FREQ_1_MHZ,CTC_MODE};



void led();
void led2();

int main(void)
{
		
	Timer_init(TIMERconfig);
	LED_init(LEDconfig);
	
	Timer_init(TIMER2config);
	LED_init(LED2config);

	if(Timer_Schedule_Fun(0.3,TIMERconfig,led));
	
	if(Timer_Schedule_Fun(0.1,TIMER2config,led2));
	
	while(1)
	{
		
	}
	
}

void led()
{
	LED_TOGGLE(LEDconfig);
}
void led2()
{
	LED_TOGGLE(LED2config);

}
