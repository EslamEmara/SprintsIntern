/*
 * UART.h
 *
 * Created: 9/22/2021 3:33:26 PM
 *  Author: Eslam Emara
 */ 


#ifndef UART_H_
#define UART_H_

#include "BIT_MATH.h"
#include "RegMap.h"
#include "TypeDefs.h"

#define END_OF_STRING		0x0D
#define MAX_STRING_SIZE		15

/*frequencies*/
typedef enum{
	FREQ_1MHz = 1000000,
	FREQ_2MHz = 2000000,
	FREQ_4MHz = 4000000,
	FREQ_8MHz = 8000000,
	FREQ_16MHz= 16000000,
}EN_FREQ_t;
/*baud rates*/
typedef enum{
	BAUD_2400 =2400,
	BAUD_4800 =4800,
	BAUD_9600 =9600,
	BAUD_14400=14400,
	BAUD_19200=19200,
	BAUD_28800=28800,
	BAUD_38400=38400,
	BAUD_57600=57600,
	BAUD_76800=76800,
	BAUD_115200=115200,
	BAUD_230400=230400,
	BAUD_250k=250000,
	BAUD_500000=500000,
	BAUD_1M=1000000,
}EN_BAUD_t;
/*parity mode*/
typedef enum{
	ODD_PARITY,
	EVEN_PARITY,
	NO_PARITY,
}EN_PARITY_t;
/*recieve complete interrupt*/
typedef enum{
		ENABLE_RX_INT,
		DISABLE_RX_INT,
}EN_RXINT_t;
/*transmission complete interrupt*/
typedef enum{
	ENABLE_TX_INT,
	DISABLE_TX_INT,
}EN_TXINT_t;

/*configuration structure*/
typedef struct uart{
	EN_FREQ_t	frequency;
	EN_BAUD_t	baud;
	EN_PARITY_t	parity;
	EN_RXINT_t	RxInt;
	EN_TXINT_t	TxInt;
}ST_UARTConfig_t;

/*
*Function to initialize uart peripheral 
*Inputs: ST_UARTconfig_t	{frequency,baud,parity,rx interrupt,tx interrupt} see UART.h for details
*EN_FREQ_t frequency 
*EN_BAUD_t baud
*EN_PARITY_t parity
*EN_RXINT_t rx interrupt
*EN_RXINT_t tx interrupt
*Example: frequency 8 mega ,baud 9600,no parity , disable interrupts
	*ST_UARTconfig_t UARTconfig = {FREQ_8MHz , BAUD_9600 , NO_PARITY ,DISABLE_RX_INT,DISABLE_TX_INT};
	*UART_Init(UARTconfig);
*/
void UART_Init(ST_UARTConfig_t	config);
/*
*Function to send 8 bits data through uart TX
*inputs: uint8_t data
*void return
*connect device to RX
*
*/
void UART_SendByte(uint8_t data);
/*
*Function to recieve 8 bits data through uart RX
*inputs: void
*return:uint8_t data
*connect device to TX
*
*/
uint8_t UART_ReceiveByte();
/*
*Function to send string until null terminator through uart TX
*input parameter: sint_8 string
*return:void
*
*
*/
void UART_SendString(sint8_t *str);
/*
*Function to recieve string until # character through uart RX
*i/o parameter: sint_8 string
*return:void
*
*
*/
void UART_ReceiveString(sint8_t *str);
/*
*Function to set the Rx complete interrupt function
*inputs: adrress of function to call every recieve complete
*return: none
*
*/
void UART_SetRXCompleteISR(void (*function)(void));
/*
*Function to set the Tx complete interrupt function
*inputs: adrress of function to call every transmission complete
*return: none
*
*/
void UART_SetTXCompleteISR(void (*function)(void));

#endif /* UART_H_ */