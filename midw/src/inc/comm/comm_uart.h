#pragma once

#include "coms_uart.h"
#include "data_rbfr.h"

typedef struct 
{
    tUART_BAUDRATE_E baudRate_E; /* Baud rate used for communication      */
    tUART_DATALEN_E  dataLen_E;  /* Number of data bits in an UART frame  */
    tRBFR_SIZE_E     queueSize;  /* Number of data packets to store for   */
                                 /* processing, each packet has a nr. of  */
                                 /* bits specified by dataLen_E *         */
} tUART_CONF_STR;

void Uart_enableModule(tUART_CONF_STR *conf_pstr);
void Uart_init(void);
void Uart_10ms(void);