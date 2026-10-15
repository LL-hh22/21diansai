#ifndef __BSP_MPPT_H
#define __BSP_MPPT_H

#include "main.h"
#include "pid.h"

typedef struct
{
    float power_now;
    float power_last;
    float U1_last;
    float duty;
    float step;
    float duty_max;
    float duty_min;
} MPPT_TypeDef;

extern PID_TypeDef mppt_pid;

void MPPT_Init(MPPT_TypeDef *mppt, float init_duty, float step, float d_max, float d_min);
float MPPT_Calc(MPPT_TypeDef *mppt, float U1, float I1);

#endif
