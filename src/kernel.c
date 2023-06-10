#include <types.h>
#include <multiboot.h>
#include <timer.h>
#include <keyboard.h>

typedef struct
{
	u32  width;
	u32  height;
	u32  pitch;
	u16  bpp;
	u8 * buffer;
	u8   padding;
}FrameBuffer;

FrameBuffer default_framebuffer;

void video_init(multiboot_info_t * mboot_ptr)
{
	default_framebuffer.buffer = mboot_ptr->framebuffer_addr;
	default_framebuffer.pitch  = mboot_ptr->framebuffer_pitch;
	default_framebuffer.width  = mboot_ptr->framebuffer_width;
	default_framebuffer.height = mboot_ptr->framebuffer_height;
	default_framebuffer.bpp    = mboot_ptr->framebuffer_bpp;
	
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
void draw_pixels(u32 x,u32 y,u32 color)
{
	u32 offset = (x + default_framebuffer.width * y) * (default_framebuffer.bpp/8);
	
	default_framebuffer.buffer[offset+3] = (color >> 24) & 0xff;
	default_framebuffer.buffer[offset+2] = (color >> 16) & 0xff;
	default_framebuffer.buffer[offset+1] = (color >>  8) & 0xff;
	default_framebuffer.buffer[offset+0] = (color >>  0) & 0xff;
}
void fill_rectangle(u32 x,u32 y,u32 width,u32 height,u32 color)
{
	//TODO check if x+width and y+height is inside of screen 
	for(u32 posy = 0;posy < width;++posy)
	{
		for(u32 posx = 0;posx < height;++posx)
		{
			draw_pixels(posx+x,posy+y,color);
		}
	}
}

typedef struct
{
	u32 x;
	u32 y;
	u32 width;
	u32 height;
	float speed;
	u32 color;
}Player;

Player g_player;
void init()
{	
	g_player.height = 32;
	g_player.width  = 32;
	g_player.x	    = (default_framebuffer.width-g_player.width)/2;
	g_player.y	    = (default_framebuffer.height-g_player.height)/2;
	g_player.speed  = 25;
	g_player.color  = 0xff0000ff; //argb = green
								  //alpha channel is ignored?
}

void update(float dt)
{
	if(keyboard_poll())
	{
		Keys key = keyboard_get_key();
		switch(key)
		{
			case KEY_D:
			{
				g_player.x += g_player.speed * dt;
			}break;
			case KEY_A:
			{
				g_player.x -= g_player.speed * dt;
			}break;
			case KEY_S:
			{
				g_player.y += g_player.speed * dt;
			}break;
			case KEY_W:
			{
				g_player.y -= g_player.speed * dt;
			}break;
		}
	}

	if(g_player.x <= g_player.width)
		g_player.x = g_player.width;
	
	if(g_player.x  >= default_framebuffer.width - g_player.width)
		g_player.x  = default_framebuffer.width - g_player.width;
	
	if(g_player.y <= g_player.height)
		g_player.y = g_player.height;
		
	if(g_player.y  >= default_framebuffer.height - g_player.height)
		g_player.y  = default_framebuffer.height - g_player.height;
}
void draw()
{
	//fill a rectangle on center of screen
	fill_rectangle(g_player.x,g_player.y,g_player.width,g_player.height,g_player.color);
}

void _kernel(multiboot_info_t * mboot_ptr)
{
	timer_init();

	video_init(mboot_ptr);
		
	float fps = 30.0f;
	u64 fps_target_time = (1.0f/fps) * 1000;
	
	init();
	
	//Game Loop
	u64 prev_time = get_time_ms();
	while(1)
	{
		u64 current_time = get_time_ms();
		
		u64 delta_time = current_time - prev_time;
		
		prev_time = current_time;
		
		update(delta_time / 1000.0f);
		
		video_clear(0xff000000);
		draw();
		
		u64 frame_time = get_time_ms() - current_time;
		if(frame_time < fps_target_time)
			delay_ms(fps_target_time - frame_time);
	}
}
