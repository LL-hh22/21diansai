#ifndef __MYADC_H
#define __MYADC_H

#include "main.h"
#include <math.h>

/*
================================================
ADC通道定义（与 adc.c 中的 Rank 顺序一致）

ADC1_Buffer[0] : PA3  ADC1_CH4     输入电压
ADC1_Buffer[1] : PB14  ADC1_CH5    输出电压
ADC1_Buffer[2] : PC0  ADC1_CH6     输出电流
ADC1_Buffer[3] : PC1  ADC1_CH7       电流
================================================
*/

#define ADC_NUM     4

/*================== 默认比例系数 ==================*/
#ifndef DC_SCALE
#define DC_SCALE    1.0f
#endif

#ifndef AC_SCALE
#define AC_SCALE    1.0f
#endif

#ifndef CURRENT_SCALE
#define CURRENT_SCALE       CURRENT_SCALE_CALC    // 使用计算值
#endif

/*
#ifndef AC_SCALE
#define AC_SCALE    1.0f
#endif
意思是其他地方如果也定义了，会以其他地方的为主
*/

#define CURRENT_SCALE_CALC  CURRENT_DIVIDER_RATIO * (CKSR15_SENSITIVITY_MV_PER_A * 0.001f)

#define REF_VOLT            3.3f        // ADC 参考电压
#define FULL_RANGE         4095.0f     // 12bit 满量程

// 信号调理参数 (根据实际分压电阻值修改!)
#define CURRENT_DIVIDER_RATIO           0.66f       // 5V→3.3V 分压比 (如 3.3k/(3.3k+1.7k))

// CKSR15 传感器参数
#define CKSR15_SENSITIVITY_MV_PER_A     41.67f      // mV/A, 5V 供电典型值

// 过流保护阈值 (A)
#define CURRENT_OVERLOAD_THRESHOLD_A    18.0f       // 超过额定 15A 的 120%

//原始值
typedef struct {
	   //原始值
    uint16_t current_out_adc1; 
    uint16_t current_out_adc2; 
    uint16_t ac_voltage_adc;  
    uint16_t dc_out_adc;
	  uint16_t dc_in_adc;
    float current_raw_diff;   // 电流原始 ADC 差值 (LSB), 用于调试
	
	//实际值
  	float current_out;         // 电流值 (A)
    float ac_rms;   // 交流有效值
    float dc_out_voltage;         
	  float dc_in_voltage;
    uint8_t ready;
} ADC_Result_t;

// 校准参数（运行时可更新）
typedef struct {
    float ac_offset_adc;    // 交流零位（无输入时 ADC 均值）
    float dc_offset_adc;    // 直流零位（无输入时 ADC 均值）
    float ac_scale;         // 实际 Vrms / (ADC 差分电压 V)
    float dc_scale;         // 实际 Vdc / (ADC 差分电压 V)
} ADC_Cal_t;

void BADC_Start(void);

uint8_t BADC_GetResult(ADC_Result_t *result);

void BADC_CalibrateOffset(void);

void BADC_CalibrateDCScale(float true_vdc);

void BADC_CalibrateZero(void);

float BADC_GetCurrentRawDiff(void);

uint8_t BADC_IsOverCurrent(void);



#endif
