#include <stdint.h>

#include "diom_pwmo.h"
#include "diio_pwmd.h"

static uint32_t pwmo_ct_ticks_U32 = 0;

void Pwmo_init(void)
{
    Pwmd_init();
}

void Pwmo_10ms(void)
{
    static int8_t counterDirection_S08 = 1;

    if (pwmo_ct_ticks_U32 == 100)
    {
        counterDirection_S08 = -1;
    }
    else if (pwmo_ct_ticks_U32 == 0)
    {
        counterDirection_S08 = 1;
    }

    Pwmd_setDutyCycle(pwmo_ct_ticks_U32);

    pwmo_ct_ticks_U32 += counterDirection_S08;
}