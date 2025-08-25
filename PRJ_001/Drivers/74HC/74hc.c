/*
 * Device.cpp
 *
 *  Created on: Jun 20, 2025
 *      Author: Administrator
 */

#include "74hc.h"

static inline void sr595_set_bit_cached(sr595_t *sr, int bit, int val)
{
    int byte = bit >> 3, off = bit & 7;
    if (val) sr->buff[byte] |=  (1u << off);
    else     sr->buff[byte] &= ~(1u << off);
}

static void pulse(sr595_t *sr, void(*set)(int), void(*us)(unsigned)){
	set(1); us(100); set(0); us(100);
}

void sr595_init(sr595_t *sr, const sr595_bus_ops_t *ops, uint8_t msb_first){
	sr->ops = *ops;
	sr->msb_first = msb_first;
	for(int i = 0; i < NUM_IC; i++) sr->buff[i] = 0;
	sr595_flush(sr); /* Clear output */
}

void sr595_flush(sr595_t *sr){
    if (sr->msb_first) {
        for (int i = NUM_IC - 1; i >= 0; --i) {
            for (int b = 7; b >= 0; --b) {
                int bit = (sr->buff[i] >> b) & 1;
                sr->ops.set_data(bit);
                pulse(sr, sr->ops.set_clk, sr->ops.usdelay);
            }
        }
    } else {
        for (int i = 0; i < NUM_IC; ++i) {
            for (int b = 0; b < 8; ++b) {
                int bit = (sr->buff[i] >> b) & 1;
                sr->ops.set_data(bit);
                pulse(sr, sr->ops.set_clk, sr->ops.usdelay);
            }
        }
    }
    pulse(sr, sr->ops.set_latch, sr->ops.usdelay);
}

/* ========== Mapping ========== */
/* IC1: LCD bus: D4..D7 = Q0..Q3, RS=Q4; E1=Q5, E2=Q6, E3=Q7
 * IC2+IC3: 8 motors (Q0..Q15) →  3-3-2 for 3 room
 * IC4: LED room1 Q0..Q7; IC5: room2; IC6: room3
 */
static inline uint8_t Q(int ic, int bit) { return (uint8_t)(ic*8 + bit); }

void homeio_default_mapping(homeio_t *sys){
	/* LCD bus: RS=IC0.Q4, D4..D7 = IC0.Q0..Q3 */
	const uint8_t RS = Q(0,4);
	const uint8_t D4 = Q(0,0);

	/* Room1 */
	sys->rooms[0].lcd_rs_bit = RS;
	sys->rooms[0].lcd_d4_bit = D4;
	sys->rooms[0].lcd_en_bit = Q(0,5);

    sys->rooms[0].motor_bit[0][0] = Q(1,0);
    sys->rooms[0].motor_bit[0][1] = Q(1,1);

    sys->rooms[0].motor_bit[1][0] = Q(1,2);
    sys->rooms[0].motor_bit[1][1] = Q(1,3);

    sys->rooms[0].motor_bit[2][0] = Q(1,4);
    sys->rooms[0].motor_bit[2][1] = Q(1,5);

    sys->rooms[0].motor_count = 3;

    for(int i = 0; i < 8; i++){
    	sys->rooms[0].led_bit[i] = Q(3,i);
    }
    sys->rooms[0].led_count = 8;

	/* Room2 */
	sys->rooms[1].lcd_rs_bit = RS;
	sys->rooms[1].lcd_d4_bit = D4;
	sys->rooms[1].lcd_en_bit = Q(0,6);

    sys->rooms[1].motor_bit[0][0] = Q(1,6);
    sys->rooms[1].motor_bit[0][1] = Q(1,7);

    sys->rooms[1].motor_bit[1][0] = Q(2,0);
    sys->rooms[1].motor_bit[1][1] = Q(2,1);

    sys->rooms[1].motor_bit[2][0] = Q(2,2);
    sys->rooms[1].motor_bit[2][1] = Q(2,3);

    sys->rooms[1].motor_count = 3;

    for(int i = 0; i < 8; i++){
    	sys->rooms[1].led_bit[i] = Q(4,i);
    }
    sys->rooms[1].led_count = 8;

    /* Room 3 */
    sys->rooms[2].lcd_rs_bit = RS;
    sys->rooms[2].lcd_d4_bit = D4;
    sys->rooms[2].lcd_en_bit  = Q(0,7);

    sys->rooms[2].motor_bit[0][0] = Q(2,4);
    sys->rooms[2].motor_bit[0][1] = Q(2,5);

    sys->rooms[2].motor_bit[1][0] = Q(2,6);
    sys->rooms[2].motor_bit[1][1] = Q(2,7);

    sys->rooms[2].motor_count = 2;

    for (int i=0;i<8;++i){
    	sys->rooms[2].led_bit[i] = Q(5, i);
    }

    sys->rooms[2].led_count = 8;
}

void homeio_init(homeio_t *sys, sr595_t *bus){
	sys->bus = bus;
	/* Clear buff*/
	for(int i = 0; i < NUM_IC; i++){
		bus->buff[i] = 0;
	}
	homeio_default_mapping(sys);
}

void homeio_flush(homeio_t *sys){
	sr595_flush(sys->bus);
}

/* ========== LED ========== */
void led_set(void *self, int room_id, int led_index, int value){
	homeio_t *sys = (homeio_t*)self;
	if(room_id <0 || room_id >=3) return;
	if((size_t)led_index >= sys->rooms[room_id].led_count) return;
    uint8_t bit = sys->rooms[room_id].led_bit[led_index];
    sr595_set_bit_cached(sys->bus, bit, value ? 1 : 0);
}

/* ========== Motor ========== */
void motor_drive(void *self, int room_id, int motor_index, int in1, int in2)
{
    homeio_t *sys = (homeio_t*)self;
    if (room_id < 0 || room_id >= 3) return;
    if ((size_t)motor_index >= sys->rooms[room_id].motor_count) return;
    uint8_t b1 = sys->rooms[room_id].motor_bit[motor_index][0];
    uint8_t b2 = sys->rooms[room_id].motor_bit[motor_index][1];
    sr595_set_bit_cached(sys->bus, b1, in1 ? 1 : 0);
    sr595_set_bit_cached(sys->bus, b2, in2 ? 1 : 0);
}

/* ========== LCD 4-bit, E for room ========== */
static void lcd_bus_write(homeio_t *sys, int room_id, int rs, uint8_t nibble)
{
    const room_map_t *rm = &sys->rooms[room_id];

    /* RS */
    sr595_set_bit_cached(sys->bus, rm->lcd_rs_bit, rs);

    /* D4..D7 */
    uint8_t d4 = rm->lcd_d4_bit;
    sr595_set_bit_cached(sys->bus, d4 + 0, (nibble >> 0) & 1);
    sr595_set_bit_cached(sys->bus, d4 + 1, (nibble >> 1) & 1);
    sr595_set_bit_cached(sys->bus, d4 + 2, (nibble >> 2) & 1);
    sr595_set_bit_cached(sys->bus, d4 + 3, (nibble >> 3) & 1);

    /* Pulse E */
    sr595_flush(sys->bus);
    sys->bus->ops.set_data(0);
    sys->bus->ops.set_clk(0);
    sys->bus->ops.set_latch(0);
    /* Toggle bit cached: */
    /* set E=1 -> flush -> set E=0 -> flush */
    sr595_set_bit_cached(sys->bus, rm->lcd_en_bit, 1);
    sr595_flush(sys->bus);
    sys->bus->ops.usdelay(50);
    sr595_set_bit_cached(sys->bus, rm->lcd_en_bit, 0);
    sr595_flush(sys->bus);
    sys->bus->ops.usdelay(50);
}

static void lcd_write_byte(homeio_t *sys, int room_id, int rs, uint8_t byte){
	lcd_bus_write(sys, room_id, 1, (byte >> 4) & 0x0F); /* high nibble */
	lcd_bus_write(sys, room_id, 1, (byte >> 0) & 0x0F); /* low nibble */
}

static void lcd_cmd_byte(homeio_t *sys, int room_id, uint8_t byte){
	lcd_bus_write(sys, room_id, 0, (byte >> 4) & 0x0F); /* high nibble */
	lcd_bus_write(sys, room_id, 0, (byte >> 0) & 0x0F); /* low nibble */
}

void lcd_init(void *self, int room_id){
	homeio_t *sys = (homeio_t*)self;
	sys->bus->ops.msdelay(10); lcd_cmd_byte(sys, room_id, 0x2);  // 4bit mode
	sys->bus->ops.msdelay(1000); lcd_cmd_byte(sys, room_id, 0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
	sys->bus->ops.msdelay(1);


	lcd_cmd_byte(sys, room_id, 0x0C); sys->bus->ops.msdelay(1);
	lcd_cmd_byte(sys, room_id, 0x01); sys->bus->ops.msdelay(2);
	lcd_cmd_byte(sys, room_id, 0x06); sys->bus->ops.msdelay(1);

	sys->bus->ops.msdelay(200);
//	lcd_put_cur(0,0);
	lcd_puts(sys, room_id, "Init LCD1 success"); // Test
//	lcd_put_cur(1,0);
//	lcd_puts(self, 2, "Init LCD2 success"); // Test

	sys->bus->ops.msdelay(500);
	lcd_clear();
}

void lcd_putc(void *self, int room_id, char c)
{
    homeio_t *sys = (homeio_t*)self;
    lcd_write_byte(sys, room_id, 1, (uint8_t)c);
}

void lcd_puts(void *self, int room_id, const char *s)
{
    while (*s) lcd_putc(self, room_id, *s++);
}

static void set_data_impl(int level)  {
	GPIO_WriteToOutPutPin(GPIOE, DS, level);
}
static void set_clk_impl(int level)   {
	GPIO_WriteToOutPutPin(GPIOE, SH_CP, level);
}
static void set_latch_impl(int level) {
	GPIO_WriteToOutPutPin(GPIOE, ST_CP, level);
}
static void usdelay_impl(unsigned us)  { delay_us(us); }
static void msdelay_impl(unsigned ms)  { delay_ms(ms); }

static struct IC_74HC_t ic_74hc;

static void ConfigPin(uint8_t pinNum) {
    ic_74hc.Pin[pinNum].pGPIOx = GPIOE;
    ic_74hc.Pin[pinNum].GPIO_Pin_Config.GPIO_PinNumber = pinNum;
    ic_74hc.Pin[pinNum].GPIO_Pin_Config.GPIO_PinMode = GPIO_MODER_OUTPUT;
    ic_74hc.Pin[pinNum].GPIO_Pin_Config.GPIO_PinSpeed = GPIO_OSPEEDR_HIGH;
    ic_74hc.Pin[pinNum].GPIO_Pin_Config.GPIO_PinPuPdControl = GPIO_PUPDR_PU;
}

void init_74test(){
	GPIOE_PCLK_EN;
	for (int i = 0; i < 3; i++){
		ConfigPin(i);
		GPIO_Init_Pin(&ic_74hc.Pin[i]);
	}
}

void sr_init(){
	init_74test();

	sr595_t sr;
	homeio_t sys;

	sr595_bus_ops_t ops = {
		.set_data = set_data_impl,
		.set_clk = set_clk_impl,
		.set_latch = set_latch_impl,
		.usdelay = usdelay_impl,
		.msdelay = msdelay_impl,
	};

	sr595_init(&sr, &ops, 1);     /* shift MSB-first */
	homeio_init(&sys, &sr);

	for (int i = 0; i < 3; i++) {lcd_init(&sys, i);}

	for (int i=0;i<8;++i) led_set(&sys, 0, i, 1);
	homeio_flush(&sys);

	motor_drive(&sys, 1, 0, 1, 0);
	homeio_flush(&sys);

//	lcd_puts(&sys, 2, "Hello");
}











































