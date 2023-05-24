#include "timer.h"

TimerDef timer1, timer2;

int TimerInit(void)
{
    TimerDef *tmpTim = &timer1;
    /* 1kHz */
    tmpTim->TIM_Handle.Instance = TIM1;
    tmpTim->TIM_Handle.Init.Prescaler = 72 - 1;
    tmpTim->TIM_Handle.Init.Period = 1000;

    __HAL_RCC_TIM1_CLK_ENABLE();
    HAL_TIM_PWM_Init(&tmpTim->TIM_Handle);

    tmpTim = &timer2;
    /* 100Hz */
    tmpTim->TIM_Handle.Instance = TIM2;
    tmpTim->TIM_Handle.Init.Prescaler = 72 - 1;
    tmpTim->TIM_Handle.Init.Period = 10000;

    __HAL_RCC_TIM2_CLK_ENABLE();
    
    /* 使能定时器2中断 */
    HAL_NVIC_EnableIRQ(TIM2_IRQn);
    HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
    
    /* 初始化并开启定时器2 */
    HAL_TIM_Base_Init(&tmpTim->TIM_Handle);
    HAL_TIM_Base_Start_IT(&tmpTim->TIM_Handle);

    return 0;
}

/**
 * \brief Set the PWM config and starts the PWM output.
 * \param handle Timer handle
 * \param channel the TIM Channel
 * \param duty the duty of PWM
 * \return status
*/
int TimerSetPulse(TimerDef *handle, uint32_t channel, float duty)
{
    int t = handle->TIM_Handle.Init.Period * duty;
    handle->TIM_OC_Handle.Pulse = t;
    handle->TIM_OC_Handle.OCMode = TIM_OCMODE_PWM1;

    HAL_TIM_PWM_ConfigChannel(&handle->TIM_Handle, &handle->TIM_OC_Handle, channel);
    HAL_TIM_PWM_Start(&handle->TIM_Handle, channel);
    return 0;
}
