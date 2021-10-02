/*
 * I2C_Driver.c
 *
 * Created: 9/25/2021 8:24:44 PM
 * Author : 20109
 */ 
#define F_CPU	1000000UL
#include "MCAL/I2C/I2C.h"
#include <util/delay.h>

int main(void)
{

	I2C_Init(FREQ_1MHz,1000);
	I2C_Start_Wait(0x20);			/* Start I2C with SLA+W */
	_delay_ms(1000);

    while (1) 
    {	
		I2C_Master_Write(0x77);
		_delay_ms(1000);
		I2C_Stop();
    }
}

