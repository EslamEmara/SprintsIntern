/*
 * Slave.c
 *
 * Created: 9/25/2021 2:47:29 PM
 * Author : 20109
 */ 

#include "./MCAL/SPI/SPI.h"
#include "MCAL/UART/UART.h"


int main(void)
{
	ST_UARTConfig_t UartConfig = {FREQ_1MHz,BAUD_4800,NO_PARITY,DISABLE_RX_INT,DISABLE_TX_INT};
	UART_Init(UartConfig);

	SPI_Slave_Init();
	sint8_t recieved_string[UART_MAX_STRING_SIZE];
    while (1) 
    {
		SPI_Slave_RecieveString(recieved_string);
		UART_SendString(recieved_string);
    }
}

