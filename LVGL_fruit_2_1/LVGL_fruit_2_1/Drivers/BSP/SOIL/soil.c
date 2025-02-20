#include "./BSP/SOIL/soil.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/SOIL/soil.h"

ADC_HandleTypeDef hadc1;
GPIO_InitTypeDef GPIO_InitStruct = {0};

void SOIL_Init(void) {

	GPIO_InitStruct.Pin = GPIO_PIN_4;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    // ����ADC
    hadc1.Instance = ADC1;
    hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
    hadc1.Init.Resolution = ADC_RESOLUTION_12B;
    hadc1.Init.ScanConvMode = DISABLE;
    hadc1.Init.ContinuousConvMode = DISABLE;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.NbrOfConversion = 1;
	HAL_ADC_Init(&hadc1);
	
    // ����ADCͨ��
    ADC_ChannelConfTypeDef sConfig;
    sConfig.Channel = ADC_CHANNEL_4; // PA4
    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;
	HAL_ADC_ConfigChannel(&hadc1, &sConfig);

}

// ��ȡADCֵ����
uint32_t SOIL_Read(void) {
    // ��ʼADCת��
    HAL_ADC_Start(&hadc1);
    
    // �ȴ�ת�����
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
    
    // ��ȡADCֵ
    return HAL_ADC_GetValue(&hadc1);
}

uint16_t GetHumidity(int times)
{
    uint32_t H_all = 0;
    float H_arg = 0;
    uint8_t t;
 
    // ���ж��ADCת�����ۼ�
    for (t = 0; t < times; t++) {
        H_all += SOIL_Read();
        delay_ms(1); // ��ʱ1����
    }
    // ����ƽ��ֵ
    H_arg = (H_all / times);
    // ����ת����ʽ����ʪ��ֵ
    uint16_t data = (4095 - H_arg) / 3292 * 100;
    // ȷ��ʪ��ֵ�ں���Χ�ڣ�0~100��
    data = data > 100 ? 100 : (data < 0 ? 0 : data);
    return data;

}
