#include "tm4c123gh6pm.h"

#include "uart.h"
#include "gpio.h"
#include "rbfr.h"

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

static uint32_t uart_rbfrDescriptor_U32 = UINT32_MAX;

/*
 * Configures and enables the UART module. 
 *
 * This will enable UART module 3 which uses pin PC6 for UART RX and 
 * pin PC7 for UART TX. 
 * 
 * @param brd_str:        Baud rate divisor
 * @param linkCtrlBf_U32: Link control bitfield
 */
static void Uart_configure(tUART_BAUDRATE_DIV_STR brd_str, uint32_t linkCtrlBf_U32)
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
static tUART_BAUDRATE_DIV_STR Uart_getBaudRateDivisor_str(tUART_BAUDRATE_E baudRate_E)
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
static uint32_t Uart_getLinkCtrlBf_U32(tUART_DATALEN_E dataLen_E)
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