#include "tm4c123gh6pm.h"

#include "gpio.h"

void Gpio_init(void)
{
    //enable GPIO Port F Run Mode Clock Gating
	SYSCTL_RCGCGPIO_R = SYSCTL_RCGCGPIO_R5;
	//set the direction of pin 1 to output
	GPIO_PORTF_DIR_R = 0x02 | 0x04 | 0x08;
	//enable digital function
	GPIO_PORTF_DEN_R = 0x02 | 0x04 | 0x08;
}

#define GPIO_LED_COLOR_U32 0x02

void Gpio_toggle(void)
{
    if (GPIO_PORTF_DATA_R == GPIO_LED_COLOR_U32)
    {
        GPIO_PORTF_DATA_R = 0;
    }
    else 
    {
        GPIO_PORTF_DATA_R = GPIO_LED_COLOR_U32;
    }
}

void Gpio_1000ms(void)
{
    Gpio_toggle();
}
