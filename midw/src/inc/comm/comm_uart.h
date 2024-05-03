#pragma once

#include "coms_uart.h"

void Uart_enableModule(tUART_CONF_STR *conf_pstr);
void Uart_init(void);
void Uart_10ms(void);