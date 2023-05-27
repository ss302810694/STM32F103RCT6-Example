#include "uart.h"


UARTDef UARTDev1;


int UARTInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    /* IO��ʼ�� */
	__HAL_RCC_GPIOA_CLK_ENABLE();
    
	GPIO_InitStruct.Pin = GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    /* UART1��ʼ�� */
    __HAL_RCC_USART1_CLK_ENABLE();
    
    UARTDev1.UART_Handle.Instance = USART1;
    UARTDev1.UART_Handle.Init.BaudRate = 115200;
    UARTDev1.UART_Handle.Init.Parity = UART_PARITY_NONE;
    UARTDev1.UART_Handle.Init.WordLength = UART_WORDLENGTH_8B;
    UARTDev1.UART_Handle.Init.StopBits = UART_STOPBITS_1;
    UARTDev1.UART_Handle.Init.Mode = UART_MODE_TX_RX;
    HAL_UART_Init(&UARTDev1.UART_Handle);

    /* UART1�жϳ�ʼ�� */
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
    
    
    /* UART1�������� */
    HAL_UART_Receive_IT(&UARTDev1.UART_Handle, UARTDev1.RxBuffer, UART_RX_BUFFSIZE);
    
    /** UART1���������ж� **/
    __HAL_UART_ENABLE_IT(&UARTDev1.UART_Handle, UART_IT_IDLE);
    
    return 0;
}

int UARTSendData(UARTDef *huart, uint8_t *pData, uint16_t Size)
{
    return HAL_UART_Transmit(&huart->UART_Handle, pData, Size, UART_TX_TIMEOUT);
}

void USART1_IRQHandler(void)
{
    UARTDef *huart = &UARTDev1;
    
	HAL_UART_IRQHandler(&huart->UART_Handle);
    
    if(__HAL_UART_GET_FLAG(&huart->UART_Handle, UART_FLAG_IDLE))
    {   /* ���յ�����һ֡���� */
        UARTSendData(huart, UARTDev1.RxBuffer, UART_RX_BUFFSIZE - UARTDev1.UART_Handle.RxXferCount);
        
        /* ������������ */
        HAL_UART_AbortReceive_IT(&UARTDev1.UART_Handle);
        HAL_UART_Receive_IT(&UARTDev1.UART_Handle, UARTDev1.RxBuffer, UART_RX_BUFFSIZE);
        /* ������ж� */
        __HAL_UART_CLEAR_IDLEFLAG(&huart->UART_Handle);
    }
}

