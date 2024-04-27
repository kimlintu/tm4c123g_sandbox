#include "tm4c123gh6pm.h"

#include "pwmo.h"

static uint32_t pwmo_ct_ticks_U32 = 0;

static void Pwmo_setDutyCycle(uint32_t dutyCycle_U32);

#define PWMO_LOAD_U16 ((uint16_t)0xC350)

void Pwmo_init(void)
{
    /* Clock gating to PWM module */
    SYSCTL_RCGCPWM_R |= SYSCTL_RCGCPWM_R1;

    /* Select alternate function to GPIOF Pin 1 to be PWM output */
    GPIO_PORTF_AFSEL_R |= (1 << 1);

    /* Select M1PWM5 input for the pin */
    GPIO_PORTF_PCTL_R |= GPIO_PCTL_PF1_M1PWM5; // 0101 0000

    /* Disable PWM output */
    PWM1_2_CTL_R = 0;

    /* Action when matching comparator => output HIGH */
    PWM1_2_GENB_R |= PWM_1_GENB_ACTCMPAD_ONE; 

    /* Action when resetting counter   => output LOW  */
    PWM1_2_GENB_R |= PWM_1_GENB_ACTLOAD_ZERO;

    /* Load (reset) value */
    PWM1_2_LOAD_R = PWMO_LOAD_U16;

    /* Initial comparator value */
    PWM1_2_CMPA_R = (0 & PWM_1_CMPA_COMPA_M);

    /* Enable PWM module */
    PWM1_2_CTL_R = 0x1;

    /* Enable PWM output to pin */
    PWM1_ENABLE_R |= PWM_ENABLE_PWM5EN;
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

    Pwmo_setDutyCycle(pwmo_ct_ticks_U32);

    pwmo_ct_ticks_U32 += counterDirection_S08;
}

static void Pwmo_setDutyCycle(uint32_t dutyCycle_U32)
{
    uint16_t cmpValue_U16 = (dutyCycle_U32 * (PWMO_LOAD_U16 / 32 - 1)) / 100; 

    PWM1_2_CMPA_R = cmpValue_U16;
}