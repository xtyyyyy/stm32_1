#ifndef __SOIL_H
#define __SOIL_H

#include "stm32f4xx_hal.h"
#include "./SYSTEM/sys/sys.h"
// ADC��ʼ������
void SOIL_Init(void);

// ��ȡADCֵ����
uint32_t SOIL_Read(void);

uint16_t GetHumidity(int times); 

#endif // __ADC_H
