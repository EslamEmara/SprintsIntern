/*
 * Lcd_config.h
 *
 * Created: 9/13/2021 3:05:10 PM
 *  Author: 20109
 */ 


#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

#include "../../MCAL/DIO/DIO.h"

#define UNDEFINED		0
#define FOUR_BIT_MODE	1
#define EIGHT_BIT_MODE	2



#define LCD_MODE		FOUR_BIT_MODE

#define LCD_RS			PORTC,PIN0
#define LCD_RW			PORTC,PIN1
#define LCD_EN			PORTC,PIN2

#if LCD_MODE == FOUR_BIT_MODE

	#define LCD_D4			PORTC,PIN3
	#define LCD_D5			PORTC,PIN4
	#define LCD_D6			PORTC,PIN5
	#define LCD_D7			PORTC,PIN6
#else 

	#define LCD_D0			UNDEFINED
	#define LCD_D1			UNDEFINED
	#define LCD_D2			UNDEFINED
	#define LCD_D3			UNDEFINED
	#define LCD_D4			PORTD,PIN4
	#define LCD_D5			PORTD,PIN5
	#define LCD_D6			PORTD,PIN6
	#define LCD_D7			PORTD,PIN7

#endif



#endif /* LCD_CONFIG_H_ */