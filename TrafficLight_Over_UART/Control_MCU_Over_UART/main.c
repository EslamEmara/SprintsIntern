/*
 * Control_MCU_Over_UART.c
 *
 * Created: 9/23/2021 1:19:50 PM
 * Author : 20109
 */ 

#include "APP/App.h"


int main(void)
{
App_Init();
    while (1) 
    {
		App();
    }
}

