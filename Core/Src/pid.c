#include "pid.h"

void PID_Init(PID_TypeDef *pid, float Kp, float Ki, float Kd,  float out_min, float out_max,  float integral_min, float integral_max,float Ts)
{
    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;

    pid->target = 0.0f;
    pid->feedback = 0.0f;

    pid->err = 0.0f;
    pid->err_last = 0.0f;
    pid->err_sum = 0.0f;
    pid->output = 0.0f;

    pid->out_max = out_max;
    pid->out_min = out_min;
    pid->integral_max = integral_max;
    pid->integral_min = integral_min;
    pid->Ts = Ts;
}

float PID_Calc(PID_TypeDef *pid)
{
   pid->err = pid->target - pid->feedback;

    // 先计算未限幅输出
    float output = pid->Kp * pid->err
                 + pid->Ki * pid->err_sum
                 + pid->Kd * (pid->err - pid->err_last);

    // 输出限幅
    if (output > pid->out_max) output = pid->out_max;
    if (output < pid->out_min) output = pid->out_min;

    // 抗积分饱和：仅当输出未饱和，或误差方向有助于退出饱和时，才累加积分
    if ((output > pid->out_min && output < pid->out_max) ||
        (output >= pid->out_max && pid->err < 0) ||
        (output <= pid->out_min && pid->err > 0))
    {
        pid->err_sum += pid->err * pid->Ts; // 显式乘 Ts
        if (pid->err_sum > pid->integral_max) pid->err_sum = pid->integral_max;
        if (pid->err_sum < pid->integral_min) pid->err_sum = pid->integral_min;
    }

    // 用更新后的积分重新计算输出
    pid->output = pid->Kp * pid->err
                + pid->Ki * pid->err_sum
                + pid->Kd * (pid->err - pid->err_last);

    // 再次输出限幅
    if (pid->output > pid->out_max) pid->output = pid->out_max;
    if (pid->output < pid->out_min) pid->output = pid->out_min;

    pid->err_last = pid->err;
    return pid->output;
}

void PID_Clear(PID_TypeDef *pid)
{
    pid->err = 0.0f;
    pid->err_last = 0.0f;
    pid->err_sum = 0.0f;
    pid->output = 0.0f;
}
