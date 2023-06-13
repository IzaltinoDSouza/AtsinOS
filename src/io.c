#include <io.h>

void out8(u16 port,u8 data)
{
	__asm__ volatile("outb %1,%0" : : "a"(data), "Nd"(port));
}
u8 in8(u16 port)
{
	u8 data;
	__asm__ volatile("inb %0,%1" : "=a"(data) : "Nd"(port));
	return data;
}
