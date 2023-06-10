#pragma once

#include <types.h>

typedef struct
{
	u32  width;
	u32  height;
	u32  pitch;
	u16  bpp;
	u8 * buffer;
	u8   padding;
}FrameBuffer;
