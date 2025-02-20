#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart2.h"

/* �������� ---------------------------------------------------------*/
/* None. */

/* ����ԭ�� ---------------------------------------------------------*/
/* None. */

/* ������ -----------------------------------------------------------*/

#if USART2_EN_RX                                     /* ���ʹ���˽��� */

/* ���ջ���, ���USART2_REC_LEN���ֽ�. */
uint8_t g_usart2_rx_buf[USART2_REC_LEN];

/*  ����״̬
 *  bit15��      ������ɱ�־
 *  bit14��      ���յ�0x0d
 *  bit13~0��    ���յ�����Ч�ֽ���Ŀ
*/
uint16_t g_usart2_rx_sta = 0;

uint8_t g_rx_buffer2[RXBUFFER2SIZE];                  /* HAL��ʹ�õĴ��ڽ��ջ��� */

UART_HandleTypeDef g_uart2_handle;                  /* UART��� */


/**
 * @brief       ����X��ʼ������
 * @param       baudrate: ������, �����Լ���Ҫ���ò�����ֵ
 * @note        ע��: ����������ȷ��ʱ��Դ, ���򴮿ڲ����ʾͻ������쳣.
 *              �����USART��ʱ��Դ��sys_stm32_clock_init()�������Ѿ����ù���.
 * @retval      ��
 */
void usart2_init(uint32_t baudrate)
{
    g_uart2_handle.Instance = USART2_UX;                         /* USART1 */
    g_uart2_handle.Init.BaudRate = baudrate;                    /* ������ */
    g_uart2_handle.Init.WordLength = UART_WORDLENGTH_8B;        /* �ֳ�Ϊ8λ���ݸ�ʽ */
    g_uart2_handle.Init.StopBits = UART_STOPBITS_1;             /* һ��ֹͣλ */
    g_uart2_handle.Init.Parity = UART_PARITY_NONE;              /* ����żУ��λ */
    g_uart2_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;        /* ��Ӳ������ */
    g_uart2_handle.Init.Mode = UART_MODE_TX_RX;                 /* �շ�ģʽ */
    HAL_UART_Init(&g_uart2_handle);                             /* HAL_UART_Init()��ʹ��UART1 */
    
    /* �ú����Ὺ�������жϣ���־λUART_IT_RXNE���������ý��ջ����Լ����ջ��������������� */
    HAL_UART_Receive_IT(&g_uart2_handle, (uint8_t *)g_rx_buffer2, RXBUFFER2SIZE);
}

/**
 * @brief       UART�ײ��ʼ������
 * @param       huart: UART�������ָ��
 * @note        �˺����ᱻHAL_UART_Init()����
 *              ���ʱ��ʹ�ܣ��������ã��ж�����
 * @retval      ��
 */
//void HAL_UART_MspInit(UART_HandleTypeDef *huart)
//{
//    GPIO_InitTypeDef gpio_init_struct;
//    if(huart->Instance == USART2_UX)                             /* ����Ǵ���1�����д���1 MSP��ʼ�� */
//    {
//        USART2_UX_CLK_ENABLE();                                  /* USART1 ʱ��ʹ�� */
//        USART2_TX_GPIO_CLK_ENABLE();                             /* ��������ʱ��ʹ�� */
//        USART2_RX_GPIO_CLK_ENABLE();                             /* ��������ʱ��ʹ�� */

//        gpio_init_struct.Pin = USART2_TX_GPIO_PIN;               /* TX���� */
//        gpio_init_struct.Mode = GPIO_MODE_AF_PP;                /* ����������� */
//        gpio_init_struct.Pull = GPIO_PULLUP;                    /* ���� */
//        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* ���� */
//        gpio_init_struct.Alternate = USART2_TX_GPIO_AF;          /* ����ΪUSART1 */
//        HAL_GPIO_Init(USART2_TX_GPIO_PORT, &gpio_init_struct);   /* ��ʼ���������� */

//        gpio_init_struct.Pin = USART2_RX_GPIO_PIN;               /* RX���� */
//        gpio_init_struct.Alternate = USART2_RX_GPIO_AF;          /* ����ΪUSART1 */
//        HAL_GPIO_Init(USART2_RX_GPIO_PORT, &gpio_init_struct);   /* ��ʼ���������� */

//#if USART2_EN_RX
//        HAL_NVIC_EnableIRQ(USART2_UX_IRQn);                      /* ʹ��USART1�ж�ͨ�� */
//        HAL_NVIC_SetPriority(USART2_UX_IRQn, 3, 4);              /* ��ռ���ȼ�3�������ȼ�3 */
//#endif
//    }
//}

/**
 * @brief       Rx����ص�����
 * @param       huart: UART�������ָ��
 * @retval      ��
 */
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//    if(huart->Instance == USART2_UX)             /* ����Ǵ���1 */
//    {
//        if((g_usart2_rx_sta & 0x8000) == 0)      /* ����δ��� */
//        {
//            if(g_usart2_rx_sta & 0x4000)         /* ���յ���0x0d */
//            {
//                if(g_rx_buffer2[0] != 0x0a) 
//                {
//                    g_usart2_rx_sta = 0;         /* ���մ���,���¿�ʼ */
//                }
//                else 
//                {
//                    g_usart2_rx_sta |= 0x8000;   /* ��������� */
//                }
//            }
//            else                                /* ��û�յ�0X0D */
//            {
//                if(g_rx_buffer2[0] == 0x0d)
//                {
//                    g_usart2_rx_sta |= 0x4000;
//                }
//                else
//                {
//                    g_usart2_rx_buf[g_usart2_rx_sta & 0X3FFF] = g_rx_buffer2[0] ;
//                    g_usart2_rx_sta++;
//                    if(g_usart2_rx_sta > (USART2_REC_LEN - 1))
//                    {
//                        g_usart2_rx_sta = 0;     /* �������ݴ���,���¿�ʼ���� */
//                    }
//                }
//            }
//        }
//        HAL_UART_Receive_IT(&g_uart2_handle, (uint8_t *)g_rx_buffer2, RXBUFFER2SIZE);
//    }
//}

/**
 * @brief       ����1�жϷ�����
 * @param       ��
 * @retval      ��
 */


void USART2_UX_IRQHandler(void)
{ 
    HAL_UART_IRQHandler(&g_uart2_handle);       /* ����HAL���жϴ����ú��� */
}

#endif


/******************** (C) Copyright nbufe ( End Of File ) ********************/
