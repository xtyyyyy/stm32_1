/*------------------------------------------------------------------------------
 * File name   : usart.h
 * Author      : nbufe
 * Copyright(C): 2021-2025 nbufe. All rights reserved.
 *------------------------------------------------------------------------------
 */
#ifndef __USART_H__
#define __USART_H__

/* 包含头文件 -------------------------------------------------------*/
#include "stdio.h"
#include "./SYSTEM/sys/sys.h"

/* 类型/句柄/宏定义 -------------------------------------------------*/
/* 引脚 和 串口 定义 
 * 默认是针对USART1的.
 * 注意: 通过修改这12个宏定义,可以支持USART1~UART7任意一个串口.
 */
#define USART_TX_GPIO_PORT              GPIOA
#define USART_TX_GPIO_PIN               GPIO_PIN_9				//蓝色OpenMV
#define USART_TX_GPIO_AF                GPIO_AF7_USART1
#define USART_TX_GPIO_CLK_ENABLE()      do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)   /* 发送引脚时钟使能 */

#define USART_RX_GPIO_PORT              GPIOA
#define USART_RX_GPIO_PIN               GPIO_PIN_10				//红色	Lora
#define USART_RX_GPIO_AF                GPIO_AF7_USART1
#define USART_RX_GPIO_CLK_ENABLE()      do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)   /* 接收引脚时钟使能 */

#define USART_UX                        USART1
#define USART_UX_IRQn                   USART1_IRQn
#define USART_UX_IRQHandler             USART1_IRQHandler
#define USART_UX_CLK_ENABLE()           do{ __HAL_RCC_USART1_CLK_ENABLE(); }while(0)  /* USART1 时钟使能 */

#define USART_REC_LEN   128             /* 定义最大接收字节数 200 */
#define USART_EN_RX     1               /* 使能（1）/禁止（0）串口1接收 */
#define RXBUFFERSIZE    1               /* 缓存大小 */

extern uint16_t USART_RX_STA; 

/* 扩展变量 ---------------------------------------------------------*/
extern UART_HandleTypeDef g_uart1_handle;       /* UART句柄 */

extern uint8_t  g_usart_rx_buf[USART_REC_LEN];  /* 接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 */
extern uint16_t g_usart_rx_sta;                 /* 接收状态标记 */
extern uint8_t g_rx_buffer[RXBUFFERSIZE];       /* HAL库USART接收Buffer */


/* 函数声明 ---------------------------------------------------------*/
void usart_init(uint32_t baudrate);             /* 串口初始化函数 */
void DMA_USART1_Init(void);
void send_hex_data(UART_HandleTypeDef *huart, uint8_t *hex_data);
#endif /* __USART_H__ */

/******************** (C) Copyright nbufe ( End Of File ) ********************/

