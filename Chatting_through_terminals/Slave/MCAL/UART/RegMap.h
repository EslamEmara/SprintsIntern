/*
 * RegMap.h
 *
 * Created: 9/22/2021 3:44:12 PM
 *  Author: 20109
 */ 


#ifndef REGMAP_H_
#define REGMAP_H_

#define REG(n)				(*((volatile uint8_t*)(n)))


#define UDR			REG(0x2C)	
#define UCSRA		REG(0x2B)
#define UCSRB		REG(0x2A)
#define UBRRL		REG(0x29)

#define UBRRH		REG(0x40)
#define UCSRC		REG(0x40)

#define STATUS_REG			REG(0x5F)



#endif /* REGMAP_H_ */