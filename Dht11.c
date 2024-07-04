#include "stm32f4xx.h"                  // Device header
#include "BitBand.h"             // Component selection
#include "delay.h"
#include "stdio.h"
void Dht11_Init()
{
	//PG9  
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;//Э�鶼������
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed=GPIO_High_Speed;
	GPIO_Init(GPIOG,&GPIO_InitStruct);
}
void Dht11_Run()
{
	uint32_t time=0;
	uint32_t i=0;
	uint32_t j=0;
	uint32_t data[5]={0};
	//����GPIO����Ϊ���ģʽ
		GPIO_InitTypeDef GPIO_InitStruct;
	//������ʼ��
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;//Э�鶼������
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed=GPIO_High_Speed;
	GPIO_Init(GPIOG,&GPIO_InitStruct);
	//Ҫ����DHT11��Ҫ����
	PGout(9)=0;//���͵�ƽ
	delay_ms(20);//Ϊ�˷���һ������18us�ĵ͵�ƽ�ź�
	PGout(9)=1;//���ߵ�ƽ
	
	delay_us(30);//Э��涨�������źź�����Ҫ��20-40us������ȡ�м�30us
	
	//�������ݻ�ȡ�׶�
	//����GPIO����Ϊ����ģʽ
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN;
	GPIO_Init(GPIOG,&GPIO_InitStruct);
//	printf("�ҵ�����ģʽ��\n");
	//�ȴ������źţ�˵��DHT11�Ѿ��õ������ݣ�׼�������㣬���㻹�ڲ��ڣ�
	time=0;
	while(PGin(9)==1)//�����ȴ��͵�ƽ������
	{
		delay_us(1);
		time++;
		if(time>=1000000)//�ų�û���յ������ź����
		{
			printf("�����źų�ʱ");
		}
	}		
	time=0;
	while(PGin(9)==0)//Э��涨��Ҫ80us�ĵ͵�ƽ
	{
		delay_us(1);
		time++;
		if(time>=100)
		{
			printf("�����źŵĵ͵�ƽ��ʱ\n");
		}
	}
	time=0;
	while(PGin(9)==1)//Э��涨��Ҫ80us�ĸߵ�ƽ
	{
		delay_us(1);
		time++;
		if(time>=100)
		{
			printf("�����źŵĸߵ�ƽ��ʱ\n");
		}
	}
//	printf("�����ź����\n");
	//��Ч���ݻ�ȡ
	for(i=0;i<5;i++)
	{
		data[i]=0;
//			printf("i����%d��������\n",i);
		for(j=0;j<8;j++)
		{
			while(PGin(9)==0);//�ȹ�����ź�
			delay_us(40);
//			printf("jjjjj����%d��������\n",j);
			if(PGin(9)==1)
			{
				data[i] |= 1<<(7-j);
				while(PGin(9)==1);
			}
		}
	}
	printf("data = %d,%d,%d,%d\n",data[0],data[1],data[2],data[3]);
}

