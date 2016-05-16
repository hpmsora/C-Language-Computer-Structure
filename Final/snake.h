#ifndef SNAKE_H
#define SNAKE_H

#include "screenmatrix.h"
#include "structure.h"

#define FOOD_COLOR screenmatrix_blue

typedef struct snake_linked_list {
  unsigned char x_move;
  unsigned char y_move;
  struct snake_linked_list *next;
} snake_linked_list_t;

typedef struct {
  unsigned char head_x;
  unsigned char head_y;
  snake_linked_list_t *tail;
  snake_linked_list_t *tail_insert_ptr;
  unsigned char size;
  direction_t orientation;
  screenmatrix_color_t color;
} snake_t;

typedef enum {
  FOOD_PICKUP,     // picked up food
  COLLIDED_SELF,   // crashed into self
  COLLIDED_OTHER,  // crashed into other player
  ILLEGAL_MOVE,    // tried to move off board
  NOTHING_SPECIAL, // moved into a blank space
} snake_move_result_t;

// initializes a snake with given parameters
void initSnake(snake_t *snake, unsigned char head_x, unsigned char head_y, direction_t orientation, screenmatrix_color_t color);

// move the snake towards direction and return what happened during the move
snake_move_result_t moveSnake(snake_t *snake, screenmatrix_t *board, screenmatrix_color_t opponentColor);

#endif
