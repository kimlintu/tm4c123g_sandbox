#pragma once

#include "data_rbfr.h"

typedef enum 
{
    UART_BAUDRATE_115200_E,
    UART_BAUDRATE_INVALID_E
} tUART_BAUDRATE_E;

typedef enum 
{
    UART_DATA_8BIT_E,
    UART_DATA_INVALID_E
} tUART_DATALEN_E;

typedef struct 
{
    tUART_BAUDRATE_E baudRate_E; /* Baud rate used for communication      */
    tUART_DATALEN_E  dataLen_E;  /* Number of data bits in an UART frame  */
    tRBFR_SIZE_E     queueSize;  /* Number of data packets to store for   */
                                 /* processing, each packet has a nr. of  */
                                 /* bits specified by dataLen_E *         */
} tUART_CONF_STR;

tUART_CONF_STR uart_conf_str = 
{
    UART_BAUDRATE_115200_E,
    UART_DATA_8BIT_E
};

typedef struct 
{
    uint32_t integer_U32;    /* Integer part of baud rate divisor    */
    uint32_t fractional_U32; /* Fractional part of baud rate divisor */
} tUART_BAUDRATE_DIV_STR;

/*
 * Configures and enables the UART module. 
 *
 * This will enable UART module 3 which uses pin PC6 for UART RX and 
 * pin PC7 for UART TX. 
 * 
 * @param brd_str:        Baud rate divisor
 * @param linkCtrlBf_U32: Link control bitfield
 */
void Uart_configure(tUART_BAUDRATE_DIV_STR brd_str, uint32_t linkCtrlBf_U32);

/*
 * Returns the baud rate divisor that is used for the baud rate generator
 *
 * @param baudRate_E: Enum specifying the desired baud rate
 */
tUART_BAUDRATE_DIV_STR Uart_getBaudRateDivisor_str(tUART_BAUDRATE_E baudRate_E);

/*
 * Returns a bitfield specifying the UART link control configuration.
 *
 * @param dataLen_E: Enum specifying the number of data bits in an UART frame
 * 
 * TODO: add other parameters
 */
uint32_t Uart_getLinkCtrlBf_U32(tUART_DATALEN_E dataLen_E);