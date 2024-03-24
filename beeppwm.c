#include "stm32f4xx.h"                  // Device header
#include "Delay.h"
#include "BItBand.h"
//PC6 TIM8_ch1
void tim_beeppwm_init()
{
	//时钟使能，GPIOC,TIM8
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM13,ENABLE);
	
	//GPIO参数配置，复用
	 GPIO_InitTypeDef GPIO_InitStructure;
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
   GPIO_Init(GPIOF, &GPIO_InitStructure);

	//复用定时器
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM13);
	
	//定时器配置，告诉定时器工作模式
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=(5000-1);
	TIM_TimeBaseInitStruct.TIM_Prescaler=(8400-1);
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM13,&TIM_TimeBaseInitStruct);	
	
	//让定时器开始工作-->cmd
	TIM_Cmd(TIM13,ENABLE);
	
	//通道参数配置
	TIM_OCInitTypeDef TIM_OCInitStruct;
	TIM_OCInitStruct.TIM_OCIdleState=TIM_OCIdleState_Set;    //空闲状态
	
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;             //确定哪一个是有效电平
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High;     //有效电平到底是高电平还是低电平
	
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse=0;      //脉冲宽度           //占空比
	TIM_OC1Init(TIM13,&TIM_OCInitStruct);

	//打通通道1
	TIM_OC1PreloadConfig(TIM13,TIM_OCPreload_Enable);
	
	//配置PWM输出开始
	TIM_CtrlPWMOutputs(TIM13,ENABLE);
	
}

/*
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
*/

void tim_beeppwm_run()
{
		TIM_SetCompare1(TIM13,5);
		PFout(8) = 1;
		delay_ms(1000);
	
		TIM_SetCompare1(TIM13,10);
		PFout(8) = 0;
		delay_ms(100);
}

