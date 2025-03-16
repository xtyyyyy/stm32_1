#ifndef _Motor_H
#define _Motor_H

#include "./SYSTEM/sys/sys.h"

void H_L_GPIO_Init(void);
void Motor_Init(void);
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim);
void Set_L(int16_t s);
void Set_R(int16_t s);
void B_Set_L(int16_t s);
void B_Set_R(int16_t s);

void GET(void);


#define MaxS		980
#define MinS 		0

  
//***************************************Ç°ÂÖ*****************************   *******/
//Motor
#define TIMx								TIM2
#define TIM_CLK_ENABLE()					do{ __HAL_RCC_TIM2_CLK_ENABLE(); }while(0)
#define L_TIM_CHANNEL						TIM_CHANNEL_3
#define R_TIM_CHANNEL						TIM_CHANNEL_4
#define TIMx_IRQn                   		TIM2_IRQn
#define TIMx_IRQHandler      	   	    	TIM2_IRQHandler


//L

#define F_L_PWM_PORT							GPIOA
#define F_L_PWM_PIN							GPIO_PIN_2
#define F_L_TIMX_GPIO_CLK_ENABLE()			do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)  					


#define F_L_H_GPIO_CLK_ENABLE() 				do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)
#define F_L_H_GPIO_PORT						GPIOA
#define F_L_H_GPIO							GPIO_PIN_4
#define F_L_L_GPIO_CLK_ENABLE() 				do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)
#define F_L_L_GPIO_PORT						GPIOA
#define F_L_L_GPIO							GPIO_PIN_5

//R


#define F_R_PWM_PORT						GPIOA
#define F_R_PWM_PIN							GPIO_PIN_3
#define F_R_TIMX_GPIO_CLK_ENABLE() 			do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)  


#define F_R_H_GPIO_CLK_ENABLE() 				do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)
#define F_R_H_GPIO_PORT						GPIOB
#define F_R_H_GPIO							GPIO_PIN_8
#define F_R_L_GPIO_CLK_ENABLE() 				do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)
#define F_R_L_GPIO_PORT						GPIOB
#define F_R_L_GPIO							GPIO_PIN_9


//HOULUN
#define B_TIMx								TIM1
#define B_TIM_CLK_ENABLE()					do{ __HAL_RCC_TIM1_CLK_ENABLE(); }while(0)
#define B_L_TIM_CHANNEL						TIM_CHANNEL_1
#define B_R_TIM_CHANNEL						TIM_CHANNEL_4
#define B_TIMx_IRQn                   		TIM1_UP_TIM10_IRQn
#define B_TIMx_IRQHandler      	   	    	TIM1_UP_TIM10_IRQnHandler


//L

#define B_L_PWM_PORT							GPIOA
#define B_L_PWM_PIN							GPIO_PIN_8
#define B_L_TIMX_GPIO_CLK_ENABLE()			do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)  					


#define B_L_H_GPIO_CLK_ENABLE() 				do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)
#define B_L_H_GPIO_PORT						GPIOC
#define B_L_H_GPIO							GPIO_PIN_9
#define B_L_L_GPIO_CLK_ENABLE() 				do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)
#define B_L_L_GPIO_PORT						GPIOC
#define B_L_L_GPIO							GPIO_PIN_8

//R


#define B_R_PWM_PORT						GPIOA 
#define B_R_PWM_PIN							GPIO_PIN_11
#define B_R_TIMX_GPIO_CLK_ENABLE() 			do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)  


#define B_R_H_GPIO_CLK_ENABLE() 				do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)
#define B_R_H_GPIO_PORT						GPIOD
#define B_R_H_GPIO							GPIO_PIN_1
#define B_R_L_GPIO_CLK_ENABLE() 				do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)
#define B_R_L_GPIO_PORT						GPIOD
#define B_R_L_GPIO							GPIO_PIN_2


#endif

