/*
 * 74HC595.c
 *
 *  Created on: Jun 5, 2025
 *      Author: Administrator
 */

#include "../../Drivers/74HC/74HC595.h"

/*****************************************************
 *	PE0->SH_CP
 *	PE1->DS
 *	PE2-ST_CP
 *****************************************************/

static IC_74HC_t ic_74hc = {
    .Pin = {
        [SH_CP] = {
            .pGPIOx = GPIOE,
			.GPIO_Pin_Config = {
				.GPIO_PinNumber = SH_CP,
				.GPIO_PinMode = GPIO_MODER_OUTPUT,
				.GPIO_PinOPType = GPIO_OTYPER_PP,
				.GPIO_PinSpeed = GPIO_OSPEEDR_HIGH,
				.GPIO_PinPuPdControl = GPIO_PUPDR_PU,
			},
        },
        [DS] = {
            .pGPIOx = GPIOE,
			.GPIO_Pin_Config = {
				.GPIO_PinNumber = DS,
				.GPIO_PinMode = GPIO_MODER_OUTPUT,
				.GPIO_PinOPType = GPIO_OTYPER_PP,
				.GPIO_PinSpeed = GPIO_OSPEEDR_HIGH,
				.GPIO_PinPuPdControl = GPIO_PUPDR_PU,
			},
        },
        [ST_CP] = {
            .pGPIOx = GPIOE,
			.GPIO_Pin_Config = {
				.GPIO_PinNumber = ST_CP,
				.GPIO_PinMode = GPIO_MODER_OUTPUT,
				.GPIO_PinOPType = GPIO_OTYPER_PP,
				.GPIO_PinSpeed = GPIO_OSPEEDR_HIGH,
				.GPIO_PinPuPdControl = GPIO_PUPDR_PU,
			},
        },
    },
};

void Clk_En(void){
	GPIO_WriteToOutPutPin(ic_74hc.Pin[SH_CP].pGPIOx, SH_CP, High);
	delay_ms(1);
	GPIO_WriteToOutPutPin(ic_74hc.Pin[SH_CP].pGPIOx, SH_CP, Low);
	delay_ms(1);
}

void Write_data(uint32_t data, uint8_t MSBorLSB){
	if (MSBorLSB == LSB){
		for(int i = (TOTAL_IO - 1); i >= 0; i--){
			if((data >> i) & 0x01){
				GPIO_WriteToOutPutPin(ic_74hc.Pin[DS].pGPIOx, DS, High);
			}else{
				GPIO_WriteToOutPutPin(ic_74hc.Pin[DS].pGPIOx, DS, Low);
			}
			Clk_En();
		}
		Latch_En();
	}
	else if (MSBorLSB == MSB){
		for(int i = 0; i < TOTAL_IO; i++){
			if((data >> i) & 0x01){
				GPIO_WriteToOutPutPin(ic_74hc.Pin[DS].pGPIOx, DS, High);
			}else{
				GPIO_WriteToOutPutPin(ic_74hc.Pin[DS].pGPIOx, DS, Low);
			}
			Clk_En();
		}
		Latch_En();
	}
}

void Latch_En(){
	GPIO_WriteToOutPutPin(ic_74hc.Pin[ST_CP].pGPIOx, ST_CP, High);
	delay_ms(5);
	GPIO_WriteToOutPutPin(ic_74hc.Pin[ST_CP].pGPIOx, ST_CP, Low);
	delay_ms(5);
}

void init_74HC595(void){
	GPIOE_PCLK_EN;
	for (int i = 0; i < total_pin; i++){
		GPIO_Init_Pin(&ic_74hc.Pin[i]);
	}
}
