/*
 * App.c
 *
 * Created: 9/23/2021 1:23:00 PM
 *  Author: 20109
 */
#include "App.h"
#include <string.h>

/*States from state machine*/
typedef enum states {
	RED,
	YELLOW,
	GREEN,
	AT,
	ERROR,
	}EN_STATES_t;
	
/*Led configurations*/
ST_LED_CONFIG_t LED_RED = {PORTA,PIN0,ACTIVE_HIGH};
ST_LED_CONFIG_t LED_YELLOW = {PORTA,PIN1,ACTIVE_HIGH};
ST_LED_CONFIG_t LED_GREEN = {PORTA,PIN2,ACTIVE_HIGH};

EN_STATES_t State;
	
void App_Init(){
	ST_UARTConfig_t uart_config = {FREQ_8MHz,BAUD_9600,NO_PARITY,DISABLE_RX_INT,DISABLE_TX_INT};

	/*driver initialization*/
	UART_Init(uart_config);
	LED_init(LED_RED);
	LED_init(LED_YELLOW);
	LED_init(LED_GREEN);
	/*initial state*/
	State = GREEN;
} 

/*app logic*/
void App(){
	
	sint8_t recieve_from_tx[15] = {'\0'};
	
	update_states();						
	UART_ReceiveString(recieve_from_tx);
	
	if ( strcmp(recieve_from_tx,"WAIT")==0){				/*change states according to input*/
		State = YELLOW;
	}
	else if (strcmp(recieve_from_tx,"START") == 0){
		State = GREEN;
	}
	else if(strcmp(recieve_from_tx,"STOP") == 0){
		State = RED;
	}
	else if(strcmp(recieve_from_tx,"AT") == 0){
		State = AT;
	}
	else{
		State = ERROR;
	}
	
}

void update_states(){
	/*states implementation*/
	switch (State){
		case RED:
			LED_ON(LED_RED);
			LED_OFF(LED_GREEN);
			LED_OFF(LED_YELLOW);
			UART_SendString(" RED LED ON ");		
			UART_SendByte(END_OF_STRING);				/*begin a new line*/
			UART_SendString("-> ");						/*start of a new command layout*/

			break;
		case YELLOW:
			LED_OFF(LED_RED);
			LED_OFF(LED_GREEN);
			LED_ON(LED_YELLOW);
			UART_SendString(" YELLOW LED ON ");
			UART_SendByte(END_OF_STRING);
			UART_SendString("-> ");

			break;
		case GREEN:
			LED_OFF(LED_RED);
			LED_ON(LED_GREEN);
			LED_OFF(LED_YELLOW);
			UART_SendString(" GREEN LED ON ");
			UART_SendByte(END_OF_STRING);
			UART_SendString("-> ");

			break;
		case AT:
			UART_SendString(" OK ");
			UART_SendByte(END_OF_STRING);
			UART_SendString("-> ");

			break;
		case ERROR:
			UART_SendString(" NOT DEFINED COMMAND ");
			UART_SendByte(END_OF_STRING);
			UART_SendString("-> ");
			break;
		
	}
}