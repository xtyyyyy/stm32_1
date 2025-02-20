/**
 ****************************************************************************************************
 * @file        led.h
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2022-4-20
 * @brief       LED 驱动代码
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 STM32F429开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 * 修改说明
 * V1.0 20220420
 * 第一次发布
 *
 ****************************************************************************************************
 */
#ifndef __DENG_H
#define __DENG_H

#include "./SYSTEM/sys/sys.h"

/******************************************************************************************/
/* 引脚 定义 */

#define DENG_GPIO_PORT                  GPIOB
#define DENG_GPIO_PIN                   GPIO_PIN_13
#define DENG_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)             /* PB口时钟使能 */


#define BUMP_GPIO_PORT                  GPIOB
#define BUMP_GPIO_PIN                   GPIO_PIN_12
#define BUMP_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)             /* PB口时钟使能 */



/******************************************************************************************/

/* LED端口定义 */
#define DENG(x)   do{ x ? \
                      HAL_GPIO_WritePin(DENG_GPIO_PORT, DENG_GPIO_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(DENG_GPIO_PORT, DENG_GPIO_PIN, GPIO_PIN_RESET); \
                  }while(0)       /* DENG = RED */

#define BUMP(x)   do{ x ? \
                      HAL_GPIO_WritePin(BUMP_GPIO_PORT, BUMP_GPIO_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(BUMP_GPIO_PORT, BUMP_GPIO_PIN, GPIO_PIN_RESET); \
                  }while(0)       /* DENG = RED */



/******************************************************************************************/
/* 外部接口函数*/
void deng_init(void);                                                                            /* 初始化 */
void bump_init(void);
#endif
