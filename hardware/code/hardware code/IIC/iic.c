#include "iic.h"
#include "delay.h"
void I2C_SDA_OUT(void)//SDA设置为输出模式
{
    GPIO_InitTypeDef GPIO_InitStructure;	
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//SDA推挽输出
	GPIO_Init(GPIOA,&GPIO_InitStructure); 						

}

void I2C_SDA_IN(void)//SDA设置为输入模式
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//上拉输入
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
}
//以下是IIC总线操作函数
void IIC_init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能PA端口时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6;	//PA4设置为推挽输出,SCL; PA5设置为推挽输出,SDA
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //初始化GPIOA
	GPIO_SetBits(GPIOA,GPIO_Pin_5|GPIO_Pin_6); 
//	I2C_SCL_H;
//	I2C_SDA_H;//释放总线
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
//产生应答信号
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
//产生非应答信号
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
//等待应答信号
//返回值：1 接收应答失败
//		  0 接收应答成功
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
	IIC_SCL=0;//拉低时钟开始数据传输
	for(i=0;i<8;i++)
	{
		IIC_SDA=(txd&0x80)>>7;//发送最高位
		txd<<=1;
		IIC_SCL=1;
		delay_us(2); //保持数据
		IIC_SCL=0;
		delay_us(2);
	}
}
//读取一个字节
u8 IIC_read_byte(u8 ack)
{
	u8 i=0,receive=0;
	I2C_SDA_IN();
   for(i=0;i<8;i++)
   {
   		IIC_SCL=0;
		delay_us(2);
		IIC_SCL=1;
		receive<<=1;//左移
		if(READ_SDA)
		   receive++;//接收数据位
		delay_us(1);	
   }

   	if(!ack)
	   	IIC_noack();
	else
		IIC_ack();

	return receive;//返回读取的字节
}













