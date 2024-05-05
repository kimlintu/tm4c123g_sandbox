#pragma once

#include <stdint.h>

void SysTick_Handler(void);
void Syst_init(void);
uint32_t Syst_getSysTick_U32(void);