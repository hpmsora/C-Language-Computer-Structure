#ifndef SCREENMATRIX_H
#define SCREENMATRIX_H
#include <f3d_lcd_sd.h>


// the amount of pixels a screenmatrix cell represents
#define SCREENMATRIX_PIXEL_SIZE 4
#define SCREENMATRIX_WIDTH (ST7735_width / SCREENMATRIX_PIXEL_SIZE)
#define SCREENMATRIX_HEIGHT (ST7735_height / SCREENMATRIX_PIXEL_SIZE)

/* new types */
typedef unsigned char screenmatrix_color_t;
typedef struct {
  screenmatrix_color_t matrix[SCREENMATRIX_WIDTH][SCREENMATRIX_HEIGHT];
} screenmatrix_t;

// color constants
extern const screenmatrix_color_t screenmatrix_blank;
extern const screenmatrix_color_t screenmatrix_red;
extern const screenmatrix_color_t screenmatrix_blue;
extern const screenmatrix_color_t screenmatrix_green;
extern const screenmatrix_color_t screenmatrix_black;

// screenmatrix functions
int screenmatrix_setpixel(screenmatrix_t *screenmatrix, unsigned char x, unsigned char y, screenmatrix_color_t color);
screenmatrix_color_t screenmatrix_getpixel(screenmatrix_t *screenmatrix, unsigned char x, unsigned char y);
uint16_t screenmatrix_convertColor(screenmatrix_color_t color);
int screenmatrix_isLegalMove(unsigned char x, unsigned char y);

#endif
