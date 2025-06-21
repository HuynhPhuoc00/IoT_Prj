/*
 * LCD1602.c
 *
 *  Created on: Jun 12, 2025
 *      Author: Administrator
 */

#ifndef INC_LCD1602_H_
#define INC_LCD1602_H_

#include "stm32f411.h"

#ifdef __cplusplus
extern "C" {
#endif

void LCD_Config_I2C(); // initialize I2C for LCD

void lcd_init (void);   // initialize lcd

void lcd_send_cmd (char cmd);  // send command to the lcd

void lcd_send_data (char data);  // send data to the lcd

void lcd_send_string (char *str);  // send string to the lcd

void lcd_clear_display (void);	//clear display lcd

void lcd_goto_XY (int row, int col); //set proper location on screen

#ifdef __cplusplus
}
#endif

#endif /* INC_LCD1602_H_ */
