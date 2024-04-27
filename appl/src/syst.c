#include "tm4c123gh6pm.h"

#include "syst.h"
#include "clck.h"
#include "gpio.h"
#include "pwmo.h"
#include "uart.h"

volatile uint32_t syst_ct_sysTick_U32 = 0;

void SysTick_Handler(void)
{
    if ((syst_ct_sysTick_U32 % 1000) == 0)
    {
        // Gpio_1000ms();
    }

    if ((syst_ct_sysTick_U32 % 10) == 0)
    {
        //Pwmo_10ms();
        Uart_10ms();
    }

    syst_ct_sysTick_U32 += 1;

    /* TODO: Do we clear the interrupt bit here? */
}

void Syst_init(void)
{
    /* Call SysTick ISR every 1ms */
    NVIC_ST_RELOAD_R = (CLCK_SYSCLOCK_HZ / 1000) - 1;

    /* The current value of systick is undefined at startup */
    /* so we need to clear it */
    NVIC_ST_CURRENT_R &= ~NVIC_ST_CURRENT_M;

    /* Set SysTick clock source to system timer */
    NVIC_ST_CTRL_R |= NVIC_ST_CTRL_CLK_SRC;

    /* Enable SyStick interrupt generation */
    NVIC_ST_CTRL_R |= NVIC_ST_CTRL_INTEN;

    /* Start counting! */
    NVIC_ST_CTRL_R |= NVIC_ST_CTRL_ENABLE;
}