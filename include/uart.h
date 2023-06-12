#pragma once

#include <io.h>
#include <utils/string.h>

#define UART_BASE_ADDRESS 		0x3F8
#define UART_DATA_REGISTER     (UART_BASE_ADDRESS + 0)  // Data register
#define UART_LINE_CONTROL      (UART_BASE_ADDRESS + 3)  // Line control register
#define UART_LINE_STATUS       (UART_BASE_ADDRESS + 5)  // Line status register

static void uart_write_ascii(char c)
{
	// Wait until the transmitter is ready
    while((in8(UART_LINE_STATUS) & 0x20) == 0) {} 
    out8(UART_DATA_REGISTER, c);
}

static void uart_write_string(const char * str)
{
    while(*str)
    {
        uart_write_ascii(*str++);
    }
}
static void uart_write_number(int number)
{
	char str[16];
	int length = int_to_string(number,str);
	for(int i = 0;i < length;++i)
	{
		uart_write_ascii(str[i]);
	}
}
