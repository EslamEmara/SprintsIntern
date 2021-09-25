/*
 * SPI_Driver.c
 *
 * Created: 9/24/2021 10:59:13 PM
 * Author : 20109
 */ 

#include "MCAL/SPI/SPI.h"
#include "MCAL/TIMER/Timer.h"

#define SLAVE_0			0
#define DELAY			1

int main(void)
{
	ST_TIMER_config_t timerconfig = {TIMER1,FREQ_1_MHZ,NORMAL_MODE};
	SPI_Master_Init(DIVISOR_128);
	Timer_init(timerconfig);

    while (1) 
    {
		SPI_Master_SendByte('A',SLAVE_0);
		Timer_Delay(DELAY,timerconfig);
		SPI_Master_SendByte('B',SLAVE_0);
		Timer_Delay(DELAY,timerconfig);
		SPI_Master_SendByte('C',SLAVE_0);
		Timer_Delay(DELAY,timerconfig);
    }
	
}