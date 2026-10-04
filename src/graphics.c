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

  sceDisplaySetFrameBuf((void*)front_buff, SCREEN_STRIDE, current_pixel_format, PSP_DISPLAY_SETBUF_NEXTFRAME);

  sceDisplayWaitVblankStart();
}

void gfx_clear_screen(unsigned int color) {
  for (int i = 0; i < SCREEN_HEIGHT; i++) {
    for (int j = 0; j < SCREEN_WIDTH; j++) {
      back_buff[j + (i * SCREEN_STRIDE)] = color;
    }
  }
}

void gfx_draw_pixel(int x, int y, unsigned int color) {
  if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
    return;
  }

  back_buff[x + (y * SCREEN_STRIDE)] = color;
}

void gfx_draw_rect(int x, int y, int w, int h, unsigned int color) {
  if (x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT || (x + w) <= 0 || (y + h) <= 0) {
    return;
  }

  if (x < 0) { w += x; x = 0; }
  if (y < 0) { h += y; y = 0; }
  if (x + w > SCREEN_WIDTH) { w = SCREEN_WIDTH - x; }
  if (y + h > SCREEN_HEIGHT) { h = SCREEN_HEIGHT - y; }

  for (int i = 0; i < h; i++) {
    int y_ = y + i;
    for (int j = 0; j < w; j++) {
      int x_ = x + j;
      back_buff[x_ + (y_ * SCREEN_STRIDE)] = color;
    }
  }
}

void gfx_draw_texture(int x, int y, Texture *texture) {
  if (x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT || (x + texture->width) <= 0 || (y + texture->height) <= 0) {
    return;
  }

  int tw = texture->width;
  int th = texture->height;

  int t_start_x = 0;
  int t_start_y = 0;

  if (x < 0) {
    int ctx = -x;
    tw -= ctx;
    t_start_x = ctx;
    x = 0;
  }
  if (y < 0) {
    int cty = -y;
    th -= cty;
    t_start_y = cty;
    y = 0;
  }
  if (x + tw > SCREEN_WIDTH) { tw = SCREEN_WIDTH - x; }
  if (y + th > SCREEN_HEIGHT) { th = SCREEN_HEIGHT - y; }

  for (int i = 0; i < th; i++) {
    int y_ = y + i;
    int t_curr_y = t_start_y + i;
    for (int j = 0; j < tw; j++) {
      int x_ = x + j;
      int t_curr_x = t_start_x + j;
      int t_ptr = t_curr_x + (t_curr_y * texture->width);
      back_buff[x_ + (y_ * SCREEN_STRIDE)] = texture->pixels[t_ptr];
    }
  }
}