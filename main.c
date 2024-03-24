#include "stm32f4xx.h"                  // Device header
#include "led.h"
#include "key.h"
#include "BitBand.h"
#include "pir.h"
#include "delay.h"
#include <stdio.h>
#include "usart.h"
#include "Hysrf.h"
#include "Beep.h" 
#include "exti.h"
#include "Tim.h"
#include "pwm.h"
#include "beeppwm.h"
#include "cap.h"

int main()
{
	uint32_t time=0;
	uint32_t i = 0;
	//Led_Init();
	//Pir_Init();
	Usart_Init();
	//Hysrf05_Init();
  //Beep_Init();  
	//exti_key_init();
	//Time_Init();
	//tim_pwm_init();
	//tim_beeppwm_init();
	cap_init();
	//printf("pwm init is ok");
	int s=0;
	//定时器配置

	while(1)
	{	
		//printf("not apple flower\n");
		//tim_pwm_run();
		//printf("run is ok");
	  //tim_beeppwm_run();
	//	i = USART_ReceiveData(USART1);
		//printf("%c\n",i);
	//SysTick_Config(SystemCoreClock / 100);
		//delay_ms(1000);
	}

}

/*	//中断服务子函数
	void SysTick_Handler(void)
{
	printf("hello apple\n");
}
*/

