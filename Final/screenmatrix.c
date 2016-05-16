#include "screenmatrix.h"
#include "rect.h"
#include <stdio.h>
#include <f3d_lcd_sd.h>

const screenmatrix_color_t screenmatrix_blank = 0;
const screenmatrix_color_t screenmatrix_red = 1;
const screenmatrix_color_t screenmatrix_blue = 2;
const screenmatrix_color_t screenmatrix_green = 3;
const screenmatrix_color_t screenmatrix_black = 4;

// set a pixel at position x, y 
int screenmatrix_setpixel(screenmatrix_t *screenmatrix, unsigned char x, unsigned char y, screenmatrix_color_t color) {
  //const int colorSendBufferSize = SCREENMATRIX_PIXEL_SIZE * SCREENMATRIX_PIXEL_SIZE;
  //static uint16_t colorSendBuffer[colorSendBufferSize];
  if (screenmatrix_isLegalMove(x, y)) {
    // set the value in the matrix
    screenmatrix->matrix[x][y] = color;
    
    // write the corresponding stm color into the send buffer
    uint16_t stm32Color = screenmatrix_convertColor(color);
    /*int i;
    for (i = 0; i < colorSendBufferSize; i++) {
      colorSendBuffer[i] = stm32Color;
      }*/
    
    // push the colors onto the LCD screen
    int startX = SCREENMATRIX_PIXEL_SIZE * x;
    int startY = SCREENMATRIX_PIXEL_SIZE * y;
    //ST7735_setAddrWindow(startX, startX + SCREENMATRIX_PIXEL_SIZE, startY, startY + SCREENMATRIX_PIXEL_SIZE, MADCTLGRAPHICS);
    //ST7735_pushColor(colorSendBuffer, colorSendBufferSize);
    rect_t r;
    initRect(&r, startX, startY, SCREENMATRIX_PIXEL_SIZE, SCREENMATRIX_PIXEL_SIZE, stm32Color);
    redrawRect(&r);
    return 1;
  }
  return 0;
}

screenmatrix_color_t screenmatrix_getpixel(screenmatrix_t *screenmatrix, unsigned char x, unsigned char y) {
  if (screenmatrix_isLegalMove(x, y)) {
    return screenmatrix->matrix[x][y];
  } else {
    return screenmatrix_blank;
  }
}

uint16_t screenmatrix_convertColor(screenmatrix_color_t color) {
  if (color == screenmatrix_red) {
    return RED;
  } else if (color == screenmatrix_blue) {
    return BLUE;
  } else if (color == screenmatrix_green) {
    return GREEN;
  } else if (color == screenmatrix_black) {
    return BLACK;
  } else {
    return WHITE;
  }
}

int screenmatrix_isLegalMove(unsigned char x, unsigned char y) {
  return x < SCREENMATRIX_WIDTH && y < SCREENMATRIX_HEIGHT;
}
