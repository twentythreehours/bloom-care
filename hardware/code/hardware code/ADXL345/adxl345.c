
#include "adxl345.h"
#include "iic.h"
#include "delay.h"
#include <math.h>

#define ADXL345_RANGE	4.0f							
#define ADXL345_SCALE	( ADXL345_RANGE / 32768.0f )	
#define M_PI 3.14159265358979323846




void adxl345_init()
{
		adxl345_write_reg(0X31,0X09);		
		adxl345_write_reg(0x2C,0x0B);		
		adxl345_write_reg(0x2D,0x08);	   	
		adxl345_write_reg(0X2E,0x80);		 
	 	adxl345_write_reg(0X1E,0x00);
		adxl345_write_reg(0X1F,0x00);
		adxl345_write_reg(0X20,0x05);	
}

void adxl345_write_reg(u8 addr,u8 val) 
{
	IIC_start();  				 
	IIC_send_byte(slaveaddress);     	 
	IIC_wait_ack();	   
    IIC_send_byte(addr);   			
	IIC_wait_ack(); 	 										  		   
	IIC_send_byte(val);     		   
	IIC_wait_ack();  		    	   
    IIC_stop();						  
}

u8 adxl345_read_reg(u8 addr)
{
	u8 temp=0;		 
	IIC_start();  				 
	IIC_send_byte(slaveaddress);	
	temp=IIC_wait_ack();	   
    IIC_send_byte(addr);   		
	temp=IIC_wait_ack(); 	 										  		   
	IIC_start();  	 	   		
	IIC_send_byte(regaddress);	
	temp=IIC_wait_ack();	   
    temp=IIC_read_byte(0);		    	   
    IIC_stop();					    
	return temp;
}
//��ȡ���ݺ���
void adxl345_read_data(short *x,short *y,short *z)
{
	u8 buf[6];
	u8 i;
	IIC_start();  				 
	IIC_send_byte(slaveaddress);	
	IIC_wait_ack();	   
    IIC_send_byte(0x32);   		
	IIC_wait_ack(); 	 										  		   
 
 	IIC_start();  	 	   		
	IIC_send_byte(regaddress);	
	IIC_wait_ack();
	for(i=0;i<6;i++)
	{
		if(i==5)buf[i]=IIC_read_byte(0);
		else buf[i]=IIC_read_byte(1);
 	}	        	   
    IIC_stop();					
	*x=(short)(((u16)buf[1]<<8)+buf[0]); 	
	*y=(short)(((u16)buf[3]<<8)+buf[2]); 	    
	*z=(short)(((u16)buf[5]<<8)+buf[4]); 
}

void adxl345_read_average(float *x,float *y,float *z,u8 times)
{
	u8 i;
	short tx,ty,tz;
	*x=0;
	*y=0;
	*z=0;
	if(times)
	{
		for(i=0;i<times;i++)
		{
			adxl345_read_data(&tx,&ty,&tz);
			*x+=tx;
			*y+=ty;
			*z+=tz;
			delay_ms(5);
		}
		*x/=times;
		*y/=times;
		*z/=times;
	}
	
	
}

	
	void get_angle(float *x_angle,float *y_angle,float *z_angle)
{
	float  ax_raw, ay_raw, az_raw;	
	float  ax, ay, az;				

	adxl345_read_average(&ax_raw, &ay_raw, &az_raw, 10);	
		

	ax = ax_raw * ADXL345_SCALE;
	ay = ay_raw * ADXL345_SCALE;
	az = az_raw * ADXL345_SCALE;
		

	*x_angle = atan(ax / sqrt(az*az + ay*ay))*180.0f / M_PI;	
	*y_angle = atan(ay / sqrt(ax*ax + az*az))*180.0f / M_PI;	
	*z_angle = atan(sqrt(ax*ax + ay*ay) /az) *180.0f / M_PI;	
} 
	



	
	
	
//void get_angle(float x_angle,float y_angle,float z_angle)
//{
//	short ax,ay,az;
//	adxl345_read_average(&ax,&ay,&az,10);
//	x_angle=atan(ax/sqrt((az*az+ay*ay)));
//	y_angle=atan(ay/sqrt((ax*ax+az*az)));
//	z_angle=atan(sqrt((ax*ax+ay*ay)/az));
//}
