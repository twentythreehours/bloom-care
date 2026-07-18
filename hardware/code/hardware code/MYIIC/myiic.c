

#include "myiic.h"





#define RCC_I2C_PORT 	RCC_APB2Periph_GPIOA		

#define PORT_I2C_SCL	GPIOA			
#define PIN_I2C_SCL		GPIO_Pin_1		

#define PORT_I2C_SDA	GPIOA			
#define PIN_I2C_SDA		GPIO_Pin_4		

#define I2C_SCL_PIN		GPIO_Pin_1			
#define I2C_SDA_PIN		GPIO_Pin_4			




#define I2C_SCL_1()  PORT_I2C_SCL->BSRR = I2C_SCL_PIN				/* SCL = 1 */
#define I2C_SCL_0()  PORT_I2C_SCL->BRR = I2C_SCL_PIN				/* SCL = 0 */

#define I2C_SDA_1()  PORT_I2C_SDA->BSRR = I2C_SDA_PIN				/* SDA = 1 */
#define I2C_SDA_0()  PORT_I2C_SDA->BRR = I2C_SDA_PIN				/* SDA = 0 */

#define I2C_SDA_READ()  ((PORT_I2C_SDA->IDR & I2C_SDA_PIN) != 0)	
#define I2C_SCL_READ()  ((PORT_I2C_SCL->IDR & I2C_SCL_PIN) != 0)	


void bsp_InitI2C(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_I2C_PORT, ENABLE);	

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;	
	
	GPIO_InitStructure.GPIO_Pin = PIN_I2C_SCL;
	GPIO_Init(PORT_I2C_SCL, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = PIN_I2C_SDA;
	GPIO_Init(PORT_I2C_SDA, &GPIO_InitStructure);


	i2c_Stop();
}


static void i2c_Delay(void)
{
	uint8_t i;

	
	for (i = 0; i < 30; i++);
}


void i2c_Start(void)
{
	
	I2C_SDA_1();
	I2C_SCL_1();
	i2c_Delay();
	I2C_SDA_0();
	i2c_Delay();
	
	I2C_SCL_0();
	i2c_Delay();
}


void i2c_Stop(void)
{
	
	I2C_SDA_0();
	I2C_SCL_1();
	i2c_Delay();
	I2C_SDA_1();
	i2c_Delay();
}


void i2c_SendByte(uint8_t _ucByte)
{
	uint8_t i;

	
	for (i = 0; i < 8; i++)
	{
		if (_ucByte & 0x80)
		{
			I2C_SDA_1();
		}
		else
		{
			I2C_SDA_0();
		}
		i2c_Delay();
		I2C_SCL_1();
		i2c_Delay();
		I2C_SCL_0();
		if (i == 7)
		{
			 I2C_SDA_1(); 
		}
		_ucByte <<= 1;	
		i2c_Delay();
	}
}


uint8_t i2c_ReadByte(void)
{
	uint8_t i;
	uint8_t value;


	value = 0;
	for (i = 0; i < 8; i++)
	{
		value <<= 1;
		I2C_SCL_1();
		i2c_Delay();
		if (I2C_SDA_READ())
		{
			value++;
		}
		I2C_SCL_0();
		i2c_Delay();
	}
	return value;
}


uint8_t i2c_WaitAck(void)
{
	uint8_t re;

	I2C_SDA_1();	
	i2c_Delay();
	I2C_SCL_1();	
	i2c_Delay();
	if (I2C_SDA_READ())	
	{
		re = 1;
	}
	else
	{
		re = 0;
	}
	I2C_SCL_0();
	i2c_Delay();
	return re;
}


void i2c_Ack(void)
{
	I2C_SDA_0();	
	i2c_Delay();
	I2C_SCL_1();	
	i2c_Delay();
	I2C_SCL_0();
	i2c_Delay();
	I2C_SDA_1();	
}


void i2c_NAck(void)
{
	I2C_SDA_1();	
	i2c_Delay();
	I2C_SCL_1();	
	i2c_Delay();
	I2C_SCL_0();
	i2c_Delay();
}


uint8_t i2c_CheckDevice(uint8_t _Address)
{
	uint8_t ucAck;

	if (I2C_SDA_READ() && I2C_SCL_READ())
	{
		i2c_Start();		

		
		i2c_SendByte(_Address | I2C_WR);
		ucAck = i2c_WaitAck();	

		i2c_Stop();			

		return ucAck;
	}
	return 1;	
}


