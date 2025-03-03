/**
 ****************************************************************************************************
 * @file        led.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2022-4-20
 * @brief       LED 驱动代码
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 阿波罗 F429开发板
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
 
#include "./BSP/DENG/deng.h"

/**
 * @brief       初始化LED相关IO口, 并使能时钟
 * @param       无
 * @retval      无
 */
void deng_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    
    DENG_GPIO_CLK_ENABLE();                                 /* DENG时钟使能 */


    gpio_init_struct.Pin = DENG_GPIO_PIN;                   /* DENG引脚 */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;            /* 推挽输出 */
    gpio_init_struct.Pull = GPIO_PULLUP;                    /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* 高速 */
    HAL_GPIO_Init(DENG_GPIO_PORT, &gpio_init_struct);       /* 初始化DENG引脚 */


    
    DENG(0);                                                /* 关闭 DENG */

}

void bump_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    
    BUMP_GPIO_CLK_ENABLE();                                 /* DENG时钟使能 */


    gpio_init_struct.Pin = BUMP_GPIO_PIN;                   /* DENG引脚 */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;            /* 推挽输出 */
    gpio_init_struct.Pull = GPIO_PULLUP;                    /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* 高速 */
    HAL_GPIO_Init(BUMP_GPIO_PORT, &gpio_init_struct);       /* 初始化DENG引脚 */


    
    BUMP(0);                                                /* 关闭 DENG */

}
