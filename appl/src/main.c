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
    
    //Pwmo_init();
    Uart_init();

    /* This will enable the SysTick interrupt, which is our scheduler, */
    /* therefore it should probably be called last.                    */
    Syst_init();
    //Gpio_toggle();

    while (1)
    {
        /* STAY ALIVE */
    }

    return 0;
}
