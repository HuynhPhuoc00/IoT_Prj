/*
 * stm32f411_I2C.c
 *
 *  Created on: Jul 6, 2023
 *      Author: HuynhPhuoc
 */

#include "stm32f411.h"
#include "I2C_u.h"

/*
    SCL
    T-high = CCR*Tpclk1 
    T-low = CCR*Tpclk1 

    pclk1 = (SystemClk/ahbp) / apb1;
*/

I2C_Error_t i2c_error;

static void I2C_GenrateStartCondition(I2C_RegDef_t *pI2Cx);
static void I2C_ClearAddrFlag(I2C_RegDef_t *pI2Cx);
static void I2C_GenrateStopCondition(I2C_RegDef_t *pI2Cx);
static void Config_GPIO_I2C();

static void I2C_GenrateStartCondition(I2C_RegDef_t *pI2Cx){
	pI2Cx->CR1 |= (1<<10);
    pI2Cx->CR1 |= (1<<8);
}

static void I2C_ClearAddrFlag(I2C_RegDef_t *pI2Cx){
    uint32_t dummyRead = pI2Cx->SR1;
    dummyRead = pI2Cx->SR2;
    (void)dummyRead;
}

static void I2C_GenrateStopCondition(I2C_RegDef_t *pI2Cx){
    pI2Cx->CR1 |= (1<<9);
}

// Enable GPIO for I2C
static void Config_GPIO_I2C(){
	GPIOB_PCLK_EN;
	// Enable port PB8, PB9
	GPIO_Handle_t SCL_SDA;	// PB8, PB9
	SCL_SDA.pGPIOx = GPIOB;
	SCL_SDA.GPIO_Pin_Config.GPIO_PinNumber = PIN_NUM_8 | PIN_NUM_9;
	SCL_SDA.GPIO_Pin_Config.GPIO_PinMode = GPIO_MODER_ALTFM;
	SCL_SDA.GPIO_Pin_Config.GPIO_PinOPType = GPIO_OTYPER_OD;
	SCL_SDA.GPIO_Pin_Config.GPIO_PinSpeed = GPIO_OSPEEDR_VERYHIGH;
	SCL_SDA.GPIO_Pin_Config.GPIO_PinPuPdControl = GPIO_PUPDR_PU;
	SCL_SDA.GPIO_Pin_Config.GPIO_PinAltFunMode_High = GPIO_AFRH_AF4;
	GPIO_Init(&SCL_SDA);
}


// Peripheral Clock setup
void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t EnOrDis){
    if(EnOrDis){
        if(pI2Cx == I2C1)		I2C1_PLCK_EN;
        else if(pI2Cx == I2C2)  I2C2_PLCK_EN;
        else if(pI2Cx == I2C3)  I2C3_PLCK_EN;
    }
    else{
        if(pI2Cx == I2C1)       I2C1_PLCK_DIS;
        else if(pI2Cx == I2C2)  I2C2_PLCK_DIS;
        else if(pI2Cx == I2C3)  I2C3_PLCK_DIS;
    }
}

// Init and DeInit
void I2C_Init(I2C_Handle_t *pI2CHandle){
#ifdef I2C_Debug
	lcd_init();
#endif
	// Enable clock for I2C
	I2C_PeriClockControl(pI2CHandle->pI2Cx, Enable);
	// Config GPIO

	Config_GPIO_I2C();
	// Software reset
	pI2CHandle->pI2Cx->CR1 |= (1<<15);
	pI2CHandle->pI2Cx->CR1 &= ~(1<<15);


	uint32_t temp;
    // Configure the FREQ of CR2
    temp = 0;
    temp |= RCC_GetPCLK1Value() / 1000000U;
    pI2CHandle->pI2Cx->CR2 = (temp & 0x3F);

    //CCR calculations
    uint16_t ccr_value = 0;
    temp = 0;
    if(pI2CHandle->I2C_Congif.I2C_SCLSpeed <= I2C_SCL_SPEED_SM){	// For normal mode
        // Mode is standard mode
        ccr_value = (RCC_GetPCLK1Value() / (2 * pI2CHandle->I2C_Congif.I2C_SCLSpeed));
        temp |= (ccr_value & 0xFFF);
    }
    else{
        // Mode is fast mode 
        temp |= (1 << 15);
        temp |= (pI2CHandle->I2C_Congif.I2C_FMDutyCyCle << 14);
        if(pI2CHandle->I2C_Congif.I2C_FMDutyCyCle == I2C_FMDUTY_2){
            ccr_value = (RCC_GetPCLK1Value() / (3 * pI2CHandle->I2C_Congif.I2C_SCLSpeed));
        }
        else{
            ccr_value = (RCC_GetPCLK1Value() / (25 * pI2CHandle->I2C_Congif.I2C_SCLSpeed));
        }
        temp |= (ccr_value & 0xFFF);
    }

    pI2CHandle->pI2Cx->CCR |= temp;

    //TRISE calculations
    uint16_t trise_value = 0;
    temp = 0;
    if(pI2CHandle->I2C_Congif.I2C_SCLSpeed <= I2C_SCL_SPEED_SM){	// Mode is standard mode
    	trise_value = (RCC_GetPCLK1Value() / pI2CHandle->I2C_Congif.I2C_SCLSpeed) + 1;
    }
    else{	// Mode is fast mode
//        temp |= (1 << 15);
//        temp |= (pI2CHandle->I2C_Congif_t.I2C_FMDutyCyCle << 14);
//        if(pI2CHandle->I2C_Congif_t.I2C_FMDutyCyCle == I2C_FMDUTY_2){
//            ccr_value = (RCC_GetPCLK1Value() / (3 * pI2CHandle->I2C_Congif_t.I2C_SCLSpeed));
//        }
//        else{
//            ccr_value = (RCC_GetPCLK1Value() / (25 * pI2CHandle->I2C_Congif_t.I2C_SCLSpeed));
//        }
//        temp |= (ccr_value & 0xFFF);
    }

    temp |= (trise_value & 0x7F);
    pI2CHandle->pI2Cx->TRISE = temp;

    // Enable I2C
    pI2CHandle->pI2Cx->CR1 |= (1<<0);
}

uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx,uint32_t FlagName){
    if(pI2Cx->SR1 & FlagName){
        return Flag_Set;
    }
    return Flag_Reset;
}

void I2C_Start(I2C_RegDef_t *pI2Cx){
    // 1. Genarate the Start condition
    I2C_GenrateStartCondition(pI2Cx);
    // 2. Confirm that start generation is completed by checking the SB flag in the SR1
    // Note: Until SB is cleared SCL will be stretched (pulled to LOW)
    while(!(I2C_GetFlagStatus(pI2Cx,I2C_FLAG_SB)));
}

I2C_Error_t I2C_Address(I2C_Handle_t *I2C_Handle, uint16_t addr){
	// 3. Send the addr of the slave with r/w bit set to w(0) (total 8 bit)
	I2C_Handle->pI2Cx->DR = addr << 1;
	// 4. Confirm that addr phase is completed by checking the Addr flas in SR1
	uint32_t TimeOut = I2C_Handle->I2C_Congif.TimeOut;
	while(!(I2C_GetFlagStatus(I2C_Handle->pI2Cx,I2C_FLAG_ADDR))){
		delay_ms(1);
		TimeOut --;
		if (TimeOut == 0){
			i2c_error.errorFlags = I2C_ERR_ADDR;
			return i2c_error;
		}
	}
	// 5. Clear the Addr flag according to its software sequence
	// Note: Until Addr is cleared SCL will be strectched (pulled to LOW)
	I2C_ClearAddrFlag(I2C_Handle->pI2Cx);
}

void I2C_MasterSend_Data(I2C_RegDef_t *pI2Cx, uint8_t data){
    // When Len becomes zero wait for TxE=1 and BTF=1 before generating the STOP condition
    // Note: TxE=1, BTF=1, means that both SR and DR are empty and next tranmission should begin
    // when BTF=1 SCL will be stretched  (pulled to LOW)
	while(!(I2C_GetFlagStatus(pI2Cx,I2C_FLAG_TxE)));
    pI2Cx->DR = data;
    while(!(I2C_GetFlagStatus(pI2Cx,I2C_FLAG_BTF)));

}

I2C_Error_t I2C_MasterSend_Multi_Data(I2C_Handle_t *I2C_Handle, uint16_t addr, uint8_t *pTxbuffer, uint32_t len){
	uint32_t TimeOut_TxE = I2C_Handle->I2C_Congif.TimeOut;
	uint32_t TimeOut_BTF = I2C_Handle->I2C_Congif.TimeOut;

	I2C_Start(I2C_Handle->pI2Cx);
	i2c_error = I2C_Address(I2C_Handle, addr);
	if(i2c_error.errorFlags == I2C_ERR_ADDR){
#ifdef I2C_Debug
		lcd_put_cur(2, 1);
		send_string_lcd("TimeOutADDR");
#endif
		return i2c_error;
	}

	// 6. Send the data until Len becomes 0
    while(len > 0){
        while(!(I2C_GetFlagStatus(I2C_Handle->pI2Cx, I2C_FLAG_TxE))) // Wait till TxE is set
        {
        	delay_ms(1);
        	TimeOut_TxE -= 1;
			if (TimeOut_TxE == 0){
#ifdef I2C_Debug
				lcd_put_cur(2, 1);
				send_string_lcd("TimeOutTxE");
				i2c_error.errorFlags = I2C_ERR_TXE;
#endif
				return i2c_error;
			}
        }
        I2C_Handle->pI2Cx->DR = (uint8_t)*pTxbuffer;
        delay_ms(1);
        pTxbuffer++;
        len--;
    }

    // 7. When Len becomes zero wait for TxE=1 and BTF=1 before generating the STOP condition
    // Note: TxE=1, BTF=1, means that both SR and DR are empty and next tranmission should begin 
    // when BTF=1 SCL will be stretched  (pulled to LOW)

    while(!(I2C_GetFlagStatus(I2C_Handle->pI2Cx,I2C_FLAG_BTF))){
    	delay_ms(1);
    	TimeOut_BTF -= 1;
		if (TimeOut_BTF == 0){
#ifdef I2C_Debug
			lcd_put_cur(2, 1);
			send_string_lcd("TimeOutBTF");
			i2c_error.errorFlags = I2C_ERR_BTF;
#endif
			return i2c_error;
		}
    }
    I2C_Stop(I2C_Handle->pI2Cx);
    i2c_error.errorFlags = I2C_ERR_NONE;
    return i2c_error;
}

void I2C_MasterRead_Data(I2C_Handle_t *I2C_Handle, uint8_t addr, uint8_t *buffer, uint8_t size) {
    if (size == 0) return;

    // 1. START + gửi địa chỉ Slave (Read)
    I2C_Start(I2C_Handle->pI2Cx);
    I2C_Handle->pI2Cx->DR = (addr << 1) | 0x01;
    while (!(I2C_GetFlagStatus(I2C_Handle->pI2Cx, I2C_FLAG_ADDR)));
    I2C_ClearAddrFlag(I2C_Handle->pI2Cx);

    if (size == 1) {
        I2C_Handle->pI2Cx->CR1 &= ~(1 << 10); // ACK = 0
        I2C_Handle->pI2Cx->CR1 |= (1 << 9);   // STOP
        while (!(I2C_GetFlagStatus(I2C_Handle->pI2Cx, I2C_FLAG_RxNE)));
        buffer[0] = I2C_Handle->pI2Cx->DR;
    } else {
        int i;
        for (i = 0; i < size - 2; i++) {
            while (!(I2C_GetFlagStatus(I2C_Handle->pI2Cx, I2C_FLAG_RxNE)));
            buffer[i] = I2C_Handle->pI2Cx->DR;
        }

        while (!(I2C_GetFlagStatus(I2C_Handle->pI2Cx, I2C_FLAG_RxNE)));
        I2C_Handle->pI2Cx->CR1 &= ~(1 << 10); // ACK = 0
        I2C_Handle->pI2Cx->CR1 |= (1 << 9);   // STOP
        buffer[i++] = I2C_Handle->pI2Cx->DR;

        while (!(I2C_GetFlagStatus(I2C_Handle->pI2Cx, I2C_FLAG_RxNE)));
        buffer[i] = I2C_Handle->pI2Cx->DR;
    }
}

I2C_Error_t I2C_MasterRead_Mem(I2C_Handle_t *I2C_Handle,
                               uint16_t DevAddr,
                               uint16_t MemAddr,
                               uint8_t MemAddrSize,
                               uint8_t *pData,
                               uint16_t Size)
{
    I2C_Error_t i2c_error;
    uint32_t timeout;

    // 1. START + SlaveAddr (Write)
    I2C_Start(I2C_Handle->pI2Cx);
    i2c_error = I2C_Address(I2C_Handle, DevAddr & 0xFE); // Write
    if (i2c_error.errorFlags != I2C_ERR_NONE) return i2c_error;

    // 2. Gửi MemAddr (command)
    if (MemAddrSize == 2) {
        while (!(I2C_GetFlagStatus(I2C_Handle->pI2Cx, I2C_FLAG_TxE)));
        I2C_Handle->pI2Cx->DR = (uint8_t)(MemAddr >> 8); // MSB

        while (!(I2C_GetFlagStatus(I2C_Handle->pI2Cx, I2C_FLAG_TxE)));
        I2C_Handle->pI2Cx->DR = (uint8_t)(MemAddr & 0xFF); // LSB
    } else {
        while (!(I2C_GetFlagStatus(I2C_Handle->pI2Cx, I2C_FLAG_TxE)));
        I2C_Handle->pI2Cx->DR = (uint8_t)MemAddr;
    }

    // 3. REPEATED START + SlaveAddr (Read)
    I2C_Start(I2C_Handle->pI2Cx);
    i2c_error = I2C_Address(I2C_Handle, DevAddr | 0x01); // Read
    if (i2c_error.errorFlags != I2C_ERR_NONE) return i2c_error;

    // 4. Đọc dữ liệu
    for (int i = 0; i < Size; i++) {
        if (i == (Size - 1)) {
            // byte cuối
            I2C_Handle->pI2Cx->CR1 &= ~(1 << 10); // ACK = 0
            I2C_Handle->pI2Cx->CR1 |= (1 << 9);   // STOP
        }
        while (!(I2C_GetFlagStatus(I2C_Handle->pI2Cx, I2C_FLAG_RxNE)));
        pData[i] = I2C_Handle->pI2Cx->DR;
    }

    i2c_error.errorFlags = I2C_ERR_NONE;
    return i2c_error;
}


void I2C_Stop(I2C_RegDef_t *pI2Cx){
	// 8. Genarate the Stop condition and Master need not to wait for the completion of stop condition
	// Note: generating STOP, automatically clears the BTF
	I2C_GenrateStopCondition(pI2Cx);

	// Wait until bus is no longer busy
	while(pI2Cx->SR2 & (1 << 1));  // Wait until BUSY = 0
}


