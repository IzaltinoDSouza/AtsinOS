#pragma once

#include <types.h>

u32 graphic_get_width();
u32 graphic_get_height();
void graphic_draw_pixel(u32 x,u32 y,u32 color);
void graphic_draw_pixels(u32 x,u32 y,u32 width,u32 height,u8 * pixels);
void graphic_fill_rectangle(u32 x,u32 y,u32 width,u32 height,u32 color);
void graphic_clear(u32 color);
void graphic_flush();
