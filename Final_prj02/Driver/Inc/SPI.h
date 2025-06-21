#ifndef INC_STM32F411_SPI_H_
#define INC_STM32F411_SPI_H_


#include"stm32f411.h"

#define SPI1_BASE_ADDR           0x400133FFU
#define SPI2_BASE_ADDR           0x40003BFFU
#define SPI3_BASE_ADDR           0x40003FFFU

// SPI Struct
typedef struct{
	uint8_t MaxCLK;
}SPI_Congif_t;


typedef struct{
    vo uint32_t CR1;
    vo uint32_t _Reserved_1;
    vo uint32_t SR;
    vo uint32_t DR;
    vo uint32_t CRCPR;
    vo uint32_t RXCRCR;
    vo uint32_t TXCRCR;
    vo uint32_t I2SCFGR;
    vo uint32_t I2SPR;
}SPI_RegDef_t;

typedef struct{
	SPI_RegDef_t *pSPIx;
	SPI_Congif_t SPI_Congif;
}SPI_Handle_t;

#define SPI1        ((SPI_RegDef_t*)SPI1_BASE_ADDR)
#define SPI2        ((SPI_RegDef_t*)SPI2_BASE_ADDR)
#define SPI3        ((SPI_RegDef_t*)SPI3_BASE_ADDR)

// Clock En APB2
#define SPI1_PLCK_EN        (RCC->APB2ENR |= (1<<12))
#define SPI2_PLCK_EN        (RCC->APB1ENR |= (1<<14))
#define SPI3_PLCK_EN        (RCC->APB1ENR |= (1<<15))

#define SPI1_PLCK_DIS       (RCC->APB2ENR &= ~(1<<12))
#define SPI2_PLCK_DIS       (RCC->APB1ENR &= ~(1<<14))
#define SPI3_PLCK_DIS       (RCC->APB1ENR &= ~(1<<15))

// SPI Status register
#define SPI_SR1_RXNE	0
#define SPI_SR1_TXE		1
#define SPI_SR1_BSY		7

// Define flag
#define SPI_FLAG_RxNE       (1 << SPI_SR1_RXNE)
#define SPI_FLAG_TxE        (1 << SPI_SR1_TXE)
#define SPI_FLAG_BSY        (1 << SPI_SR1_BSY)


void SPI_Init(SPI_Handle_t *pSPI_Handle);
void SPI_Transmit (SPI_RegDef_t *pSPIx, uint8_t *data);
void SPI_Receive (SPI_RegDef_t *pSPIx, uint8_t *data, int size);

uint8_t GetBaudRate(SPI_RegDef_t *pSPIx, uint8_t Max_CLK);

#endif  //INC_STM32F411_SPI_H_
