#include "iic.h"
#include "delay.h"
void I2C_SDA_OUT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;	
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA,&GPIO_InitStructure); 						

}

void I2C_SDA_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
}

void IIC_init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 
	GPIO_SetBits(GPIOA,GPIO_Pin_5|GPIO_Pin_6); 

}
void IIC_start()
{
	I2C_SDA_OUT();
	IIC_SDA=1;	  
	IIC_SCL=1;
	delay_us(5);
	IIC_SDA=0;
	delay_us(5);
	IIC_SCL=0;
}
void IIC_stop()
{
	I2C_SDA_OUT();
	IIC_SCL=0;
	IIC_SDA=0;
	delay_us(5);
	IIC_SCL=1; 
	IIC_SDA=1;
	delay_us(5);
}
//����Ӧ���ź�
void IIC_ack()
{
	IIC_SCL=0;
	I2C_SDA_OUT();
  IIC_SDA=0;
   delay_us(2);
   IIC_SCL=1;
   delay_us(5);
   IIC_SCL=0;	
}
//������Ӧ���ź�
void IIC_noack()
{
	IIC_SCL=0;
	I2C_SDA_OUT();
   IIC_SDA=1;
   delay_us(2);
   IIC_SCL=1;
   delay_us(2);
   IIC_SCL=0;
}

u8 IIC_wait_ack()
{
	u8 tempTime=0;
	I2C_SDA_IN();
	IIC_SDA=1;
	delay_us(1);
	IIC_SCL=1;
	delay_us(1);

	while(READ_SDA)
	{
		tempTime++;
		if(tempTime>250)
		{
			IIC_stop();
			return 1;
		}	 
	}

	IIC_SCL=0;
	return 0;
}
void IIC_send_byte(u8 txd)
{
	u8 i=0;
	I2C_SDA_OUT();
	IIC_SCL=0;
	for(i=0;i<8;i++)
	{
		IIC_SDA=(txd&0x80)>>7;
		txd<<=1;
		IIC_SCL=1;
		delay_us(2); 
		IIC_SCL=0;
		delay_us(2);
	}
}

u8 IIC_read_byte(u8 ack)
{
	u8 i=0,receive=0;
	I2C_SDA_IN();
   for(i=0;i<8;i++)
   {
   		IIC_SCL=0;
		delay_us(2);
		IIC_SCL=1;
		receive<<=1;
		if(READ_SDA)
		   receive++;
		delay_us(1);	
   }

   	if(!ack)
	   	IIC_noack();
	else
		IIC_ack();

	return receive;
}













