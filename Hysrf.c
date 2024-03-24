#include "stm32f4xx.h"                  // Device header
#include "BitBand.h"
#include "delay.h"
//#include "beep.h"
#include<stdio.h>

void Hysrf05_Init()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);
	//PF12输出引脚-->Trig
	GPIO_InitTypeDef GPIO_Initstruct;
	GPIO_Initstruct.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_Initstruct.GPIO_OType=GPIO_OType_PP;
	GPIO_Initstruct.GPIO_Pin=GPIO_Pin_12;
	GPIO_Initstruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_Initstruct.GPIO_Speed=GPIO_High_Speed;
	
	GPIO_Init(GPIOF,&GPIO_Initstruct);

	//PF11输入引脚-->Echo
	GPIO_Initstruct.GPIO_Mode=GPIO_Mode_IN;
	GPIO_Initstruct.GPIO_OType=GPIO_OType_OD;
	GPIO_Initstruct.GPIO_Pin=GPIO_Pin_11;
	GPIO_Initstruct.GPIO_PuPd=GPIO_PuPd_DOWN;
	GPIO_Initstruct.GPIO_Speed=GPIO_High_Speed;
	
	GPIO_Init(GPIOF,&GPIO_Initstruct);

}

uint32_t Get_S_Hysrf05()
{
	uint32_t time=0;
	while(1)
	{
		//给予10us的高电压,完成触发动作
		PFout(12)=1;
		delay_us(10);
		//获得信号
		PFout(12)=0;
		
		while(PFin(11)==0)
		{			
			time++;
			delay_us(10);
			if(time>=2000)
			{
				printf("time out\n");
				break;				
			}
		}
		//等待PF11（Echo）为高电压，统计时间
		time=0;
		while(PFin(11)==1)
		{
			//用time的值计算高电平维持了几微秒
			time++;
			delay_us(8);
		}
//			delay_ms(1000);
	//	  printf("time=%d\n",time); 
		  int s=time*17;
			s = s/10;
		  printf("距离为%d mm\n",s);
		  time=0;
		
	return s;
	}
}
