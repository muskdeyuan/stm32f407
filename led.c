#include "stm32f4xx.h"                  // Device header
#include "BItBand.h"
#include "delay.h"

void Led_Init()
{
	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);
	
	GPIO_InitTypeDef gpio_init;
	
	gpio_init.GPIO_Mode=GPIO_Mode_OUT;
	gpio_init.GPIO_OType=GPIO_OType_PP;
	gpio_init.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15|GPIO_Pin_2;
	gpio_init.GPIO_PuPd=GPIO_PuPd_NOPULL;
	gpio_init.GPIO_Speed=GPIO_High_Speed;
	
	GPIO_Init(GPIOF,&gpio_init);
	
			PFout(2)=1;
	PFout(9)=1;
	PFout(10)=1;
	PFout(12)=1;
	PFout(13)=1;
	PFout(14)=1;
	PFout(15)=1;
}


void Traffic_Led()
{
	
//SysTick_Config(SystemCoreClock/100);//每0.01s调用中断
	
	
	  PFout(9)=0;
		 PFout(10)=1;
		 PFout(12)=1;	
		delay_ms(1000);
		
		PFout(9)=1;
		 PFout(10)=0;
		 PFout(12)=1;	
		delay_ms(1000);
		
		 PFout(9)=1;
		 PFout(10)=1;
		 PFout(12)=0;	
		delay_ms(1000);
}

/*


void SysTick_Handler(void)//滴答中断调用
{
	
	
		static uint32_t i=0;
		i++;
		if(i==100)//1s
		{
			
		 PFout(9)=0;
		 PFout(10)=1;
		 PFout(12)=1;		
		}
		if(i==200)
		{
		 PFout(9)=1;
		 PFout(10)=0;
		 PFout(12)=1;	
		}
		if(i==300)
		{
		 i=0;
		 PFout(9)=1;
		 PFout(10)=1;
		 PFout(12)=0;	
		}
		
	}
*/	

