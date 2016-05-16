#include "snake.h"
#include "screenmatrix.h"
#include "structure.h"
#include <stdio.h>
#include <stdlib.h>

void initSnake(snake_t *snake, unsigned char head_x, unsigned char head_y, direction_t orientation, screenmatrix_color_t color) {
  snake->head_x = head_x;
  snake->head_y = head_y;

  snake_linked_list_t *tail = malloc(sizeof(snake_linked_list_t));
  tail->x_move = head_x;
  tail->y_move = head_y;
  tail->next = NULL;

  snake->tail = tail;
  snake->tail_insert_ptr = tail;
  snake->size = 1;
  snake->orientation = orientation;
  snake->color = color;
}

snake_move_result_t moveSnake(snake_t *snake, screenmatrix_t *board, screenmatrix_color_t opponentColor) {
  unsigned char newHeadX = snake->head_x, newHeadY = snake->head_y;

  switch(snake->orientation) {
  case NORTH:
    newHeadY--;
    break;
  case SOUTH:
    newHeadY++;
    break;
  case EAST:
    newHeadX++;
    break;
  case WEST:
    newHeadX--;
    break;
  }

  if (!screenmatrix_isLegalMove(newHeadX, newHeadY)) {
    // this move is out of bounds
    return ILLEGAL_MOVE;
  }

  unsigned char prevSize = snake->size;
  screenmatrix_color_t colorAtSquare = screenmatrix_getpixel(board, newHeadX, newHeadY);
  snake_move_result_t moveResult;

  if (colorAtSquare == opponentColor) {
    // crashed into opponent
    return COLLIDED_OTHER;
  } else if (colorAtSquare == snake->color) {
    // crashed into self
    return COLLIDED_SELF;
  } else if (colorAtSquare == FOOD_COLOR) {
    // picked up food
    snake->size++;
    moveResult = FOOD_PICKUP;
  } else {
    // nothing special happened
    moveResult = NOTHING_SPECIAL;
  }

  // move head to new space
  screenmatrix_setpixel(board, newHeadX, newHeadY, snake->color);
  snake->head_x = newHeadX;
  snake->head_y = newHeadY;

  if (prevSize == snake->size) {
    // snake did not grow, consume some of the tail
    screenmatrix_setpixel(board, snake->tail->x_move, snake->tail->y_move, screenmatrix_black);

    snake_linked_list_t *next = snake->tail->next;
    free(snake->tail);
    snake->tail = next;
  }

  snake_linked_list_t *breadcrumb = malloc(sizeof(snake_linked_list_t));
  breadcrumb->x_move = newHeadX;
  breadcrumb->y_move = newHeadY;
  breadcrumb->next = NULL;

  if (snake->tail == NULL) {
    snake->tail = breadcrumb;
  }

  snake->tail_insert_ptr->next = breadcrumb;
  snake->tail_insert_ptr = breadcrumb;

  return moveResult;
}
