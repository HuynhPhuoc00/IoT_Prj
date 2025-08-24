/*
 * Device.cpp
 *
 *  Created on: Jun 20, 2025
 *      Author: Administrator
 */

#include "Device.h"



Device::Device(std::string name){

//	Write_data(0x1, DS3, MSB);
//	Write_data(0x00000100, DS3, LSB);
//	Write_data(0x00001000, DS3, LSB);
//	Write_data(0x10000000, DS3, LSB);

//	lcd_init();
//	Key_Config_Pin();
//	start_dht();
//	Read_DHT();



	/* Busy loop for initialization, because the main loop does not work without
	 * a sensor.
	 */
}

Device::~Device() {
	GPIOA_PCLK_DIS;
	GPIOB_PCLK_DIS;
	GPIOC_PCLK_DIS;
	GPIOD_PCLK_DIS;
	GPIOE_PCLK_DIS;
}

void Device::TurnOnLed(uint8_t data){
//	Write_data(data, id_74HC[0], MSB);
}

void Device::TurnOffLed(uint8_t data){
//	Write_data((data >> data) & 0x0 , id, MSB);
}

void Device::ShowDisplay(char *data, int row, int col){
//	lcd_goto_XY(row, col);
//	lcd_send_string(data);
}



