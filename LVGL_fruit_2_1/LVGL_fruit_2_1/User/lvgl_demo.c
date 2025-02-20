/**
 ****************************************************************************************************
 * @file        lvgl_demo.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2022-01-11
 * @brief       LVGL V8操作系统移植
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
 ****************************************************************************************************
 */
#include <string.h>
#include <stdio.h>
#include "lvgl_demo.h"
#include "./BSP/LED/led.h"
#include "./BSP/DHT11/DHT11.h"
#include "FreeRTOS.h"
#include "task.h"
#include "./SYSTEM/usart/usart2.h"
#include "lvgl.h"
#include "lv_port_disp_template.h"
#include "lv_port_indev_template.h"
#include "lv_demo_stress.h"
#include "./BSP/BH1750/bh1750.h"
#include "./BSP/esp8266/esp8266.h"
#include "./BSP/DENG/deng.h"
#include "./BSP/JSON/cJSON.h"

/******************************************************************************************************/
/*FreeRTOS配置*/

/* START_TASK 任务 配置
 * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
 */
#define START_TASK_PRIO     1           /* 任务优先级 */
#define START_STK_SIZE      128         /* 任务堆栈大小 */
TaskHandle_t StartTask_Handler;         /* 任务句柄 */
void start_task(void *pvParameters);    /* 任务函数 */

/* LV_DEMO_TASK 任务 配置
 * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
 */
#define LV_DEMO_TASK_PRIO   3           /* 任务优先级 */
#define LV_DEMO_STK_SIZE    1024        /* 任务堆栈大小 */
TaskHandle_t LV_DEMOTask_Handler;       /* 任务句柄 */
void lv_demo_task(void *pvParameters);  /* 任务函数 */

/* LED_TASK 任务 配置
 * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
 */
#define LED_TASK_PRIO       4           /* 任务优先级 */
#define LED_STK_SIZE        128         /* 任务堆栈大小 */
TaskHandle_t LEDTask_Handler;           /* 任务句柄 */
void led_task(void *pvParameters);      /* 任务函数 */
/******************************************************************************************************/

#define DHT11_TASK_PRIO       4           /* 任务优先级 */
#define DHT11_STK_SIZE        128         /* 任务堆栈大小 */
TaskHandle_t DHT11Task_Handler;           /* 任务句柄 */
void dht11_task(void *pvParameters);      /* 任务函数 */

#define MQTT_TASK_PRIO       4           /* 任务优先级 */
#define MQTT_STK_SIZE        128        /* 任务堆栈大小 */
TaskHandle_t MQTTTask_Handler;           /* 任务句柄 */
void mqtt_task(void *pvParameters);      /* 任务函数 */

#define CJSON_TASK_PRIO       3           /* 任务优先级 */
#define CJSON_STK_SIZE        256         /* 任务堆栈大小 */
TaskHandle_t CJSONTask_Handler;           /* 任务句柄 */
void cjson_task(void *pvParameters);      /* 任务函数 */


/******************************************************************************************************/
DHT11_Data_TypeDef DHT11_Data;
float light1 = 0;
extern char rx_buffer[236];

/******************************************************************************************************/
/**
 * @brief       lvgl_demo入口函数
 * @param       无
 * @retval      无
 */
void lvgl_demo(void)
{
    lv_init();                                          /* lvgl系统初始化 */
    lv_port_disp_init();                                /* lvgl显示接口初始化,放在lv_init()的后面 */
    lv_port_indev_init();                               /* lvgl输入接口初始化,放在lv_init()的后面 */

    xTaskCreate((TaskFunction_t )start_task,            /* 任务函数 */
                (const char*    )"start_task",          /* 任务名称 */
                (uint16_t       )START_STK_SIZE,        /* 任务堆栈大小 */
                (void*          )NULL,                  /* 传递给任务函数的参数 */
                (UBaseType_t    )START_TASK_PRIO,       /* 任务优先级 */
                (TaskHandle_t*  )&StartTask_Handler);   /* 任务句柄 */

    vTaskStartScheduler();                              /* 开启任务调度 */
}

/**
 * @brief       start_task
 * @param       pvParameters : 传入参数(未用到)
 * @retval      无
 */
void start_task(void *pvParameters)
{
    pvParameters = pvParameters;
    
    taskENTER_CRITICAL();           /* 进入临界区 */

    /* 创建LVGL任务 */
    xTaskCreate((TaskFunction_t )lv_demo_task,
                (const char*    )"lv_demo_task",
                (uint16_t       )LV_DEMO_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )LV_DEMO_TASK_PRIO,
                (TaskHandle_t*  )&LV_DEMOTask_Handler);

    /* LED测试任务 */
    xTaskCreate((TaskFunction_t )led_task,
                (const char*    )"led_task",
                (uint16_t       )LED_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )LED_TASK_PRIO,
                (TaskHandle_t*  )&LEDTask_Handler);
				
    xTaskCreate((TaskFunction_t )dht11_task,
                (const char*    )"dht11_task",
                (uint16_t       )DHT11_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )DHT11_TASK_PRIO,
                (TaskHandle_t*  )&DHT11Task_Handler);
				
    xTaskCreate((TaskFunction_t )mqtt_task,
                (const char*    )"mqtt_task",
                (uint16_t       )MQTT_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )MQTT_TASK_PRIO,
                (TaskHandle_t*  )&MQTTTask_Handler);
	
    xTaskCreate((TaskFunction_t )cjson_task,
                (const char*    )"cjson_task",
                (uint16_t       )CJSON_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )CJSON_TASK_PRIO,
                (TaskHandle_t*  )&CJSONTask_Handler);
				
				

    taskEXIT_CRITICAL();            /* 退出临界区 */
    vTaskDelete(StartTask_Handler); /* 删除开始任务 */
}

/**
 * @brief       LVGL运行例程
 * @param       pvParameters : 传入参数(未用到)
 * @retval      无
 */
void lv_demo_task(void *pvParameters)
{
    pvParameters = pvParameters;
    
    //lv_demo_stress();       /* 测试的demo */
	
	//my_demo();
    while(1)
    {
		my_demo();
		//rgb565_test(); 
        lv_timer_handler(); /* LVGL计时器 */
        vTaskDelay(5);
    }
}

/**
 * @brief       led_task
 * @param       pvParameters : 传入参数(未用到)
 * @retval      无
 */
void led_task(void *pvParameters)
{
    pvParameters = pvParameters;
    
    while(1)
    {
        LED0_TOGGLE();
        vTaskDelay(1000);
    }
}

void dht11_task(void *pvParameters)
{
    pvParameters = pvParameters;
    
    while(1)
    {
				
		DHT11_ReadData(&DHT11_Data);	
		light1 = read_BH1750();	
		if((int)read_BH1750()<=30)
			DENG(1);
		//printf("light_buf: %f", read_BH1750());
        vTaskDelay(300);
    }
}

//cJSON* cjson_test = NULL;
cJSON* cjson_name = NULL;

cJSON* cjson_items = NULL;
cJSON* cjson_items_LEDSwitch = NULL;
cJSON* cjson_items_LEDSwitch_value = NULL;
uint8_t flag_json = 0;

char *message;

void cjson_task(void *pvParameters)
{
    pvParameters = pvParameters;
    
    while(1)
    {
		//char *message = "{\"deviceType\":\"CustomCategory\",\"iotId\":\"7qgWBqB2LZuLuBPpQH9Gk266f0\",\"requestId\":\"null\",\"checkFailedData\":{},\"productKey\":\"k266fnG1Vi1\",\"gmtCreate\":1736408956479,\"deviceName\":\"app_\",\"items\":{\"LEDSwitch\":{\"time\":1736408956435,\"value\":1}}}";
		//cjson_items_LEDSwitch_value->valueint = -1;
		cJSON* cjson_test = NULL;
		message = rx_buffer;
		cjson_test = cJSON_Parse(message);
		if(cjson_test == NULL)
		{
			printf("parse fail.\n");
			printf("%s\r\n",rx_buffer);
		}
		else if(flag_json)
		{
		/* 依次根据名称提取JSON数据（键值对） */
			cjson_name = cJSON_GetObjectItem(cjson_test, "deviceName");

			//fprintf(stderr,"n %s\n", cjson_name->valuestring);

		/* 解析嵌套json数据 */
			cjson_items = cJSON_GetObjectItem(cjson_test, "items");
			cjson_items_LEDSwitch = cJSON_GetObjectItem(cjson_items, "LEDSwitch");
			cjson_items_LEDSwitch_value = cJSON_GetObjectItem(cjson_items_LEDSwitch, "value");
			//fprintf(stderr,"led:%d\n", cjson_items_LEDSwitch_value->valueint);
			flag_json = 0;
		}
		cJSON_Delete(cjson_test);
			vTaskDelay(1000);
    }
}



void mqtt_task(void *pvParameters)
{ 
    pvParameters = pvParameters;
    
    while(1)
    {
		fprintf(stderr,"AT+MQTTPUBRAW=0,\"/sys/%s/%s/thing/event/property/post\",%d,1,0\r\n",PRODUCTID,DEVICENAME,83);
		vTaskDelay(30);
		fprintf(stderr,"{\"params\":{\"temp\":%d,\"Humd\":%d,\"LightLux\":%5d,\"servo\":30,\"bump\":0,\"LEDSwitch\":1}}\r\n",\
				DHT11_Data.temp_int,DHT11_Data.humi_int,(int)light1);//消息内容	
        vTaskDelay(5000);
    }
}

