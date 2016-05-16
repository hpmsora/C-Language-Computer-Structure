#include <stm32f30x.h>
#include <f3d_uart.h>
#include <f3d_user_btn.h>
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_i2c2.h>
#include <f3d_nunchuk.h>
#include <f3d_delay.h>
#include <f3d_dac.h>
#include <f3d_rtc.h>
#include <ff.h>
#include <diskio.h>
#include "rect.h"
#include "screen.h"
#include "screenmatrix.h"
#include "structure.h"
#include "snake.h"
#include "soundfx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <strings.h>
#include <read_nunchuk_direction.h>

#define EVENT_LOOP_TIME 200
#define FOOD_COUNT 31

//Global Varialbes
int p1_direction = 3;
int p2_direction = 1;
int food_left = FOOD_COUNT;

//Nunchuck Data Initialization
nunchuk_t nunchuk1_data;
nunchuk_t *nunchuk1_ptr = &nunchuk1_data;
nunchuk_t nunchuk2_data;
nunchuk_t *nunchuk2_ptr = &nunchuk2_data;

void takeTurn(snake_t *snake);
void endGame(snake_t *loser);
int randIntInRange(int lowest, int highest);

static screenmatrix_t screenmatrix;
static snake_t player1;
static snake_t player2;

/*The event loop for changing the nunchuk data*/
void nunchuk_change() {
  //Nunchuk Part
  f3d_nunchuk_read(nunchuk1_ptr);
  delay(10);
  f3d_nunchuk_read_2(nunchuk2_ptr);
  delay(10);
  if((p1_direction != getDirection(nunchuk1_ptr)) &&
     (getDirection(nunchuk1_ptr) != 4) &&
     ((getDirection(nunchuk1_ptr) + 2) % 4 != p1_direction)) 
    p1_direction = getDirection(nunchuk1_ptr);
  if((p2_direction != getDirection(nunchuk2_ptr)) &&
     (getDirection(nunchuk2_ptr) != 4) &&
     ((getDirection(nunchuk2_ptr) + 2) % 4 != p2_direction))
    p2_direction = getDirection(nunchuk2_ptr);

}

/*The event loop that handles the key input*/
void takeTurn(snake_t *snake) {
  //Changing Direction
  //player 1
  if (snake == &player1) {
    if(p1_direction == 0)
      snake->orientation = EAST;
    else if(p1_direction == 1)
      snake->orientation = NORTH;
    else if(p1_direction == 2)
      snake->orientation = WEST;
    else if(p1_direction == 3)
      snake->orientation = SOUTH;
    else {}
  }
  //player 2
  if (snake == &player2) {
    if(p2_direction == 0)
      snake->orientation = EAST;
    else if(p2_direction == 1)
      snake->orientation = NORTH;
    else if(p2_direction == 2)
      snake->orientation = WEST;
    else if(p2_direction == 3)
      snake->orientation = SOUTH;
    else {}
  }

  screenmatrix_color_t opponentColor = (snake == &player1) ? player2.color : player1.color;

  snake_move_result_t moveResult = moveSnake(snake, &screenmatrix, opponentColor);
  switch(moveResult) {
  case FOOD_PICKUP:
    food_left--;
    break;
  case COLLIDED_SELF:
    endGame(snake);
    break;
  case COLLIDED_OTHER:
    endGame(snake);
    break;
  case ILLEGAL_MOVE:
    endGame(snake);
    break;
  case NOTHING_SPECIAL:
    break;
  }
  if (food_left == 0) {
    endGame(NULL);
  }
}

/* called from the real main() of the application */
int main( int argc, char *argv[] ) {
  f3d_uart_init();
  f3d_dac_init();
  f3d_rtc_init();
  f3d_timer2_init();
  f3d_delay_init();

  f3d_i2c1_init();
  delay(10);
  f3d_i2c2_init();
  delay(10);
  f3d_nunchuk_init();
  delay(10);
  f3d_user_btn_init();
  f3d_lcd_init();

  //set buffers
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  //srand(time(NULL));

  f3d_lcd_fillScreen(BLACK);
  playEatNoise();

  int isFirstRun = 1;
  initSnake(&player1, 0, 0, SOUTH, screenmatrix_green);

  unsigned char player2_x = SCREENMATRIX_WIDTH - 1, player2_y = SCREENMATRIX_HEIGHT - 1;
  initSnake(&player2, player2_x, player2_y, NORTH, screenmatrix_red);

  int row, col;
  int foodsToAllocate = FOOD_COUNT;
  while (foodsToAllocate > 0) {
    col = randIntInRange(1, SCREENMATRIX_WIDTH - 2);
    row = randIntInRange(0, SCREENMATRIX_HEIGHT);
    if (screenmatrix_getpixel(&screenmatrix, row, col) != FOOD_COLOR) {
      // create a food here
      screenmatrix_setpixel(&screenmatrix, row, col, FOOD_COLOR);
      foodsToAllocate--;
    }
  }  

  while (1) {
    if (isFirstRun) {
      screenmatrix_setpixel(&screenmatrix, 0, 0, player1.color);
      screenmatrix_setpixel(&screenmatrix, player2_x, player2_y, player2.color);
    }

    nunchuk_change();
    takeTurn(&player1);
    takeTurn(&player2);
    delay(EVENT_LOOP_TIME);
    isFirstRun = 0;
  }
}

void endGame(snake_t *loser) {\
  char msg[60];
  int textColor;

  if (loser == NULL) {
    // game completed fully, loser must be calculated
    char *winnerName = (player1.size > player2.size) ? "player1" : "player2";
    screenmatrix_color_t winnerColor = (player1.size > player2.size) ? player1.color : player2.color;
    textColor = screenmatrix_convertColor(winnerColor);
    sprintf(msg, "%s wins!", winnerName);
  } else {
    char *loserName = (loser == &player1) ? "player1" : "player2";
    screenmatrix_color_t loserColor = (loser == &player1) ? player1.color : player2.color;
    textColor = screenmatrix_convertColor(loserColor);
    sprintf(msg, "%s is a LOSER", loserName);
  }

  drawString(0, ST7735_height / 2, msg, textColor, BLACK);
  (loser == NULL) ? playHappyGameOverNoise() : playLoseNoise();
  
  while(1);
}

int randIntInRange(int lowest, int highest) {
  int r, i;
  int N = lowest,
      M = highest;

  return  M + rand() / (RAND_MAX / (N - M + 1) + 1);
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
#endif
