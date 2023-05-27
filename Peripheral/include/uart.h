#ifndef __UART__H__
#define __UART__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"

#define UART_RX_BUFFSIZE    1024
#define UART_TX_TIMEOUT     3000

typedef struct UARTDef
{
    UART_HandleTypeDef UART_Handle;
    uint8_t RxBuffer[UART_RX_BUFFSIZE];
    
}UARTDef;



int UARTInit(void);
int UARTSendData(UARTDef *huart, uint8_t *pData, uint16_t Size);

extern UARTDef UARTDev1;


#ifdef __cplusplus
}
#endif

#endif