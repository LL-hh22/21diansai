#ifndef __PID_H
#define __PID_H

#include "main.h"
typedef struct
{
    float Kp;
    float Ki;
    float Kd;

    float target;
    float feedback;

    float err;
    float err_last;
    float err_sum;

    float output;
    float out_max;
    float out_min;
	
	 float integral_max, integral_min; // 积分限幅
    float Ts;                         // 采样周期
	
} PID_TypeDef;

void PID_Init(PID_TypeDef *pid, float kp, float ki, float kd, float out_max, float out_minfloat ,float integral_min, float integral_max,float Ts);
float PID_Calc(PID_TypeDef *pid);
void PID_Clear(PID_TypeDef *pid);

#endif
