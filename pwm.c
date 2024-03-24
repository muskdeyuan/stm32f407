#include "stm32f4xx.h"                  // Device header
#include "delay.h"
//PC6 TIM8_ch1
void tim_pwm_init()
{
	//时钟使能，GPIOC,TIM8
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);
	
	//GPIO参数配置，复用
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF;//复用？
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;//推挽
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_6;//PC6
	//GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed=GPIO_High_Speed;
	GPIO_Init(GPIOC,&GPIO_InitStruct);
	
	//复用定时器
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM8);
	
	//定时器配置，告诉定时器工作模式
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=(5000-1);
	TIM_TimeBaseInitStruct.TIM_Prescaler=(8400-1);
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM8,&TIM_TimeBaseInitStruct);	
	
	//让定时器开始工作-->cmd
	TIM_Cmd(TIM8,ENABLE);
	
	//通道参数配置
	TIM_OCInitTypeDef TIM_OCInitStruct;
	TIM_OCInitStruct.TIM_OCIdleState=TIM_OCIdleState_Set;    //空闲状态
	
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;             //确定哪一个是有效电平
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High;     //有效电平到底是高电平还是低电平
	
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse=0;      //脉冲宽度           //占空比
	TIM_OC1Init(TIM8,&TIM_OCInitStruct);

	//打通通道1
	TIM_OC1PreloadConfig(TIM8,TIM_OCPreload_Enable);
	
	//配置PWM输出开始
	TIM_CtrlPWMOutputs(TIM8,ENABLE);
	
}
void tim_pwm_run()
{
	
	TIM_SetCompare1(TIM8,5);
	delay_ms(1000);
	
	
	TIM_SetCompare1(TIM8,50);
	delay_ms(1000);
}

