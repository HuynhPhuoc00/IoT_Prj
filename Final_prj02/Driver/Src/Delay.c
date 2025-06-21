/*
 * Delay.c
 *
 *  Created on: Apr 27, 2025
 *      Author: Administrator
 */

#include "Delay.h"

void TIM5Config (void)
{
	/************** STEPS TO FOLLOW *****************
	1. Enable Timer clock
	2. Set the prescalar and the ARR
	3. Enable the Timer, and wait for the update Flag to set
	************************************************/

// 1. Enable Timer clock
	RCC->APB1ENR |= (1<<3);  // Enable the TIM5 clock

// 2. Set the prescalar and the ARR
	TIM5_PSC = 90-1;  // 90MHz/90 = 1 MHz ~~ 1 uS delay
	TIM5_ARR = 0xffff;  // MAX ARR value

// 3. Enable the Timer, and wait for the u pdate Flag to set
	TIM5_CR1 |= (1<<0); // Enable the Counter
	while (!(TIM5_SR & (1<<0)))
	while (!(TIM5_SR & (1<<0)));  // UIF: Update interrupt flag..  This bit is set by hardware when the registers are updated
}

void Delay_us (uint16_t us)
{
	/************** STEPS TO FOLLOW *****************
	1. RESET the Counter
	2. Wait for the Counter to reach the entered value. As each count will take 1 us,
		 the total waiting time will be the required us delay
	************************************************/
	TIM5_CNT = 0;
	while (TIM5_CNT < us);
}

void Delay_ms (uint16_t ms)
{
	for (uint16_t i=0; i<ms; i++)
	{
		Delay_us (50); // delay of 1 ms
	}
}


