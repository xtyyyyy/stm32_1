/*-----------------------------------------------------------------------------
 *      (C) Copyright 2023-2032, nbufe. All Rights Reserved 
 *-----------------------------------------------------------------------------
 * File name   : usart.c
 * Description : 串口初始化代码(一般是串口1)，支持printf
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
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/usart/usart2.h" 
#include "./SYSTEM/usart/usart3.h" 
/* 类型/句柄/宏定义 -------------------------------------------------*/

/* 加入以下代码, 支持printf函数, 而不需要选择use MicroLIB */
#if 1
#if (__ARMCC_VERSION >= 6010050)                    /* 使用AC6编译器时 */
__asm(".global __use_no_semihosting\n\t");          /* 声明不使用半主机模式 */
__asm(".global __ARM_use_no_argv \n\t");            /* AC6下需要声明main函数为无参数格式，否则部分例程可能出现半主机模式 */

#else
/* 使用AC5编译器时, 要在这里定义__FILE 和 不使用半主机模式 */
#pragma import(__use_no_semihosting)

struct __FILE
{
    int handle;
    /* Whatever you require here. If the only file you are using is */
    /* standard output using printf() for debugging, no file handling */
    /* is required. */
};

#endif

/* 不使用半主机模式，至少需要重定义_ttywrch\_sys_exit\_sys_command_string函数,以同时兼容AC6和AC5模式 */
int _ttywrch(int ch)
{
    ch = ch;
    return ch;
}

/* 定义_sys_exit()以避免使用半主机模式 */
void _sys_exit(int x)
{
    x = x;
}

char *_sys_command_string(char *cmd, int len)
{
    return NULL;
}

/* FILE 在 stdio.h里面定义. */
FILE __stdout;

/* 重定义fputc函数, printf函数最终会通过调用fputc输出字符串到串口 */
//int fputc(int ch, FILE *f)
//{
//    while ((USART1->SR & 0X40) == 0);               /* 等待上一个字符发送完成 */

//    USART1->DR = (uint8_t)ch;                       /* 将要发送的字符 ch 写入到DR寄存器 */
//    return ch;
//}
int fputc(int ch, FILE *f)
{
	if(f == stdout){/* 将要发送的字符 ch 写入到DR寄存器 */
		while ((USART_UX->SR & 0X40) == 0);               /* 等待上一个字符发送完成 */
		USART_UX->DR = (uint8_t)ch; 
	}else{	/* 将要发送的字符 ch 写入到DR寄存器 */
		while ((USART2_UX->SR & 0X40) == 0);               /* 等待上一个字符发送完成 */
		USART2_UX->DR = (uint8_t)ch; 
	}
    return ch;
}

/**
 * @brief   发送十六进制数据到串口
 * @param   huart: UART句柄指针，指向已经初始化的UART_HandleTypeDef结构体
 * @param   hex_data: 指向存放十六进制数据的数组的指针
 * @param   data_len: 数据长度
 * @retval  无
 */
void send_hex_data(UART_HandleTypeDef *huart, uint8_t *hex_data)
{
	uint8_t data_len = sizeof(hex_data) / sizeof(hex_data[0]);  // 计算数组长度
    // 发送每个字节
    for (int i = 0; i < data_len; i++)
    {
        // 等待发送寄存器空
        while ((huart->Instance->SR & UART_FLAG_TXE) == 0);

        // 将数据发送到数据寄存器
        huart->Instance->DR = hex_data[i];
    }

    // 等待发送完成
    while ((huart->Instance->SR & UART_FLAG_TC) == 0);
}



//int fputc(int ch, FILE *f)
//{
//	uint8_t c = (uint8_t)ch;
//	if(f == stdout)
//	{
//		HAL_UART_Transmit(&amp,g_uart1_handle,&amp;c,1,1000);
//		HAL_UART_Transmit(&amp,g_uart2_handle,&amp;c,1,1000);
//	}
//	return ch;
//}
#endif


/* 变量定义 ---------------------------------------------------------*/
/* None. */

/* 函数原形 ---------------------------------------------------------*/
/* None. */

/* 函数体 -----------------------------------------------------------*/

#if USART_EN_RX                                     /* 如果使能了接收 */

/* 接收缓冲, 最大USART_REC_LEN个字节. */
uint8_t g_usart_rx_buf[USART_REC_LEN];

/*  接收状态
 *  bit15，      接收完成标志
 *  bit14，      接收到0x0d
 *  bit13~0，    接收到的有效字节数目
*/
uint16_t g_usart_rx_sta = 0;

uint8_t g_rx_buffer[RXBUFFERSIZE];                  /* HAL库使用的串口接收缓冲 */

UART_HandleTypeDef g_uart1_handle;                  /* UART句柄 */


/**
 * @brief       串口X初始化函数
 * @param       baudrate: 波特率, 根据自己需要设置波特率值
 * @note        注意: 必须设置正确的时钟源, 否则串口波特率就会设置异常.
 *              这里的USART的时钟源在sys_stm32_clock_init()函数中已经设置过了.
 * @retval      无
 */
void usart_init(uint32_t baudrate)
{
    g_uart1_handle.Instance = USART_UX;                         /* USART1 */
    g_uart1_handle.Init.BaudRate = baudrate;                    /* 波特率 */
    g_uart1_handle.Init.WordLength = UART_WORDLENGTH_8B;        /* 字长为8位数据格式 */
    g_uart1_handle.Init.StopBits = UART_STOPBITS_1;             /* 一个停止位 */
    g_uart1_handle.Init.Parity = UART_PARITY_NONE;              /* 无奇偶校验位 */
    g_uart1_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;        /* 无硬件流控 */
    g_uart1_handle.Init.Mode = UART_MODE_TX_RX;                 /* 收发模式 */
    HAL_UART_Init(&g_uart1_handle);                             /* HAL_UART_Init()会使能UART1 */
    
    /* 该函数会开启接收中断：标志位UART_IT_RXNE，并且设置接收缓冲以及接收缓冲接收最大数据量 */
    HAL_UART_Receive_IT(&g_uart1_handle, (uint8_t *)g_rx_buffer, RXBUFFERSIZE);
}

/**
 * @brief       UART底层初始化函数
 * @param       huart: UART句柄类型指针
 * @note        此函数会被HAL_UART_Init()调用
 *              完成时钟使能，引脚配置，中断配置
 * @retval      无
 */
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    GPIO_InitTypeDef gpio_init_struct;
    if(huart->Instance == USART_UX)                             /* 如果是串口1，进行串口1 MSP初始化 */
    {
        USART_UX_CLK_ENABLE();                                  /* USART1 时钟使能 */
        USART_TX_GPIO_CLK_ENABLE();                             /* 发送引脚时钟使能 */
        USART_RX_GPIO_CLK_ENABLE();                             /* 接收引脚时钟使能 */

        gpio_init_struct.Pin = USART_TX_GPIO_PIN;               /* TX引脚 */
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;                /* 复用推挽输出 */
        gpio_init_struct.Pull = GPIO_PULLUP;                    /* 上拉 */
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* 高速 */
        gpio_init_struct.Alternate = USART_TX_GPIO_AF;          /* 复用为USART1 */
        HAL_GPIO_Init(USART_TX_GPIO_PORT, &gpio_init_struct);   /* 初始化发送引脚 */

        gpio_init_struct.Pin = USART_RX_GPIO_PIN;               /* RX引脚 */
        gpio_init_struct.Alternate = USART_RX_GPIO_AF;          /* 复用为USART1 */
        HAL_GPIO_Init(USART_RX_GPIO_PORT, &gpio_init_struct);   /* 初始化接收引脚 */

#if USART_EN_RX
        HAL_NVIC_EnableIRQ(USART_UX_IRQn);                      /* 使能USART1中断通道 */
        HAL_NVIC_SetPriority(USART_UX_IRQn, 3, 3);              /* 抢占优先级3，子优先级3 */
#endif
    }
	    if(huart->Instance == USART2_UX)                             /* 如果是串口1，进行串口1 MSP初始化 */
    {
        USART2_UX_CLK_ENABLE();                                  /* USART1 时钟使能 */
        USART2_TX_GPIO_CLK_ENABLE();                             /* 发送引脚时钟使能 */
        USART2_RX_GPIO_CLK_ENABLE();                             /* 接收引脚时钟使能 */

        gpio_init_struct.Pin = USART2_TX_GPIO_PIN;               /* TX引脚 */
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;                /* 复用推挽输出 */
        gpio_init_struct.Pull = GPIO_PULLUP;                    /* 上拉 */
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* 高速 */
        gpio_init_struct.Alternate = USART2_TX_GPIO_AF;          /* 复用为USART1 */
        HAL_GPIO_Init(USART2_TX_GPIO_PORT, &gpio_init_struct);   /* 初始化发送引脚 */

        gpio_init_struct.Pin = USART2_RX_GPIO_PIN;               /* RX引脚 */
        gpio_init_struct.Alternate = USART2_RX_GPIO_AF;          /* 复用为USART1 */
        HAL_GPIO_Init(USART2_RX_GPIO_PORT, &gpio_init_struct);   /* 初始化接收引脚 */

#if USART_EN_RX
        HAL_NVIC_EnableIRQ(USART2_UX_IRQn);                      /* 使能USART1中断通道 */
        HAL_NVIC_SetPriority(USART2_UX_IRQn, 3, 4);              /* 抢占优先级3，子优先级3 */
#endif
    }
	if(huart->Instance == USART3_UX)                             /* 如果是串口1，进行串口1 MSP初始化 */
		{
			USART3_UX_CLK_ENABLE();                                  /* USART1 时钟使能 */
			USART3_TX_GPIO_CLK_ENABLE();                             /* 发送引脚时钟使能 */
			USART3_RX_GPIO_CLK_ENABLE();                             /* 接收引脚时钟使能 */

			gpio_init_struct.Pin = USART3_TX_GPIO_PIN;               /* TX引脚 */
			gpio_init_struct.Mode = GPIO_MODE_AF_PP;                /* 复用推挽输出 */
			gpio_init_struct.Pull = GPIO_PULLUP;                    /* 上拉 */
			gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* 高速 */
			gpio_init_struct.Alternate = USART3_TX_GPIO_AF;          /* 复用为USART1 */
			HAL_GPIO_Init(USART3_TX_GPIO_PORT, &gpio_init_struct);   /* 初始化发送引脚 */

			gpio_init_struct.Pin = USART3_RX_GPIO_PIN;               /* RX引脚 */
			gpio_init_struct.Alternate = USART3_RX_GPIO_AF;          /* 复用为USART1 */
			HAL_GPIO_Init(USART3_RX_GPIO_PORT, &gpio_init_struct);   /* 初始化接收引脚 */

	#if USART_EN_RX
			HAL_NVIC_EnableIRQ(USART3_UX_IRQn);                      /* 使能USART1中断通道 */
			HAL_NVIC_SetPriority(USART3_UX_IRQn, 3, 4);              /* 抢占优先级3，子优先级3 */
	#endif
		}
}



int buma_zhuanhuan(uint16_t buma)
{
	uint16_t fanma=0;
	signed int yuanma=0;
	uint16_t index,temp=0;
	
	if(buma & 0x8000)
	{
		fanma=buma-1;
		
		for(index=0;index<15;index++)
		{
		   temp=fanma>>index;
		   temp=~temp;
		   temp&=0x01;
		   temp=temp<<index;
		   yuanma+=temp;
		 }
		
		if(fanma&0x8000)
		{
		   yuanma=-yuanma;
		}
	}
	else yuanma = buma;
	
	return yuanma;
}



void uart_echo(UART_HandleTypeDef *huart, uint8_t *data, uint16_t length)
{
    HAL_UART_Transmit(huart, data, length, HAL_MAX_DELAY);  // 使用HAL库的UART发送函数直接发送数据
}


uint8_t USARTReceIn = 0;
uint8_t USARTReceFullFlag = 0;
uint16_t USARTReceBuff[11] = {0};

uint8_t USARTReceIn3 = 0;
uint8_t USARTReceFullFlag3 = 0;
char USARTReceBuff3[11] = {0};
#define startflag		0x55
float rol = 0;
float pit = 0;
float yaw = 0;

uint8_t num = 0;
int distance = 0;
volatile int open_id,open_x,open_y;
/**
 * @brief       Rx传输回调函数
 * @param       huart: UART句柄类型指针
 * @retval      无
 */
 
 
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == USART_UX)             /* 如果是串口1 */
    {
        if((g_usart_rx_sta & 0x8000) == 0)      /* 接收未完成 */
        {
            if(g_usart_rx_sta & 0x4000)         /* 接收到了0x0d */
            {
                if(g_rx_buffer[0] != 0x0a) 
                {
                    g_usart_rx_sta = 0;         /* 接收错误,重新开始 */
                }
                else 
                {
                    g_usart_rx_sta |= 0x8000;   /* 接收完成了 */
                }
            }
            else                                /* 还没收到0X0D */
            {
                if(g_rx_buffer[0] == 0x0d)
                {
                    g_usart_rx_sta |= 0x4000;
                }
                else
                {
                    g_usart_rx_buf[g_usart_rx_sta & 0X3FFF] = g_rx_buffer[0] ;
                    g_usart_rx_sta++;
                    if(g_usart_rx_sta > (USART_REC_LEN - 1))
                    {
                        g_usart_rx_sta = 0;     /* 接收数据错误,重新开始接收 */
                    }
                }
            }
        }
		//uart_echo(&g_uart2_handle, g_rx_buffer, RXBUFFER2SIZE);  //将2号串口的值显示到1号串口上
       // HAL_UART_Receive_DMA(&g_uart1_handle, (uint8_t *)g_rx_buffer, RXBUFFERSIZE);
		
        HAL_UART_Receive_IT(&g_uart1_handle, (uint8_t *)g_rx_buffer, RXBUFFERSIZE);
    }
	
	if(huart->Instance == USART2_UX)             /* 如果是串口1 */
    {
		if ((g_usart2_rx_sta & 0x8000) == 0)      /* 接收未完成 */
    {
        if ((g_usart2_rx_sta & 0x4000) == 0)   /* 还没收到0x0D */
        {
            if (g_rx_buffer2[0] == 0x55)
            {
                g_usart2_rx_buf[g_usart2_rx_sta & 0x3FFF] = g_rx_buffer2[0];
                g_usart2_rx_sta = 1;  /* 设置接收状态为1，开始接收数据 */
            }
        }
        else  /* 已经收到0x0D，接收数据阶段 */
        {
            g_usart2_rx_buf[g_usart2_rx_sta & 0x3FFF] = g_rx_buffer2[0];
            g_usart2_rx_sta++;
            
            if (g_usart2_rx_sta > (USART2_REC_LEN - 1))
            {
                g_usart2_rx_sta = 0;  /* 接收数据错误，重新开始接收 */
            }
            else if (g_rx_buffer2[0] == 0x0A)
            {
                g_usart2_rx_sta |= 0x8000;  /* 接收完成 */
            }
        }
    }
		//fprintf(stderr,"%s",g_rx_buffer2);
		
		switch(USARTReceIn)
		{
			case 0: if(g_rx_buffer2[0] == startflag)
				USARTReceBuff[USARTReceIn++] = g_rx_buffer2[0];
			else 
				USARTReceIn = 0;
			break;
			
			default:
				USARTReceBuff[USARTReceIn++] = g_rx_buffer2[0];
			break;
		}
		if(USARTReceIn >= 11)
		{
			USARTReceFullFlag = 1;
		}
		if(USARTReceFullFlag)
		{
			if(USARTReceBuff[0] == 0x55 && USARTReceBuff[1] == 0x53)
			{
				rol = (buma_zhuanhuan(USARTReceBuff[2] | (USARTReceBuff[3]<<8) )) / 32768.0 * 180;
				//printf("%f,", rol);
				pit = (buma_zhuanhuan(USARTReceBuff[4] | (USARTReceBuff[5]<<8) )) / 32768.0 * 180;
				//printf("%f,", pit);
				yaw = (buma_zhuanhuan(USARTReceBuff[6] | (USARTReceBuff[7]<<8) )) / 32768.0 * 180;
				//printf("%f\r\n", yaw);
			}
			USARTReceFullFlag = 0;
			USARTReceIn = 0;
		}
		
        HAL_UART_Receive_IT(&g_uart2_handle, (uint8_t *)g_rx_buffer2, RXBUFFER2SIZE);
		
    }
	if(huart->Instance == USART3_UX)             /* 如果是串口1 */
    {
			//printf("1111\r\n");
		
		switch (USARTReceIn3) {
            case 0:
                if (g_rx_buffer3[0] == 'i') {
					num++;
					if(num==1)
                    USARTReceBuff3[USARTReceIn3++] = g_rx_buffer3[0];
                } else {
                    USARTReceIn3 = 0;
                }
                break;
            default:
				if (g_rx_buffer3[0] == '.')
				{
					USARTReceFullFlag3 = 1;
					//printf("111\r\n");
					num=0;
				}
				USARTReceBuff3[USARTReceIn3++] = g_rx_buffer3[0];
                break;
        }
        


       if(USARTReceFullFlag3 == 1)
			{
				sscanf(USARTReceBuff3,"i%d,%d,%d.",&open_id,&open_x,&open_y);
				//printf("i%d,x%d,y%d\r\n",open_id,open_x,open_y);

			USARTReceFullFlag3 = 0;
			USARTReceIn3 = 0;
			}
        HAL_UART_Receive_IT(&g_uart3_handle, (uint8_t *)g_rx_buffer3, RXBUFFER3SIZE);
				//uart_echo(&g_uart1_handle, g_rx_buffer3, RXBUFFER3SIZE);
						

			//printf("id%d,x%d,y%d\r\n", id,x,y);
    }
}

DMA_HandleTypeDef hdma_usart1_rx;
DMA_HandleTypeDef hdma_usart1_tx;

// DMA初始化配置
void DMA_USART1_Init(void) {
  // DMA发送配置
  hdma_usart1_tx.Instance = DMA2_Stream7;
  hdma_usart1_tx.Init.Channel = DMA_CHANNEL_4;
  hdma_usart1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
  hdma_usart1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
  hdma_usart1_tx.Init.MemInc = DMA_MINC_ENABLE;
  hdma_usart1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
  hdma_usart1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
  hdma_usart1_tx.Init.Mode = DMA_NORMAL;
  hdma_usart1_tx.Init.Priority = DMA_PRIORITY_LOW;
  hdma_usart1_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
  HAL_DMA_Init(&hdma_usart1_tx);
  __HAL_LINKDMA(&g_uart1_handle, hdmatx, hdma_usart1_tx);

  // DMA接收配置
  hdma_usart1_rx.Instance = DMA2_Stream2;
  hdma_usart1_rx.Init.Channel = DMA_CHANNEL_4;
  hdma_usart1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
  hdma_usart1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
  hdma_usart1_rx.Init.MemInc = DMA_MINC_ENABLE;
  hdma_usart1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
  hdma_usart1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
  hdma_usart1_rx.Init.Mode = DMA_NORMAL;
  hdma_usart1_rx.Init.Priority = DMA_PRIORITY_HIGH;
  hdma_usart1_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
  HAL_DMA_Init(&hdma_usart1_rx);
  __HAL_LINKDMA(&g_uart1_handle, hdmarx, hdma_usart1_rx);
}

/**
 * @brief       串口1中断服务函数
 * @param       无
 * @retval      无
 */


void USART_UX_IRQHandler(void)
{ 
    HAL_UART_IRQHandler(&g_uart1_handle);       /* 调用HAL库中断处理公用函数 */
}

#endif


/******************** (C) Copyright nbufe ( End Of File ) ********************/

