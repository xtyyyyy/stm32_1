#include "./BSP/Red/Red.h"
#include "./SYSTEM/usart/usart.h"

void RED_GPIO_Init (void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	
	R1_RCC();
	GPIO_InitStructure.Pin = R1_Pin;
	HAL_GPIO_Init(R1_PORT,&GPIO_InitStructure);
	
	R2_RCC();
	GPIO_InitStructure.Pin = R2_Pin;
	HAL_GPIO_Init(R2_PORT,&GPIO_InitStructure);
	
	R3_RCC();
	GPIO_InitStructure.Pin = R3_Pin;
	HAL_GPIO_Init(R3_PORT,&GPIO_InitStructure);
	
	R4_RCC();
	GPIO_InitStructure.Pin = R3_Pin;
	HAL_GPIO_Init(R3_PORT,&GPIO_InitStructure);
	
	R5_RCC();
	GPIO_InitStructure.Pin = R3_Pin;
	HAL_GPIO_Init(R3_PORT,&GPIO_InitStructure);
}

