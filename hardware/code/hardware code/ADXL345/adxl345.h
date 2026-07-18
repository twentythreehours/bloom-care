#ifndef __ADXL345_H
#define __ADXL345_H
#include "sys.h"


#define X_AXLE 0   
#define Y_AXLE 1   
#define Z_AXLE 2  

#define	slaveaddress   0xA6	 


#define THRESH_TAP     0X1D	  

#define OFSX           0X1E   
#define OFSY           0X1F   
#define OFSZ           0X20   
#define DUR            0x21   
#define LATENT         0X22  

#define WINDOW         0X23  

#define THRESH_ACT     0X24  

#define	THRESH_INACT   0X25   

#define TIME_INACT     0X26   

#define ACT_INACT_CTL  0X27 


#define THRESH_FF      0X28   

#define TIME_FF        0X29   

#define TAP_AXES       0X2A   

#define ACT_TAP_STATUS 0X2B   

#define BW_RATE        0X2C  

#define POWER_CTL      0X2D

#define INT_ENABLE     0X2E 

#define INT_MAP        0X2F   

#define INT_SOURCE     0X30   

#define DATA_FORMAT    0X31

#define DATAX0         0X32
#define DATAX1         0X33 
#define DATAY0         0X34
#define DATAY1         0X35  
#define DATAZ0         0X36
#define DATAZ1         0X37  
#define FIFO_CTL       0X38

#define FIFO_STATUS    0X39	 
#define regaddress 0XA7
#define DEVICE_ID 0X00
void adxl345_init(void);
u8 adxl345_read_reg(u8 addr);
void adxl345_write_reg(u8 addr,u8 val);
void adxl345_read_data(short *x,short *y,short *z);
void adxl345_read_average(float *x,float *y,float *z,u8 times);
void ADXL345_Start(void);
void ADXL345_Stop(void);
void get_angle(float *x_angle,float *y_angle,float *z_angle);
uint8_t FallDetect(void);
#endif
