/*------------------------------------------------------------------------------
 * File name   : usart.h
 * Author      : nbufe
 * Copyright(C): 2021-2025 nbufe. All rights reserved.
 *------------------------------------------------------------------------------
 */
#ifndef __usart3_H__
#define __usart3_H__

/* 包含头文件 -------------------------------------------------------*/
#include "stdio.h"
#include "./SYSTEM/sys/sys.h"

/* 类型/句柄/宏定义 -------------------------------------------------*/
/* 引脚 和 串口 定义 
 * 默认是针对USART1的.
 * 注意: 通过修改这12个宏定义,可以支持USART1~UART7任意一个串口.
 */
#define USART3_TX_GPIO_PORT              GPIOC
#define USART3_TX_GPIO_PIN               GPIO_PIN_10						//橙色
#define USART3_TX_GPIO_AF                GPIO_AF8_UART4
#define USART3_TX_GPIO_CLK_ENABLE()      do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)   /* 发送引脚时钟使能 */

#define USART3_RX_GPIO_PORT              GPIOC
#define USART3_RX_GPIO_PIN               GPIO_PIN_11						//黄色
#define USART3_RX_GPIO_AF                GPIO_AF8_UART4
#define USART3_RX_GPIO_CLK_ENABLE()      do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)   /* 接收引脚时钟使能 */

#define USART3_UX                        UART4
#define USART3_UX_IRQn                   UART4_IRQn
#define USART3_UX_IRQHandler             UART4_IRQHandler
#define USART3_UX_CLK_ENABLE()           do{ __HAL_RCC_UART4_CLK_ENABLE(); }while(0)  /* USART1 时钟使能 */

#define USART3_REC_LEN   128             /* 定义最大接收字节数 200 */
#define USART3_EN_RX     1               /* 使能（1）/禁止（0）串口1接收 */
#define RXBUFFER3SIZE    1               /* 缓存大小 */

extern uint16_t USART3_RX_STA; 

/* 扩展变量 ---------------------------------------------------------*/
extern UART_HandleTypeDef g_uart3_handle;       /* UART句柄 */

extern uint8_t  g_usart3_rx_buf[USART3_REC_LEN];  /* 接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 */
extern uint16_t g_usart3_rx_sta;                 /* 接收状态标记 */
extern uint8_t g_rx_buffer3[RXBUFFER3SIZE];       /* HAL库USART接收Buffer */


/* 函数声明 ---------------------------------------------------------*/
void usart3_init(uint32_t baudrate);             /* 串口初始化函数 */

#endif /* __USART_H__ */

/******************** (C) Copyright nbufe ( End Of File ) ********************/
