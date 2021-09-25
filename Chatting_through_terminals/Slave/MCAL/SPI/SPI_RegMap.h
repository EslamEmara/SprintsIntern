/*
 * SPI_RegMap.h
 *
 * Created: 9/24/2021 11:16:04 PM
 *  Author: 20109
 */ 


#ifndef SPI_REGMAP_H_
#define SPI_REGMAP_H_
#include "BIT_MATH.h"

#define reg(n)				(*((volatile uint8_t*)(n)))

#define SPI_CONTROL					reg(0x2D)
#define SPI_STATUS					reg(0x2E)
#define SPI_DATA_REG				reg(0x2F)

#define SPI_PORTB						reg(0x38)
#define SPI_PORTB_DIR					reg(0x37)


#define SPI_ENABLE					SETBIT(SPI_CONTROL,6)
#define MASTER_ENABLE				SETBIT(SPI_CONTROL,4)
#define SLAVE_ENABLE				CLRBIT(SPI_CONTROL,4)

#define	SPR_0						(SPI_CONTROL,0)
#define	SPR_1						(SPI_CONTROL,1)
#define SPI_2X						(SPI_STATUS,0)




#define MOSI						(5)
#define MISO						(6)
#define SCK							(7)
#define SS							(4)

#define SPI_FLAG							(SPI_STATUS,7)


#endif /* SPI_REGMAP_H_ */