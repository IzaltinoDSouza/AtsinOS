#include <timer.h>
#include <keyboard.h>
#include <graphics/graphics.h>

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

size_t screen_width = 800;
size_t screen_height = 600;

void init()
{	
	screen_width = graphic_get_width();
	screen_height = graphic_get_height();

	g_player.height = 32;
	g_player.width  = 32;
	g_player.x	    = (screen_width  - g_player.width)/2;
	g_player.y	    = (screen_height - g_player.height)/2;
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
	
	if(g_player.x  >= screen_width - g_player.width)
		g_player.x  = screen_width - g_player.width;
	
	if(g_player.y <= g_player.height)
		g_player.y = g_player.height;
		
	if(g_player.y  >= screen_height - g_player.height)
		g_player.y  = screen_height - g_player.height;
}
void draw()
{
	//fill a rectangle on center of screen
	graphic_fill_rectangle(g_player.x,g_player.y,g_player.width,g_player.height,g_player.color);
}

void game01_loop()
{
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
		
		graphic_clear(0xff000000);
		draw();
		graphic_flush();
		
		u64 frame_time = get_time_ms() - current_time;
		if(frame_time < fps_target_time)
			delay_ms(fps_target_time - frame_time);
	}
}
