#include <keyboard.h>
#include <types.h>
#include <io.h>

#define KEYBOARD_STATUS_PORT 0x64
#define KEYBOARD_DATA_PORT   0x60

u8 read_keyboard_status()
{
    return in8(KEYBOARD_STATUS_PORT);
}

u8 read_scan_code()
{
    return in8(KEYBOARD_DATA_PORT);
}

bool keyboard_poll()
{
	return read_keyboard_status() & 0x01;
}

u8 keyboard_get_key()
{
	return read_scan_code();
}
