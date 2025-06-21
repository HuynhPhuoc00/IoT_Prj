/*
 * LCD1602.c
 *
 *  Created on: Jun 12, 2025
 *      Author: Administrator
 */

#include "LCD1602.h"

#define SLAVE_ADDRESS_LCD 0x27 // change this according to ur setup
I2C_Handle_t *hi2c1;

void LCD_Config_I2C(){
	I2C_Init(&hi2c1);
	hi2c1->pI2Cx = I2C1;
	hi2c1->I2C_Congif.I2C_SCLSpeed = I2C_SCL_SPEED_SM;
	hi2c1->I2C_Congif.I2C_DeviceAddr = SLAVE_ADDRESS_LCD;
	hi2c1->I2C_Congif.I2C_AckControl = I2C_ACK_DIS;
	hi2c1->I2C_Congif.I2C_FMDutyCyCle = I2C_FMDUTY_2;
}

void lcd_send_cmd (char cmd)
{
  char data_u, data_l;
	uint8_t data_t[4];
	data_u = (cmd&0xf0);
	data_l = ((cmd<<4)&0xf0);
	data_t[0] = data_u|0x0C;  //en=1, rs=0
	data_t[1] = data_u|0x08;  //en=0, rs=0
	data_t[2] = data_l|0x0C;  //en=1, rs=0
	data_t[3] = data_l|0x08;  //en=0, rs=0
	I2C_MasterSend_Multi_Data (hi2c1->pI2Cx, data_t, 4);
}

void lcd_send_data (char data)
{
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (data&0xf0);
	data_l = ((data<<4)&0xf0);
	data_t[0] = data_u|0x0D;  //en=1, rs=0
	data_t[1] = data_u|0x09;  //en=0, rs=0
	data_t[2] = data_l|0x0D;  //en=1, rs=0
	data_t[3] = data_l|0x09;  //en=0, rs=0
	I2C_MasterSend_Multi_Data (hi2c1->pI2Cx, data_t, 4);
}

void lcd_init (void)
{
	lcd_send_cmd (0x33); /* set 4-bits interface */
	lcd_send_cmd (0x32);
	Delay_ms(50);
	lcd_send_cmd (0x28); /* start to set LCD function */
	Delay_ms(50);
	lcd_send_cmd (0x01); /* clear display */
	Delay_ms(50);
	lcd_send_cmd (0x06); /* set entry mode */
	Delay_ms(50);
	lcd_send_cmd (0x0c); /* set display to on */
	Delay_ms(50);
	lcd_send_cmd (0x02); /* move cursor to home and set data address to 0 */
	Delay_ms(50);
	lcd_send_cmd (0x80);
}

void lcd_send_string (char *str)
{
	while (*str) lcd_send_data (*str++);
}

void lcd_clear_display (void)
{
	lcd_send_cmd (0x01); //clear display
}

void lcd_goto_XY (int row, int col)
{
	uint8_t pos_Addr;
	if(row == 1)
	{
		pos_Addr = 0x80 + row - 1 + col;
	}
	else
	{
		pos_Addr = 0x80 | (0x40 + col);
	}
	lcd_send_cmd(pos_Addr);
}

