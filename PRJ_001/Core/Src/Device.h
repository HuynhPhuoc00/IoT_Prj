/*
 * Device.h
 *
 *  Created on: Jun 20, 2025
 *      Author: Administrator
 */

#ifndef SRC_DEVICE_H_
#define SRC_DEVICE_H_

#include <stdint.h>
#include <string>
//#include "i2c_lcd2.h"

#include "../../Drivers/74HC/74HC595.h"
//#include "lcd.h"
//#include "dht11.h"
//#include "keyboard.h"
//#include "sht3x.h"

enum Room_ID{
	em_LV_R = 2,
	em_KC_R = 3,
	em_B_R = 4
};

class Device{
private:
	uint8_t id;
	uint8_t id_74HC[5];
public:
	enum emDevice{
		em_Led0 = 0,
		em_Led1 = 1,
		em_Led2 = 2,
		em_Led3 = 3,
		em_Led4 = 4,
		em_Led5 = 5,
		em_Led6 = 6,
		em_Led7 = 7,
	};
	Device(std::string name);
	~Device();
	void TurnOnLed(uint8_t data);
	void TurnOffLed(uint8_t data);
	void TurnOnFan(uint8_t data);
	void TurnOffFan(uint8_t data);
	void ShowDisplay(uint8_t *data, int row, int col);
	void ReadSensor(char *name);

};


#endif /* SRC_DEVICE_H_ */
