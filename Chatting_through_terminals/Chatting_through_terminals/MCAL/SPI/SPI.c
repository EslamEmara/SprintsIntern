/*
 * SPI.c
 *
 * Created: 9/24/2021 11:15:31 PM
 *  Author: 20109
 */ 

#include "SPI.h"
/*
*Function to adjust frequency of spi according to initializer
*static function
*/
static void Adjust_Freq(EN_OSC_t oscillator){
	if ((oscillator>>0) & 1){					/*set first bit of oscillator in SPR0*/
		SETBIT(SPI_CONTROL,SPR_0);
	}
	else{
		CLRBIT(SPI_CONTROL,SPR_0);
	}
	if ((oscillator>>1) & 1){				/*second bit in SPI1*/
		SETBIT(SPI_CONTROL,SPR_1);
	}
	else{
		CLRBIT(SPI_CONTROL,SPR_1);
	}
	if ((oscillator>>2) & 1){				/*third bit in SPI2X*/
		SETBIT(SPI_STATUS,SPI_2X);
	}
	else{
		CLRBIT(SPI_STATUS,SPI_2X);
	}
	
}
/*
*Function to initalize Master Spi with desired frequency
*Inputs: EN_OSC_t with divisior oscillator (see spi.h for definition)
*void return
*
*
*/
void SPI_Master_Init(EN_OSC_t oscillator)					/* SPI Initialize function */
{
	SETBIT(SPI_PORTB_DIR,MOSI);
	SETBIT(SPI_PORTB_DIR,SCK);
	SETBIT(SPI_PORTB_DIR,SS);
	CLRBIT(SPI_PORTB_DIR,MISO);
	
	SETBIT(SPI_PORTB,SS);
	Adjust_Freq(oscillator);
	SPI_ENABLE;
	MASTER_ENABLE;
}
/*
*Function to send byte to selected slave according to daisy chain connection 
*inputs: uint8_t data to send , uint8_t Slave number in connection 
*void return
*/
void SPI_Master_SendByte(uint8_t data,uint8_t SlaveID)		/* SPI write data function */
{
	uint8_t no_of_slaves = 0;
	uint8_t read_data_reg;

	for ( no_of_slaves = 0 ; no_of_slaves<=SlaveID ; no_of_slaves++)
	{
		CLRBIT(SPI_PORTB,SS);
		SPI_DATA_REG = data;					
		while(!(SPI_STATUS & (1<<SPI_FLAG)));	
		read_data_reg = SPI_DATA_REG;			/* read the data register to flush it */
		SETBIT(SPI_PORTB,SS);
	}

}
/*
*Function to receive byte from selected slave according to daisy chain connection
*inputs: uint8_t Slave number in connection
*return : uint8_t data received
*/
uint8_t SPI_Master_RecieveByte(uint8_t SlaveID)
{
	uint8_t no_of_slaves = 0;
	uint8_t read_data = 0;
	for ( no_of_slaves = 0 ; no_of_slaves<=SlaveID ; no_of_slaves++)
	{
		SPI_DATA_REG = 0xFF;
		while(!GETBIT(SPI_STATUS,SPI_FLAG));
		read_data = SPI_DATA_REG;
	}
	
	return(read_data);

}
/*
*Function to send string to selected slave according to daisy chain connection
*inputs: sint8_t * data to send points to array of MAX_CHARS defined in .h file , uint8_t Slave number in connection
*void return
*/
void SPI_Master_SendString(sint8_t *str,uint8_t SlaveID)
{
	uint8_t character=0;
	
	for (character=0; str[character]!='\0';character++){
		SPI_Master_SendByte(str[character],SlaveID);
	}
}
/*
*Function to receive string to selected slave according to daisy chain connection
*i/o: sint8_t * data to send points to array of MAX_CHARS defined in .h file
input: uint8_t Slave number in connection
*void return
*/
void SPI_Master_RecieveString(sint8_t *str,uint8_t SlaveID)
{
	uint8_t character = 0;
	
	for (character = 0 ;character<SPI_MAX_STRING_SIZE;character++){
		str[character] = SPI_Master_RecieveByte(SlaveID);
		
		if(str[character]==SPI_END_OF_STRING){
			str[character] = '\0';
			break;
		}
	}
}
/*
*Function to initialize SLAVE SPI 
*Inputs:None
*void return
*/
void SPI_Slave_Init()
{
	CLRBIT(SPI_PORTB_DIR,MOSI);
	CLRBIT(SPI_PORTB_DIR,SCK);
	CLRBIT(SPI_PORTB_DIR,SS);
	SETBIT(SPI_PORTB_DIR,MISO);
	
	SPI_ENABLE;
	SLAVE_ENABLE;
}
/*
*Function to receive byte from master
input:none
*return: received byte
*/
uint8_t SPI_Slave_ReceiveByte()
{
	while(!GETBIT(SPI_STATUS,SPI_FLAG));
	return(SPI_DATA_REG);
}
/*
*Function to receive string from master
*i/o: sint8_t * data to send points to array of MAX_CHARS defined in .h file
*void return
*/
void SPI_Slave_RecieveString(sint8_t *str)
{
	uint8_t i = 0;
	
	for (i = 0 ;i<SPI_MAX_STRING_SIZE;i++){
		str[i] = SPI_Slave_ReceiveByte();
		
		if(str[i]==SPI_END_OF_STRING){
			str[i] = '\0';
			break;
		}
	}
}