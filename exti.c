#include "stm32f4xx.h"                  // Device header
#include "BitBand.h"
#include "stdio.h"
#include "delay.h"

void exti_key_init()
{
	//时钟配置
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	
	//给GPIO参数配置
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_3|GPIO_Pin_2;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed=GPIO_High_Speed;
	
	GPIO_Init(GPIOE,&GPIO_InitStruct);
	//把GPIOE组的第2个引脚连接到EXTI2
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource2);
	//把GPIOE组的第3个引脚连接到EXTI3
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource3);
	
	//EXTI参数配置
	//告诉EXTI2、3，看见上升沿，就给NVIC发送中断信号
	EXTI_InitTypeDef EXTI_InitStruct;
	
	EXTI_InitStruct.EXTI_Line=EXTI_Line2|EXTI_Line3;
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Rising;
	
	EXTI_Init(&EXTI_InitStruct);
	
	//分组方式，2位给抢占优先级，2位给响应优先级
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//从此处判断核心需求数量（2）
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel=EXTI2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;
	
	NVIC_Init(&NVIC_InitStruct);
	
	
	//分组方式，2位给抢占优先级，2位给响应优先级
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);//从此处判断核心需求数量（2）
	
	NVIC_InitStruct.NVIC_IRQChannel=EXTI3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;
	
	NVIC_Init(&NVIC_InitStruct);
	
}

//中断服务子函数，给EXTI2服务
void EXTI2_IRQHandler()
{
	if(EXTI_GetITStatus(EXTI_Line2))
	{
		printf("key2 apple tree\n");
	}
	
	EXTI_ClearITPendingBit(EXTI_Line2);
}
	

//中断服务子函数，给EXTI3服务
void EXTI3_IRQHandler()
{
	if(EXTI_GetITStatus(EXTI_Line3))
	{
		printf("key3 apple tree\n");
	}
	
	EXTI_ClearITPendingBit(EXTI_Line3);
}
	
