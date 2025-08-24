/*
 * 74HC595.h
 *
 *  Created on: Jun 5, 2025
 *      Author: Administrator
 */

#ifndef INC_74HC595_H_
#define INC_74HC595_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "../STM32/stm32f411.h"
#include "GPIO.h"
#define IO 8
#define NUM_IC 3
#define TOTAL_IO (IO * NUM_IC)

/*****************************************************
 *	PE0->SH_CP
 *	PE1->ST_CP
 *	PE2->DS0
 *	PE3->DS1
 *	PE4->DS2
 *****************************************************/
enum PIN_Num{
	SH_CP = GPIO_PIN_NUM_0,
	DS = GPIO_PIN_NUM_1,
	ST_CP = GPIO_PIN_NUM_2,
	total_pin = 3,
};


typedef struct{
    GPIO_Handle_t Pin[total_pin];
}IC_74HC_t;

void init_74HC595(void);

void Clk_En(void);
void Write_data(uint32_t data, uint8_t MSBorLSB);
void Latch_En(void);

enum MSBorLSB{
	LSB	= 0,
	MSB	= 1,
};

#ifdef __cplusplus
}
#endif
#endif /* INC_74HC595_H_ */
