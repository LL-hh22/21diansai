#include "bsp_usart.h"

/* MX生成的USART句柄，在usart.c里定义 */
extern UART_HandleTypeDef huart2;

uint8_t Serial_RxData;
uint8_t Serial_RxFlag;

void Serial_Init(void)
{
    // MX已经初始化了USART2，这里只需要启动接收中断
    HAL_UART_Receive_IT(&huart2, &Serial_RxData, 1);
}

void Serial_SendByte(uint8_t Byte)
{
    HAL_UART_Transmit(&huart2, &Byte, 1, HAL_MAX_DELAY);
}

void Serial_SendArray(uint8_t *Array, uint16_t Length)
{
    HAL_UART_Transmit(&huart2, Array, Length, HAL_MAX_DELAY);
}

void Serial_SendString(char *String)
{
    HAL_UART_Transmit(&huart2, (uint8_t *)String, strlen(String), HAL_MAX_DELAY);
}

uint32_t Serial_Pow(uint32_t X, uint32_t Y)
{
    uint32_t Result = 1;
    while(Y--)
    {
        Result *= X;
    }
    return Result;
}

void Serial_SendNumber(uint32_t Number, uint8_t Length)
{
    uint8_t i;
    for(i = 0; i < Length; i++)
    {
        Serial_SendByte(Number / Serial_Pow(10, Length - i - 1) % 10 + '0');
    }
}

// printf重定向到USART2
int fputc(int ch, FILE *f)
{
    HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
    return ch;
}

void Serial_Printf(char *format, ...)
{
    char String[100];
    va_list arg;
    va_start(arg, format);
    vsprintf(String, format, arg);
    va_end(arg);
    Serial_SendString(String);
}

uint8_t Serial_GetRxFlag(void)
{
    if(Serial_RxFlag == 1)
    {
        Serial_RxFlag = 0;
        return 1;
    }
    return 0;
}

uint8_t Serial_GetRxData(void)
{
    return Serial_RxData;
}

// 接收完成回调函数（HAL自动调用）
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == USART2)
    {
        Serial_RxFlag = 1;
        // 重新启动接收中断，准备接收下一个字节
        HAL_UART_Receive_IT(&huart2, &Serial_RxData, 1);
    }
}
