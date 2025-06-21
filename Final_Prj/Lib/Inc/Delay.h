/*
 * Delay.h
 *
 *  Created on: Apr 27, 2025
 *      Author: Administrator
 */

#ifndef INC_DELAY_H_
#define INC_DELAY_H_

#include "stm32f411.h"

void TIM5Config (void);

void Delay_us (uint16_t us);

void Delay_ms (uint16_t ms);

#define TIM5_BASE 	0x40000C00U

#define CR1_off		0x00U
#define SR_off		0x10U
#define CNT_off		0x24U
#define PSC_off		0x28U
#define ARR_off		0x2CU


#define TIM5_CR1 (*(vo uint32_t *)(TIM5_BASE+ CR1_off))
#define TIM5_SR	 (*(vo uint32_t *)(TIM5_BASE+ SR_off))
#define TIM5_CNT (*(vo uint32_t *)(TIM5_BASE+ CNT_off))
#define TIM5_PSC (*(vo uint32_t *)(TIM5_BASE+ PSC_off))
#define TIM5_ARR (*(vo uint32_t *)(TIM5_BASE+ ARR_off))

#endif /* INC_DELAY_H_ */
