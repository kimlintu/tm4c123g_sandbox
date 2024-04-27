#include <stdint.h>

#include "startup.h"

extern uint32_t _lnk_stackTop;

typedef void (*tVECT_HANDLER_FN)(void);

__attribute__((weak)) void NMI_Handler(void)
{
    while (1)
    {
    };
}

__attribute__((weak)) void HardFault_Handler(void)
{
    while (1)
    {
    };
}

__attribute__((weak)) void MemManage_Handler(void)
{
    while (1)
    {
    };
}

__attribute__((weak)) void BusFault_Handler(void)
{
    while (1)
    {
    };
}

__attribute__((weak)) void UsageFault_Handler(void)
{
    while (1)
    {
    };
}

__attribute__((weak)) void SVC_Handler(void)
{
    while (1)
    {
    };
}

__attribute__((weak)) void DebugMon_Handler(void)
{
    while (1)
    {
    };
}

__attribute__((weak)) void PendSV_Handler(void)
{
    while (1)
    {
    };
}

__attribute__((weak)) void SysTick_Handler(void)
{
    while (1)
    {
    };
}

__attribute__((section(".appl_isr_vector")))
tVECT_HANDLER_FN vectorTable_af[] =
{
    (tVECT_HANDLER_FN)&_lnk_stackTop,
    (tVECT_HANDLER_FN)startup,
    (tVECT_HANDLER_FN)NMI_Handler,
    (tVECT_HANDLER_FN)HardFault_Handler,
    (tVECT_HANDLER_FN)MemManage_Handler,
    (tVECT_HANDLER_FN)BusFault_Handler,
    (tVECT_HANDLER_FN)UsageFault_Handler,
    (tVECT_HANDLER_FN)0,
    (tVECT_HANDLER_FN)0,
    (tVECT_HANDLER_FN)0,
    (tVECT_HANDLER_FN)0,
    (tVECT_HANDLER_FN)SVC_Handler,
    (tVECT_HANDLER_FN)DebugMon_Handler,
    (tVECT_HANDLER_FN)0,
    (tVECT_HANDLER_FN)PendSV_Handler,
    (tVECT_HANDLER_FN)SysTick_Handler,
};
