/*********************************************************** 
 *
 * Group:  STRT - Startup
 * Module: Vect - Interrupt vector table
 * 
 * This module contains the interrupt vector table for
 * the CPU.
 * 
 ***********************************************************/
#include <stdint.h>

#include "strt_main.h"

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

__attribute__((section(".base_isr_vector")))
const tVECT_HANDLER_FN const Vect_vectorTable_af[] =
{
    (tVECT_HANDLER_FN)&_lnk_stackTop,
    (tVECT_HANDLER_FN)Strt_main,
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

#define NVIC_VTABLE_R           (*((volatile uint32_t *)0xE000ED08))

void Vect_updateVectorTableOffset(void)
{
    NVIC_VTABLE_R |= (uint32_t)Vect_vectorTable_af;
}