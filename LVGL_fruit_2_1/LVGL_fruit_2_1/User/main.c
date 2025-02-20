/**
 ****************************************************************************************************
 * @file        main.c
 * @author      xty
 * @version     V2.1
 * @date        2025-1-24
 * @brief       ���ܹ�԰LVGL
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
    HAL_Init();                                 /* ��ʼ��HAL�� */
    sys_stm32_clock_init(360, 25, 2, 8);        /* ����ʱ��,180Mhz */
    delay_init(180);                            /* ��ʱ��ʼ�� */
    usart_init(115200);                         /* ���ڳ�ʼ��Ϊ115200 */
	usart2_init(115200);
    led_init();                                 /* ��ʼ��LED */
    key_init();                                 /* ��ʼ������ */
    sdram_init();                               /* SRAM��ʼ�� */
    my_mem_init(SRAMIN);                        /* ��ʼ���ڲ�SRAM�ڴ�� */
    my_mem_init(SRAMEX);                        /* ��ʼ���ⲿSRAM�ڴ�� */
	Init_BH1750();
	
    //mqtt_init();

	deng_init();
	bump_init();
	
	printf("111");
    lvgl_demo();                                /* ����FreeRTOS���� */
}
