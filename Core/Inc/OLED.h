#ifndef __OLED_H
#define __OLED_H

#include "main.h"

// 直接用GPIO_PIN_6/7，不依赖MX标签
#define OLED_W_SCL(x)   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, (x) ? GPIO_PIN_SET : GPIO_PIN_RESET)
#define OLED_W_SDA(x)   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, (x) ? GPIO_PIN_SET : GPIO_PIN_RESET)

void OLED_I2C_Init(void);
void OLED_Init(void);
void OLED_Clear(void);
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowFloat(uint8_t Line, uint8_t Column, float Number, uint8_t IntLen, uint8_t DecLen);

#endif

