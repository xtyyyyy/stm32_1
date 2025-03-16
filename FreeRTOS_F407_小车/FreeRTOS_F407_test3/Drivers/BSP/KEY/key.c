/*-----------------------------------------------------------------------------
 *      (C) Copyright 2023-2032, nbufe. All Rights Reserved 
 *-----------------------------------------------------------------------------
 * File name   : key.c
 * Description : 按键输入 驱动代码
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
#include "./BSP/KEY/key.h"
#include "./SYSTEM/delay/delay.h"

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
 * 功能: 按键初始化函数
 * 参数: None
 * 返回: None
 * 说明: None
 */
void key_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;                          /* GPIO配置参数存储变量 */
    KEY0_GPIO_CLK_ENABLE();                                     /* KEY0时钟使能 */
    KEY1_GPIO_CLK_ENABLE();                                     /* KEY1时钟使能 */
    KEY2_GPIO_CLK_ENABLE();                                     /* KEY2时钟使能 */
    WKUP_GPIO_CLK_ENABLE();                                     /* WKUP时钟使能 */

    gpio_init_struct.Pin = KEY0_GPIO_PIN;                       /* KEY0引脚 */
    gpio_init_struct.Mode = GPIO_MODE_INPUT;                    /* 输入 */
    gpio_init_struct.Pull = GPIO_PULLUP;                        /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;              /* 高速 */
    HAL_GPIO_Init(KEY0_GPIO_PORT, &gpio_init_struct);           /* KEY0引脚模式设置,上拉输入 */

    gpio_init_struct.Pin = KEY1_GPIO_PIN;                       /* KEY1引脚 */
    gpio_init_struct.Mode = GPIO_MODE_INPUT;                    /* 输入 */
    gpio_init_struct.Pull = GPIO_PULLUP;                        /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;              /* 高速 */
    HAL_GPIO_Init(KEY1_GPIO_PORT, &gpio_init_struct);           /* KEY1引脚模式设置,上拉输入 */

    gpio_init_struct.Pin = KEY2_GPIO_PIN;                       /* KEY2引脚 */
    gpio_init_struct.Mode = GPIO_MODE_INPUT;                    /* 输入 */
    gpio_init_struct.Pull = GPIO_PULLUP;                        /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;              /* 高速 */
    HAL_GPIO_Init(KEY2_GPIO_PORT, &gpio_init_struct);           /* KEY2引脚模式设置,上拉输入 */

    gpio_init_struct.Pin = WKUP_GPIO_PIN;                       /* WKUP引脚 */
    gpio_init_struct.Mode = GPIO_MODE_INPUT;                    /* 输入 */
    gpio_init_struct.Pull = GPIO_PULLDOWN;                      /* 下拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;              /* 高速 */
    HAL_GPIO_Init(WKUP_GPIO_PORT, &gpio_init_struct);           /* WKUP引脚模式设置,下拉输入 */

}

/*
 * 功能: 按键扫描函数
 * 参数: None
 * 返回: None
 * 说明: 该函数有响应优先级(同时按下多个按键): WK_UP > KEY2 > KEY1 > KEY0!!
 *        mode:0 / 1, 具体含义如下:
 *        0,  不支持连续按(当按键按下不放时, 只有第一次调用会返回键值,
 *            必须松开以后, 再次按下才会返回其他键值)
 *        1,  支持连续按(当按键按下不放时, 每次调用该函数都会返回键值)
 *            键值, 定义如下:
 *            KEY0_PRES, 1, KEY0按下
 *            KEY1_PRES, 2, KEY1按下
 *            KEY2_PRES, 3, KEY2按下
 *            WKUP_PRES, 4, WKUP按下
 */
uint8_t key_scan(uint8_t mode)
{
    static uint8_t key_up = 1;  /* 按键按松开标志 */
    uint8_t keyval = 0;

    if (mode) key_up = 1;       /* 支持连按 */

    if (key_up && (KEY0 == 0 || KEY1 == 0 || KEY2 == 0 || WK_UP == 1))  /* 按键松开标志为1, 且有任意一个按键按下了 */
    {
        delay_ms(10);           /* 去抖动 */
        key_up = 0;

        if (KEY0 == 0)  keyval = KEY0_PRES;

        if (KEY1 == 0)  keyval = KEY1_PRES;

        if (KEY2 == 0)  keyval = KEY2_PRES;

        if (WK_UP == 1) keyval = WKUP_PRES;
    }
    else if (KEY0 == 1 && KEY1 == 1 && KEY2 == 1 && WK_UP == 0)         /* 没有任何按键按下, 标记按键松开 */
    {
        key_up = 1;
    }

    return keyval;              /* 返回键值 */
}


/******************** (C) Copyright nbufe ( End Of File ) ********************/
