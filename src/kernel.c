#include <types.h>
#include <multiboot.h>
#include <log.h>
#include <cpu.h>
#include <video/video.h>
#include <timer.h>
#include <keyboard.h>

void _kernel(multiboot_info_t * mboot_ptr)
{
	log_info("AtsinOS");
	
	cpu_info();

	timer_init();

	video_init(mboot_ptr);

	game01_loop();
}
