#include "mppt.h"
#include "myadc.h"



void MPPT_Init(MPPT_TypeDef *mppt, float init_duty, float step, float d_max, float d_min)
{
    mppt->power_now  = 0.0f;
    mppt->power_last = 0.0f;
    mppt->U1_last    = 0.0f;

    mppt->duty   = init_duty;
    mppt->step   = step;

    mppt->duty_max = d_max;
    mppt->duty_min = d_min;
}

float MPPT_Calc(MPPT_TypeDef *mppt, float U1, float I1)
{
    float P_now = U1 * I1;

    if(P_now > mppt->power_last)
    {
        if(U1 > mppt->U1_last)
            mppt->duty += mppt->step;
        else
            mppt->duty -= mppt->step;
    }
    else
    {
        if(U1 > mppt->U1_last)
            mppt->duty -= mppt->step;
        else
            mppt->duty += mppt->step;
    }

    mppt->power_last = P_now;
    mppt->U1_last = U1;

    if(mppt->duty > mppt->duty_max)
        mppt->duty = mppt->duty_max;
    if(mppt->duty < mppt->duty_min)
        mppt->duty = mppt->duty_min;

    return mppt->duty;
}
