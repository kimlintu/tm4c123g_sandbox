#include "comm_uart.h"
#include "gnio_gpio.h"
#include "clck_sysc.h"
#include "diom_pwmo.h"
#include "time_syst.h"

#include "main.h"

int32_t main(void)
{
    uint32_t sysTick_U32;

    Clck_init();
    Gpio_init();

//    Pwmo_init();
    Uart_init();

    /* This will enable the SysTick interrupt, which is our scheduler, */
    /* therefore it should probably be called last.                    */
    Syst_init();
    //Gpio_toggle();

    while (1)
    {
        /* STAY ALIVE */
        sysTick_U32 = Syst_getSysTick_U32();

        if ((sysTick_U32 % 10) == 0)
        {
            Uart_10ms();
        }
    }

    return 0;
}
