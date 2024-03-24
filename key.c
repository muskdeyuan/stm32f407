#include "stm32f4xx.h"                  // Device header

void Key_Init()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	
	GPIO_InitTypeDef gpio_key;
	
	gpio_key.GPIO_Mode=GPIO_Mode_IN;
	gpio_key.GPIO_OType=GPIO_OType_OD;
	gpio_key.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
	gpio_key.GPIO_PuPd=GPIO_PuPd_UP;
	gpio_key.GPIO_Speed=GPIO_High_Speed;
	
	GPIO_Init(GPIOE,&gpio_key);
}

