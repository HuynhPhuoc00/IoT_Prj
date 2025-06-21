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

#include "stm32f411.h"

/*****************************************************
 *	PE0->SH_CP
 *	PE1->ST_CP
 *	PE2->DS0
 *	PE3->DS1
 *	PE4->DS2
 *****************************************************/
enum DS_Num{
	DS0 = GPIO_PIN_NUM_2,
	DS1 = GPIO_PIN_NUM_3,
	DS2 = GPIO_PIN_NUM_4,
};

typedef struct{
	uint8_t Num_id;
	GPIO_Handle_t SH_CP;
	GPIO_Handle_t DS;
	GPIO_Handle_t ST_CP;
}Pin_74H595;

extern Pin_74H595 Pin_74H595_0;
extern Pin_74H595 Pin_74H595_1;
extern Pin_74H595 Pin_74H595_2;

Pin_74H595 Set_74HC595(Pin_74H595 *Pin_74H595_t, uint8_t data_num);

void Clk_En(uint8_t data_num);
void Write_data(uint8_t data, uint8_t data_num);
void Latch_En(uint8_t data_num);



void init_74HC595(uint8_t DS_NUM);


#ifdef __cplusplus
}
#endif
#endif /* INC_74HC595_H_ */
