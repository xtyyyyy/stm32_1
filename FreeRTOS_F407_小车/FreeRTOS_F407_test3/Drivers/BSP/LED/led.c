/*-----------------------------------------------------------------------------
 *      (C) Copyright 2023-2032, nbufe. All Rights Reserved 
 *-----------------------------------------------------------------------------
 * File name   : led.c
 * Description : LED 驱动代码
 * Author      : nbufe
 * Date        : 2023-09-14
 *-----------------------------------------------------------------------------
 * Attention
 *
 * 实验平台: 
 *     C32F407Pro 开发板
 *
 * 修改说明:
 *     V1.0 20230914(第一次发布)
**/

/* 包含头文件 -------------------------------------------------------*/
#include "./BSP/LED/led.h"

/* 私有类型定义 -----------------------------------------------------*/
/* None. */

/* 私有宏定义 -------------------------------------------------------*/
/* None. */

/* 私有变量 ---------------------------------------------------------*/
/* None. */

/* 扩展变量 ---------------------------------------------------------*/
/* None. */

/* 私有函数原形 -----------------------------------------------------*/
/* None. */

/* 函数体 -----------------------------------------------------------*/
/*
 * 功能: 初始化LED相关IO口, 并使能时钟
 * 参数: None
 * 返回: None
 * 说明: None
 */
void led_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    
    LED0_GPIO_CLK_ENABLE();                                 /* LED0时钟使能 */
    LED1_GPIO_CLK_ENABLE();                                 /* LED1时钟使能 */
    LED2_GPIO_CLK_ENABLE();                                 /* LED2时钟使能 */
    LED3_GPIO_CLK_ENABLE();                                 /* LED3时钟使能 */
	
    gpio_init_struct.Pin = LED0_GPIO_PIN;                   /* LED0引脚 */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;            /* 推挽输出 */
    gpio_init_struct.Pull = GPIO_PULLUP;                    /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* 高速 */
    HAL_GPIO_Init(LED0_GPIO_PORT, &gpio_init_struct);       /* 初始化LED0引脚 */

    gpio_init_struct.Pin = LED1_GPIO_PIN;                   /* LED1引脚 */
    HAL_GPIO_Init(LED1_GPIO_PORT, &gpio_init_struct);       /* 初始化LED1引脚 */

    gpio_init_struct.Pin = LED2_GPIO_PIN;                   /* LED1引脚 */
    HAL_GPIO_Init(LED2_GPIO_PORT, &gpio_init_struct);       /* 初始化LED1引脚 */

    gpio_init_struct.Pin = LED3_GPIO_PIN;                   /* LED1引脚 */
    HAL_GPIO_Init(LED3_GPIO_PORT, &gpio_init_struct);       /* 初始化LED1引脚 */
		
    LED0(1);                                                /* 关闭 LED0 */
    LED1(1);                                                /* 关闭 LED1 */    
		LED2(1);                                                /* 关闭 LED2 */
    LED3(1);                                                /* 关闭 LED3 */
}

/******************** (C) Copyright nbufe ( End Of File ) ********************/



