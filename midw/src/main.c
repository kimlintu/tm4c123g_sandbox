#include "tm4c123gh6pm.h"

#include "comm_uart.h"
#include "gnio_gpio.h"
#include "clck_sysc.h"
#include "diio_pwmd.h"
#include "time_syst.h"

int32_t main(void)
{
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
