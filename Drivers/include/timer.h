#ifndef __TIMER__H__
#define __TIMER__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_hal.h"


typedef struct TimerDef
{
    TIM_HandleTypeDef TIM_Handle;
    TIM_OC_InitTypeDef TIM_OC_Handle;

}TimerDef;



int TimerInit(void);


int TimerSetPulse(TimerDef *handle, uint32_t channel, float duty);


extern TimerDef timer1, timer2;

#ifdef __cplusplus
}
#endif

#endif
