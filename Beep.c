#include "stm32f4xx.h"                  // Device header
#include "BItBand.h"
#include "Delay.h"
#include<stdio.h>

static GPIO_InitTypeDef  GPIO_InitStructure;
void Beep_Init(void)
{
  /* GPIOF Peripheral clock enable  */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	
 
  /* Configure PF9 in output pushpull mode */
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
   GPIO_Init(GPIOF, &GPIO_InitStructure);

}
void Beep_Once(uint32_t time,uint32_t fre)
{
	uint32_t fre_time = 500000/fre;
	while(time--)
	{
		PFout(8) = 1;
		delay_us(fre_time);

		PFout(8) = 0;
		delay_us(fre_time);
	}
}

