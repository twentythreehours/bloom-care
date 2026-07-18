#ifndef __DELAY_H
#define __DELAY_H

#include "sys.h"

void delay_init(u8 SYSCLK);
void delay_ms(u16 nms);
void delay_us(u32 nus);


uint32_t delay_get_tick(void);
void delay_inc_tick(void);

#endif

