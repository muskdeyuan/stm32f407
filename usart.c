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
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);//ʱ��ʹ��A��,��ҪPA10��PA9����
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//ʹ��usart1
	
	//GPIO�������ã�����GPIO PA9��PA10 ��ι���
	GPIO_InitTypeDef gpio_struct;
	gpio_struct.GPIO_Mode=GPIO_Mode_AF;//����ģʽ
	gpio_struct.GPIO_OType=GPIO_OType_PP;//��Ӱ�죬����һ��������
	gpio_struct.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_10;
	gpio_struct.GPIO_PuPd=GPIO_PuPd_NOPULL;
	gpio_struct.GPIO_Speed=GPIO_High_Speed;
	GPIO_Init(GPIOA,&gpio_struct);//��PA9��PA10֪���Ը���ģʽ����
	
	//���߸���ģ�飬������Ҫ������һ�����ܣ�����ѡ����usart
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

	//usart1�������ã���������ι���
	USART_InitTypeDef usart_struct;
	usart_struct.USART_BaudRate= 115200;  //����
	usart_struct.USART_HardwareFlowControl= USART_HardwareFlowControl_None;  //���أ�Ŀǰ���������//usartҲ�ǿ���Э��
	usart_struct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;  //�Ƚ����ַ���
	usart_struct.USART_Parity= USART_Parity_No;  //У��λ���Э���ʱ��Ū
	usart_struct.USART_StopBits= USART_StopBits_1;  //ֹͣλ
	usart_struct.USART_WordLength= USART_WordLength_8b;  //��Ч����
	
	USART_Init(USART1,&usart_struct);
	
	USART_Cmd(USART1, ENABLE);//��usart����
	
	//���ߴ��ڣ���Ҫ���ж�
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel=USART1_IRQn;//��Ӧ�ж�ͨ��
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=7;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
	
	NVIC_Init(&NVIC_InitStruct);


}

void USART1_IRQHandler(void)
{
	//��Ľ�����������
	if(USART_GetITStatus(USART1, USART_IT_RXNE))
	{
		uint32_t i=USART_ReceiveData(USART1);
		//printf("IRQ i=%c\n",i);
		USART_SendData(USART1,i);
		//USART_SendData(USART1,'\n');
	}
	USART_ClearITPendingBit(USART1, USART_IT_RXNE);
}

