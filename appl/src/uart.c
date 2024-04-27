#include "tm4c123gh6pm.h"

#include "uart.h"
#include "gpio.h"

void Uart_init(void)
{
    /* Enable clock to UART module (3) */
    SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R3;

    /* Enable clock to needed GPIO module (C) */
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R2;

    /* Set pins to digital IO */
    GPIO_PORTC_DEN_R = (0x01 << 6) | (0x01 << 7);
    
    /* Set alternate function for pins (PD6, PD7) */
    /* for UART RX & TX */
    GPIO_PORTC_AFSEL_R |= (0x01 << 7)  | (0x01 << 6);
    GPIO_PORTC_PCTL_R  |= (0x01 << 28) | (0x01 << 24);

    /* Disable UART */    
    UART3_CTL_R &= ~UART_CTL_UARTEN;

    /* Integer part of baud-rate clock divisor */
    UART3_IBRD_R = 0x1B;

    /* Fraction part of baud-rate clock divisor */
    UART3_FBRD_R = 0x08;

    /* UART line control     */
    /* 8-bit data            */
    /* Disable FIFO-Q        */
    /* 1 stop bit            */
    /* Parity check disabled */
    UART3_LCRH_R = (0x03 << 5);

    /* UART clock source = System clock */
    UART3_CC_R = 0;

    /* Enable UART */
    UART3_CTL_R |= UART_CTL_UARTEN;
}

void Uart_10ms(void)
{
    uint8_t rxData_U08;
    uint32_t uartDataAndFlags_U32;

    /* Check if we received anything */
    if ((UART3_FR_R & UART_FR_RXFF) == UART_FR_RXFF)
    {
        uartDataAndFlags_U32 = UART3_DR_R;

        rxData_U08 = (uint8_t)(uartDataAndFlags_U32 & 0xFF);

        if (rxData_U08 == 'l')
        {
            Gpio_toggle();
        }
    }
}