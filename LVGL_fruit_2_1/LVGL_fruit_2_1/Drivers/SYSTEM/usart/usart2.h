/*------------------------------------------------------------------------------
 * File name   : usart.h
 * Author      : nbufe
 * Copyright(C): 2021-2025 nbufe. All rights reserved.
 *------------------------------------------------------------------------------
 */
#ifndef __usart2_H__
#define __usart2_H__

/* ����ͷ�ļ� -------------------------------------------------------*/
#include "stdio.h"
#include "./SYSTEM/sys/sys.h"

/* ����/���/�궨�� -------------------------------------------------*/
/* ���� �� ���� ���� 
 * Ĭ�������USART1��.
 * ע��: ͨ���޸���12���궨��,����֧��USART1~UART7����һ������.
 */
#define USART2_TX_GPIO_PORT              GPIOA
#define USART2_TX_GPIO_PIN               GPIO_PIN_2						//��ɫ
#define USART2_TX_GPIO_AF                GPIO_AF7_USART2
#define USART2_TX_GPIO_CLK_ENABLE()      do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)   /* ��������ʱ��ʹ�� */

#define USART2_RX_GPIO_PORT              GPIOA
#define USART2_RX_GPIO_PIN               GPIO_PIN_3						//��ɫ
#define USART2_RX_GPIO_AF                GPIO_AF7_USART2
#define USART2_RX_GPIO_CLK_ENABLE()      do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)   /* ��������ʱ��ʹ�� */

#define USART2_UX                        USART2
#define USART2_UX_IRQn                   USART2_IRQn
#define USART2_UX_IRQHandler             USART2_IRQHandler
#define USART2_UX_CLK_ENABLE()           do{ __HAL_RCC_USART2_CLK_ENABLE(); }while(0)  /* USART1 ʱ��ʹ�� */

#define USART2_REC_LEN   128             /* �����������ֽ��� 200 */
#define USART2_EN_RX     1               /* ʹ�ܣ�1��/��ֹ��0������1���� */
#define RXBUFFER2SIZE    1               /* �����С */



/* ��չ���� ---------------------------------------------------------*/
extern UART_HandleTypeDef g_uart2_handle;       /* UART��� */

extern uint8_t  g_usart2_rx_buf[USART2_REC_LEN];  /* ���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� */
extern uint16_t g_usart2_rx_sta;                 /* ����״̬��� */
extern uint8_t g_rx_buffer2[RXBUFFER2SIZE];       /* HAL��USART����Buffer */


/* �������� ---------------------------------------------------------*/
void usart2_init(uint32_t baudrate);             /* ���ڳ�ʼ������ */

#endif /* __USART_H__ */

/******************** (C) Copyright nbufe ( End Of File ) ********************/
