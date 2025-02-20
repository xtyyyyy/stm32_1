#ifndef __SOIL_H
#define __SOIL_H

#include "stm32f4xx_hal.h"
#include "./SYSTEM/sys/sys.h"
// ADC初始化函数
void SOIL_Init(void);

// 获取ADC值函数
uint32_t SOIL_Read(void);

uint16_t GetHumidity(int times); 

#endif // __ADC_H
