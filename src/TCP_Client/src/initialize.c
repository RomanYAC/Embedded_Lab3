#include "initialize.h"

extern int8_t messageIndex;

uint32_t usTicks;
 
void SysTick_Handler()
{
    if (usTicks != 0)usTicks--;
}

void initializeDelay(void)
{
	  SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock / 1000000);
}

void initializeButtons (void)
{
	GPIO_InitTypeDef 	GPIO_Init_Struct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	
	GPIO_Init_Struct.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_9|GPIO_Pin_6;
	GPIO_Init_Struct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init_Struct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init_Struct.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_Struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_Init_Struct);
	
	GPIO_Init_Struct.GPIO_Pin = GPIO_Pin_15;
	GPIO_Init_Struct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init_Struct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init_Struct.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_Struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_Init_Struct);
}

void initializeInterruptions(void)
{
	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI15_10_IRQn|EXTI9_5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource6);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource8);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource9);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource11);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource15);

	EXTI_InitStruct.EXTI_Line = EXTI_Line6|EXTI_Line8|EXTI_Line9|EXTI_Line11|EXTI_Line15;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStruct);
}

void EXTI9_5_IRQHandler(void) 
{
	if (EXTI_GetITStatus(EXTI_Line6) != RESET) 
	{
		messageIndex = 1;
		EXTI_ClearITPendingBit(EXTI_Line6);
	}
	if (EXTI_GetITStatus(EXTI_Line8) != RESET) 
	{
		messageIndex = 2;
		EXTI_ClearITPendingBit(EXTI_Line8);
	}
	if (EXTI_GetITStatus(EXTI_Line9) != RESET) 
	{
		messageIndex = 3;
		EXTI_ClearITPendingBit(EXTI_Line9);
	}
}

void EXTI15_10_IRQHandler(void) 
{
	if (EXTI_GetITStatus(EXTI_Line15) != RESET) 
	{
		messageIndex = 4;
		EXTI_ClearITPendingBit(EXTI_Line15);
	}
	if (EXTI_GetITStatus(EXTI_Line11) != RESET) 
	{
		messageIndex = 5;
		EXTI_ClearITPendingBit(EXTI_Line11);
	}
}

void Delay(uint32_t miliseconds)
{
    while (miliseconds--) 
		{
			usTicks = 1000;
			while (usTicks);
		}
}
