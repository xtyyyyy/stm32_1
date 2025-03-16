#include "./BSP/Motor/Motor.h"
#include "./BSP/PID/PID.h"



#define PSC 		720-1
#define ARR 		1000-1

/* 定时器配置句柄 定义 */
TIM_HandleTypeDef TIM_Handler;     /* 定时器x句柄 */
TIM_OC_InitTypeDef TIM_PWM_OC; /* 定时器输出句柄 */
TIM_HandleTypeDef E_L_TIM_Handler;
TIM_HandleTypeDef E_R_TIM_Handler;

TIM_HandleTypeDef B_TIM_Handler;     /* 定时器x句柄 */
TIM_OC_InitTypeDef B_TIM_PWM_OC; /* 定时器输出句柄 */
TIM_HandleTypeDef B_E_L_TIM_Handler;
TIM_HandleTypeDef B_E_R_TIM_Handler;

void H_L_GPIO_Init(void)
{
	GPIO_InitTypeDef gpio_init_struct;
	
	F_R_H_GPIO_CLK_ENABLE(); /* 开启通道y的CPIO时钟 */
	gpio_init_struct.Pin = F_R_H_GPIO | F_R_L_GPIO; /* 通道y的CPIO口 */
	gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;            /* 复用推完输出 */
    gpio_init_struct.Pull = GPIO_PULLUP;                /* 上拉 */
	gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;      /* 高速 */
	HAL_GPIO_Init(F_R_H_GPIO_PORT, &gpio_init_struct);
	
	
	F_L_H_GPIO_CLK_ENABLE(); /* 开启通道y的CPIO时钟 */
	gpio_init_struct.Pin = F_L_H_GPIO | F_L_L_GPIO; /* 通道y的CPIO口 */
	gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;            /* 复用推完输出 */
    gpio_init_struct.Pull = GPIO_PULLUP;                /* 上拉 */
	gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;      /* 高速 */
	HAL_GPIO_Init(F_L_H_GPIO_PORT, &gpio_init_struct);
	
	
	B_R_H_GPIO_CLK_ENABLE(); /* 开启通道y的CPIO时钟 */
	gpio_init_struct.Pin = B_R_H_GPIO | B_R_L_GPIO; /* 通道y的CPIO口 */
	gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;            /* 复用推完输出 */
    gpio_init_struct.Pull = GPIO_PULLUP;                /* 上拉 */
	gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;      /* 高速 */
	HAL_GPIO_Init(B_R_H_GPIO_PORT, &gpio_init_struct);
	
	
	B_L_H_GPIO_CLK_ENABLE(); /* 开启通道y的CPIO时钟 */
	gpio_init_struct.Pin = B_L_H_GPIO | B_L_L_GPIO; /* 通道y的CPIO口 */
	gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;            /* 复用推完输出 */
    gpio_init_struct.Pull = GPIO_PULLUP;                /* 上拉 */
	gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;      /* 高速 */
	HAL_GPIO_Init(B_L_H_GPIO_PORT, &gpio_init_struct);
	

}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
		if(htim->Instance == TIMx)
		{
			GPIO_InitTypeDef gpio_init_struct;
			F_L_TIMX_GPIO_CLK_ENABLE(); /* 开启通道y的CPIO时钟 */

			gpio_init_struct.Pin = F_L_PWM_PIN; /* 通道y的CPIO口 */
			gpio_init_struct.Mode = GPIO_MODE_AF_PP;            /* 复用推完输出 */
			gpio_init_struct.Pull = GPIO_NOPULL;                /* 上拉 */
			gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;      /* 高速 */
			gpio_init_struct.Alternate = GPIO_AF1_TIM2;
			HAL_GPIO_Init(F_L_PWM_PORT, &gpio_init_struct);
			
			F_R_TIMX_GPIO_CLK_ENABLE(); /* 开启通道y的CPIO时钟 */
			gpio_init_struct.Pin = F_R_PWM_PIN; /* 通道y的CPIO口 */
			gpio_init_struct.Mode = GPIO_MODE_AF_PP;            /* 复用推完输出 */
			gpio_init_struct.Pull = GPIO_NOPULL;                /* 上拉 */
			gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;      /* 高速 */
			gpio_init_struct.Alternate = GPIO_AF1_TIM2;
			HAL_GPIO_Init(F_R_PWM_PORT, &gpio_init_struct);
		} 
		if(htim->Instance == B_TIMx)
		{
			GPIO_InitTypeDef gpio_init_struct;
			B_L_TIMX_GPIO_CLK_ENABLE(); /* 开启通道y的CPIO时钟 */

			gpio_init_struct.Pin = B_L_PWM_PIN; /* 通道y的CPIO口 */
			gpio_init_struct.Mode = GPIO_MODE_AF_PP;            /* 复用推完输出 */
			gpio_init_struct.Pull = GPIO_NOPULL;                /* 上拉 */
			gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;      /* 高速 */
			gpio_init_struct.Alternate = GPIO_AF1_TIM1;
			HAL_GPIO_Init(B_L_PWM_PORT, &gpio_init_struct);
			
			B_R_TIMX_GPIO_CLK_ENABLE(); /* 开启通道y的CPIO时钟 */
			gpio_init_struct.Pin = B_R_PWM_PIN; /* 通道y的CPIO口 */
			gpio_init_struct.Mode = GPIO_MODE_AF_PP;            /* 复用推完输出 */
			gpio_init_struct.Pull = GPIO_NOPULL;                /* 上拉 */
			gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;      /* 高速 */
			gpio_init_struct.Alternate = GPIO_AF1_TIM1;
			HAL_GPIO_Init(B_R_PWM_PORT, &gpio_init_struct);
		} 


}


void Motor_Init()
{
    TIM_CLK_ENABLE();      /* TIMX 时钟使能 */

    TIM_Handler.Instance = TIMx;                   /* 定时器x */
    TIM_Handler.Init.Prescaler = PSC;                        /* 定时器分频 */
    TIM_Handler.Init.CounterMode = TIM_COUNTERMODE_UP;     /* 向上计数模式 */
    TIM_Handler.Init.Period = ARR;                           /* 自动重装载值 */
    TIM_Handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1; /* 时钟分频因子 */
    TIM_Handler.Init.RepetitionCounter = 0;                  /* 开始时不计数 */
	TIM_Handler.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    HAL_TIM_PWM_Init(&TIM_Handler);                          /* 初始化PWM */

    TIM_PWM_OC.OCMode = TIM_OCMODE_PWM1;                                                /* 模式选择PWM1 */
    TIM_PWM_OC.OCPolarity = TIM_OCPOLARITY_HIGH;                                         /* 输出比较极性为高 */
	TIM_PWM_OC.Pulse = 0;
    HAL_TIM_PWM_ConfigChannel(&TIM_Handler, &TIM_PWM_OC, L_TIM_CHANNEL); /* 配置TIMx通道y */

    TIM_PWM_OC.OCMode = TIM_OCMODE_PWM1;                                                /* 模式选择PWM1 */
    TIM_PWM_OC.OCPolarity = TIM_OCPOLARITY_HIGH;                                         /* 输出比较极性为高 */
	TIM_PWM_OC.Pulse = 0;
    HAL_TIM_PWM_ConfigChannel(&TIM_Handler, &TIM_PWM_OC, R_TIM_CHANNEL); /* 配置TIMx通道y */
	
    HAL_TIM_PWM_Start(&TIM_Handler, L_TIM_CHANNEL);      /* 开启对应PWM通道 */
    HAL_TIM_PWM_Start(&TIM_Handler, R_TIM_CHANNEL);      /* 开启对应PWM通道 */

	
	B_TIM_CLK_ENABLE();      /* TIMX 时钟使能 */

    B_TIM_Handler.Instance = B_TIMx;                   /* 定时器x */
    B_TIM_Handler.Init.Prescaler = PSC;                        /* 定时器分频 */
    B_TIM_Handler.Init.CounterMode = TIM_COUNTERMODE_UP;     /* 向上计数模式 */
    B_TIM_Handler.Init.Period = ARR;                           /* 自动重装载值 */
    B_TIM_Handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1; /* 时钟分频因子 */
    B_TIM_Handler.Init.RepetitionCounter = 0;                  /* 开始时不计数 */
	B_TIM_Handler.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    HAL_TIM_PWM_Init(&B_TIM_Handler);                          /* 初始化PWM */

    B_TIM_PWM_OC.OCMode = TIM_OCMODE_PWM1;                                                /* 模式选择PWM1 */
    B_TIM_PWM_OC.OCPolarity = TIM_OCPOLARITY_HIGH;                                         /* 输出比较极性为高 */
	B_TIM_PWM_OC.Pulse = 0;
    HAL_TIM_PWM_ConfigChannel(&B_TIM_Handler, &B_TIM_PWM_OC, B_L_TIM_CHANNEL); /* 配置TIMx通道y */

    B_TIM_PWM_OC.OCMode = TIM_OCMODE_PWM1;                                                /* 模式选择PWM1 */
    B_TIM_PWM_OC.OCPolarity = TIM_OCPOLARITY_HIGH;                                         /* 输出比较极性为高 */
	B_TIM_PWM_OC.Pulse = 0;
    HAL_TIM_PWM_ConfigChannel(&B_TIM_Handler, &B_TIM_PWM_OC, B_R_TIM_CHANNEL); /* 配置TIMx通道y */
	
    HAL_TIM_PWM_Start(&B_TIM_Handler, B_L_TIM_CHANNEL);      /* 开启对应PWM通道 */
    HAL_TIM_PWM_Start(&B_TIM_Handler, B_R_TIM_CHANNEL);      /* 开启对应PWM通道 */

}


void Set_L(int16_t s)
{
	int16_t speed = s;
	if(speed >= 0)
	{
		speed = s;
		HAL_GPIO_WritePin(F_L_H_GPIO_PORT,F_L_H_GPIO,GPIO_PIN_SET);
		HAL_GPIO_WritePin(F_L_L_GPIO_PORT,F_L_L_GPIO,GPIO_PIN_RESET);
	}else{
		speed = -s;
		HAL_GPIO_WritePin(F_L_H_GPIO_PORT,F_L_H_GPIO,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(F_L_L_GPIO_PORT,F_L_L_GPIO,GPIO_PIN_SET);
	}		
	if(speed >MaxS)
		speed =MaxS;
	if(speed <MinS)
		speed = 0;

	__HAL_TIM_SET_COMPARE(&TIM_Handler, L_TIM_CHANNEL, speed);
}

void Set_R(int16_t s)
{
	int16_t speed = s;
	if(speed >= 0)
	{
		speed = s;
		HAL_GPIO_WritePin(F_R_H_GPIO_PORT,F_R_H_GPIO,GPIO_PIN_SET);
		HAL_GPIO_WritePin(F_R_L_GPIO_PORT,F_R_L_GPIO,GPIO_PIN_RESET);
	}else{
		speed = -s;
		HAL_GPIO_WritePin(F_R_H_GPIO_PORT,F_R_H_GPIO,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(F_R_L_GPIO_PORT,F_R_L_GPIO,GPIO_PIN_SET);
	}		
	if(speed >MaxS)
		speed =MaxS;
	if(speed <MinS)
		speed = 0;

	__HAL_TIM_SET_COMPARE(&TIM_Handler, R_TIM_CHANNEL, speed);
}

void B_Set_L(int16_t s)
{
	int16_t speed = s;
	if(speed >= 0)
	{
		speed = s;
		HAL_GPIO_WritePin(B_L_H_GPIO_PORT,B_L_H_GPIO,GPIO_PIN_SET);
		HAL_GPIO_WritePin(B_L_L_GPIO_PORT,B_L_L_GPIO,GPIO_PIN_RESET);
	}else{
		speed = -s;
		HAL_GPIO_WritePin(B_L_H_GPIO_PORT,B_L_H_GPIO,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(B_L_L_GPIO_PORT,B_L_L_GPIO,GPIO_PIN_SET);
	}		
	if(speed >MaxS)
		speed =MaxS;
	if(speed <MinS)
		speed = 0;


	__HAL_TIM_SET_COMPARE(&B_TIM_Handler, B_L_TIM_CHANNEL, speed);
}

void B_Set_R(int16_t s)
{
	int16_t speed = s;
	if(speed >= 0)
	{
		speed = s;
		HAL_GPIO_WritePin(B_R_H_GPIO_PORT,B_R_H_GPIO,GPIO_PIN_SET);
		HAL_GPIO_WritePin(B_R_L_GPIO_PORT,B_R_L_GPIO,GPIO_PIN_RESET);
	}else{
		speed = -s;
		HAL_GPIO_WritePin(B_R_H_GPIO_PORT,B_R_H_GPIO,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(B_R_L_GPIO_PORT,B_R_L_GPIO,GPIO_PIN_SET);
	}		
	if(speed >MaxS)
		speed =MaxS;
	if(speed <MinS)
		speed = 0;

	__HAL_TIM_SET_COMPARE(&B_TIM_Handler, B_R_TIM_CHANNEL, speed);
}

