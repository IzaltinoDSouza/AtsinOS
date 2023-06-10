#include <io.h>

void out8(u16 port,u8 data)
{
	__asm__ volatile("outb %0, %w1" : : "a"(data), "Nd"(port));
}
u8 in8(u16 port)
{
	u8 data;
	__asm__ volatile("inb %w1, %0" : "=a"(data) : "Nd"(port));
	return data;
}
