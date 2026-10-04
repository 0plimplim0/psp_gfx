#ifndef GRAPHICS_H
#define GRAPHICS_H

#define VRAM_BLOCK_0 0x44000000
#define VRAM_BLOCK_1 0x44088000

#define VRAM_END 0x44200000

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272
#define SCREEN_STRIDE 512

typedef struct Texture {
  int width;
  int height;
  unsigned int *pixels;
} Texture;

void gfx_init(int pixel_format);
void gfx_swap_bufs(void);
void gfx_clear_screen(unsigned int color);
void gfx_draw_pixel(int x, int y, unsigned int color);
void gfx_draw_rect(int x, int y, int w, int h, unsigned int color);
void gfx_draw_texture(int x, int y, Texture *texture);

#endif