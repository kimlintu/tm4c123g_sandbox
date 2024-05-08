#include "tm4c123gh6pm.h"

#include "clck_sysc.h"

static void Clck_initSysClock(void);

/*
 * Initializes the system clock. Oscillator source is set to PIOSC (default).
 * Currently sets the system clock to 50MHz.
 */
static void Clck_initSysClock(void)
{
    /* Disable PLL */
    SYSCTL_RCC_R |= SYSCTL_RCC_BYPASS;

    /* Clear System Clock Divisor */
    SYSCTL_RCC_R &= ~SYSCTL_RCC_SYSDIV_M;

    /* System Clock Divisor = (400 / 2) / (3 + 1) = 50MHz */
    SYSCTL_RCC_R |= 0x01800000;

    /* Enable use of System Divisor   */
    SYSCTL_RCC_R |= SYSCTL_RCC_USESYSDIV;

    /* Set PLL to normal operation */
    SYSCTL_RCC_R &= ~SYSCTL_RCC_PWRDN;

    /* Wait for PLL to be locked (stable )*/
    while ((SYSCTL_PLLSTAT_R & SYSCTL_PLLSTAT_LOCK) == 0)
    {
    };

    /* Start using PLL  */
    SYSCTL_RCC_R &= ~SYSCTL_RCC_BYPASS;
}

void Clck_init(void)
{
    Clck_initSysClock();
}