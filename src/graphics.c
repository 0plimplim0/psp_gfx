#include <pspdisplay.h>

#include "graphics.h"

static int current_pixel_format;

static unsigned int *front_buff;
static unsigned int *back_buff;

void gfx_init(int pixel_format) {
  current_pixel_format = pixel_format;

  front_buff = (unsigned int*)VRAM_BLOCK_0;
  back_buff = (unsigned int*)VRAM_BLOCK_1;

  sceDisplaySetMode(0, SCREEN_WIDTH, SCREEN_HEIGHT);
  sceDisplaySetFrameBuf((void*)front_buff, SCREEN_STRIDE, pixel_format, PSP_DISPLAY_SETBUF_IMMEDIATE);
}

void gfx_swap_bufs(void) {
  unsigned int *temp = front_buff;
  front_buff = back_buff;
  back_buff = temp;

  sceDisplayWaitVblankStart();

  sceDisplaySetFrameBuf((void*)front_buff, SCREEN_STRIDE, current_pixel_format, PSP_DISPLAY_SETBUF_NEXTFRAME);
}

void gfx_clear_screen(unsigned int color) {
  for (int i = 0; i < SCREEN_HEIGHT; i++) {
    for (int j = 0; j < SCREEN_WIDTH; j++) {
      back_buff[j + (i * SCREEN_STRIDE)] = color;
    }
  }
}