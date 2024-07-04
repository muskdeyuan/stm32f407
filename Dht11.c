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
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;//协议都配推挽
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
	//更改GPIO引脚为输出模式
		GPIO_InitTypeDef GPIO_InitStruct;
	//参数初始化
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;//协议都配推挽
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed=GPIO_High_Speed;
	GPIO_Init(GPIOG,&GPIO_InitStruct);
	//要告诉DHT11我要数据
	PGout(9)=0;//拉低电平
	delay_ms(20);//为了发送一个大于18us的低电平信号
	PGout(9)=1;//拉高电平
	
	delay_us(30);//协议规定，发送信号后续需要等20-40us，我们取中间30us
	
	//进入数据获取阶段
	//更改GPIO引脚为输入模式
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN;
	GPIO_Init(GPIOG,&GPIO_InitStruct);
//	printf("我到输入模式了\n");
	//等待回响信号，说明DHT11已经拿到了数据，准备发给你，看你还在不在？
	time=0;
	while(PGin(9)==1)//阻塞等待低电平到来，
	{
		delay_us(1);
		time++;
		if(time>=1000000)//排除没有收到发送信号情况
		{
			printf("回响信号超时");
		}
	}		
	time=0;
	while(PGin(9)==0)//协议规定需要80us的低电平
	{
		delay_us(1);
		time++;
		if(time>=100)
		{
			printf("回响信号的低电平超时\n");
		}
	}
	time=0;
	while(PGin(9)==1)//协议规定需要80us的高电平
	{
		delay_us(1);
		time++;
		if(time>=100)
		{
			printf("回响信号的高电平超时\n");
		}
	}
//	printf("回响信号完毕\n");
	//有效数据获取
	for(i=0;i<5;i++)
	{
		data[i]=0;
//			printf("i到第%d个数据了\n",i);
		for(j=0;j<8;j++)
		{
			while(PGin(9)==0);//度过间隔信号
			delay_us(40);
//			printf("jjjjj到第%d个数据了\n",j);
			if(PGin(9)==1)
			{
				data[i] |= 1<<(7-j);
				while(PGin(9)==1);
			}
		}
	}
	printf("data = %d,%d,%d,%d\n",data[0],data[1],data[2],data[3]);
}

