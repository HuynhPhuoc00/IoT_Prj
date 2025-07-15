/*
 * SPI.c
 *
 *  Created on: May 2, 2025
 *      Author: Administrator
 */
#include "SPI.h"
static void Config_GPIO_SPI();
static uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName);
static void Config_GPIO_SPI(){
	GPIOA_PCLK_EN;

	GPIO_Handle_t PA5;	// CLK
	PA5.pGPIOx = GPIOA;
	PA5.GPIO_Pin_Config_t.GPIO_PinNumber = GPIO_PIN_NUM_5;
	PA5.GPIO_Pin_Config_t.GPIO_PinMode = GPIO_MODER_ALTFM;
	PA5.GPIO_Pin_Config_t.GPIO_PinSpeed = GPIO_OSPEEDR_HIGH;
	PA5.GPIO_Pin_Config_t.GPIO_PinAltFunMode_High = GPIO_AFRL_AF5;
	GPIO_Init(&PA5);

	GPIO_Handle_t PA6;	// MISO
	PA6.pGPIOx = GPIOA;
	PA6.GPIO_Pin_Config_t.GPIO_PinNumber = GPIO_PIN_NUM_6;
	PA6.GPIO_Pin_Config_t.GPIO_PinMode = GPIO_MODER_ALTFM;
	PA6.GPIO_Pin_Config_t.GPIO_PinSpeed = GPIO_OSPEEDR_HIGH;
	PA6.GPIO_Pin_Config_t.GPIO_PinAltFunMode_High = GPIO_AFRL_AF5;
	GPIO_Init(&PA6);

	GPIO_Handle_t PA7;	// MOSI
	PA7.pGPIOx = GPIOA;
	PA7.GPIO_Pin_Config_t.GPIO_PinNumber = GPIO_PIN_NUM_7;
	PA7.GPIO_Pin_Config_t.GPIO_PinMode = GPIO_MODER_OUTPUT;
	PA7.GPIO_Pin_Config_t.GPIO_PinSpeed = GPIO_OSPEEDR_HIGH;
	PA7.GPIO_Pin_Config_t.GPIO_PinAltFunMode_High = GPIO_AFRL_AF5;
	GPIO_Init(&PA7);

	GPIO_Handle_t PA9;	// Slave select
	PA9.pGPIOx = GPIOA;
	PA9.GPIO_Pin_Config_t.GPIO_PinNumber = GPIO_PIN_NUM_9;
	PA9.GPIO_Pin_Config_t.GPIO_PinMode = GPIO_MODER_OUTPUT;
	PA9.GPIO_Pin_Config_t.GPIO_PinSpeed = GPIO_OSPEEDR_HIGH;
	GPIO_Init(&PA9);
}

uint8_t GetBaudRate(SPI_RegDef_t *pSPIx, uint8_t Max_CLK){
	uint32_t pclk2 = RCC_GetPCLK2Value();
	uint16_t DIV[8] = {2,4,8,16,32,64,128,256};
	for (int i = 7; i >= 0 ; i--){
		if ((pclk2 / DIV[i]) <= Max_CLK){
			return i;
		}
	}
}

void SPI_Init(SPI_Handle_t *pSPI_Handle){
	// Config GPIO
	Config_GPIO_SPI();

	// Enable SPI
	SPI1_PLCK_EN;

	// Reset CR1
	pSPI_Handle->pSPIx->CR1 = 0x0;
	// Master / full-duplex mode (BIDIMODE=0 and RXONLY=0)
	pSPI_Handle->pSPIx->CR1 |= (1<<0) | (1<<1);	// CPHA = 1, CPOL = 1;

	// Master mode
	pSPI_Handle->pSPIx->CR1 |= (1<<2);

	// Set Baud Rate
	pSPI_Handle->pSPIx->CR1 |= (GetBaudRate(pSPI_Handle->pSPIx, pSPI_Handle->SPI_Congif_t.MaxCLK)) << 3;

	// Software slave management enable
	pSPI_Handle->pSPIx->CR1 |= (1<<9);
}

void SPI_Transmit (SPI_RegDef_t *pSPIx, uint8_t *data){
	while(*data){
		while(!(SPI_GetFlagStatus(pSPIx, SPI_FLAG_TxE)));
		pSPIx->DR = *data++;
	}
	while(!(SPI_GetFlagStatus(pSPIx, SPI_FLAG_BSY)));
}

void SPI_Receive (SPI_RegDef_t *pSPIx, uint8_t *data, int size){
	while(size){
		while(!(SPI_GetFlagStatus(pSPIx, SPI_FLAG_BSY)));
		pSPIx->DR = 0;  // send dummy data
		while(!(SPI_GetFlagStatus(pSPIx, SPI_FLAG_RxNE)));
		*data++ = pSPIx->DR;
		size--;
	}
}


static uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName){
    if(pSPIx->SR & FlagName){
        return Flag_Set;
    }
    return Flag_Reset;
}
