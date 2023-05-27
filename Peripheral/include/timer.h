#ifndef __TIMER__H__
#define __TIMER__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"


typedef struct TimerDef
{
    TIM_HandleTypeDef TIM_Handle;
    TIM_OC_InitTypeDef TIM_OC_Handle;

}TimerDef;


int TimerInit();
int TimerStartIT(TimerDef *htim);
int TimerSetPulse(TimerDef *htim, int a);

extern TimerDef Timer1;


#ifdef __cplusplus
}
#endif

#endif
