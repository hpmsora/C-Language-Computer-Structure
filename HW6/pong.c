/* pong.c --- 
 * 
 * Filename: pong.c
 * Description: 
 * Author: Won Yong Ha
 * Maintainer: 
 * Created: 10 April 2016
 * Last-Updated: 10 April 2016
 *           By: 
 *     Update #: 3
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Commentary: 
 * 
 * 
 * 
 */

/* Change log:
 * 
 * 
 */

/* Copyright (c) 2004-2007 The Trustees of Indiana University and 
 * Indiana University Research and Technology Corporation.  
 * 
 * All rights reserved. 
 * 
 * Additional copyrights may follow 
 */

/* Code: */

#include "c335sim.h"
#include "rect.h"
#include "screen.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL/SDL.h>
#include <string.h>

#define PADDLE_MOVE_INCREMENT 3
#define PADDLE_HEIGHT 25
#define PADDLE_WIDTH 25
#define PADDLE_THICKNESS 3
#define BALL_DIM 3
#define EVENT_LOOP_TIME 20



rect_t left_paddle;
rect_t right_paddle;
rect_t ball;

int ball_vx = 1;
int ball_vy = 2;

int mode = 0;
int count = 0;

int N_ing = 1;
int file_size = 0;

float gyroText[999][3];

/*The event loop that handles the key input*/
void event_loop(void) {
  static int paddle_left_move = 0; 
  static int paddle_right_move = 0;
  SDL_Event event;
  SDL_PollEvent(&event);
  switch(event.type) {
  case SDL_KEYUP:
    switch (event.key.keysym.sym) {
    case SDLK_UP:
      paddle_right_move = 0;
      break;
    case SDLK_DOWN:
      paddle_right_move = 0;
      break;
    case SDLK_a:
      paddle_left_move = 0;
      break;
    case SDLK_z:
      paddle_left_move = 0;
      break;
    case SDLK_n:
      break;
    default:
      break;
    }
    break;
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {
    case SDLK_UP:
      paddle_right_move = -PADDLE_MOVE_INCREMENT;
      break;
    case SDLK_DOWN:
      paddle_right_move = PADDLE_MOVE_INCREMENT;
      break;
    case SDLK_a:
      paddle_left_move = -PADDLE_MOVE_INCREMENT; 
      break;
    case SDLK_z:
      paddle_left_move = PADDLE_MOVE_INCREMENT; 
      break;
    case SDLK_q:
      printf("Q PRESSED - Exit Program\n");
      exit(0);
      break;
    case SDLK_n:
      N_ing++;
      break;
    default:
      break;
    }
    break;
  }

  //PORTRAIT
  if (mode) {
    if (paddle_left_move) {
      moveRect(&left_paddle, paddle_left_move, 0, BLACK);
    }

    if (paddle_right_move) {
      moveRect(&right_paddle, paddle_right_move, 0, BLACK);
    }
  
  } else {
  
    if (paddle_left_move) {
      moveRect(&left_paddle, 0, paddle_left_move, BLACK);
    }
    if (paddle_right_move) {
      moveRect(&right_paddle, 0, paddle_right_move, BLACK);
    }
  }
  
}

/*Where the collisions are handled*/
void pong_game(void) {
  int collision;

  drawString(40,60,"hit q to quit",WHITE,BLACK);
  redrawRect(&left_paddle);
  redrawRect(&right_paddle);
  event_loop();
  collision = moveRect(&ball, ball_vx, ball_vy, BLACK);

  switch (collision) {
  case COLLISION_TOP:
    ball_vy = -ball_vy;
    break;
  case COLLISION_BOTTOM:
    ball_vy = -ball_vy;
    break;
  case COLLISION_LEFT:
    ball_vx = -ball_vx;
    break;
  case COLLISION_RIGHT:
    ball_vx = -ball_vx;
    break;
  }
}

/*Where the pong_game() is called the rectangels are initialized. */
int c335_main( int argc, char *argv[] ) {

  if (argc > 1){

    char fn[10] = "gyro.txt";
    FILE * file = fopen(fn, "r");
    char line[256];
    int i = 0;
    while(fgets(line, sizeof(line), file)) {
      sscanf(line, "%f,%f,%f", &gyroText[i][0], &gyroText[i][1], &gyroText[i][2]);
      i++;
    }

    printf("%f\n", gyroText[0][0]);
    file_size = i;
    
    fclose(file);

    mode = !strcasecmp(argv[1], "PORTRAIT");

    if (mode) {
      //portrait
      fillScreen(BLACK);
      //left bar
      initRect(&left_paddle,ST7735_width/2-(PADDLE_WIDTH/2),0,PADDLE_WIDTH,PADDLE_THICKNESS,WHITE);
      //right bar
      initRect(&right_paddle,ST7735_width/2-(PADDLE_WIDTH/2),ST7735_height-(PADDLE_THICKNESS),PADDLE_WIDTH,PADDLE_THICKNESS,WHITE);
      //ball
      initRect(&ball,ST7735_width/2-(BALL_DIM/2),ST7735_height/2-(BALL_DIM/2),BALL_DIM,BALL_DIM,WHITE);

      ///////////loop
      while (1) {
	pong_game();
	Delay(EVENT_LOOP_TIME);

	printf("%f\n", gyroText[N_ing][0]);
	printf("%f\n", gyroText[N_ing][1]);
	printf("%f\n", gyroText[N_ing][2]);
      }
    } else {
      //landscape
      fillScreen(BLACK);
      //left bar
      initRect(&left_paddle,0,ST7735_height/2-(PADDLE_HEIGHT/2),PADDLE_THICKNESS,PADDLE_HEIGHT,WHITE);
      //right bar
      initRect(&right_paddle,ST7735_width-PADDLE_THICKNESS,ST7735_height/2-(PADDLE_HEIGHT/2),PADDLE_THICKNESS,PADDLE_HEIGHT,WHITE);
      //ball
      initRect(&ball,ST7735_width/2-(BALL_DIM/2),ST7735_height/2-(BALL_DIM/2),BALL_DIM,BALL_DIM,WHITE);
      
      ///////////loop
      while (1) {
	pong_game();
	Delay(EVENT_LOOP_TIME);

	pong_game();
	Delay(EVENT_LOOP_TIME);
	
	printf("%f\n", gyroText[N_ing][0]);
	printf("%f\n", gyroText[N_ing][1]);
	printf("%f\n", gyroText[N_ing][2]);
      }
    }  
  } else {
    printf("Please provide a command line argument \"PORTRAIT\" or \"LANDSCAPE\"\n");
  }   
} 

/* pong.c ends here */
