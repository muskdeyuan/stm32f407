#include "stm32f4xx.h"   // Device header
#include "stdio.h"

//PA0  TIM5_CH1
void cap_init()
{
	//时钟使能
	RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd (RCC_APB1Periph_TIM5,ENABLE);
	
	//参数配置
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_DOWN;
	GPIO_InitStruct.GPIO_Speed=GPIO_High_Speed;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//复用模块
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM5);//和复用功能绑定
	
	//定时器
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = (20000-1);
	TIM_TimeBaseInitStruct.TIM_Prescaler = (8400-1);
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStruct);
	
	//定时器开始工作
	//TIM_Cmd(TIM5, ENABLE);
	
	TIM_ICInitTypeDef TIM_ICInitStruct;
	TIM_ICInitStruct.TIM_Channel=TIM_Channel_1;
	//TIM_ICInitStruct.TIM_ICFilter=0;
	TIM_ICInitStruct.TIM_ICPolarity=TIM_ICPolarity_BothEdge;//上升和下降沿
	TIM_ICInitStruct.TIM_ICPrescaler=TIM_ICPSC_DIV1;//预分频器
	TIM_ICInitStruct.TIM_ICSelection=TIM_ICSelection_DirectTI;//直接
	TIM_ICInit(TIM5,&TIM_ICInitStruct);
	
	/*
	TIM_ICInitTypeDef TIM_ICInitStruct;
	TIM_ICInitStruct.TIM_Channel=TIM_Channel_1;
	//TIM_ICInitStruct.TIM_ICFilter=0;
	TIM_ICInitStruct.TIM_ICPolarity=TIM_ICPolarity_Rising;//上升沿
	TIM_ICInitStruct.TIM_ICPrescaler=TIM_ICPSC_DIV1;//预分频器
	TIM_ICInitStruct.TIM_ICSelection=TIM_ICSelection_DirectTI;//直接
	TIM_ICInit(TIM5,&TIM_ICInitStruct);
	
	TIM_ICInitTypeDef TIM_ICInitStruct2;
	TIM_ICInitStruct2.TIM_Channel=TIM_Channel_1;
	//TIM_ICInitStruct.TIM_ICFilter=0;
	TIM_ICInitStruct2.TIM_ICPolarity=TIM_ICPolarity_Falling;//下降沿
	TIM_ICInitStruct2.TIM_ICPrescaler=TIM_ICPSC_DIV1;//预分频器
	TIM_ICInitStruct2.TIM_ICSelection=TIM_ICSelection_DirectTI;//直接
	TIM_ICInit(TIM5,&TIM_ICInitStruct2);
	*/
	//配置中断
	TIM_ITConfig(TIM5, TIM_IT_CC1|TIM_IT_Update, ENABLE);
	//    nvic内部中断
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = TIM5_IRQn;//抓中断源
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
}	

static uint32_t flag = 0;
static uint32_t val = 0;
static uint32_t cir = 0;
//中断服务子函数
//static uint32_t stat= 0;
void TIM5_IRQHandler()
{
	if(TIM_GetITStatus(TIM5,TIM_IT_CC1))//通道1电平变化
	{
		if(flag==0)//开始数数
		{
			TIM5->CCR1=0;
			TIM_Cmd(TIM5, ENABLE);
			printf("通道1电平变化按下开关！\n");
			flag=1;
		}
		else//告知我数到多少了
		{	
			TIM_Cmd(TIM5, DISABLE);
			val=(TIM5->CCR1)+cir*20000;
			printf("通道1电平变化开关上来！\n");
			flag=0;
			printf("val=%d\n",val);
			cir=0;
		}
	TIM_ClearITPendingBit(TIM5,TIM_IT_CC1);
	}
	else if(TIM_GetITStatus(TIM5,TIM_IT_Update))//tim数到一轮回
	{
	  cir++; 
		printf("Tim一轮回！\n");
	TIM_ClearITPendingBit(TIM5,TIM_IT_Update);
	}
	
	//printf("apple flower!\n");
	//TIM_ClearITPendingBit(TIM5,TIM_IT_Update);
	/*
	if(TIM_GetITStatus(TIM5,TIM_IT_CC1))
	{
		if(flag == 0)
		{
			TIM5->CCR1=0;
			TIM_Cmd(TIM5, ENABLE);
			flag = 1;
		}
		else
		{
			TIM_Cmd(TIM5, DISABLE);
			val=TIM_GetCapture1(TIM5);//相当于value    拿出CCR的数值
			
			val = val + cir*5000;
			printf("val = %d\n",val);
			flag=0;
			cir =0;
		}
		 TIM_ClearITPendingBit(TIM5,TIM_IT_CC1);

	}
	if(TIM_GetITStatus(TIM5,TIM_IT_Update))
	{
	   cir++; 
		//清楚中断标记
     TIM_ClearITPendingBit(TIM5,TIM_IT_Update);
	}
	*/
}
