#include "myadc.h"
#include "adc.h"
#include "OLED.h"

ADC_Result_t adc1;

static uint16_t ADC1_Buffer[ADC_NUM];


//启动ADC DMA
void BADC_Start(void)
{
    HAL_ADC_Start_DMA(&hadc1, (uint32_t*)ADC1_Buffer, ADC_NUM);
}

uint8_t BADC_GetResult(ADC_Result_t *result)
{
	for(uint16_t  i;i<ADC_NUM;i++){
		adc1.dc_in_adc= ADC1_Buffer[0];
		adc1.dc_out_adc= ADC1_Buffer[1];
		adc1.current_out_adc1= ADC1_Buffer[2];
    adc1.current_out_adc2 = ADC1_Buffer[3];
    adc1.current_raw_diff=adc1.current_out_adc1-adc1.current_out_adc2; 
		
		}
	
		
	  adc1.current_out=(3.3/4095)*adc1.current_raw_diff/CURRENT_SCALE;         // 电流值 (A)
    adc1.dc_out_voltage=(3.3/4095)*adc1.dc_out_adc*DC_SCALE;         
	  adc1.dc_in_voltage=(3.3/4095)*adc1.dc_in_adc*DC_SCALE;
		
		
}

/*
================================================
偏置校准（上电无输入时执行一次）
================================================
*/
void BADC_CalibrateOffset(void)
{
   
}

/*
================================================
直流比例校准
@param true_vdc : 用万用表测得的实际直流电压（如 48.0f）
================================================
*/
void BADC_CalibrateDCScale(float true_vdc)
{
   
}

/*
================================================
电流零点校准（无电流时执行）
================================================
*/
void BADC_CalibrateZero(void)
{
   
}

/*
================================================
获取电流原始 ADC 差值 (LSB)
用于调试: 观察噪声水平、验证分压比、检查零点
================================================
*/

float BADC_GetCurrentRawDiff(void)
{
   
}

/*
================================================
过流检测
@return 1: 过流 (|I| > CURRENT_OVERLOAD_THRESHOLD_A)
        0: 正常
================================================
*/
uint8_t BADC_IsOverCurrent(void)
{
   
}

