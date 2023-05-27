#include "main.h"

int main()
{
	HAL_Init();
    SystemClockInit();
    GPIOInit();
    UARTInit();
    
	while(1)
	{
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_8);
        HAL_Delay(500);
	}
}
