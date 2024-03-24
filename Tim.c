#include "stm32f4xx.h"                  // Device header
#include "stdio.h"

//定时器的初始化
void Time_Init()
{
	//时钟使能
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//1
	//参数配置，84M 84 000 000
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;//3
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;//4
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=(5000-1);//工作量（路程），每一趟执行一次中断
	TIM_TimeBaseInitStruct.TIM_Prescaler=(8400-1);//84M除以8400=10 000，工作速度（10 000/s）
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);//2
	
	//让定时器开始工作
	
	TIM_Cmd(TIM2,ENABLE);
	
	//定时器开启中断,看到TIM_Period，数到头，给NVIC说一声
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	
	//中断分组
	//分组方式，2位给抢占优先级，2位给响应优先级
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//从此处判断核心需求数量（2）
	
	//NVIC参数配置
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;
	
	NVIC_Init(&NVIC_InitStruct);
	
}
void TIM2_IRQHandler()
{
	//信号判断，中断进一步确认
	if(TIM_GetITStatus(TIM2,TIM_IT_Update))
	{
		printf("not apple tree!\n");
	}
	//中断信号清除
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
}













