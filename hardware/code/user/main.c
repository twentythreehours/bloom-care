#include "stm32f10x.h"
#include "led.h"
#include "beep.h"
#include "usart.h"
#include "delay.h"
#include "oled.h"
#include "key.h"
#include "Modules.h"
#include "adcx.h"
#include "TIM2.h" 
#include "timer.h"
#include "max30102_read.h"  
#include "ds18b20.h"		
#include "adxl345.h"		
#include "myiic.h"
#include "iic.h"




#define KEY_Long1	11
#define KEY_1		1
#define KEY_2		2
#define KEY_3		3
#define KEY_4		4

#define AUTO_MODE     1   
#define MANUAL_MODE   2   
#define SETTINGS_MODE 3   
SensorModules sensorData;								
SensorThresholdValue Sensorthreshold;		
DriveModules driveData;									
uint8_t mode = 1;
uint8_t step_num = 0;
extern unsigned char p[16];
uint8_t count_m = 1;  
uint8_t count_s = 1;	 
uint8_t auto_page = 1;   

void OLED_autoPage1(void)		
{
	
	  OLED_ShowChinese(0, 0, 23, 16, 1);  
	  OLED_ShowChinese(16, 0, 24, 16, 1);  
    OLED_ShowChar(32, 0, ':', 16, 1);	
		OLED_ShowChinese(0, 16, 49, 16, 1);  
	  OLED_ShowChinese(16, 16, 50, 16, 1);  
    OLED_ShowChar(32, 16, ':', 16, 1);
    OLED_ShowChinese(0, 32, 9, 16, 1);  
    OLED_ShowChinese(16, 32, 10, 16, 1); 
    OLED_ShowChinese(48, 32, 11, 16, 1); 
    OLED_ShowChinese(64, 32, 12, 16, 1); 
    OLED_ShowChinese(96, 32, 53, 16, 1); 
    OLED_ShowChinese(112, 32, 54, 16, 1); 
	  OLED_Refresh();
}

void SensorDataDisplay1(void)		
{
		OLED_ShowString(48,0,(u8*)p ,16,1);
	  OLED_ShowNum(0,48,sensorData.hrAvg,3,16,1);
    OLED_ShowNum(48,48,sensorData.spo2Avg,3,16,1);
	  OLED_ShowNum(96,48,sensorData.stepCount,3,16,1);
	
	if(sensorData.shake)
	{
		OLED_ShowChinese(48,16,46,16,1); 
		
	}
	else
	{
		OLED_ShowChinese(48,16,47,16,1);
	}
}

void OLED_manualPage1(void)
{
    OLED_ShowChinese(16, 0, 53, 16, 1); 
    OLED_ShowChinese(32, 0, 54, 16, 1); 
    OLED_ShowChinese(48, 0, 15, 16, 1); 
    OLED_ShowChinese(64, 0, 16, 16, 1); 
    OLED_ShowNum(90,0,sensorData.stepCount,3,16,1);
    OLED_ShowChinese(16, 16, 31, 16, 1); 
    OLED_ShowChinese(32, 16, 32, 16, 1); 
    OLED_ShowChar(64, 16, ':', 16, 1);
}


void ManualSettingsDisplay1(void)
{
    if (driveData.LED_Flag)
    {
        OLED_ShowChinese(96, 16, 29, 16, 1); 
    }
    else
    {
        OLED_ShowChinese(96, 16, 30, 16, 1); 
    }
		
}

void OLED_settingsPage1(void)
{
   OLED_ShowChinese(16, 0, 23, 16, 1); 
   OLED_ShowChinese(32, 0, 24, 16, 1); 
   OLED_ShowChinese(48, 0, 18, 16, 1); 
   OLED_ShowChinese(64, 0, 19, 16, 1); 
   OLED_ShowChar(80, 0, ':', 16, 1); 
   OLED_ShowChinese(16, 16, 23, 16, 1);
   OLED_ShowChinese(32, 16, 24, 16, 1);
   OLED_ShowChinese(48, 16, 17, 16, 1);
   OLED_ShowChinese(64, 16, 19, 16, 1);
   OLED_ShowChar(80, 16, ':', 16, 1);
   OLED_ShowChinese(16, 32, 9, 16, 1); 
   OLED_ShowChinese(32, 32, 10, 16, 1);
   OLED_ShowChinese(48, 32, 18, 16, 1);
   OLED_ShowChinese(64, 32, 19, 16, 1);
   OLED_ShowChar(80, 32, ':', 16, 1);
   OLED_ShowChinese(16, 48, 9, 16, 1); 
   OLED_ShowChinese(32, 48, 10, 16, 1);
   OLED_ShowChinese(48, 48, 17, 16, 1);
   OLED_ShowChinese(64, 48, 19, 16, 1);
   OLED_ShowChar(80, 48, ':', 16, 1);
}


void SettingsThresholdDisplay1(void)
{
	OLED_ShowNum(90, 0, Sensorthreshold.tempminValue , 3,16,1);
	OLED_ShowNum(90, 16, Sensorthreshold.tempmaxValue , 3,16,1);
	OLED_ShowNum(90, 32, Sensorthreshold.hrMin , 3,16,1);
  OLED_ShowNum(90, 48, Sensorthreshold.hrMax , 3,16,1);
}


uint8_t SetAuto(void)  
{

    return auto_page;  
}

uint8_t SetManual(void)  
{
   
	if(KeyNum == KEY_2)  
	{
		KeyNum = 0;  
		count_m++;  
		if (count_m > 2)  
		{
			OLED_Clear();  
			count_m = 1;  
		}
	}
	return count_m;  
}

uint8_t SetSelection(void)
{
    
     if (KeyNum == KEY_2 )
    {
        KeyNum = 0;
        count_s++;
        
//        if (count_s == 5) 
//					OLED_Clear();
      if (count_s > 4)
        {
            OLED_Clear();
            count_s = 1;
        }
    }
    return count_s;
}


void OLED_manualOption(uint8_t num)
{
	switch(num)
	{
		case 1:	
			OLED_ShowChar(0, 0,'>',16,1);
			OLED_ShowChar(0,16,' ',16,1);
			OLED_ShowChar(0,32,' ',16,1);
			OLED_ShowChar(0,48,' ',16,1);
			break;
		case 2:	
			OLED_ShowChar(0, 0,' ',16,1);
			OLED_ShowChar(0,16,'>',16,1);
			OLED_ShowChar(0,32,' ',16,1);
			OLED_ShowChar(0,48,' ',16,1);
		break;
		case 3:	
			OLED_ShowChar(0, 0,' ',16,1);
			OLED_ShowChar(0,16,' ',16,1);
			OLED_ShowChar(0,32,'>',16,1);
			OLED_ShowChar(0,48,' ',16,1);
			break;
		case 4:	
			OLED_ShowChar(0, 0,' ',16,1);
			OLED_ShowChar(0,16,' ',16,1);
			OLED_ShowChar(0,32,' ',16,1);
			OLED_ShowChar(0,48,'>',16,1);
			break;
		default: break;
	}
}

void OLED_settingsOption(uint8_t num)
{
	static uint8_t prev_num = 1; 

    switch(prev_num)
    {
        case 1: OLED_ShowChar(0, 0, ' ', 16, 1); break; 
        case 2: OLED_ShowChar(0, 16, ' ', 16, 1); break; 
        case 3: OLED_ShowChar(0, 32, ' ', 16, 1); break; 
        case 4: OLED_ShowChar(0, 48, ' ', 16, 1); break; 
        case 5: OLED_ShowChar(0, 0, ' ', 16, 1); break; 
        case 6: OLED_ShowChar(0, 16, ' ', 16, 1); break; 
			  case 7: OLED_ShowChar(0, 32, ' ', 16, 1); break; 
        default: break;
    }
	switch(num)
	{
		case 1:	
			OLED_ShowChar(0, 0,'>',16,1);
			OLED_ShowChar(0,16,' ',16,1);
			OLED_ShowChar(0,32,' ',16,1);
			OLED_ShowChar(0,48,' ',16,1);
			break;
		case 2:	
			OLED_ShowChar(0, 0,' ',16,1);
			OLED_ShowChar(0,16,'>',16,1);
			OLED_ShowChar(0,32,' ',16,1);
			OLED_ShowChar(0,48,' ',16,1);
			break;
		case 3:	
			OLED_ShowChar(0, 0,' ',16,1);
			OLED_ShowChar(0,16,' ',16,1);
			OLED_ShowChar(0,32,'>',16,1);
			OLED_ShowChar(0,48,' ',16,1);
			break;
		case 4:	
			OLED_ShowChar(0, 0,' ',16,1);
			OLED_ShowChar(0,16,' ',16,1);
			OLED_ShowChar(0,32,' ',16,1);
			OLED_ShowChar(0,48,'>',16,1);
			break;
		case 5:
      OLED_ShowChar(0, 0, '>', 16, 1);
      OLED_ShowChar(0, 16, ' ', 16, 1);
      OLED_ShowChar(0, 32, ' ', 16, 1);
      OLED_ShowChar(0, 48, ' ', 16, 1);
            break;
        case 6:
      OLED_ShowChar(0, 0, ' ', 16, 1);
      OLED_ShowChar(0, 16, '>', 16, 1);
      OLED_ShowChar(0, 32, ' ', 16, 1);
      OLED_ShowChar(0, 48, ' ', 16, 1);
            break;
				case 7:
      OLED_ShowChar(0, 0, ' ', 16, 1);
      OLED_ShowChar(0, 16, ' ', 16, 1);
      OLED_ShowChar(0, 32, '>', 16, 1);
      OLED_ShowChar(0, 48, ' ', 16, 1);
            break;
		default: break;
	}
	 prev_num = num;
   OLED_Refresh();
}


void AutoControl(void)
{
	if(
     
        (sensorData.temp_valid == 1 && (sensorData.temp < Sensorthreshold.tempminValue || sensorData.temp > Sensorthreshold.tempmaxValue)) ||
        (sensorData.hrAvg > 0 && (sensorData.hrAvg < Sensorthreshold.hrMin || sensorData.hrAvg > Sensorthreshold.hrMax)) ||
        (sensorData.spo2Avg > 0 && (sensorData.spo2Avg < Sensorthreshold.spo2Min || sensorData.spo2Avg > Sensorthreshold.spo2Max)||
	       sensorData.shake) 

    )
    {
			driveData.BEEP_Flag = 1;
		}
		
		else
		{
			driveData.BEEP_Flag = 0;
		}
	
}

void ManualControl(uint8_t num)
{
	  if(KeyNum == 0) return;
	switch(num)
	{
		case 1:  
       if(KeyNum == KEY_3 || KeyNum == KEY_4)
         {
             sensorData.stepCount = 0;  
             step_num = 1;
             KeyNum = 0;  
         }
            break;
		case 2:  
            if(KeyNum == KEY_3)  
            {
                KeyNum = 0;
                driveData.LED_Flag = 1;
            }
            if(KeyNum == KEY_4) 
            {
                KeyNum = 0;
                driveData.LED_Flag = 0;
            }
            break;
		default: break;
	}
}


void Control_Manager(void)
{
    if(driveData.LED_Flag )
			   LED_On(); 
    else LED_Off();
		
    if(driveData.BEEP_Flag ) 
				  BEEP_On(); 
    else 	BEEP_Off();
}


int main(void)
{ 
    SystemInit();
    delay_init(72);  
    ADCx_Init();
    LED_Init();
    BEEP_Init();
    BEEP_Off();
    USART1_Config();
    Key_Init();
    OLED_Init(); 
    OLED_Clear();
    DS18B20_Init(); 
    IIC_init();	
    adxl345_init(); 
    Init_MAX30102();
    delay_ms(100); 
    TIM2_Init(72-1,1000-1);  
    delay_ms(200);
  	Sensorthreshold.tempminValue = 20;
  	Sensorthreshold.tempmaxValue = 30;
  	Sensorthreshold.hrMin = 70;
  	Sensorthreshold.hrMax = 95;
  	Sensorthreshold.spo2Min = 80;
  	Sensorthreshold.spo2Max = 95;
	
    while (1)
    {		
		
        SensorScan(); 	
        uint8_t current_key_num = KeyNum; 

            switch(mode)
            {
                case AUTO_MODE:
									   OLED_autoPage1();		
									   SensorDataDisplay1();	

                     AutoControl();
                     Control_Manager();
                    if(current_key_num == KEY_1)
                    {
                        mode = MANUAL_MODE;
                        count_m = 1;
                        driveData.LED_Flag = 0;
                        driveData.BEEP_Flag = 0;
											  OLED_Clear();
                        KeyNum = 0;
                    }
                    else if(current_key_num == KEY_Long1)
                    {
											  OLED_Clear(); 
                        mode = SETTINGS_MODE;
                        count_s = 1;
                        KeyNum = 0; 
                    }
                    break;
                case MANUAL_MODE:
									
									  OLED_manualPage1();
										OLED_manualOption(SetManual());
								    ManualSettingsDisplay1();
								    ManualControl(count_m);
							     	Control_Manager();
                    if(current_key_num == KEY_1)
                    {
                         mode = AUTO_MODE;
                         OLED_Clear();
                         auto_page = 1;
                         KeyNum = 0; 
                    }
										
                    break;
										
               case SETTINGS_MODE:
             {
                    uint8_t sel = SetSelection();               
                    OLED_settingsPage1();
                    SettingsThresholdDisplay1();               
                    OLED_settingsOption(sel);      
                    OLED_Refresh();
                 
                    if(current_key_num == KEY_1)
                    {      
                            mode = AUTO_MODE;
                            count_s = 1; 
                            OLED_Clear();
                            OLED_autoPage1();
                     
                        KeyNum = 0;
                    }
                    break;
            }
					}          
        
        }

      }

