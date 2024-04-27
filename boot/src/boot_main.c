#include "stdint.h"

#define BOOT_SIZE_U32 ((uint32_t)0x1000)

typedef void (*tVECT_HANDLER_FN)(void);

void boot_main(void);

extern uint8_t __StackTop; 

__attribute__((section(".boot_isr_vector")))
tVECT_HANDLER_FN vectorTable_aSTR[] = 
{
    (tVECT_HANDLER_FN)&__StackTop, 
    (tVECT_HANDLER_FN)boot_main
};

void boot_main(void)
{
    uint32_t        *vectorTable_pU32 = (uint32_t *)BOOT_SIZE_U32;
    tVECT_HANDLER_FN resetVector_pf   = (tVECT_HANDLER_FN)vectorTable_pU32[1];

    /* Call the reset handler */
    resetVector_pf();
}