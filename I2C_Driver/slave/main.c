/*
 * slave.c
 *
 * Created: 9/26/2021 12:31:34 PM
 * Author : 20109
 */ 

#include "MCAL/I2C/I2C.h"
#include <avr/io.h>

int main(void)
{	DDRD = 0xFF;
	uint8_t x;
	I2C_Slave_Init(0x20);
	sint8_t count = 0;
    while (1) 
    {
		switch(I2C_Slave_Listen())	/* Check for SLA+W or SLA+R */
		{
			case 0:
			{
				do
				{
					count = I2C_Slave_Receive();/* Receive data byte*/
					if(count != 255)
						PORTD = count;
					
				} while (count != -1);/* Receive until STOP/REPEATED START */
					
				count = 0;
				break;
			}
			
		}
	}
}

