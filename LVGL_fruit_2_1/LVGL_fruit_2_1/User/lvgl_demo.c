/**
 ****************************************************************************************************
 * @file        lvgl_demo.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2022-01-11
 * @brief       LVGL V8����ϵͳ��ֲ
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� ������ F429������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
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
/*FreeRTOS����*/

/* START_TASK ���� ����
 * ����: ������ �������ȼ� ��ջ��С ��������
 */
#define START_TASK_PRIO     1           /* �������ȼ� */
#define START_STK_SIZE      128         /* �����ջ��С */
TaskHandle_t StartTask_Handler;         /* ������ */
void start_task(void *pvParameters);    /* ������ */

/* LV_DEMO_TASK ���� ����
 * ����: ������ �������ȼ� ��ջ��С ��������
 */
#define LV_DEMO_TASK_PRIO   3           /* �������ȼ� */
#define LV_DEMO_STK_SIZE    1024        /* �����ջ��С */
TaskHandle_t LV_DEMOTask_Handler;       /* ������ */
void lv_demo_task(void *pvParameters);  /* ������ */

/* LED_TASK ���� ����
 * ����: ������ �������ȼ� ��ջ��С ��������
 */
#define LED_TASK_PRIO       4           /* �������ȼ� */
#define LED_STK_SIZE        128         /* �����ջ��С */
TaskHandle_t LEDTask_Handler;           /* ������ */
void led_task(void *pvParameters);      /* ������ */
/******************************************************************************************************/

#define DHT11_TASK_PRIO       4           /* �������ȼ� */
#define DHT11_STK_SIZE        128         /* �����ջ��С */
TaskHandle_t DHT11Task_Handler;           /* ������ */
void dht11_task(void *pvParameters);      /* ������ */

#define MQTT_TASK_PRIO       4           /* �������ȼ� */
#define MQTT_STK_SIZE        128        /* �����ջ��С */
TaskHandle_t MQTTTask_Handler;           /* ������ */
void mqtt_task(void *pvParameters);      /* ������ */

#define CJSON_TASK_PRIO       3           /* �������ȼ� */
#define CJSON_STK_SIZE        256         /* �����ջ��С */
TaskHandle_t CJSONTask_Handler;           /* ������ */
void cjson_task(void *pvParameters);      /* ������ */


/******************************************************************************************************/
DHT11_Data_TypeDef DHT11_Data;
float light1 = 0;
extern char rx_buffer[236];

/******************************************************************************************************/
/**
 * @brief       lvgl_demo��ں���
 * @param       ��
 * @retval      ��
 */
void lvgl_demo(void)
{
    lv_init();                                          /* lvglϵͳ��ʼ�� */
    lv_port_disp_init();                                /* lvgl��ʾ�ӿڳ�ʼ��,����lv_init()�ĺ��� */
    lv_port_indev_init();                               /* lvgl����ӿڳ�ʼ��,����lv_init()�ĺ��� */

    xTaskCreate((TaskFunction_t )start_task,            /* ������ */
                (const char*    )"start_task",          /* �������� */
                (uint16_t       )START_STK_SIZE,        /* �����ջ��С */
                (void*          )NULL,                  /* ���ݸ��������Ĳ��� */
                (UBaseType_t    )START_TASK_PRIO,       /* �������ȼ� */
                (TaskHandle_t*  )&StartTask_Handler);   /* ������ */

    vTaskStartScheduler();                              /* ����������� */
}

/**
 * @brief       start_task
 * @param       pvParameters : �������(δ�õ�)
 * @retval      ��
 */
void start_task(void *pvParameters)
{
    pvParameters = pvParameters;
    
    taskENTER_CRITICAL();           /* �����ٽ��� */

    /* ����LVGL���� */
    xTaskCreate((TaskFunction_t )lv_demo_task,
                (const char*    )"lv_demo_task",
                (uint16_t       )LV_DEMO_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )LV_DEMO_TASK_PRIO,
                (TaskHandle_t*  )&LV_DEMOTask_Handler);

    /* LED�������� */
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
				
				

    taskEXIT_CRITICAL();            /* �˳��ٽ��� */
    vTaskDelete(StartTask_Handler); /* ɾ����ʼ���� */
}

/**
 * @brief       LVGL��������
 * @param       pvParameters : �������(δ�õ�)
 * @retval      ��
 */
void lv_demo_task(void *pvParameters)
{
    pvParameters = pvParameters;
    
    //lv_demo_stress();       /* ���Ե�demo */
	
	//my_demo();
    while(1)
    {
		my_demo();
		//rgb565_test(); 
        lv_timer_handler(); /* LVGL��ʱ�� */
        vTaskDelay(5);
    }
}

/**
 * @brief       led_task
 * @param       pvParameters : �������(δ�õ�)
 * @retval      ��
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
		/* ���θ���������ȡJSON���ݣ���ֵ�ԣ� */
			cjson_name = cJSON_GetObjectItem(cjson_test, "deviceName");

			//fprintf(stderr,"n %s\n", cjson_name->valuestring);

		/* ����Ƕ��json���� */
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
				DHT11_Data.temp_int,DHT11_Data.humi_int,(int)light1);//��Ϣ����	
        vTaskDelay(5000);
    }
}

