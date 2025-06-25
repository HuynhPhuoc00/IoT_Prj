/*
 * stm32f411.h
 *
 *  Created on: Jul 6, 2023
 *      Author: HuynhPhuoc
 */


#ifndef INC_STM32F411_H_
#define INC_STM32F411_H_

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "stm32f4xx_hal.h"
// Base address of Sram and Flash
#define FLASH_BASE_ADDR                  0x08000000U
#define SRAM1_BASE_ADDR                  0x20000000U
#define ROM_BASE_ADDR                    0x1FFF0000U
#define SRAM                             SRAM1_BASEADDR

// Base address of bus
#define APB1_BASE_ADDR                   0x40000000U
#define APB2_BASE_ADDR                   0x40010000U
#define AHB1_BASE_ADDR                   0x40020000U
#define AHB2_BASE_ADDR				     0x50000000U

// GPIO base address
#define GPIOA_BASE_ADDR                  0x40020000U
#define GPIOB_BASE_ADDR                  0x40020400U
#define GPIOC_BASE_ADDR                  0x40020800U
#define GPIOD_BASE_ADDR                  0x40020C00U
#define GPIOE_BASE_ADDR                  0x40021000U


#define vo volatile

// GPIO Register
typedef struct
{
    vo uint32_t MODER  ;
    vo uint32_t OTYPER ;
    vo uint32_t OSPEEDR;
    vo uint32_t PUPDR  ;
    vo uint32_t IDR    ;
    vo uint32_t ODR    ;
    vo uint32_t BSRR   ;
    vo uint32_t LCKR   ;
    vo uint32_t AFRL   ;
    vo uint32_t AFRH   ;
}GPIO_RegDef_t;

// Peripheral definition
#define GPIOA   ((GPIO_RegDef_t*)GPIOA_BASE_ADDR)
#define GPIOB   ((GPIO_RegDef_t*)GPIOB_BASE_ADDR)
#define GPIOC   ((GPIO_RegDef_t*)GPIOC_BASE_ADDR)
#define GPIOD   ((GPIO_RegDef_t*)GPIOD_BASE_ADDR)
#define GPIOD   ((GPIO_RegDef_t*)GPIOD_BASE_ADDR)
#define GPIOE   ((GPIO_RegDef_t*)GPIOE_BASE_ADDR)
// RCC Register struct
typedef struct
{
    vo uint32_t CR;
    vo uint32_t PLLCFGR;
    vo uint32_t CFGR;
    vo uint32_t CIR;
    vo uint32_t AHB1RSTR;
    vo uint32_t AHB2RSTR;
    uint32_t    RESERVED1[2];
    vo uint32_t APB1RSTR;
    vo uint32_t APB2RSTR;
    uint32_t    RESERVED2[2];
    vo uint32_t AHB1ENR;
    vo uint32_t AHB2ENR;
    uint32_t    RESERVED3[2];
    vo uint32_t APB1ENR;
    vo uint32_t APB2ENR;
    uint32_t    RESERVED4[2];
    vo uint32_t AHB1LPENR;
    vo uint32_t AHB2LPENR;
    uint32_t    RESERVED5[2];
    vo uint32_t APB1LPENR;
    vo uint32_t APB2LPENR;
    uint32_t    RESERVED6[2];
    vo uint32_t BDCR;
    vo uint32_t CSR;
    uint32_t    RESERVED7[2];
    vo uint32_t SSCGR;
    vo uint32_t PLLI2SCFGR;
    uint32_t    RESERVED8;
    vo uint32_t DCKCFGR;
}RCC_RegDef_t;


// RCC base address
#define RCC_BASE_ADDR                    0x40023800U

#define RCC ((RCC_RegDef_t*)RCC_BASE_ADDR)

// GPIO peripheral clock enable register
#define GPIOA_PCLK_EN           (RCC->AHB1ENR |= (1<<0))
#define GPIOB_PCLK_EN           (RCC->AHB1ENR |= (1<<1))
#define GPIOC_PCLK_EN           (RCC->AHB1ENR |= (1<<2))
#define GPIOD_PCLK_EN           (RCC->AHB1ENR |= (1<<3))
#define GPIOE_PCLK_EN           (RCC->AHB1ENR |= (1<<4))

// GPIO peripheral clock disable register
#define GPIOA_PCLK_DIS          (RCC->AHB1ENR &= ~(1<<0))
#define GPIOB_PCLK_DIS          (RCC->AHB1ENR &= ~(1<<1))
#define GPIOC_PCLK_DIS          (RCC->AHB1ENR &= ~(1<<2))
#define GPIOD_PCLK_DIS          (RCC->AHB1ENR &= ~(1<<3))
#define GPIOE_PCLK_DIS          (RCC->AHB1ENR &= ~(1<<4))

//Marco reset GPIOx peripheral
#define GPIOA_REG_RST()         do{RCC->AHB1RSTR |= (1<<0);RCC->AHB1RSTR &= ~(1<<0);} while(0)
#define GPIOB_REG_RST()         do{RCC->AHB1RSTR |= (1<<1);RCC->AHB1RSTR &= ~(1<<1);} while(0)
#define GPIOC_REG_RST()         do{RCC->AHB1RSTR |= (1<<2);RCC->AHB1RSTR &= ~(1<<2);} while(0)
#define GPIOD_REG_RST()         do{RCC->AHB1RSTR |= (1<<3);RCC->AHB1RSTR &= ~(1<<3);} while(0)
#define GPIOE_REG_RST()         do{RCC->AHB1RSTR |= (1<<4);RCC->AHB1RSTR &= ~(1<<4);} while(0)

//Some generic marco
#define Enable 				1
#define Disable 			0
#define High 				1
#define Low		 			0
#define Read				Enable
#define Write				Disable
#define SET					Enable
#define RESET 				Disable
#define GPIO_PIN_SET		SET
#define GPIO_PIN_RESET		RESET
#define Flag_Set   			1
#define Flag_Reset 			0

uint32_t RCC_GetPCLK1Value(void);
uint32_t RCC_GetPCLK2Value(void);
uint32_t Get_Output_CLK();

#include "GPIO.h"
//#include "I2C.h"
//#include "USART.h"
//#include "SPI.h"

#endif /* INC_STM32F411_H_ */
