/* main.c ---
*
* Filename: main.c
* Description: Application to measure pitch and roll. Also a poor compass.
* Author: Max McLennan (mpmclenn)
*         Won Yong Ha  (woha)
* Maintainer:
* Created: Thu Jan 10 11:23:43 2013
/* Code: */

#include <stm32f30x.h> // Pull in include files for F30x standard drivers
#include <f3d_uart.h>
#include <f3d_user_btn.h>
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_accel.h>
#include <f3d_mag.h>
#include <f3d_gyro.h>
#include <f3d_nunchuk.h>
#include <stdio.h>
#include <math.h>

#define TIMER 20000
#define COMPASS_MODE 0
#define PITCHROLL_MODE 1
#define GYRO_MODE 2
#define NUNCHUK_MODE 3

//function prototypes
float rad_to_deg(float radians);
float deg_to_rad(float degrees);
void drawStraightupLine(int color);
void drawRect(int, int, int, int, int);
void drawGyroRect(int x, int y, int color);

//static variable for center of screen
static int centerX;
static int centerY;

// gyro constants
const int RECT_WIDTH = 20;
const int RECT_LENGTH = 20;
int START_X;
int START_Y;
int GYRO_UPPER_BOUND;
int X_MARGIN;
int Y_MARGIN;

int main(void) {
  //various initializations
  f3d_uart_init();
  f3d_i2c1_init();
  delay(10);
  f3d_accel_init();
  delay(10);
  f3d_mag_init();
  delay(10);
  f3d_gyro_init();
  delay(10);
  f3d_nunchuk_init();
  delay(10);
  f3d_user_btn_init();
  f3d_lcd_init();

  //reset pixels by filling screen RED
  f3d_lcd_fillScreen(RED);

  //set buffers
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  // initialize gyro constants
  START_X = (ST7735_width / 2) - (RECT_WIDTH / 2);
  START_Y = (ST7735_height / 2) - (RECT_LENGTH / 2);
  GYRO_UPPER_BOUND = 120;
  X_MARGIN = (ST7735_width - RECT_WIDTH) / 2;
  Y_MARGIN = (ST7735_height - RECT_LENGTH) / 2;

  //set centerX and centerY by using global varaibles from library
  centerX = ST7735_width / 2;
  centerY = ST7735_height / 2;

  // constants for the PITCHROLL_MODE
  const int barGraphWidth = 40;
  const int rollStartY = 30;
  const int pitchStartY = 120;

  //variables for keeping track of data from previous point
  int prevRollX = 0, prevRollY = 0;
  int prevPitchX = 0, prevPitchY = 0;
  int prevGyroRow = START_X, prevGyroCol = START_Y;

  //set float arrays for accel and mag data
  float accel_buffer[3];
  float mag_buffer[3];
  float gyro_buffer[3];
  nunchuk_t nunchuk_data;
  nunchuk_t *nunchuk_ptr = &nunchuk_data;

  //start board in compass mode
  int app_mode = COMPASS_MODE;
  char *app_mode_title;
  
  while(1) {
    //retrieve accel and mag data and insert into their buffers
    f3d_accel_read(accel_buffer);
    f3d_mag_read(mag_buffer);
    f3d_gyro_getdata(gyro_buffer);
    f3d_nunchuk_read(nunchuk_ptr);
    delay(10);    

    float Ax1 = accel_buffer[0];
    float Ay1 = accel_buffer[1];
    float Az1 = accel_buffer[2];
    
    //calcuation of sum of squares
    float A_sum_squares = sqrt(Ax1 * Ax1 + Ay1 * Ay1 + Az1 * Az1);
    
    //calculate pitch using accel data and atan2
    float pitch = atan2(Ax1, sqrt(Ay1 * Ay1 + Az1 * Az1));
    
    //calculate roll in a similar manner
    float roll = atan2(Ay1, sqrt(Ax1 * Ax1 + Az1 * Az1));
    
    //feed mag buffers mag x, y, and z
    float Mx = mag_buffer[0];
    float My = mag_buffer[1];
    float Mz = mag_buffer[2];
    
    //calculate heading in degrees 
    float Xh = Mx * cos(pitch) + Mz * sin(pitch);
    float Yh = Mx * sin(roll) * sin(pitch) + My * cos(roll) - Mz * sin(roll) * cos(pitch);
    float headingDegrees = rad_to_deg(atan2(Yh, Xh));

    // convert heading degrees to a circular system
    float newHeadingDegrees = 0.0;
    if (headingDegrees > 90.0) {
      // quad I
      newHeadingDegrees = fabsf(headingDegrees - 180.0);
    } else if (headingDegrees > 0.0) {
      // quad II
      newHeadingDegrees = 180.0 - headingDegrees;
    } else {
      // quads III and IV
      newHeadingDegrees = 180.0 + fabsf(headingDegrees);
    }

    int prev_app_mode = app_mode;
    // change mode based on nunchuk
    const unsigned char joystick_epsilon = 50;
    int c_pressed = nunchuk_ptr->z;
    int z_pressed = nunchuk_ptr->c;
    if (c_pressed != z_pressed) {
      // decide based on buttons
      if (c_pressed) {
	// go right
	app_mode = (app_mode + 1) % 4;
      } else {
	// go left
	app_mode = (app_mode + 3) % 4;
      }
    } else {
      // decide based on joystick
      const int joystick_x_center = 141;
      int joystick_delta = nunchuk_ptr->jx - joystick_x_center;
      if (abs(joystick_delta) >= joystick_epsilon) {
	// only switch app mode if joystick change is significant
	if (joystick_delta < 0) {
	  // go right
	  app_mode = (app_mode + 1) % 4;
	} else {
	  // go left
	  app_mode = (app_mode + 3) % 4;
	}
      }
    }
    if (app_mode != prev_app_mode) {
      f3d_lcd_fillScreen(RED);
    }

    //define variables for row and columns of type int
    int row, col;

    switch(app_mode) {
    case COMPASS_MODE: // compass mode
      f3d_lcd_fillScreen(RED);
      f3d_lcd_drawString(0, 0, "Compass", WHITE, RED);

      //draw static white line point upwards on LCD 
      drawStraightupLine(WHITE);

      const float radius = 30.0;
      float theta = deg_to_rad(newHeadingDegrees) - (M_PI / 2.0);
      //calculat x and y offset
      float xOffset = radius * cos(theta);
      float yOffset = radius * sin(theta);
      
      //set second point
      int x2 = centerX + ((int) xOffset);
      int y2 = centerY + ((int) yOffset);

      //draw point on the screen at location x2 and y2
      f3d_lcd_drawPixel(x2, y2, CYAN);
      break;
    case PITCHROLL_MODE: // tilt mode
      app_mode_title = "Board";

    pitchroll_label:
      // erase old bars
      drawRect(0, rollStartY, prevRollX, prevRollY, RED);
      drawRect(0, pitchStartY, prevPitchX, prevPitchY, RED);
      //draw the word "Roll" on upper left of LCD
      f3d_lcd_drawString(0, 0, "Roll", CYAN, RED);

      // title the application
      f3d_lcd_drawString((int) ST7735_width * 0.65, 0, app_mode_title, CYAN, RED);

      //set color for redrawing of the bars
      int rollColor = (roll < 0.0) ? MAGENTA : CYAN;
      //calculate perceentage using fabsf (absolute value for float)
      float rollPercentage = fabsf(roll) / M_PI;
      //calculate rollX and rollY for drawing the roll bar
      int rollX = rollPercentage * ST7735_width;
      int rollY = rollStartY + barGraphWidth;
      drawRect(0, rollStartY, rollX, rollY, rollColor);

      //draw the word pitch 90 pixels below Roll
      f3d_lcd_drawString(0, 90, "Pitch", CYAN, RED);
      //set color for redrawing
      int pitchColor = (pitch < 0.0) ? MAGENTA : CYAN;
      //calculate pitchPercentage using fabsf(absolute for float)
      float pitchPercentage = fabsf(pitch) / M_PI;
      //calculate pitchX and pitch Y for drawing Pitch rectangle
      int pitchX = pitchPercentage * ST7735_width;
      int pitchY = pitchStartY + barGraphWidth;
      drawRect(0, pitchStartY, pitchX, pitchY, pitchColor);

      //keep track of RollX and PitchX for loop
      prevRollX = rollX; prevRollY = rollY;
      prevPitchX = pitchX; prevPitchY = pitchY;
      break;
    case GYRO_MODE: // gyro mode
      f3d_lcd_fillScreen(RED);
      float gyroDataAvg = (gyro_buffer[0] + gyro_buffer[1] + gyro_buffer[2]) / 3.0f;
      float percentageOffset = gyroDataAvg / GYRO_UPPER_BOUND;
      int xPixelsFromCenter = (percentageOffset * X_MARGIN) / 1;
      int yPixelsFromCenter = (percentageOffset * Y_MARGIN) / 1;

      row = START_X + xPixelsFromCenter;
      col = START_Y + yPixelsFromCenter;

      prevGyroRow = row;
      prevGyroCol = col;
      drawGyroRect(col, row, WHITE);
      break;
    case NUNCHUK_MODE:
      app_mode_title = "Nunchuk";

      const int nunchuk_tilt_upperbound = 1023;
      const int nunchuk_tilt_midpoint = nunchuk_tilt_upperbound / 2;

      int ax = nunchuk_ptr->ax - nunchuk_tilt_midpoint;
      int ay = nunchuk_ptr->ay - nunchuk_tilt_midpoint;
      int az = nunchuk_ptr->az;

      // calculate pitch and roll of nunchuk
      pitch = atan2(ay, sqrt(pow(ay, 2) + pow(az, 2)));
      roll = atan2(ax, sqrt(pow(ax, 2) + pow(az, 2)));

      // double pitch and roll values to exaggerate their size on bar graph
      pitch *= 2;
      roll *= 2;

      // all the rest is the same as board accelerometer application, so...
      goto pitchroll_label;

      break;
    default:
      break;
    }
  }
}

void drawStraightupLine(int color) {
  // draw the compass straight line
  int row;
  for (row = 0; row < centerY; row++) {
    f3d_lcd_drawPixel(centerX, row, color);
  }
}

// draw a fixed-sized rectangle starting at origin x, y
void drawRect(int x1, int y1, int x2, int y2, int color) {
  int colBound = y2;
  int rowBound = x2;
  
  int r, c;
  for (r = x1; r < rowBound; r++) {
    for (c = y1; c < colBound; c++) {
      f3d_lcd_drawPixel(r, c, color);
    }
  }
}

// draw a fixed-sized rectangle starting at origin x, y for the gyroscope app
void drawGyroRect(int x, int y, int color) {
    int rowBound = y + RECT_LENGTH;
    int colBound = x + RECT_WIDTH;

    int r, c;
    for (r = y; r < rowBound; r++) {
        for (c = x; c < colBound; c++) {
	  f3d_lcd_drawPixel(r, c, color);
	}
    }
}

//equation to convert radians to degres
float rad_to_deg(float radians) {
  return radians * (180.0f / M_PI);
}

//equation to convert degrees to radians
float deg_to_rad(float degrees) {
  return degrees * (M_PI / 180.0f);
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
#endif

/* main.c ends here */

