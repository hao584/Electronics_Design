#include "key.h"

struct keys key[3];

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM1 )
	{
		key[0].key_sta  = HAL_GPIO_ReadPin (GPIOC,GPIO_PIN_1 );
		key[1].key_sta  = HAL_GPIO_ReadPin (GPIOC,GPIO_PIN_2 );
		key[2].key_sta  = HAL_GPIO_ReadPin (GPIOC,GPIO_PIN_3 );
	}
	for (int i=0;i<3;i++)
	{
		switch(key[i].judge_sta )
		{
			case 0:
			{
				if(key[i].key_sta  ==0)
				{key[i].judge_sta =1;
				 key[i].key_time = 0;}
				
			}break;
			case 1:
			{
				if(key[i].key_sta  ==0){key[i].judge_sta =2;}
				else {key[i].judge_sta =0;}
			}break;
			case 2:
			{
				if(key[i].key_sta  ==1){key[i].judge_sta =0;
					if(key[i].key_time <70){key[i].press =1;}		
					else {key[i].long_press =1;}
			  }
				else {key[i].key_time ++;}
				break;
		  }
	  }
  }
}
