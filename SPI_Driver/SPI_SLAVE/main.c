/*
 * SPI_SLAVE.c
 *
 * Created: 9/25/2021 12:10:45 AM
 * Author : 20109
 */ 

#include "MCAL/SPI/SPI.h"
#include "MCAL/DIO/DIO.h"
#include "ECUAL/LCD/Lcd.h"

int main(void)
{
	sint8_t recieve_char;

	SPI_Slave_Init();
	Lcd_init();
	
	DIO_setPortDir(PORTC,OUT);
	
    while (1) 
    {
		recieve_char = SPI_Slave_ReceiveByte();
		Lcd_GoToXY(0,0);
		Lcd_SendChar(recieve_char);
    }
}

