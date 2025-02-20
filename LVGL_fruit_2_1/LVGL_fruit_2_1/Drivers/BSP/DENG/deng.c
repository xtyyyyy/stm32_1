/**
 ****************************************************************************************************
 * @file        led.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2022-4-20
 * @brief       LED ��������
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� ������ F429������
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
 
#include "./BSP/DENG/deng.h"

/**
 * @brief       ��ʼ��LED���IO��, ��ʹ��ʱ��
 * @param       ��
 * @retval      ��
 */
void deng_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    
    DENG_GPIO_CLK_ENABLE();                                 /* DENGʱ��ʹ�� */


    gpio_init_struct.Pin = DENG_GPIO_PIN;                   /* DENG���� */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;            /* ������� */
    gpio_init_struct.Pull = GPIO_PULLUP;                    /* ���� */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* ���� */
    HAL_GPIO_Init(DENG_GPIO_PORT, &gpio_init_struct);       /* ��ʼ��DENG���� */


    
    DENG(0);                                                /* �ر� DENG */

}

void bump_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    
    BUMP_GPIO_CLK_ENABLE();                                 /* DENGʱ��ʹ�� */


    gpio_init_struct.Pin = BUMP_GPIO_PIN;                   /* DENG���� */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;            /* ������� */
    gpio_init_struct.Pull = GPIO_PULLUP;                    /* ���� */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* ���� */
    HAL_GPIO_Init(BUMP_GPIO_PORT, &gpio_init_struct);       /* ��ʼ��DENG���� */


    
    BUMP(0);                                                /* �ر� DENG */

}
