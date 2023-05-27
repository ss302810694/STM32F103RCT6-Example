#include "timer.h"

TimerDef Timer1;

int TimerInit()
{
    Timer1.TIM_Handle.Instance = TIM1;
    Timer1.TIM_Handle.Init.Prescaler = 7;
    Timer1.TIM_Handle.Init.CounterMode = TIM_COUNTERMODE_UP;
    Timer1.TIM_Handle.Init.Period = 10000;
    Timer1.TIM_Handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    Timer1.TIM_Handle.Init.RepetitionCounter = 0;
    Timer1.TIM_Handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

    __HAL_RCC_TIM1_CLK_ENABLE();

    HAL_TIM_PWM_Init(&Timer1.TIM_Handle);

    Timer1.TIM_OC_Handle.OCMode = TIM_OCMODE_PWM1;
    Timer1.TIM_OC_Handle.Pulse = 9999;

    HAL_TIM_PWM_ConfigChannel(&Timer1.TIM_Handle, &Timer1.TIM_OC_Handle, TIM_CHANNEL_1);

    HAL_TIM_PWM_Start(&Timer1.TIM_Handle, TIM_CHANNEL_1);

    return 0;
}

int Timer_Start_IT(TimerDef *htim)
{
    return HAL_TIM_Base_Start_IT(&htim->TIM_Handle);
}

int TimerSetPulse(TimerDef *htim, int a)
{
    htim->TIM_OC_Handle.Pulse = a;
    HAL_TIM_PWM_ConfigChannel(&htim->TIM_Handle, &htim->TIM_OC_Handle, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim->TIM_Handle, TIM_CHANNEL_1);

    return 0;
}
