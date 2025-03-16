#ifndef __Line_H
#define __Line_H

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"


void RED_GPIO_Init(void);


#define R1_RCC()			do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)
#define R1_PORT				GPIOC
#define R1_Pin				GPIO_PIN_0

#define R2_RCC()			do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)
#define R2_PORT				GPIOC
#define R2_Pin				GPIO_PIN_1

#define R3_RCC()			do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)
#define R3_PORT				GPIOC
#define R3_Pin				GPIO_PIN_2

#define R4_RCC()			do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)
#define R4_PORT				GPIOC
#define R4_Pin				GPIO_PIN_3

#define R5_RCC()			do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)
#define R5_PORT				GPIOC
#define R5_Pin				GPIO_PIN_4

#define R1					HAL_GPIO_ReadPin(R1_PORT,R1_Pin)
#define R2					HAL_GPIO_ReadPin(R2_PORT,R2_Pin)
#define R3					HAL_GPIO_ReadPin(R3_PORT,R3_Pin)
#define R4					HAL_GPIO_ReadPin(R4_PORT,R4_Pin)
#define R5					HAL_GPIO_ReadPin(R5_PORT,R5_Pin)




#endif

