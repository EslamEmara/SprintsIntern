/*
 * Chatting_through_terminals.c
 *
 * Created: 9/25/2021 2:30:39 PM
 * Author : 20109
 */ 

#include "./MCAL/SPI/SPI.h"
#include "MCAL/UART/UART.h"

#define SLAVE_0		0

int main(void)
{

	ST_UARTConfig_t UartConfig = {FREQ_1MHz,BAUD_4800,NO_PARITY,DISABLE_RX_INT,DISABLE_TX_INT};
	SPI_Master_Init(DIVISOR_16);
	UART_Init(UartConfig);
	sint8_t recieved_string[UART_MAX_STRING_SIZE];
	
	
    while (1) 
    {
		UART_ReceiveString(recieved_string);
		SPI_Master_SendString(recieved_string,SLAVE_0);
		SPI_Master_SendByte(SPI_END_OF_STRING,SLAVE_0);
	}
}

