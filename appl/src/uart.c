#include "tm4c123gh6pm.h"

#include "uart.h"

void Uart_init(void)
{
    /* Enable clock to UART module (2) */
    SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R2;

    /* Enable clock to needed GPIO module (D) */
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R3;

    /* PD7 is special and needs to be unlocked */ 
    /* before changes can be commited to its GPIO 
    /* registers. GPIOLOCK, GPIOCR */
    GPIO_PORTD_LOCK_R = 0x4C4F434B;
    GPIO_PORTD_CR_R  |= (0x01 << 7);

    /* Set pins to digital IO */
    GPIO_PORTD_DEN_R = 0x06 | 0x07;
    
    /* Set alternate function for pins (PD6, PD7) */
    /* for UART RX & TX */
    GPIO_PORTD_AFSEL_R |= (0x01 << 7)  | (0x01 << 6);
    GPIO_PORTD_PCTL_R  |= (0x01 << 28) | (0x01 << 24);

    /* Disable UART */    
    UART2_CTL_R &= ~UART_CTL_UARTEN;

    /* Integer part of baud-rate clock divisor */
    UART2_IBRD_R = 0x1B;

    /* Fraction part of baud-rate clock divisor */
    UART2_FBRD_R = 0x08;

    /* UART line control     */
    /* 8-bit data            */
    /* Disable FIFO-Q        */
    /* 1 stop bit            */
    /* Parity check disabled */
    UART2_LCRH_R |= (0x03 << 5);

    /* UART clock source = System clock */
    UART2_CC_R = 0;

    /* Enable UART */
    UART2_CTL_R |= UART_CTL_UARTEN;
}