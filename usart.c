#include "stm32f4xx.h"                  // Device header
#include <stdio.h>

int fputc(int ch,FILE* pf)
{
    USART_SendData(USART1,ch);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);	
	return ch;
}


void Usart_Init()
{
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);//时钟使能A组,需要PA10和PA9工作
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//使能usart1
	
	//GPIO参数配置，告诉GPIO PA9和PA10 如何工作
	GPIO_InitTypeDef gpio_struct;
	gpio_struct.GPIO_Mode=GPIO_Mode_AF;//复用模式
	gpio_struct.GPIO_OType=GPIO_OType_PP;//不影响，但是一般配推挽
	gpio_struct.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_10;
	gpio_struct.GPIO_PuPd=GPIO_PuPd_NOPULL;
	gpio_struct.GPIO_Speed=GPIO_High_Speed;
	GPIO_Init(GPIOA,&gpio_struct);//让PA9和PA10知道以复用模式工作
	
	//告诉复用模块，到底想要复用哪一个功能，我们选择了usart
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

	//usart1参数配置，告诉它如何工作
	USART_InitTypeDef usart_struct;
	usart_struct.USART_BaudRate= 115200;  //速率
	usart_struct.USART_HardwareFlowControl= USART_HardwareFlowControl_None;  //流控，目前不启用这块//usart也是控制协议
	usart_struct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;  //既接收又发送
	usart_struct.USART_Parity= USART_Parity_No;  //校验位，深化协议的时候弄
	usart_struct.USART_StopBits= USART_StopBits_1;  //停止位
	usart_struct.USART_WordLength= USART_WordLength_8b;  //有效负载
	
	USART_Init(USART1,&usart_struct);
	
	USART_Cmd(USART1, ENABLE);//让usart工作
	
	//告诉串口，我要用中断
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel=USART1_IRQn;//对应中断通道
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=7;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
	
	NVIC_Init(&NVIC_InitStruct);


}

void USART1_IRQHandler(void)
{
	//真的接收数据了吗
	if(USART_GetITStatus(USART1, USART_IT_RXNE))
	{
		uint32_t i=USART_ReceiveData(USART1);
		//printf("IRQ i=%c\n",i);
		USART_SendData(USART1,i);
		//USART_SendData(USART1,'\n');
	}
	USART_ClearITPendingBit(USART1, USART_IT_RXNE);
}