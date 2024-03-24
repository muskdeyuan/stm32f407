#include "stm32f4xx.h"  

void delay_ms(uint32_t ms)
{
	while(ms--)
		{
	SysTick->CTRL=0;//使其工作
	SysTick->LOAD=(SystemCoreClock/1000);//一毫秒
	SysTick->VAL=0;//清空
	SysTick->CTRL=5;//让内部时钟开始干活
	while((SysTick->CTRL & 0x00010000)==0);
	SysTick->CTRL=0;
		}
}

void delay_us(uint32_t us)
{
	while(us--)
		{
	SysTick->CTRL=0;//使其工作
	SysTick->LOAD=(SystemCoreClock/1000000);//一微秒
	SysTick->VAL=0;//清空
	SysTick->CTRL=5;//让内部时钟开始干活
	while((SysTick->CTRL & 0x00010000)==0);
	SysTick->CTRL=0;
		}
}


