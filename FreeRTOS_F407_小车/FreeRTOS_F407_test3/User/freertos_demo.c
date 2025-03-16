#include "freertos_demo.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/Motor/Motor.h"
#include "./BSP/Encoder/Encoder.h"
#include "./BSP/PID/PID.h"
#include "./BSP/Red/Red.h"
#include "./BSP/IWDG/iwdg.h"

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "event_groups.h"




#define START_TASK_PRIO 1                   /* 任务优先级 */
#define START_STK_SIZE  1024                /* 任务堆栈大小 */
TaskHandle_t            StartTask_Handler;  /* 任务句柄 */
void start_task(void *pvParameters);        /* 任务函数 */


#define TASK1_PRIO      2                   /* 任务优先级 */
#define TASK1_STK_SIZE  128                 /* 任务堆栈大小 */
TaskHandle_t            Task1Task_Handler;  /* 任务句柄 */
void TLY(void *pvParameters);               /* 任务函数 */


#define TASK4_PRIO      2                   /* 任务优先级 */
#define TASK4_STK_SIZE  128               /* 任务堆栈大小 */
TaskHandle_t            Task4Task_Handler;  /* 任务句柄 */
void Speed(void *pvParameters);             /* 任务函数 */

#define TASK3_PRIO      2                   /* 任务优先级 */
#define TASK3_STK_SIZE  128               /* 任务堆栈大小 */
TaskHandle_t            Task3Task_Handler;  /* 任务句柄 */
void Speed2(void *pvParameters);             /* 任务函数 */


////////////////////////////////////////////////////////
/* 新增     2025/3/14   */ 
/*此任务为判断台上台下的任务，通过其发送通知，让其执行台上程序或台下程序*/
#define STATE_PRIO      3                   /* 任务优先级    设为最高，因为需要首先判断台上台下*/ 
#define STATE_STK_SIZE  64               /* 任务堆栈大小 */
TaskHandle_t            STATETask_Handler;  /* 任务句柄 */
void state_task(void *pvParameters);             /* 任务函数 */

#define TAISHANG_PRIO      3                   /* 任务优先级*/ 
#define TAISHANG_STK_SIZE  128               /* 任务堆栈大小 */
TaskHandle_t            TAISHANGTask_Handler;  /* 任务句柄 */
void taishang_task(void *pvParameters);             /* 任务函数 */

#define TAIXIA_PRIO      3                   /* 任务优先级*/ 
#define TAIXIA_STK_SIZE  64               /* 任务堆栈大小 */
TaskHandle_t            TAIXIATask_Handler;  /* 任务句柄 */
void taixia_task(void *pvParameters);             /* 任务函数 */

#define XUNHANG_PRIO      3                   /* 任务优先级*/ 
#define XUNHANG_STK_SIZE  128               /* 任务堆栈大小 */
TaskHandle_t            XUNHANGTask_Handler;  /* 任务句柄 */
void xunhang_task(void *pvParameters);             /* 任务函数 */

#define BIANYUAN_PRIO      3                   /* 任务优先级*/ 
#define BIANYUAN_STK_SIZE  128               /* 任务堆栈大小 */
TaskHandle_t            BIANYUANTask_Handler;  /* 任务句柄 */
void bianyuan_task(void *pvParameters);             /* 任务函数 */

#define SHIBIE_PRIO      3                   /* 任务优先级*/ 
#define SHIBIE_STK_SIZE  128               /* 任务堆栈大小 */
TaskHandle_t            SHIBIETask_Handler;  /* 任务句柄 */
void shibie_task(void *pvParameters);             /* 任务函数 */

#define IWDG_PRIO      2                   /* 任务优先级*/ 
#define IWDG_STK_SIZE  64               /* 任务堆栈大小 */
TaskHandle_t            IWDGTask_Handler;  /* 任务句柄 */
void iwdg_task(void *pvParameters);             /* 任务函数 */



PID_LocTypeDef PID_F,PID_R,PID_B_F,PID_B_R,PID_ZITAI;
extern float rol, pit, yaw;

//float RS = -900;
//float LS = -900;
//float B_RS = -900;
//float B_LS = -900;

//float Act_LS = 0;
//float Act_RS = 0;
//float Act_B_LS = 0;
//float Act_B_RS = 0;

//float Speed_YAW = 0;

void freertos_demo(void)
{
//	PID_F.kp = 4;
//	PID_F.ki = 0.1;  
//	PID_F.kd = 0.05;
//	PID_F.ka = 1;
//	PID_F.limit = MaxS ;
//	
//	PID_R.kp = 4;
//	PID_R.ki = 0.1;
//	PID_R.kd = 0.05;
//	PID_R.ka = 1;
//	PID_R.limit = MaxS ;
//	
//	PID_B_F.kp = 4;
//	PID_B_F.ki = 0.1;
//	PID_B_F.kd = 0.05;
//	PID_B_F.ka = 1;
//	PID_B_F.limit = MaxS ;
//	
//	PID_B_R.kp = 4;
//	PID_B_R.ki = 0.1;
//	PID_B_R.kd = 0.05;
//	PID_B_R.ka = 1;
//	PID_B_R.limit = MaxS ;

//	PID_ZITAI.kp = 3.8;
//	PID_ZITAI.ki = 0.01;
//	PID_ZITAI.kd = 0.0035;
//	PID_ZITAI.ka = 1;
//	PID_ZITAI.limit = 220 ;
	
	Motor_Init();
	H_L_GPIO_Init();
	Encoder_Init();
	RED_GPIO_Init();
	
	
    xTaskCreate((TaskFunction_t )start_task,            /* 任务函数 */
                (const char*    )"start_task",          /* 任务名称 */
                (uint16_t       )START_STK_SIZE,        /* 任务堆栈大小 */
                (void*          )NULL,                  /* 传入给任务函数的参数 */
                (UBaseType_t    )START_TASK_PRIO,       /* 任务优先级 */
                (TaskHandle_t*  )&StartTask_Handler);   /* 任务句柄 */
	
	
	
    vTaskStartScheduler();
}


void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           /* 进入临界区 */
//	
 
	
    /* 创建任务1 */
//    xTaskCreate((TaskFunction_t )TLY,
//                (const char*    )"MPU6050",
//                (uint16_t       )TASK1_STK_SIZE,
//                (void*          )NULL, 
//                (UBaseType_t    )TASK1_PRIO,
//                (TaskHandle_t*  )&Task1Task_Handler);

//    xTaskCreate((TaskFunction_t )Speed,
//                (const char*    )"Speed",
//                (uint16_t       )TASK4_STK_SIZE,
//                (void*          )NULL,
//                (UBaseType_t    )TASK4_PRIO,
//                (TaskHandle_t*  )&Task4Task_Handler);
//				
//    xTaskCreate((TaskFunction_t )Speed2,
//                (const char*    )"Speed2",
//                (uint16_t       )TASK3_STK_SIZE,
//                (void*          )NULL,
//                (UBaseType_t    )TASK3_PRIO,
//                (TaskHandle_t*  )&Task3Task_Handler);
				
	
				
    xTaskCreate((TaskFunction_t )state_task,
                (const char*    )"State_task",
                (uint16_t       )STATE_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )STATE_PRIO,
                (TaskHandle_t*  )&STATETask_Handler);	

    xTaskCreate((TaskFunction_t )taishang_task,
                (const char*    )"taishang_task",
                (uint16_t       )TAISHANG_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )TAISHANG_PRIO,
                (TaskHandle_t*  )&TAISHANGTask_Handler);	

//    xTaskCreate((TaskFunction_t )taixia_task,
//                (const char*    )"taixia_task",
//                (uint16_t       )TAISHANG_STK_SIZE,
//                (void*          )NULL,
//                (UBaseType_t    )TAIXIA_PRIO,
//                (TaskHandle_t*  )&TAIXIATask_Handler);	
				
    xTaskCreate((TaskFunction_t )xunhang_task,
                (const char*    )"xunhang_task",
                (uint16_t       )XUNHANG_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )XUNHANG_PRIO,
                (TaskHandle_t*  )&XUNHANGTask_Handler);		

    xTaskCreate((TaskFunction_t )bianyuan_task,
                (const char*    )"bianyuan_task",
                (uint16_t       )BIANYUAN_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )BIANYUAN_PRIO,
                (TaskHandle_t*  )&BIANYUANTask_Handler);	
				
    xTaskCreate((TaskFunction_t )shibie_task,
                (const char*    )"shibie_task",
                (uint16_t       )SHIBIE_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )SHIBIE_PRIO,
                (TaskHandle_t*  )&SHIBIETask_Handler);
				
    xTaskCreate((TaskFunction_t )iwdg_task,
                (const char*    )"iwdg_task",
                (uint16_t       )IWDG_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )IWDG_PRIO,
                (TaskHandle_t*  )&IWDGTask_Handler);

	Set_L(-980);   //倒车上台
	Set_R(-980);
	B_Set_L(-980);
	B_Set_R(-980);
	delay_ms(1000);
	Set_L(400);   //倒车上台
	Set_R(400);
	B_Set_L(-400);
	B_Set_R(-400);
	delay_ms(300);
	
	MX_IWDG_Init();  //看门狗
				
	vTaskDelete(StartTask_Handler); /* 删除开始任务 */

    taskEXIT_CRITICAL();            /* 退出临界区 */
}

void state_task(void *pvParameters)
{
	while(1)
	{
	//if(R) 
	/* 目前传感器已拆所以不考虑台下情况，只让其开始启动时上台*/
		xTaskNotifyGive(TAISHANGTask_Handler); //
		vTaskDelay(10); //100ms判断一次，同时挂起任务让别的任务得以执行。
	}
}
extern volatile int open_id,open_x,open_y;  //串口中断中获取
EventGroupHandle_t eventGroup;   //通过事件组来通知各个任务执行

#define BIANYUAN_EVENT 	(1 << 0)
#define XUNHANG_EVENT  	(1 << 1)
#define SHIBIE_EVENT	(1 << 2)

/* 在此任务里进行台上的判断，并控制相应任务启动*/
void taishang_task(void *pvParameters)
{
	eventGroup = xEventGroupCreate();
	while(1)
	{
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		
		 //xEventGroupClearBits(eventGroup, BIANYUAN_EVENT | XUNHANG_EVENT | SHIBIE_EVENT); 
		
		if(R1||R2)  //边缘情况 优先级最高，所以放在第一位
			xEventGroupSetBits(eventGroup, BIANYUAN_EVENT);
		else //下面是不在边缘的情况
		{
			
			if(open_id!=-1/*  && Rn==1  目前不知道是否需要避让，暂不判断车头红外状态*/ )
				xEventGroupSetBits(eventGroup, SHIBIE_EVENT);
			else //巡航模式
			{
				xEventGroupSetBits(eventGroup, XUNHANG_EVENT);  
			}
		}
		
		vTaskDelay(10);

	}
}

void taixia_task(void *pvParameters)
{
	while(1)
	{
	//if(R) 
	/* 目前台下监测传感器已拆所以不考虑台下情况，只让其开始启动时上台*/
		vTaskDelay(100);
	}
}

void xunhang_task(void *pvParameters)  //感觉后续有机会优化可以加某种算法，使其能够遍历整个场地
{
	while(1)
	{  
		xEventGroupWaitBits(eventGroup, XUNHANG_EVENT, pdTRUE, pdFALSE, portMAX_DELAY);
		
		Set_L(300);
		Set_R(300);
		B_Set_L(300);
		B_Set_R(300);
		xEventGroupClearBits(eventGroup, XUNHANG_EVENT);
		
	}
}

void bianyuan_task(void *pvParameters) 
{
	while(1)
	{	
		xEventGroupWaitBits(eventGroup, BIANYUAN_EVENT, pdTRUE, pdFALSE, portMAX_DELAY);
		taskENTER_CRITICAL();
		Set_L(-980);
		Set_R(-980);
		B_Set_L(-980);
		B_Set_R(-980);
		delay_ms(100);
		Set_L(-400);   //zhuanxiang
		Set_R(400);
		B_Set_L(-400);
		B_Set_R(400); 
		delay_ms(150);
		taskEXIT_CRITICAL();
		/* 如果这里使用闭环控制的话，延时结束记得清空PID累积的值，重新开始计算。*/
		/* 或者这里的延时可采用软件定时器来实现，就不需要清空清空PID累积的值*/
		/* 另建议单独使用任务来进行计算PID  例如下面的任务Speed*/
	}
}


//识别April_Tag,open_x传参在usart.c里
void shibie_task(void *pvParameters)
{
	uint8_t kp = 2;   //电机差速比例系数
	uint8_t pingmuzhongxin = 80;   //屏幕中心像素值
	while(1)
	{ 
		/*这里后续可以尝试闭环*/    
		xEventGroupWaitBits(eventGroup, SHIBIE_EVENT, pdTRUE, pdFALSE, portMAX_DELAY);
		taskENTER_CRITICAL();
		Set_L(kp*pingmuzhongxin+(open_x-pingmuzhongxin)*kp);    //suodi
		B_Set_L(kp*pingmuzhongxin+(open_x-pingmuzhongxin)*kp);
		Set_R(kp*pingmuzhongxin-(open_x-pingmuzhongxin)*kp);
		B_Set_R(kp*pingmuzhongxin-(open_x-pingmuzhongxin)*kp);
		
		xEventGroupClearBits(eventGroup, SHIBIE_EVENT);
		taskEXIT_CRITICAL();
	}
}

void iwdg_task(void *pvParameters) 
{
	while(1)
	{	
		HAL_IWDG_Refresh(&hiwdg);  // 喂狗防止程序跑死
        vTaskDelay(100 );  
	}
}




		
extern __IO int16_t Encoder_Overflow_Count;
extern __IO int16_t Encoder_Overflow_Count2;

extern TIM_HandleTypeDef TIM_EncoderHandle;
extern TIM_HandleTypeDef TIM_EncoderHandle2;

extern __IO int16_t B_Encoder_Overflow_Count;
extern __IO int16_t B_Encoder_Overflow_Count2;

extern TIM_HandleTypeDef B_TIM_EncoderHandle;
extern TIM_HandleTypeDef B_TIM_EncoderHandle2;


///* 电机旋转方向 */
//__IO int8_t Motor_Direction = 0;
///* 当前时刻总计数值 */
//__IO int32_t Capture_Count = 0;
//__IO int32_t Capture_Count2 = 0;

//__IO int32_t B_Capture_Count = 0;
//__IO int32_t B_Capture_Count2 = 0;
///* 电机转轴转速 */
//__IO float Shaft_Speed = 0.0f;

//void Speed(void *pvParameters)
//{
//    TickType_t xLastWakeTime;
//    const TickType_t xFrequency = pdMS_TO_TICKS(10);

//    // 初始化上次唤醒时间
//    // Initialize last wake time
//    xLastWakeTime = xTaskGetTickCount();

//    while (1)
//    {
//        taskENTER_CRITICAL();  // Enter critical section to ensure atomic operation

//        // Determine if encoder is counting down and adjust overflow count accordingly
//        Encoder_Overflow_Count = __HAL_TIM_IS_TIM_COUNTING_DOWN(&TIM_EncoderHandle) ? -1 : 0;
//		Encoder_Overflow_Count2 = __HAL_TIM_IS_TIM_COUNTING_DOWN(&TIM_EncoderHandle2) ? -1 : 0;
//        // Calculate Capture_Count (current encoder count adjusted for overflow)
//        Capture_Count = __HAL_TIM_GET_COUNTER(&TIM_EncoderHandle) + (Encoder_Overflow_Count * 65535);
//		Capture_Count2 = __HAL_TIM_GET_COUNTER(&TIM_EncoderHandle2) + (Encoder_Overflow_Count2 * 65535);
//        // Reset encoder counter to zero for next measurement interval
//        __HAL_TIM_SetCounter(&TIM_EncoderHandle, 0);
//		__HAL_TIM_SetCounter(&TIM_EncoderHandle2, 0);
//        // Print the calculated Capture_Count value
//		Act_LS = PID_Loc(LS, -Capture_Count* 10, &PID_F);
//        Act_RS = PID_Loc(RS, Capture_Count2 * 10, &PID_R);
//	
//        //printf("%d,%d,", -Capture_Count,Capture_Count2);

//        taskEXIT_CRITICAL();  // Exit critical section

//        // Wait for next execution cycle (10ms interval)
//        vTaskDelayUntil(&xLastWakeTime, xFrequency);
//    }
//}

extern uint32_t count; // 计数器

//void Speed2(void *pvParameters)
//{
//    TickType_t xLastWakeTime2;
//    const TickType_t xFrequency2 = pdMS_TO_TICKS(10);

//    // 初始化上次唤醒时间
//    // Initialize last wake time
//    xLastWakeTime2 = xTaskGetTickCount();

//    while (1)
//    {
//        taskENTER_CRITICAL();  // Enter critical section to ensure atomic operation
//  
//        // Determine if encoder is counting down and adjust overflow count accordingly
//        B_Encoder_Overflow_Count = __HAL_TIM_IS_TIM_COUNTING_DOWN(&B_TIM_EncoderHandle) ? -1 : 0;
//		B_Encoder_Overflow_Count2 = __HAL_TIM_IS_TIM_COUNTING_DOWN(&B_TIM_EncoderHandle2) ? -1 : 0;
//        // Calculate Capture_Count (current encoder count adjusted for overflow)
//        B_Capture_Count = __HAL_TIM_GET_COUNTER(&B_TIM_EncoderHandle) + (B_Encoder_Overflow_Count * 65535);
//		B_Capture_Count2 = __HAL_TIM_GET_COUNTER(&B_TIM_EncoderHandle2) + (B_Encoder_Overflow_Count2 * 65535);
//        // Reset encoder counter to zero for next measurement interval
//        __HAL_TIM_SetCounter(&B_TIM_EncoderHandle, 0);
//		__HAL_TIM_SetCounter(&B_TIM_EncoderHandle2, 0);
//        // Print the calculated Capture_Count value
//		Act_B_LS = PID_Loc(B_LS, -B_Capture_Count* 10, &PID_B_F);
////        Act_B_RS = PID_Loc(B_RS, count*2.215 * 10, &PID_B_R);
//		Act_B_RS = Act_RS;
//        //printf("%d,%d\r\n", -B_Capture_Count,count);
//		count = 0;
//        taskEXIT_CRITICAL();  // Exit critical section

//        // Wait for next execution cycle (10ms interval)
//        vTaskDelayUntil(&xLastWakeTime2, xFrequency2);
//    }
//}



//extern int distance;

//uint8_t last_flag_xia = 0;
//uint8_t state = 0;
//uint16_t Dis[4];
//uint16_t direction = 0;

/*陀螺仪代码*/
/*原来那份里面有，是激光测四个方向的数据，然后决定最短的方向上台*/
/*可考虑用视觉方案代替*/
void TLY(void *pvParameters)
{
		
    while(1)
    {
		taskENTER_CRITICAL();
			
		vTaskDelay(100);
		
		taskEXIT_CRITICAL();
		
    }
}



