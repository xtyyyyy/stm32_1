#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/usart/usart2.h"
#include "./SYSTEM/usart/usart3.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/KEY/key.h"
#include "./BSP/SRAM/sram.h"
#include "./BSP/Encoder/Encoder.h"
#include "./BSP/Motor/Motor.h"
#include "./BSP/Red/Red.h"
#include "./MALLOC/malloc.h"

#include "freertos_demo.h"

/* 私有类型定义 -----------------------------------------------------*/
/* None. */

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    sys_stm32_clock_init(336, 16, 2, 7); /* 设置时钟,168Mhz */
    delay_init(168);                    /* 延时初始化 */
    usart_init(115200);                 /* 串口初始化为115200 */	
	usart2_init(115200);                 /* 串口初始化为115200 */	
	usart3_init(115200);
    sram_init();                        /* SRAM初始化 */
    my_mem_init(SRAMIN);                /* 初始化内部SRAM内存池 */
    my_mem_init(SRAMEX);                /* 初始化外部SRAM内存池 */
    my_mem_init(SRAMCCM);               /* 初始化内部CCM内存池 */
	fprintf(stderr,"%c%c%c%c%c",0xFF, 0xAA, 0x69, 0x88, 0xB5);
	delay_ms(100);
	fprintf(stderr,"%c%c%c%c%c%c%c%c%c%c", 0xFF, 0xAA, 0x01,0x08, 0x00, 0xFF, 0xAA, 0x00, 0x00, 0x00);  //陀螺仪置0
	delay_ms(1000);
	//while(R3 || R4);
	printf("ddd");
    freertos_demo();                    /* 运行FreeRTOS例程 */
}

