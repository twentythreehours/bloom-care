#include "ds18b20.h"
#include "delay.h"	
	



void DS18B20_Rst(void)	   
{                 
		DS18B20_Mode(OUT); 	
    DS18B20_Low; 				
    delay_us(750);    	
    DS18B20_High; 			
		delay_us(15);     	
}

u8 DS18B20_Check(void) 	   
{   
	u8 retry=0;
	DS18B20_Mode(IN);	//SET  INPUT	 
    while (GPIO_ReadInputDataBit(DS18B20_GPIO_PORT,DS18B20_GPIO_PIN)&&retry<200)
	{
		retry++;
		delay_us(1);
	};	 
	if(retry>=200)return 1;
	else retry=0;
    while (!GPIO_ReadInputDataBit(DS18B20_GPIO_PORT,DS18B20_GPIO_PIN)&&retry<240)
	{
		retry++;
		delay_us(1);
	};
	if(retry>=240)return 1;	    
	return 0;
}

u8 DS18B20_Read_Bit(void) 	 
{
    u8 data;
	DS18B20_Mode(OUT);	//SET OUTPUT
    DS18B20_Low; 
	delay_us(2);
    DS18B20_High; 
	DS18B20_Mode(IN);	//SET INPUT
	delay_us(12);
	if(GPIO_ReadInputDataBit(DS18B20_GPIO_PORT,DS18B20_GPIO_PIN))data=1;
    else data=0;	 
    delay_us(50);           
    return data;
}

u8 DS18B20_Read_Byte(void)     
{        
    u8 i,j,dat;
    dat=0;
	for (i=1;i<=8;i++) 
	{
        j=DS18B20_Read_Bit();
        dat=(j<<7)|(dat>>1);
    }						    
    return dat;
}

void DS18B20_Write_Byte(u8 dat)     
 {             
    u8 j;
    u8 testb;
	DS18B20_Mode(OUT);	//SET OUTPUT;
    for (j=1;j<=8;j++) 
	{
        testb=dat&0x01;
        dat=dat>>1;
        if (testb) 
        {
            DS18B20_Low;	// Write 1
            delay_us(2);                            
            DS18B20_High;
            delay_us(60);             
        }
        else 
        {
            DS18B20_Low;	// Write 0
            delay_us(60);             
            DS18B20_High;
            delay_us(2);                          
        }
    }
}

void DS18B20_Start(void) 
{   						               
    DS18B20_Rst();	   
		DS18B20_Check();	 
    DS18B20_Write_Byte(0xcc);	// skip rom
    DS18B20_Write_Byte(0x44);	// convert
} 

   	 
u8 DS18B20_Init(void)
{
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_APB2PeriphClockCmd(DS18B20_GPIO_CLK, ENABLE);	 
	
 	GPIO_InitStructure.GPIO_Pin = DS18B20_GPIO_PIN;				
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		  
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(DS18B20_GPIO_PORT, &GPIO_InitStructure);

 	GPIO_SetBits(DS18B20_GPIO_PORT,DS18B20_GPIO_PIN);   

	DS18B20_Rst();

	return DS18B20_Check();
}  

short DS18B20_Get_Temp(void)
{
    u8 temp;
    u8 TL,TH;
	short tem;
    DS18B20_Start ();  			// ds1820 start convert
    DS18B20_Rst();
    DS18B20_Check();	 
    DS18B20_Write_Byte(0xcc);	// skip rom
    DS18B20_Write_Byte(0xbe);	// convert	    
    TL=DS18B20_Read_Byte(); 	// LSB   
    TH=DS18B20_Read_Byte(); 	// MSB  
	    	  
    if(TH>7)
    {
        TH=~TH;
        TL=~TL; 
        temp=0;					
    }else temp=1;				 	  
    tem=TH; 					
    tem<<=8;    
    tem+=TL;					
    tem=(float)tem*0.625;		  
		 if(tem > 800)
    {
        return 0;  
    }
	if(temp)return tem; 		
	else return -tem;    
}

void DS18B20_Mode(u8 mode)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(DS18B20_GPIO_CLK, ENABLE);	
	
	if(mode)
	{
		GPIO_InitStructure.GPIO_Pin = DS18B20_GPIO_PIN;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	}
	else
	{
		GPIO_InitStructure.GPIO_Pin =  DS18B20_GPIO_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	}
	GPIO_Init(DS18B20_GPIO_PORT, &GPIO_InitStructure);
}


 
