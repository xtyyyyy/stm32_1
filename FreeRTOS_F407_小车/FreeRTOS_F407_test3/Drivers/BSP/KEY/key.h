/*------------------------------------------------------------------------------
 * File name   : key.h
 * Author      : nbufe
 * Copyright(C): 2021-2025 nbufe. All rights reserved.
 *------------------------------------------------------------------------------
 */
#ifndef __XXX_H__
#define __XXX_H__

/* 包含头文件 -------------------------------------------------------*/
#include "./SYSTEM/sys/sys.h"

/* 类型定义 ---------------------------------------------------------*/
/* None. */

/* 宏定义 -----------------------------------------------------------*/
/* 引脚 定义 */
#define KEY0_GPIO_PORT                  GPIOA
#define KEY0_GPIO_PIN                   GPIO_PIN_3
#define KEY0_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)   /* PA口时钟使能 */

#define KEY1_GPIO_PORT                  GPIOA
#define KEY1_GPIO_PIN                   GPIO_PIN_5
#define KEY1_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)   /* PA口时钟使能 */

#define KEY2_GPIO_PORT                  GPIOA
#define KEY2_GPIO_PIN                   GPIO_PIN_7
#define KEY2_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)   /* PA口时钟使能 */

#define WKUP_GPIO_PORT                  GPIOA
#define WKUP_GPIO_PIN                   GPIO_PIN_0
#define WKUP_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)   /* PA口时钟使能 */

#define KEY0        HAL_GPIO_ReadPin(KEY0_GPIO_PORT, KEY0_GPIO_PIN)     /* 读取KEY2引脚 */
#define KEY1        HAL_GPIO_ReadPin(KEY1_GPIO_PORT, KEY1_GPIO_PIN)     /* 读取KEY3引脚 */
#define KEY2        HAL_GPIO_ReadPin(KEY2_GPIO_PORT, KEY2_GPIO_PIN)     /* 读取KEY4引脚 */
#define WK_UP       HAL_GPIO_ReadPin(WKUP_GPIO_PORT, WKUP_GPIO_PIN)     /* 读取WKUP引脚 */

#define KEY0_PRES    1              /* KEY0按下 */
#define KEY1_PRES    2              /* KEY1按下 */
#define KEY2_PRES    3              /* KEY2按下 */
#define WKUP_PRES    4              /* KEY_UP按下(即WK_UP) */

/* 扩展变量 ---------------------------------------------------------*/
/* None. */

/* 函数声明 ---------------------------------------------------------*/
void key_init(void);                /* 按键初始化函数 */
uint8_t key_scan(uint8_t mode);     /* 按键扫描函数 */

#endif /* __XXX_H__ */

/******************** (C) Copyright nbufe ( End Of File ) ********************/
