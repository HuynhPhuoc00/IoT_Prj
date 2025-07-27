/*
 * keyboard.h
 *
 *  Created on: Jun 27, 2025
 *      Author: Administrator
 */

#ifndef SRC_KEYBOARD_H_
#define SRC_KEYBOARD_H_

#ifdef __cplusplus
extern "C" {
#endif

// KeyBoard
#include "stm32f411.h"

extern GPIO_Handle_t Key_Pin;

/*
 * Key 0 	= R1 C1
 * Key 1 	= R1 C2
 * Key 2 	= R1 C3
 * Key 3 	= R1 C4
 * Key 4 	= R2 C1
 * Key 5 	= R2 C2
 * Key 6 	= R2 C3
 * Key 7 	= R2 C4
 * Key 8 	= R3 C1
 * Key 9 	= R3 C2
 * Key 10 	= R3 C3
 * Key 11 	= R3 C4
 * Key 12 	= R4 C1
 * Key 13 	= R4 C2
 * Key 14 	= R4 C3
 * Key 15 	= R4 C4
 * */

#define KeyRow 4
#define KeyCol 4

typedef enum{
	R1 = 0,
	R2 = 1,
	R3 = 2,
	R4 = 3,
	C1 = 4,
	C2 = 5,
	C3 = 6,
	C4 = 7,
}KeyIO;

void Key_Config_Pin();
char ReadKey();
#define Reset_Row()\
		do{\
			GPIO_WriteToOutPutPin(Key_Pin_R.pGPIOx, R1, Low);\
			GPIO_WriteToOutPutPin(Key_Pin_R.pGPIOx, R2, Low);\
			GPIO_WriteToOutPutPin(Key_Pin_R.pGPIOx, R3, Low);\
			GPIO_WriteToOutPutPin(Key_Pin_R.pGPIOx, R4, Low);\
		}while (0)


// Interrupt
#define PDxPin 	0x3

#define SYSCFG_BASEADDR		0x40013800u
#define EXTI_BASEADDR		0x40013C00u

typedef struct{
	vo uint32_t MEMRMP;
	vo uint32_t PMC;
	vo uint32_t EXTICR1;
	vo uint32_t EXTICR2;
	vo uint32_t EXTICR3;
	vo uint32_t EXTICR4;
	vo uint32_t RESERVED[2];
	vo uint32_t CMPCR;
}Syscfg_Reg_Def_t;

#define SYSCFG ((Syscfg_Reg_Def_t *)SYSCFG_BASEADDR)

typedef struct{
	vo uint32_t IMR;
	vo uint32_t EMR;
	vo uint32_t RTSR;
	vo uint32_t FTSR;
	vo uint32_t SWIER;
	vo uint32_t PR;
}Exti_Reg_Def_t;

#define EXTI ((Exti_Reg_Def_t *)EXTI_BASEADDR)

void Interrupt_Config();
void EXTI0_IRQHandler();
void EXTI1_IRQHandler();
void EXTI2_IRQHandler();
void EXTI3_IRQHandler();
void EXTI4_IRQHandler();
void EXTI9_5_IRQHandler();

#ifdef __cplusplus
}
#endif

#endif /* SRC_KEYBOARD_H_ */
