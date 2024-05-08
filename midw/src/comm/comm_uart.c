#include "tm4c123gh6pm.h"

#include "comm_uart.h"
#include "coms_uart.h"
#include "gnio_gpio.h"

tUART_CONF_STR uart_conf_str = 
{
    UART_BAUDRATE_115200_E,
    UART_DATA_8BIT_E
};

static uint32_t uart_rbfrDescriptor_U32 = UINT32_MAX;

void Uart_enableModule(tUART_CONF_STR *conf_pstr)
{
    tUART_BAUDRATE_DIV_STR baudRateDivisor_str; /* Divisor for setting the baud rate generator */
    uint32_t               linkCtrlBf_U32;      /* Bitfield for the link control register      */

    if (conf_pstr->baudRate_E < UART_BAUDRATE_INVALID_E)
    {
        baudRateDivisor_str = Uart_getBaudRateDivisor_str(conf_pstr->baudRate_E);

        if (conf_pstr->dataLen_E < UART_DATA_INVALID_E)
        {
            linkCtrlBf_U32 = Uart_getLinkCtrlBf_U32(conf_pstr->dataLen_E);

            if (Rbfr_new_B(&uart_rbfrDescriptor_U32, RBFR_SIZE_8_E) == true)
            {
                Uart_configure(baudRateDivisor_str, linkCtrlBf_U32);
            }
            else 
            {
                /* Failed to get a ring buffer */
                /* TODO: error logging         */
            }
        }
        else 
        {
            /* Invalid data length */
            /* TODO: error logging */
        }
    }
    else 
    {
        /* Invalid baud rate   */
        /* TODO: error logging */
    }
}

void Uart_init(void)
{
    Uart_enableModule(&uart_conf_str);
}

void Uart_10ms(void)
{
    uint8_t rxData_U08;
    uint8_t txData_U08;
    uint32_t uartDataAndFlags_U32;
    bool writeOp_B;
    bool readOp_B;

    if (uart_rbfrDescriptor_U32 != UINT32_MAX)
    {
        /* Uart is configured, TODO: better way of deciding this */

        /* Check if we received anything */
        if ((UART3_FR_R & UART_FR_RXFF) == UART_FR_RXFF)
        {
            uartDataAndFlags_U32 = UART3_DR_R;

            rxData_U08 = (uint8_t)(uartDataAndFlags_U32 & 0xFF);

            writeOp_B = Rbfr_write_B(uart_rbfrDescriptor_U32, rxData_U08);

            /* Echo data */
            if ((UART3_FR_R & UART_FR_TXFE) == UART_FR_TXFE)
            {
                readOp_B |= Rbfr_read_B(uart_rbfrDescriptor_U32, &txData_U08);
                /* TX buffer is empty, we can send data */
                UART3_DR_R = rxData_U08;
            }

            if ((writeOp_B == false) || (readOp_B == false))
            {
                Gpio_toggle();
            }

            if (rxData_U08 == 'l')
            {
                Gpio_toggle();
            }

        }
    }
}