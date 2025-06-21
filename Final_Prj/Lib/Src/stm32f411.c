/*
 * stm32f411.c
 *
 *  Created on: May 2, 2025
 *      Author: Administrator
 */

#include "stm32f411.h"

uint16_t AHB_Prescaler[8] = {2,4,8,16,64,128,256,512};
uint8_t APB1_Prescaler[4] = {2,4,8,16};
uint8_t APB2_Prescaler[4] = {2,4,8,16};

uint32_t Get_Output_CLK(){
    return;
}
uint32_t RCC_GetPCLK1Value(void){
    uint32_t pclk1, SystemClk;
    uint8_t clksrc, temp, ahbp, apb1;
    clksrc = (RCC->CFGR >> 2) & 0x3;
    if(clksrc == 0){
        SystemClk = 16000000; // HSI = 16MHz
    }
    else if(clksrc == 1){
        SystemClk = 8000000; // HSE optional
    }
    else if(clksrc == 2){
        SystemClk = Get_Output_CLK();
    }

    // AHB
    temp = (RCC->CFGR >> 4) & 0xFF;
    if(temp < 8){
        ahbp = 1;
    }
    else {
        ahbp = AHB_Prescaler[temp - 8];
    }

    // APB1
    temp = (RCC->CFGR >> 10) & 0xFF;
    if(temp < 4){
        apb1 = 1;
    }
    else {
    	apb1 = APB1_Prescaler[temp - 4];
    }

    pclk1 = (SystemClk/ahbp) / apb1;
    return pclk1;
}

uint32_t RCC_GetPCLK2Value(void){
    uint32_t pclk2, SystemClk;
    uint8_t clksrc, temp, ahbp, apb2;
    clksrc = (RCC->CFGR >> 2) & 0x3;
    if(clksrc == 0){
        SystemClk = 16000000; // HSI = 16MHz
    }
    else if(clksrc == 1){
        SystemClk = 8000000; // HSE optional
    }
    else if(clksrc == 2){
        SystemClk = Get_Output_CLK();
    }

    // AHB
    temp = (RCC->CFGR >> 4) & 0xFF;
    if(temp < 8){
        ahbp = 1;
    }
    else {
        ahbp = AHB_Prescaler[temp - 8];
    }

    // APB1
    temp = (RCC->CFGR >> 13) & 0xFF;
    if(temp < 4){
        apb2 = 1;
    }
    else {
    	apb2 = APB2_Prescaler[temp - 4];
    }

    pclk2 = (SystemClk/ahbp) / apb2;
    return pclk2;
}
