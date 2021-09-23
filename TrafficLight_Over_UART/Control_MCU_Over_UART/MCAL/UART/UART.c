/*
 * UART.c
 *
 * Created: 9/22/2021 3:33:36 PM
 *  Author: Eslam Emara
 */ 

#include "UART.h"

void __vector_13(void) __attribute__((signal,used));			//RX interrupt
void (*RX_ISR)(void);

void __vector_15(void) __attribute__((signal,used));			//TX interrupt
void (*TX_ISR)(void);


/*
*Function to initialize uart peripheral 
*Inputs: ST_UARTconfig_t	{frequency,baud,parity,rx interrupt,tx interrupt} see UART.h for details
*EN_FREQ_t frequency 
*EN_BAUD_t baud
*EN_PARITY_t parity
*EN_RXINT_t RX interrupt
*EN_RXINT_t TX interrupt
*Example: frequency 8 mega ,baud 9600,no parity , disable interrupts
	*ST_UARTconfig_t UARTconfig = {FREQ_8MHz , BAUD_9600 , NO_PARITY ,DISABLE_RX_INT,DISABLE_TX_INT};
	*UART_Init(UARTconfig);
*/
void UART_Init(ST_UARTConfig_t	config){
	
	uint16_t baud_mapping = (((config.frequency / (config.baud * 16))) - 1);
	
	/*enabling rx and tx*/
	SETBIT (UCSRB,4);			/*enable reciever*/
	SETBIT (UCSRB,3);			/*enalbe transmit*/
	
	/*setting baud rate*/
	UBRRL =  baud_mapping;	
	CLRBIT(UBRRH,7);				/*write to ubrrh reg*/
	UBRRH =	 (baud_mapping >> 8);
	
	/*asynchronus mode*/
	SETBIT(UCSRC,7);				/*write to UCSRC reg*/
	CLRBIT(UCSRC,6);				/*asynchronous*/
	
	/*parity mode*/
	if(config.parity == EVEN_PARITY){
		SETBIT(UCSRC,5);
		CLRBIT(UCSRC,4);
	}
	else if(config.parity == ODD_PARITY){
		SETBIT(UCSRC,5);
		SETBIT(UCSRC,4);
	}
	else if(config.parity == NO_PARITY){
		CLRBIT(UCSRC,5);
		CLRBIT(UCSRC,4);
	}
	
	/*8-bit data mode*/
	SETBIT (UCSRC , 1);
	SETBIT (UCSRC , 2);
	
	/*interrupt config*/
	if(config.RxInt == ENABLE_RX_INT){
		SETBIT(STATUS_REG,7);
		SETBIT(UCSRB,7);
	}
	if(config.TxInt == ENABLE_TX_INT){
		SETBIT(STATUS_REG,7);
		SETBIT(UCSRB,6);
	}
	
	
}
/*
*Function to send 8 bits data through uart TX
*inputs: uint8_t data
*void return
*connect device to RX
*
*/
void UART_SendByte(uint8_t data)
{
	while (!GETBIT(UCSRA,5));	/* Wait for empty transmit buffer*/
	UDR = data ;
	SETBIT(UCSRA,6);			/*clear transmit flag*/

}

/*
*Function to recieve 8 bits data through uart RX
*inputs: void
*return:uint8_t data
*connect device to TX
*
*/

uint8_t UART_ReceiveByte()
{
	while (!GETBIT(UCSRA,7));
	return	(UDR);
}
/*
*Function to send string until null terminator through uart TX
*input parameter: sint_8 string
*return:void
*
*
*/
void UART_SendString(sint8_t *str)
{
	uint8_t j=0;
	for (j=0; str[j]!='\0';j++){
		UART_SendByte(str[j]);
	}
}
/*
*Function to recieve string until # character through uart RX
*i/o parameter: sint_8 string 
*return:void
*
*
*/
void UART_ReceiveString(sint8_t *str)
{
	uint8_t i = 0;
	
	for (i = 0 ;i<MAX_STRING_SIZE;i++){
		str[i] = UART_ReceiveByte();
		
		if(str[i]==END_OF_STRING){
			str[i] = '\0';
			break;
		}
		
	}
}

/*
*Function to set the Rx complete interrupt function 
*inputs: adrress of function to call every recieve complete
*return: none
*
*/
void UART_SetRXCompleteISR(void (*function)(void)){
	RX_ISR = function;
}
/*
*Function to set the Tx complete interrupt function
*inputs: adrress of function to call every transmission complete
*return: none
*
*/
void UART_SetTXCompleteISR(void (*function)(void)){
	TX_ISR = function;
}


/*ISRs*/
void __vector_13(){
	RX_ISR();
	SETBIT(UCSRA,7);
}

void __vector_15(){
	TX_ISR();
	SETBIT(UCSRA,6);

}

