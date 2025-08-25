/*
 * Device.h
 *
 *  Created on: Jun 20, 2025
 *      Author: Administrator
 */

#ifndef SRC_74HC_H_
#define SRC_74HC_H_

#include <stdint.h>
#include "lcd.h"

typedef struct{
	void (*set_data)(int val);
	void (*set_clk)(int pin);
	void (*set_latch)(int pin);
	void (*usdelay)(unsigned int us);
	void (*msdelay)(unsigned int us);
}sr595_bus_ops_t;

#define NUM_IC 6

#define SR_BITS (NUM_IC * 8)

typedef struct {
	sr595_bus_ops_t ops;
	uint8_t buff[NUM_IC];
	uint8_t msb_first;
}sr595_t;

/* Device interface */
typedef struct{
	void(*set)(void *seft, uint8_t index, uint8_t value);
	void *self;
}led_if_t;

typedef struct{
	void(*drive)(void *seft, uint8_t index, uint8_t in1, uint8_t in2);
	void *self;
}motor_if_t;

typedef struct{
	void (*init)(void *seft, uint8_t room_id, void(*md)(unsigned));
	void(*puts)(void *seft, uint8_t room_id, const char *s);
	void *self;
}lcd_if_t;

typedef struct{
	/* LCD */
	uint8_t lcd_rs_bit;
	uint8_t lcd_d4_bit;
	uint8_t lcd_en_bit;

	/* Motor */
	uint8_t motor_bit[3][2];
	size_t motor_count;

	/* LED */
	uint8_t led_bit[8];
	size_t led_count;
}room_map_t;

typedef struct{
	sr595_t *bus;
	room_map_t rooms[3];
}homeio_t;

/* API */
void sr595_init(sr595_t *sr, const sr595_bus_ops_t *ops, uint8_t msb_first);
static inline void sr595_set_bit_cached(sr595_t *sr, int bit, int val);
void sr595_flush(sr595_t *sr); /* flush buff out to IC */


/* Device dev */
typedef struct{
	homeio_t *sys;
}led_dev_t;

typedef struct{
	homeio_t *sys;
}motor_dev_t;

typedef struct{
	homeio_t *sys;
}lcd_dev_t;

enum Pin_conf{
	SH_CP,
	DS,
	ST_CP,
};

/* Adapters “interface” */
void led_set(void *self, int room_id, int led_index, int value);
void motor_drive(void *self, int room_id, int motor_index, int in1, int in2);
void lcd_puts(void *self, int room_id, const char *s);
void lcd_init(void *self, int room_id);

void homeio_init(homeio_t *sys, sr595_t *bus);
void homeio_default_mapping(homeio_t *sys);
void homeio_flush(homeio_t *sys);

void sr_init();

#endif /* SRC_74HC_H_ */
