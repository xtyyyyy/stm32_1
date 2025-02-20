/**
 ****************************************************************************************************
 * @file        main.c
 * @author      xty
 * @version     V2.1
 * @date        2025-1-24
 * @brief       智能果园LVGL
 ****************************************************************************************************
 */

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/usart/usart2.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/KEY/key.h"
#include "./BSP/SDRAM/sdram.h"
#include "./BSP/DHT11/DHT11.h"
#include "./BSP/BH1750/bh1750.h"
#include "./BSP/SOIL/soil.h"
#include "./BSP/DENG/deng.h"
#include "./MALLOC/malloc.h"
#include "./BSP/esp8266/esp8266.h"
#include "lvgl_demo.h"
#include "./BSP/JSON/cJSON.h"


int main(void)
{
    HAL_Init();                                 /* 初始化HAL库 */
    sys_stm32_clock_init(360, 25, 2, 8);        /* 设置时钟,180Mhz */
    delay_init(180);                            /* 延时初始化 */
    usart_init(115200);                         /* 串口初始化为115200 */
	usart2_init(115200);
    led_init();                                 /* 初始化LED */
    key_init();                                 /* 初始化按键 */
    sdram_init();                               /* SRAM初始化 */
    my_mem_init(SRAMIN);                        /* 初始化内部SRAM内存池 */
    my_mem_init(SRAMEX);                        /* 初始化外部SRAM内存池 */
	Init_BH1750();
	
    //mqtt_init();

	deng_init();
	bump_init();
	
	printf("111");
    lvgl_demo();                                /* 运行FreeRTOS例程 */
}
