#include <graphics/graphics.h>
#include <video/framebuffer.h>

extern FrameBuffer * double_framebuffer;

u32 graphic_get_width()
{
	return double_framebuffer->width;
}
u32 graphic_get_height()
{
	return double_framebuffer->height;
}

void graphic_draw_pixel(u32 x,u32 y,u32 color)
{
	u32 offset = (x + double_framebuffer->width * y) * (double_framebuffer->bpp/8);
	
	double_framebuffer->buffer[offset+3] = (color >> 24) & 0xff;
	double_framebuffer->buffer[offset+2] = (color >> 16) & 0xff;
	double_framebuffer->buffer[offset+1] = (color >>  8) & 0xff;
	double_framebuffer->buffer[offset+0] = (color >>  0) & 0xff;
}

void graphic_draw_pixels(u32 x,u32 y,u32 width,u32 height,u8 * pixels)
{
	//TODO check if x+width and y+height is inside of screen 
	for(u32 posy = 0;posy < height;++posy)
	{
		for(u32 posx = 0;posx < width;++posx)
		{
			u32 offset = (posx + double_framebuffer->width * posy) * (double_framebuffer->bpp/8);
			graphic_draw_pixel(posx+x,posy+y,pixels[offset]);
		}
	}
}

void graphic_fill_rectangle(u32 x,u32 y,u32 width,u32 height,u32 color)
{
	//TODO check if x+width and y+height is inside of screen 
	for(u32 posy = 0;posy < height;++posy)
	{
		for(u32 posx = 0;posx < width;++posx)
		{
			graphic_draw_pixel(posx+x,posy+y,color);
		}
	}
}

void graphic_clear(u32 color)
{
	/* TODO :only use this with real double framebuffer
	u32 size    = double_framebuffer->width * double_framebuffer->height;
	u32 * begin = (u32*)double_framebuffer->buffer;
	u32 * end   = ((u32*)double_framebuffer->buffer) + size;
			  
	while(begin != end)
	{
		*begin++ = color;
	}*/
	
	video_clear(color);
}
void graphic_flush()
{
	video_flush();
}
