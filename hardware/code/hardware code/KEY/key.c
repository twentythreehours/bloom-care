#include "key.h"



uint16_t		key1_cnt;				
uint8_t			key1_short_flag;	
uint8_t			key1_lock_flag;		
uint8_t			key1_long_flag;		




uint16_t	key2_cnt;					
uint8_t		key2_short_flag;	
uint8_t		key2_lock_flag;		
uint8_t		key2_long_flag;		




uint16_t	key3_cnt;					
uint16_t	key3_cnt2;				
uint8_t		key3_short_flag;	
uint8_t		key3_lock_flag;		






uint16_t	key4_cnt;					
uint16_t	key4_cnt2;				
uint8_t		key4_short_flag;	
uint8_t		key4_lock_flag;		


u8 KeyNum = 0;							
/**
  * @brief  
  * @param  
  * @retval 
  */
void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = KEY1_GPIO_PIN | KEY2_GPIO_PIN | KEY3_GPIO_PIN | KEY4_GPIO_PIN ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(KEY_PORT, &GPIO_InitStructure);
	
}

/**
  * @brief  
  * @param  
  * @retval 
  */
void Key_scan(void)
{
	

	if(KEY1) 												  
	{
		key1_lock_flag = 0;					    
		key1_cnt = 0; 								   
		if(key1_short_flag)
		{
			key1_short_flag = 0;			     
			KeyNum = KEY1_Short; 					 
		}
		if(key1_long_flag)
		{
			key1_long_flag = 0;						 
			KeyNum = KEY1_Long; 						
		}
	}
 										
	else if(!key1_lock_flag)
	{
		key1_cnt++; 											
		if(key1_cnt > KEY_DELAY_TIME)		
		{
			key1_cnt = 0; 									
			key1_short_flag = 1;						
			key1_long_flag = 0;							
			key1_lock_flag = 1; 						
		}
	}
	
		else
	{
		key1_cnt++;												
		
		if(key1_cnt > KEY_LONG_TIME	)			
			
			key1_short_flag = 0;						
			key1_long_flag = 1;							
	}

/*-------------------------------------------------------------------------------------------------*/		
	
	
	if(KEY2) 														
	{
		key2_lock_flag = 0; 							 
		key2_cnt = 0; 										
		if(key2_short_flag)
		{
			key2_short_flag = 0; 						 
			KeyNum = KEY2_Short; 					
		}
		if(key2_long_flag)
		{
			key2_long_flag = 0;							
			KeyNum = KEY2_Long;							
		}
	}
	
												
	else if(!key2_lock_flag)
	{
		key2_cnt++; 											
		if(key2_cnt > KEY_DELAY_TIME)
		{
			key2_cnt = 0; 										
			key2_short_flag = 1;
			key2_long_flag = 0;								
			key2_lock_flag = 1; 							
		}
	}
		else
	{
		key2_cnt++;													
		if(key2_cnt > KEY_LONG_TIME)
		{
			key2_short_flag = 0;							
			key2_long_flag = 1;								
		}
	}
	
	
/*-------------------------------------------------------------------------------------------------*/	
	
	

	if(KEY3) 																  
	{
		key3_lock_flag = 0; 									   
		key3_cnt = 0; 												  
				 
	}
														 
	else if(!key3_lock_flag)
	{
		key3_cnt++; 														 
		if(key3_cnt > KEY_DELAY_TIME)
		{
			key3_cnt = 0; 												 
			KeyNum = KEY3_Short; 										
			key3_lock_flag = 1; 									  
		}
	}
																						  
	else if(key3_cnt < KEY_Continue_TIME)				
	{
		key3_cnt++;															
	}
																							
	else																				
	{

		key3_cnt2++;															
		if(key3_cnt2 > KEY_Continue_Trigger_TIME )
		{
			key3_cnt2 = 0;													
			KeyNum = KEY3_Lianji;										
		}
		

	
	}
	
/*-------------------------------------------------------------------------------------------------*/		
	
	
	if(KEY4) 																		   
	{
		key4_lock_flag = 0; 											  
		key4_cnt = 0; 														   
	}
	else if(!key4_lock_flag)
	{
		key4_cnt++; 															   
		if(key4_cnt > KEY_DELAY_TIME)
		{
			key4_cnt = 0; 													  
			KeyNum =  KEY4_Short; 										
			key4_lock_flag = 1; 											
		}
	}
	else if(key4_cnt < KEY_Continue_TIME)
	{
		key4_cnt++;																	 
	}
	else																						
	{	
		key4_cnt2++;																	
		if(key4_cnt2 > KEY_Continue_Trigger_TIME)
		{
			key4_cnt2 = 0;														  
			KeyNum = KEY4_Lianji;												
		}

	
	}
}



















