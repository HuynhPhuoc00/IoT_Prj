/*
 * Room.h
 *
 *  Created on: Jun 5, 2025
 *      Author: Administrator
 */

#ifndef INC_ROOM_H_
#define INC_ROOM_H_

#include "stm32f411.h"
#include <Device.h>


class Room : public Device {
private:
public:
    Room(std::string name) : Device(name) {}
};

#endif /* INC_ROOM_H_ */
