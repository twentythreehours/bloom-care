#ifndef MAX30102_READ_H_
#define MAX30102_READ_H_

#include "stm32f10x.h"
#include "stdbool.h"
extern int32_t hrAvg;
extern int32_t spo2Avg;
extern uint32_t aun_ir_buffer[150];
extern uint32_t aun_red_buffer[150];  
extern int32_t n_ir_buffer_length;

void Init_MAX30102(void);
void ReadHeartRateSpO2(void);

#endif 

