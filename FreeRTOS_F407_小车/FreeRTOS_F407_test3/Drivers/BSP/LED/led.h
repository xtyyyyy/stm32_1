/*------------------------------------------------------------------------------
 * File name   : xxx.h
 * Author      : nbufe
 * Copyright(C): 2021-2025 nbufe. All rights reserved.
 *------------------------------------------------------------------------------
 */
#ifndef __LED_H__
#define __LED_H__

/* 包含头文件 -------------------------------------------------------*/
#include "./SYSTEM/sys/sys.h"

/* 类型定义 ---------------------------------------------------------*/
/* None. */

/* 宏定义 -----------------------------------------------------------*/

/* 引脚 定义 */
#define LED0_GPIO_PORT                  GPIOC
#define LED0_GPIO_PIN                   GPIO_PIN_0						//褐色
#define LED0_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)             /* PC口时钟使能 */

#define LED1_GPIO_PORT                  GPIOC
#define LED1_GPIO_PIN                   GPIO_PIN_1
#define LED1_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)             /* PC口时钟使能 */

#define LED2_GPIO_PORT                  GPIOC
#define LED2_GPIO_PIN                   GPIO_PIN_2
#define LED2_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)             /* PC口时钟使能 */

#define LED3_GPIO_PORT                  GPIOC
#define LED3_GPIO_PIN                   GPIO_PIN_3
#define LED3_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)             /* PC口时钟使能 */

/* LED端口定义 */
#define LED0(x)   do{ x ? \
                      HAL_GPIO_WritePin(LED0_GPIO_PORT, LED0_GPIO_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LED0_GPIO_PORT, LED0_GPIO_PIN, GPIO_PIN_RESET); \
                  }while(0)       /* LED0 = RED */

#define LED1(x)   do{ x ? \
                      HAL_GPIO_WritePin(LED1_GPIO_PORT, LED1_GPIO_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LED1_GPIO_PORT, LED1_GPIO_PIN, GPIO_PIN_RESET); \
                  }while(0)       /* LED1 = GREEN */

#define LED2(x)   do{ x ? \
                      HAL_GPIO_WritePin(LED2_GPIO_PORT, LED2_GPIO_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LED2_GPIO_PORT, LED2_GPIO_PIN, GPIO_PIN_RESET); \
                  }while(0)       /* LED2 = RED */

#define LED3(x)   do{ x ? \
                      HAL_GPIO_WritePin(LED3_GPIO_PORT, LED3_GPIO_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LED3_GPIO_PORT, LED3_GPIO_PIN, GPIO_PIN_RESET); \
                  }while(0)       /* LED3 = GREEN */
									
/* LED取反定义 */
#define LED0_TOGGLE()    do{ HAL_GPIO_TogglePin(LED0_GPIO_PORT, LED0_GPIO_PIN); }while(0)       /* LED0 = !LED0 */
#define LED1_TOGGLE()    do{ HAL_GPIO_TogglePin(LED1_GPIO_PORT, LED1_GPIO_PIN); }while(0)       /* LED1 = !LED1 */
#define LED2_TOGGLE()    do{ HAL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_GPIO_PIN); }while(0)       /* LED2 = !LED2 */
#define LED3_TOGGLE()    do{ HAL_GPIO_TogglePin(LED3_GPIO_PORT, LED3_GPIO_PIN); }while(0)       /* LED3 = !LED3 */

/* 扩展变量 ---------------------------------------------------------*/
/* None. */

/* 函数声明 ---------------------------------------------------------*/
/* 外部接口函数*/
void led_init(void);                                                                            /* 初始化 */


#endif /* __LED_H__ */

/******************** (C) Copyright nbufe ( End Of File ) ********************/

