/**
 ****************************************************************************************************
 * @file        led.h
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2022-4-20
 * @brief       LED ��������
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� STM32F429������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 * �޸�˵��
 * V1.0 20220420
 * ��һ�η���
 *
 ****************************************************************************************************
 */
#ifndef __DENG_H
#define __DENG_H

#include "./SYSTEM/sys/sys.h"

/******************************************************************************************/
/* ���� ���� */

#define DENG_GPIO_PORT                  GPIOB
#define DENG_GPIO_PIN                   GPIO_PIN_13
#define DENG_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)             /* PB��ʱ��ʹ�� */


#define BUMP_GPIO_PORT                  GPIOB
#define BUMP_GPIO_PIN                   GPIO_PIN_12
#define BUMP_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)             /* PB��ʱ��ʹ�� */



/******************************************************************************************/

/* LED�˿ڶ��� */
#define DENG(x)   do{ x ? \
                      HAL_GPIO_WritePin(DENG_GPIO_PORT, DENG_GPIO_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(DENG_GPIO_PORT, DENG_GPIO_PIN, GPIO_PIN_RESET); \
                  }while(0)       /* DENG = RED */

#define BUMP(x)   do{ x ? \
                      HAL_GPIO_WritePin(BUMP_GPIO_PORT, BUMP_GPIO_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(BUMP_GPIO_PORT, BUMP_GPIO_PIN, GPIO_PIN_RESET); \
                  }while(0)       /* DENG = RED */



/******************************************************************************************/
/* �ⲿ�ӿں���*/
void deng_init(void);                                                                            /* ��ʼ�� */
void bump_init(void);
#endif
