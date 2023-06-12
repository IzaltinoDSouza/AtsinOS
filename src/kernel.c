#include <types.h>
#include <multiboot.h>
#include <log.h>
#include <video/video.h>
#include <timer.h>
#include <keyboard.h>

void _kernel(multiboot_info_t * mboot_ptr)
{
	log_info("AtsinOS");

	timer_init();

	video_init(mboot_ptr);

	game01_loop();
}
