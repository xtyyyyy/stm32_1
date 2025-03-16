#include "./BSP/IWDG/iwdg.h"


IWDG_HandleTypeDef hiwdg;

void MX_IWDG_Init(void)
{
    hiwdg.Instance = IWDG; // 选择独立看门狗
    hiwdg.Init.Prescaler = IWDG_PRESCALER_64; // 预分频 64
    hiwdg.Init.Reload = 1000-1;  // 设定超时时间约 2s
    HAL_IWDG_Init(&hiwdg);  // 初始化看门狗
}
