/*
 * keyboard.c
 *
 *  Created on: Jun 27, 2025
 *      Author: Administrator
 */
#include "keyboard.h"

// KeyBoard
GPIO_Handle_t Key_Pin_R;
GPIO_Handle_t Key_Pin_C;
USART_Handle_t usart;
GPIO_Handle_t LED;

char KeyMap[4][4]= {
	{'1', '2', '3', 'A'},
	{'4', '5', '6', 'B'},
	{'7', '8', '9', 'C'},
	{'*', '0', '#', 'D'},
};

void Key_Config_Pin(){
	GPIOD_PCLK_EN;
	Key_Pin_R.pGPIOx = GPIOD;
	Key_Pin_R.GPIO_Pin_Config.GPIO_PinNumber = \
	PIN_NUM_0 | PIN_NUM_1 | PIN_NUM_2 | PIN_NUM_3;
	Key_Pin_R.GPIO_Pin_Config.GPIO_PinMode = GPIO_MODER_OUTPUT;
	Key_Pin_R.GPIO_Pin_Config.GPIO_PinPuPdControl = GPIO_PUPDR_PU;
	GPIO_Init(&Key_Pin_R);

	Key_Pin_C.pGPIOx = GPIOD;
	Key_Pin_C.GPIO_Pin_Config.GPIO_PinNumber = \
	PIN_NUM_4 | PIN_NUM_5 | PIN_NUM_6 | PIN_NUM_7;
	Key_Pin_C.GPIO_Pin_Config.GPIO_PinMode = GPIO_MODER_INPUT;
	Key_Pin_C.GPIO_Pin_Config.GPIO_PinPuPdControl = GPIO_PUPDR_PU;

	GPIO_Init(&Key_Pin_C);

	Interrupt_Config();
}

char ReadKey(){
	//	Read col for R1
	GPIO_WriteToOutPutPin(Key_Pin_R.pGPIOx, R1, Low);
	GPIO_WriteToOutPutPin(Key_Pin_R.pGPIOx, R2, High);
	GPIO_WriteToOutPutPin(Key_Pin_R.pGPIOx, R3, High);
	GPIO_WriteToOutPutPin(Key_Pin_R.pGPIOx, R4, High);

	for (int8_t i = 0; i < KeyCol; i++){
		if(!GPIO_ReadFromInputPin(Key_Pin_C.pGPIOx, (C1 + i))){
			Reset_Row();
			GPIO_WriteToOutputPort(LED.pGPIOx, i<<12);
			return KeyMap[R1][i];
		}
	}

	//	Read col for R2
	GPIO_WriteToOutPutPin(Key_Pin_R.pGPIOx, R1, High);
	GPIO_WriteToOutPutPin(Key_Pin_R.pGPIOx, R2, Low);
	GPIO_WriteToOutPutPin(Key_Pin_R.pGPIOx, R3, High);
	GPIO_WriteToOutPutPin(Key_Pin_R.pGPIOx, R4, High);

	for (int8_t i = 0; i < KeyCol; i++){
		if(!GPIO_ReadFromInputPin(Key_Pin_C.pGPIOx, (C1 + i))){
			Reset_Row();
			GPIO_WriteToOutputPort(LED.pGPIOx, (4 + i)<<12);
			return KeyMap[R2][i];
		}
	}

 	//	Read col for R3
	GPIO_WriteToOutPutPin(Key_Pin_R.pGPIOx, R1, High);
	GPIO_WriteToOutPutPin(Key_Pin_R.pGPIOx, R2, High);
	GPIO_WriteToOutPutPin(Key_Pin_R.pGPIOx, R3, Low);
	GPIO_WriteToOutPutPin(Key_Pin_R.pGPIOx, R4, High);

	for (int8_t i = 0; i < KeyCol; i++){
		if(!GPIO_ReadFromInputPin(Key_Pin_C.pGPIOx, (C1 + i))){
			Reset_Row();
			GPIO_WriteToOutputPort(LED.pGPIOx, (8 + i)<<12);
			return KeyMap[R3][i];
		}
	}

	//	Read col for R4
	GPIO_WriteToOutPutPin(Key_Pin_R.pGPIOx, R1, High);
	GPIO_WriteToOutPutPin(Key_Pin_R.pGPIOx, R2, High);
	GPIO_WriteToOutPutPin(Key_Pin_R.pGPIOx, R3, High);
	GPIO_WriteToOutPutPin(Key_Pin_R.pGPIOx, R4, Low);

	for (int8_t i = 0; i < KeyCol; i++){
		if(!GPIO_ReadFromInputPin(Key_Pin_C.pGPIOx, (C1 + i))){
			Reset_Row();
			GPIO_WriteToOutputPort(LED.pGPIOx, (12 + i)<<12);
			return KeyMap[R4][i];
		}
	}
	Reset_Row();
	return 0;
}

// Interrput
void Interrupt_Config(){
	GPIOE_PCLK_EN;
	LED.pGPIOx = GPIOE;
	LED.GPIO_Pin_Config.GPIO_PinNumber = PIN_NUM_12 | PIN_NUM_13 | PIN_NUM_14 | PIN_NUM_15;
	LED.GPIO_Pin_Config.GPIO_PinMode = GPIO_MODER_OUTPUT;
	GPIO_Init(&LED);
	// Enable SYSCFG
	// Config EXTIx PDxPin (x = 4->7)
	for(int i = 0; i < 4; i++){
		SYSCFG->EXTICR2 |= PDxPin << (4*i);
	}
	// Set Interrupt not mask in line 4->7
	EXTI->IMR |= 0xF0;
	// Falling trigger in line 4->7
	EXTI->FTSR |= 0xF0;

	// Set Priority
	NVIC_SetPriority(EXTI4_IRQn, 0);
	NVIC_SetPriority(EXTI9_5_IRQn, 0);

	// Enable Interrupt
	NVIC_EnableIRQ(EXTI4_IRQn);
	NVIC_EnableIRQ(EXTI9_5_IRQn);
}


void EXTI4_IRQHandler(){
	if (EXTI->PR & (1<<4)){
		EXTI->PR |= (1<<4); // clear pending
		ReadKey();
	}
}

void EXTI9_5_IRQHandler(){
	if (EXTI->PR & (1<<5)){
		EXTI->PR |= (1<<5); // clear pending
		ReadKey();
	}
	else if (EXTI->PR & (1<<6)){
		EXTI->PR |= (1<<6); // clear pending
		ReadKey();
	}
	else if (EXTI->PR & (1<<7)){
		EXTI->PR |= (1<<7); // clear pending
		ReadKey();
	}
	else{
		EXTI->PR |= (3<<8); // clear pending bit 8 and 9
	}
}
