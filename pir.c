#include "stm32f4xx.h"                  // Device header


void Pir_Init()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);
	
	GPIO_InitTypeDef gpio_init;
	
	gpio_init.GPIO_Mode=GPIO_Mode_IN;
//	gpio_init.GPIO_OType=GPIO_OType_OD;
	gpio_init.GPIO_Pin=GPIO_Pin_14;
	gpio_init.GPIO_PuPd=GPIO_PuPd_DOWN;//默认为低电平
	gpio_init.GPIO_Speed=GPIO_High_Speed;
	
	GPIO_Init(GPIOF,&gpio_init);
}
