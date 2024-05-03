#include <stdint.h>

#include "coms_uart.h"
#include "tm4c123gh6pm.h"

/*
 * Configures and enables the UART module. 
 *
 * This will enable UART module 3 which uses pin PC6 for UART RX and 
 * pin PC7 for UART TX. 
 * 
 * @param brd_str:        Baud rate divisor
 * @param linkCtrlBf_U32: Link control bitfield
 */
void Uart_configure(tUART_BAUDRATE_DIV_STR brd_str, uint32_t linkCtrlBf_U32)
{
    /* Enable clock to UART module (3) */
    SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R3;

    /* Enable clock to needed GPIO module (C) */
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R2;

    /* Set pins to digital IO */
    GPIO_PORTC_DEN_R = (0x01 << 6) | (0x01 << 7);
    
    /* Set alternate function for pins (PC6, PC7) */
    /* for UART RX & TX */
    GPIO_PORTC_AFSEL_R |= (0x01 << 7)  | (0x01 << 6);
    GPIO_PORTC_PCTL_R  |= (0x01 << 28) | (0x01 << 24);

    /* Disable UART */    
    UART3_CTL_R &= ~UART_CTL_UARTEN;

    /* Integer part of baud-rate clock divisor */
    UART3_IBRD_R = brd_str.integer_U32;

    /* Fraction part of baud-rate clock divisor */
    UART3_FBRD_R = brd_str.fractional_U32;

    /* UART line control     */
    /* 8-bit data            */
    /* Disable FIFO-Q        */
    /* 1 stop bit            */
    /* Parity check disabled */
    UART3_LCRH_R = linkCtrlBf_U32;

    /* UART clock source = System clock */
    UART3_CC_R = 0;

    /* Enable UART */
    UART3_CTL_R |= UART_CTL_UARTEN;
}

/*
 * Returns the baud rate divisor that is used for the baud rate generator
 *
 * @param baudRate_E: Enum specifying the desired baud rate
 */
tUART_BAUDRATE_DIV_STR Uart_getBaudRateDivisor_str(tUART_BAUDRATE_E baudRate_E)
{
    tUART_BAUDRATE_DIV_STR baudRate_str;

    switch (baudRate_E)
    {
        case UART_BAUDRATE_115200_E:
            baudRate_str.integer_U32    = 0x1B;
            baudRate_str.fractional_U32 = 0x08;

            break;
        default:
            baudRate_str.integer_U32    = UINT32_MAX;
            baudRate_str.fractional_U32 = UINT32_MAX;
    }

    return baudRate_str;
}

/*
 * Returns a bitfield specifying the UART link control configuration.
 *
 * @param dataLen_E: Enum specifying the number of data bits in an UART frame
 * 
 * TODO: add other parameters
 */
uint32_t Uart_getLinkCtrlBf_U32(tUART_DATALEN_E dataLen_E)
{
    uint32_t linkCtrlBf_U32 = 0;

    /* Data length in UART frame */
    switch (dataLen_E)
    {
        case UART_DATA_8BIT_E:
            linkCtrlBf_U32 |= (0x03 << 5);

            break;
    }

    return linkCtrlBf_U32;
}