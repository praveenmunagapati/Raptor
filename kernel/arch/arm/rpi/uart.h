#include <liblox/common.h>
#include <kernel/tty/tty.h>

#include "board.h"

enum {
    UART0_BASE = BOARD_UART0_BASE,
    UART0_DR = (UART0_BASE + 0x00), // The offsets for reach register for the UART.
    UART0_RSRECR = (UART0_BASE + 0x04),
    UART0_FR = (UART0_BASE + 0x18),
    UART0_ILPR = (UART0_BASE + 0x20),
    UART0_IBRD = (UART0_BASE + 0x24),
    UART0_FBRD = (UART0_BASE + 0x28),
    UART0_LCRH = (UART0_BASE + 0x2C),
    UART0_CR = (UART0_BASE + 0x30),
    UART0_IFLS = (UART0_BASE + 0x34),
    UART0_IMSC = (UART0_BASE + 0x38),
    UART0_RIS = (UART0_BASE + 0x3C),
    UART0_MIS = (UART0_BASE + 0x40),
    UART0_ICR = (UART0_BASE + 0x44),
    UART0_DMACR = (UART0_BASE + 0x48),
    UART0_ITCR = (UART0_BASE + 0x80),
    UART0_ITIP = (UART0_BASE + 0x84),
    UART0_ITOP = (UART0_BASE + 0x88),
    UART0_TDR = (UART0_BASE + 0x8C)
};

extern tty_t* uart_tty;

void uart_init(void);
void uart_putc(unsigned char byte);
bool uart_poll(void);
uint8_t uart_poll_getc(void);
uint8_t uart_getc(void);
void uart_write(const uint8_t* buffer, size_t size);
void uart_puts(const char *str);
void uart_kpload(void);
