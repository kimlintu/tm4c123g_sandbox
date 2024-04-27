#ifndef __NO_SYSTEM_INIT
void SystemInit()
{}
#endif

#include "tm4c123gh6pm.h"

#include "gpio.h"
#include "clck.h"
#include "syst.h"
#include "pwmo.h"

void enable_interrupts(void)
{
	//__asm__("CPSID i");
}

void change_vect(void)
{
	NVIC_VTABLE_R |= 0x1000; 
}

int32_t main(void)
{
	change_vect();
	Clck_init();
	Gpio_init();
	Syst_init();
	Pwmo_init();

	//Gpio_toggle();

	enable_interrupts();

	while (1) 
	{
		/* STAY ALIVE */
	}

	return 0;
}

