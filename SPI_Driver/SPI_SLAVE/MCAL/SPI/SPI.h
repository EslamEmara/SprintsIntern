/*
 * SPI.h
 *
 * Created: 9/24/2021 11:15:41 PM
 *  Author: 20109
 */ 


#ifndef SPI_H_
#define SPI_H_

#include "BIT_MATH.h"
#include "SPI_RegMap.h"
#include "TypeDefs.h"

#define END_OF_STRING	'#'
#define MAX_STRING_SIZE 20

typedef enum {
	
	DIVISOR_4 = 0b000,
	DIVISOR_16 = 0b001,
	DIVISOR_64 = 0b010,
	DIVISOR_128 = 0b011,
	DIVISOR_2 = 0b100,
	DIVISOR_8 = 0b101,
	DIVISOR_32 = 0b110,
	
	}EN_OSC_t;

/*
*Function to initalize Master Spi with desired frequency
*Inputs: EN_OSC_t with divisior oscillator (see spi.h for definition)
*void return
*/
void SPI_Master_Init(EN_OSC_t oscillator);				

/*
*Function to send byte to selected slave according to daisy chain connection
*inputs: uint8_t data to send , uint8_t Slave number in connection
*void return
*/
void SPI_Master_SendByte(uint8_t data,uint8_t SlaveID);	
/*
*Function to receive byte from selected slave according to daisy chain connection
*inputs: uint8_t Slave number in connection
*return : uint8_t data received
*/
uint8_t SPI_Master_RecieveByte(uint8_t SlaveID);
/*
*Function to receive string to selected slave according to daisy chain connection
*i/o: sint8_t * data to send points to array of MAX_CHARS defined in .h file
input: uint8_t Slave number in connection
*void return
*/
void SPI_Master_RecieveString(sint8_t *str,uint8_t SlaveID);
/*
*Function to send string to selected slave according to daisy chain connection
*inputs: sint8_t * data to send points to array of MAX_CHARS defined in .h file , uint8_t Slave number in connection
*void return
*/
void SPI_Master_SendString(sint8_t *str,uint8_t SlaveID);
/*
*Function to initialize device as SLAVE SPI
*Inputs:None
*void return
*/
void SPI_Slave_Init();
/*
*Function to receive byte from master
input:none
*return: received byte
*/
uint8_t SPI_Slave_ReceiveByte();
/*
*Function to receive string from master
*i/o: sint8_t * data to send points to array of MAX_CHARS defined in .h file
*void return
*/
void SPI_Slave_RecieveString(sint8_t *str);

#endif /* SPI_H_ */