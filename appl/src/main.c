#include "tm4c123gh6pm.h"

#include "gpio.h"
#include "clck.h"
#include "syst.h"
#include "pwmo.h"
#include "uart.h"

void Vect_updateVectorTableOffset(void)
{
    NVIC_VTABLE_R |= 0x1000;
}

int32_t main(void)
{
    Vect_updateVectorTableOffset();
    Clck_init();
    Gpio_init();
    Syst_init();
    Pwmo_init();
    Uart_init();

    while (1)
    {
        /* STAY ALIVE */
    }

    return 0;
}
