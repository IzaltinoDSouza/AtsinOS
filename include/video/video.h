#pragma once

#include <types.h>
#include <multiboot.h>

#include "framebuffer.h"

FrameBuffer double_framebuffer;
FrameBuffer default_framebuffer;
extern _double_framebuffer_buffer;
void video_init(multiboot_info_t * mboot_ptr)
{
	default_framebuffer.buffer = mboot_ptr->framebuffer_addr;
	default_framebuffer.pitch  = mboot_ptr->framebuffer_pitch;
	default_framebuffer.width  = mboot_ptr->framebuffer_width;
	default_framebuffer.height = mboot_ptr->framebuffer_height;
	default_framebuffer.bpp    = mboot_ptr->framebuffer_bpp;
	
	//TODO : create a real double buffer
	double_framebuffer.buffer = &_double_framebuffer_buffer;
	double_framebuffer.pitch  = mboot_ptr->framebuffer_pitch;
	double_framebuffer.width  = mboot_ptr->framebuffer_width;
	double_framebuffer.height = mboot_ptr->framebuffer_height;
	double_framebuffer.bpp    = mboot_ptr->framebuffer_bpp;
}
void video_clear(u32 color)
{
	u32 size    = default_framebuffer.width * default_framebuffer.height;
	u32 * begin = (u32*)default_framebuffer.buffer;
	u32 * end   = ((u32*)default_framebuffer.buffer) + size;
			  
	while(begin != end)
	{
		*begin++ = color;
	}
}

void video_flush()
{
	u32 size = default_framebuffer.width * default_framebuffer.height;
	u32 * video_begin = (u32*)default_framebuffer.buffer;
	u32 * video_end   = ((u32*)default_framebuffer.buffer) + size;
	
	u32 * double_framebuffer_video_begin = (u32*)double_framebuffer.buffer;
	u32 * double_framebuffer_video_end   = ((u32*)double_framebuffer.buffer) + size;
	
	while(video_begin != video_end)
	{
		*video_begin++ = *double_framebuffer_video_begin++;
	}
}
