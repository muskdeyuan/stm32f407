#include "stm32f4xx.h"                  // Device header
#include "stdio.h"

	//PF7  
void ADC_Light_Init()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AN;//模拟
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_7;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;//不确定电压，
	GPIO_InitStruct.GPIO_Speed=GPIO_High_Speed;
	GPIO_Init(GPIOF,&GPIO_InitStruct);
	
	//ADC和模拟模块绑定，引脚只走它一个，所以配复用就不需要啦！
	
	//ADC参数配置
	ADC_InitTypeDef ADC_InitStruct;
	ADC_InitStruct.ADC_ContinuousConvMode=DISABLE;
	ADC_InitStruct.ADC_DataAlign=ADC_DataAlign_Right;
	//ADC_InitStruct.ADC_ExternalTrigConv=ADC_ExternalTrigConv_T1_CC3;
	ADC_InitStruct.ADC_ExternalTrigConvEdge=ADC_ExternalTrigConvEdge_None;
	ADC_InitStruct.ADC_NbrOfConversion=1;//转化列表
	ADC_InitStruct.ADC_Resolution=ADC_Resolution_12b;
	ADC_InitStruct.ADC_ScanConvMode=DISABLE;
	ADC_Init(ADC3,&ADC_InitStruct);
	
	//开始工作
	ADC_Cmd(ADC3,ENABLE);
	
	//通道配置
	ADC_RegularChannelConfig(ADC3, ADC_Channel_5,1,ADC_SampleTime_3Cycles);
	
}

void Light_GetData()
{
	//软件开启测量和转换工作
	ADC_SoftwareStartConv(ADC3);
	//等待转换数据完成
	while(ADC_GetSoftwareStartConvStatus(ADC3)){}
	
		uint32_t val=ADC_GetConversionValue(ADC3);
		printf("val = %d\n",val);
	

}
