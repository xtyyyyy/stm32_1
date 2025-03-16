/**
  ******************************************************************************
  * @file    bsp_motor_control.c
  * @author  fire
  * @version V1.0
  * @date    2019-xx-xx
  * @brief   编码器接口
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火  STM32 F407 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */ 

#include "./BSP/Encoder/Encoder.h"

/* 定时器溢出次数 */
__IO int16_t Encoder_Overflow_Count = 0;
__IO int16_t Encoder_Overflow_Count2 = 0;

__IO int16_t B_Encoder_Overflow_Count = 0;
__IO int16_t B_Encoder_Overflow_Count2 = 0;

TIM_HandleTypeDef TIM_EncoderHandle;
TIM_HandleTypeDef TIM_EncoderHandle2;

TIM_HandleTypeDef B_TIM_EncoderHandle;
TIM_HandleTypeDef B_TIM_EncoderHandle2;
/**
  * @brief  编码器接口引脚初始化
  * @param  无
  * @retval 无
  */
static void Encoder_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* 定时器通道引脚端口时钟使能 */
	ENCODER_TIM_F_L_CH1_GPIO_CLK_ENABLE();
	ENCODER_TIM_F_L_CH2_GPIO_CLK_ENABLE();

	/* 设置输入类型 */
	GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
	/* 设置上拉 */
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	/* 设置引脚速率 */
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

	/* 选择要控制的GPIO引脚 */	
	GPIO_InitStruct.Pin = ENCODER_TIM_F_L_CH1_PIN;
	/* 设置复用 */
	GPIO_InitStruct.Alternate = ENCODER_TIM_F_L_CH1_GPIO_AF;
	/* 调用库函数，使用上面配置的GPIO_InitStructure初始化GPIO */
	HAL_GPIO_Init(ENCODER_TIM_F_L_CH1_GPIO_PORT, &GPIO_InitStruct);

	/* 选择要控制的GPIO引脚 */	
	GPIO_InitStruct.Pin = ENCODER_TIM_F_L_CH2_PIN;
	/* 设置复用 */
	GPIO_InitStruct.Alternate = ENCODER_TIM_F_L_CH2_GPIO_AF;
	/* 调用库函数，使用上面配置的GPIO_InitStructure初始化GPIO */
	HAL_GPIO_Init(ENCODER_TIM_F_L_CH2_GPIO_PORT, &GPIO_InitStruct);




	/* 定时器通道引脚端口时钟使能 */
	ENCODER_TIM_F_R_CH1_GPIO_CLK_ENABLE();
	ENCODER_TIM_F_R_CH2_GPIO_CLK_ENABLE();

	/* 设置输入类型 */
	GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
	/* 设置上拉 */
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	/* 设置引脚速率 */
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

	/* 选择要控制的GPIO引脚 */	
	GPIO_InitStruct.Pin = ENCODER_TIM_F_R_CH1_PIN;
	/* 设置复用 */
	GPIO_InitStruct.Alternate = ENCODER_TIM_F_R_CH1_GPIO_AF;
	/* 调用库函数，使用上面配置的GPIO_InitStructure初始化GPIO */
	HAL_GPIO_Init(ENCODER_TIM_F_R_CH1_GPIO_PORT, &GPIO_InitStruct);

	/* 选择要控制的GPIO引脚 */	
	GPIO_InitStruct.Pin = ENCODER_TIM_F_R_CH2_PIN;
	/* 设置复用 */
	GPIO_InitStruct.Alternate = ENCODER_TIM_F_R_CH2_GPIO_AF;
	/* 调用库函数，使用上面配置的GPIO_InitStructure初始化GPIO */
	HAL_GPIO_Init(ENCODER_TIM_F_R_CH2_GPIO_PORT, &GPIO_InitStruct);
	
	//后轮
	
	/* 定时器通道引脚端口时钟使能 */
	ENCODER_TIM_B_L_CH1_GPIO_CLK_ENABLE();
	ENCODER_TIM_B_L_CH2_GPIO_CLK_ENABLE();

	/* 设置输入类型 */
	GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
	/* 设置上拉 */
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	/* 设置引脚速率 */
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

	/* 选择要控制的GPIO引脚 */	
	GPIO_InitStruct.Pin = ENCODER_TIM_B_L_CH1_PIN;
	/* 设置复用 */
	GPIO_InitStruct.Alternate = ENCODER_TIM_B_L_CH1_GPIO_AF;
	/* 调用库函数，使用上面配置的GPIO_InitStructure初始化GPIO */
	HAL_GPIO_Init(ENCODER_TIM_B_L_CH1_GPIO_PORT, &GPIO_InitStruct);

	/* 选择要控制的GPIO引脚 */	
	GPIO_InitStruct.Pin = ENCODER_TIM_B_L_CH2_PIN;
	/* 设置复用 */
	GPIO_InitStruct.Alternate = ENCODER_TIM_B_L_CH2_GPIO_AF;
	/* 调用库函数，使用上面配置的GPIO_InitStructure初始化GPIO */
	HAL_GPIO_Init(ENCODER_TIM_B_L_CH2_GPIO_PORT, &GPIO_InitStruct);




	/* 定时器通道引脚端口时钟使能 */
	ENCODER_TIM_B_R_CH1_GPIO_CLK_ENABLE();
	ENCODER_TIM_B_R_CH2_GPIO_CLK_ENABLE();

	/* 设置输入类型 */
	GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
	/* 设置上拉 */
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	/* 设置引脚速率 */
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

	/* 选择要控制的GPIO引脚 */	
	GPIO_InitStruct.Pin = ENCODER_TIM_B_R_CH1_PIN;
	/* 设置复用 */
	GPIO_InitStruct.Alternate = ENCODER_TIM_B_R_CH1_GPIO_AF;
	/* 调用库函数，使用上面配置的GPIO_InitStructure初始化GPIO */
	HAL_GPIO_Init(ENCODER_TIM_B_R_CH1_GPIO_PORT, &GPIO_InitStruct);

	/* 选择要控制的GPIO引脚 */	
	GPIO_InitStruct.Pin = ENCODER_TIM_B_R_CH2_PIN;
	/* 设置复用 */
	GPIO_InitStruct.Alternate = ENCODER_TIM_B_R_CH2_GPIO_AF;
	/* 调用库函数，使用上面配置的GPIO_InitStructure初始化GPIO */
	HAL_GPIO_Init(ENCODER_TIM_B_R_CH2_GPIO_PORT, &GPIO_InitStruct);
}

/**
  * @brief  配置TIMx编码器模式
  * @param  无
  * @retval 无
  */
static void TIM_Encoder_Init(void)
{ 
	TIM_Encoder_InitTypeDef Encoder_ConfigStructure;
	TIM_Encoder_InitTypeDef Encoder_ConfigStructure2;
	TIM_Encoder_InitTypeDef B_Encoder_ConfigStructure;
	TIM_IC_InitTypeDef B_IC_ConfigStructure2;
	/* 使能编码器接口时钟 */
	ENCODER_TIM_F_L_CLK_ENABLE();

	/* 定时器初始化设置 */
	TIM_EncoderHandle.Instance = ENCODER_TIM_F_L;
	TIM_EncoderHandle.Init.Prescaler = ENCODER_TIM_F_L_PRESCALER;
	TIM_EncoderHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
	TIM_EncoderHandle.Init.Period = ENCODER_TIM_F_L_PERIOD;
	TIM_EncoderHandle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	TIM_EncoderHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

	/* 设置编码器倍频数 */
	Encoder_ConfigStructure.EncoderMode = ENCODER_MODE;
	/* 编码器接口通道1设置 */
	Encoder_ConfigStructure.IC1Polarity = ENCODER_IC1_POLARITY;
	Encoder_ConfigStructure.IC1Selection = TIM_ICSELECTION_DIRECTTI;
	Encoder_ConfigStructure.IC1Prescaler = TIM_ICPSC_DIV1;
	Encoder_ConfigStructure.IC1Filter = 0;
	/* 编码器接口通道2设置 */
	Encoder_ConfigStructure.IC2Polarity = ENCODER_IC2_POLARITY;
	Encoder_ConfigStructure.IC2Selection = TIM_ICSELECTION_DIRECTTI;
	Encoder_ConfigStructure.IC2Prescaler = TIM_ICPSC_DIV1;
	Encoder_ConfigStructure.IC2Filter = 0;
	/* 初始化编码器接口 */
	HAL_TIM_Encoder_Init(&TIM_EncoderHandle, &Encoder_ConfigStructure);

	/* 清零计数器 */
	__HAL_TIM_SET_COUNTER(&TIM_EncoderHandle, 0);


	/* 使能编码器接口 */
	HAL_TIM_Encoder_Start(&TIM_EncoderHandle, TIM_CHANNEL_ALL);



	ENCODER_TIM_F_R_CLK_ENABLE();

	/* 定时器初始化设置 */
	TIM_EncoderHandle2.Instance = ENCODER_TIM_F_R;
	TIM_EncoderHandle2.Init.Prescaler = ENCODER_TIM_F_R_PRESCALER;
	TIM_EncoderHandle2.Init.CounterMode = TIM_COUNTERMODE_UP;
	TIM_EncoderHandle2.Init.Period = ENCODER_TIM_F_R_PERIOD;
	TIM_EncoderHandle2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	TIM_EncoderHandle2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

	/* 设置编码器倍频数 */
	Encoder_ConfigStructure2.EncoderMode = ENCODER_MODE;
	/* 编码器接口通道1设置 */
	Encoder_ConfigStructure2.IC1Polarity = ENCODER_IC1_POLARITY;
	Encoder_ConfigStructure2.IC1Selection = TIM_ICSELECTION_DIRECTTI;
	Encoder_ConfigStructure2.IC1Prescaler = TIM_ICPSC_DIV1;
	Encoder_ConfigStructure2.IC1Filter = 0;
	/* 编码器接口通道2设置 */
	Encoder_ConfigStructure2.IC2Polarity = ENCODER_IC2_POLARITY;
	Encoder_ConfigStructure2.IC2Selection = TIM_ICSELECTION_DIRECTTI;
	Encoder_ConfigStructure2.IC2Prescaler = TIM_ICPSC_DIV1;
	Encoder_ConfigStructure2.IC2Filter = 0;
	/* 初始化编码器接口 */
	HAL_TIM_Encoder_Init(&TIM_EncoderHandle2, &Encoder_ConfigStructure2);

	/* 清零计数器 */
	__HAL_TIM_SET_COUNTER(&TIM_EncoderHandle2, 0);

	/* 使能编码器接口 */
	HAL_TIM_Encoder_Start(&TIM_EncoderHandle2, TIM_CHANNEL_ALL);
	
	  
//HOU
	
	ENCODER_TIM_B_L_CLK_ENABLE();

	/* 定时器初始化设置 */
	B_TIM_EncoderHandle.Instance = ENCODER_TIM_B_L;
	B_TIM_EncoderHandle.Init.Prescaler = ENCODER_TIM_B_L_PRESCALER;
	B_TIM_EncoderHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
	B_TIM_EncoderHandle.Init.Period = ENCODER_TIM_B_L_PERIOD;
	B_TIM_EncoderHandle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	B_TIM_EncoderHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

	/* 设置编码器倍频数 */
	B_Encoder_ConfigStructure.EncoderMode = ENCODER_MODE;
	/* 编码器接口通道1设置 */
	B_Encoder_ConfigStructure.IC1Polarity = ENCODER_IC1_POLARITY;
	B_Encoder_ConfigStructure.IC1Selection = TIM_ICSELECTION_DIRECTTI;
	B_Encoder_ConfigStructure.IC1Prescaler = TIM_ICPSC_DIV1;
	B_Encoder_ConfigStructure.IC1Filter = 0;
	/* 编码器接口通道2设置 */
	B_Encoder_ConfigStructure.IC2Polarity = ENCODER_IC2_POLARITY;
	B_Encoder_ConfigStructure.IC2Selection = TIM_ICSELECTION_DIRECTTI;
	B_Encoder_ConfigStructure.IC2Prescaler = TIM_ICPSC_DIV1;
	B_Encoder_ConfigStructure.IC2Filter = 0;
	/* 初始化编码器接口 */
	HAL_TIM_Encoder_Init(&B_TIM_EncoderHandle, &B_Encoder_ConfigStructure);

	/* 清零计数器 */
	__HAL_TIM_SET_COUNTER(&B_TIM_EncoderHandle, 0);

	/* 使能编码器接口 */
	HAL_TIM_Encoder_Start(&B_TIM_EncoderHandle, TIM_CHANNEL_1);
	HAL_TIM_Encoder_Start(&B_TIM_EncoderHandle, TIM_CHANNEL_2);



	ENCODER_TIM_B_R_CLK_ENABLE();

	/* 定时器初始化设置 */
	B_TIM_EncoderHandle2.Instance = ENCODER_TIM_B_R;
	B_TIM_EncoderHandle2.Init.Prescaler = ENCODER_TIM_B_R_PRESCALER;
	B_TIM_EncoderHandle2.Init.CounterMode = TIM_COUNTERMODE_UP;
	B_TIM_EncoderHandle2.Init.Period = ENCODER_TIM_B_R_PERIOD;
	B_TIM_EncoderHandle2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	B_TIM_EncoderHandle2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	HAL_TIM_IC_Init(&B_TIM_EncoderHandle2);

	/* 设置编码器倍频数 */
	
	B_IC_ConfigStructure2.ICPrescaler = TIM_ICPSC_DIV1;
    B_IC_ConfigStructure2.ICFilter = 0;
    B_IC_ConfigStructure2.ICPolarity = TIM_INPUTCHANNELPOLARITY_BOTHEDGE;
    B_IC_ConfigStructure2.ICSelection = TIM_ICSELECTION_DIRECTTI;
    HAL_TIM_IC_ConfigChannel(&B_TIM_EncoderHandle2, &B_IC_ConfigStructure2, TIM_CHANNEL_1);
	
	B_IC_ConfigStructure2.ICSelection = TIM_ICSELECTION_INDIRECTTI;
    HAL_TIM_IC_ConfigChannel(&B_TIM_EncoderHandle2, &B_IC_ConfigStructure2, TIM_CHANNEL_2);
	
	__HAL_TIM_SET_COUNTER(&B_TIM_EncoderHandle2, 0);
	
	HAL_TIM_IC_Start_IT(&B_TIM_EncoderHandle2, TIM_CHANNEL_1); // 开启通道1的中断捕获
    HAL_TIM_IC_Start(&B_TIM_EncoderHandle2, TIM_CHANNEL_2); // 开启通道2的捕获
	
	HAL_NVIC_SetPriority(TIM1_BRK_TIM9_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM1_BRK_TIM9_IRQn);
	/* 清零计数器 */
}

void TIM1_BRK_TIM9_IRQHandler(void) {
    HAL_TIM_IRQHandler(&B_TIM_EncoderHandle2);
}

uint32_t count = 0; // 计数器

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
    
    
    if (htim->Instance == TIM9) {
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) {
            // 通道1捕获事件发生

            count++; // 每次捕获到上升沿，计数值加一
        } else if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2) {
            // 通道2捕获事件发生

            count++; // 每次捕获到上升沿，计数值加一
        }
    }
}

/**
  * @brief  编码器接口初始化
  * @param  无
  * @retval 无
  */
void Encoder_Init(void)
{
  Encoder_GPIO_Init();    /* 引脚初始化 */
  TIM_Encoder_Init();     /* 配置编码器接口 */
}


/*********************************************END OF FILE**********************/

