/* main.c --- 
 * 
 * Filename: main.c
 * Description: CSCI-C 335 Lab 8
 * Author: Won Yong Ha & John Barnes McKivigan
 * Created: 10 March 2016
 * Last-Updated: 10 March 2016
 *     Update #: 29
 * 
 */

/* Commentary: 
 * None
 * 
 * 
 */

/* Change log:
 * None
 * 
 */
/* Code: */

#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_uart.h>
//#include <f3d_gyro.h>
#include <f3d_lcd_sd.h>
#include <stdio.h>
#include <f3d_i2c.h>
#include <f3d_accel.h>
#include <f3d_mag.h>
#include <f3d_user_btn.h>
#include <math.h>

//delay function around .2 second
//Method from Lab5
void delay_lab8(void) {
  int i = 1000000;
  while (i-- > 0) {
    asm("nop"); /* This stops it optimising code out */
  }
}

int main(void) { 

  double PI = 3.14159265358979323846;

  f3d_user_btn_init();
  f3d_uart_init();
  f3d_lcd_init();

  f3d_i2c1_init();
  delay(10);
  f3d_accel_init();
  delay(10);
  f3d_mag_init();
  delay(10);
  
  //Init stuff for printf
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  float ad[3];
  float mag[3];

  //Test the LCD
  f3d_lcd_fillScreen(BLACK);

  //Button checking value
  int i = 1;

  //Counting pixels
  int j = 0;

  while (1) {
    //read the axis
    f3d_accel_read(ad);
    f3d_mag_read(mag);

    //decalre variables for accel values
    double x;
    x = (double) ad[0];
    double y;
    y = (double) ad[1];
    double z;
    z = (double) ad[2];
    double pitch, roll, angz;

    //declare varialbes for mag values
    double mx;
    mx = (double) mag[0];
    double my;
    my = (double) mag[1];
    double mz;
    mz = (double) mag[2];

    //Calculating pitch, roll, angz
    pitch = atan(x / sqrt(y*y + z*z));
    roll = atan(y/ sqrt(x*x + z*z));

    //Calculating heading
    double horizx;
    horizx = (x * (cos(pitch)))+(z * sin(pitch));
    double horizy;
    horizy = (x *(sin(roll)*sin(pitch)))+(y*(cos(roll)))-(sin(roll)*cos(pitch));
    double heading;
    //heading=atan(horizy/horizx) * 180 / PI;
    double mx2 = mx * cos(pitch) + mz * sin(pitch);
    double  my2 = mx * sin(roll) * sin(pitch) + my * cos(roll) - mz * sin(roll) * cos(pitch);
    heading = atan(my2/mx2) * 180 / PI;
    //printf("%f\n", heading);

    //Test the tilt angle and heading
    //printf("%f %f \n",x, y);
    //printf("%f\n", heading);
    //printf("%f %f\n", pitch, roll);

    //LCD String value
    char heading_str[100];
    char tilt_angle_str[100];

    //Convert double to string
    sprintf(heading_str, "H: %f", heading);
    sprintf(tilt_angle_str, "TA: %f %f", pitch, roll);

    //print on LCD
    if (i == 1) {
      f3d_lcd_drawString(5, 0, heading_str, YELLOW, BLACK);
     //showing @ heading direction
     if(heading >= -45 && heading <= 45){
       f3d_lcd_drawChar(ST7735_width*.3, ST7735_height*.6, 'W', YELLOW, BLACK);
       f3d_lcd_drawChar(ST7735_width*.7, ST7735_height*.6, 'E', YELLOW, BLACK);
       f3d_lcd_drawChar(ST7735_width*.5, ST7735_height*.8, 'S', YELLOW, BLACK);
       f3d_lcd_drawChar(ST7735_width*.5, ST7735_height*.4, 'N', YELLOW, BLACK); 
     }
     else if (heading > -45 && heading < -135 || (heading >= 136 && heading <= 180)){
       f3d_lcd_drawChar(ST7735_width*.3, ST7735_height*.6, 'S', YELLOW, BLACK);
       f3d_lcd_drawChar(ST7735_width*.7, ST7735_height*.6, 'N', YELLOW, BLACK);
       f3d_lcd_drawChar(ST7735_width*.5, ST7735_height*.8, 'E', YELLOW, BLACK);
       f3d_lcd_drawChar(ST7735_width*.5, ST7735_height*.4, 'W', YELLOW, BLACK);
     }
     else if ((heading <= -135 && heading >= -180) || (heading >= 136 && heading <= 180)) { 
       f3d_lcd_drawChar(ST7735_width*.3, ST7735_height*.6, 'E', YELLOW, BLACK);
       f3d_lcd_drawChar(ST7735_width*.7, ST7735_height*.6, 'W', YELLOW, BLACK);
       f3d_lcd_drawChar(ST7735_width*.5, ST7735_height*.8, 'N', YELLOW, BLACK);
       f3d_lcd_drawChar(ST7735_width*.5, ST7735_height*.4, 'W', YELLOW, BLACK);
     }
     else{
       f3d_lcd_drawChar(ST7735_width*.3, ST7735_height*.6, 'N', YELLOW, BLACK);
       f3d_lcd_drawChar(ST7735_width*.7, ST7735_height*.6, 'S', YELLOW, BLACK);
       f3d_lcd_drawChar(ST7735_width*.5, ST7735_height*.8, 'W', YELLOW, BLACK);
       f3d_lcd_drawChar(ST7735_width*.5, ST7735_height*.4, 'E', YELLOW, BLACK);
     }
    }
    else {
      //Roll-----------------------------------------------

      //Calculate width
      int width_r = 0;
      width_r = roll * 2 / PI * ST7735_width / 2;
      //if ((width_p < (int) (ST7735_width * 0.01)) && (width_p > (int) (ST7735_width* -0.01))) {
      //width_p = (int) (ST7735_width* 0.01);
      //}
      if (width_r >= 0) {
	width_r = width_r + ST7735_width / 2;
	f3d_lcd_setAddrWindow((int)ST7735_width*.495,
			      (int)ST7735_height*.3,
			      width_r, 
			      (int)ST7735_height*.5,
			      MADCTLGRAPHICS);
	int count_r_r = (int)((width_r - ST7735_width*.495) * (ST7735_height*.8 - ST7735_height*.3));
	uint16_t color_list_r_r[count_r_r];
	for (j = 0; j < count_r_r; j++) {
	  color_list_r_r[j] = YELLOW;
	}
	f3d_lcd_pushColor(color_list_r_r, count_r_r);

	f3d_lcd_drawString(5, 0, tilt_angle_str, YELLOW, BLACK);
	//erasing
	f3d_lcd_setAddrWindow((int)ST7735_width*.505,
			      (int)ST7735_height*.3,
			      width_r, 
			      (int)ST7735_height*.5,
			      MADCTLGRAPHICS);
	count_r_r = (int)((width_r - ST7735_width*.505) * (ST7735_height*.8 - ST7735_height*.3));
	color_list_r_r[count_r_r];
	for (j = 0; j < count_r_r; j++) {
	  color_list_r_r[j] = BLACK;
	}
	f3d_lcd_pushColor(color_list_r_r, count_r_r);
      }

      else {
	width_r = width_r + ST7735_width / 2;
	f3d_lcd_setAddrWindow(width_r,
			      (int)ST7735_height*.3,
			      (int)ST7735_width*.505, 
			      (int)ST7735_height*.5,
			      MADCTLGRAPHICS);
	int count_r_l = (int)((ST7735_width*.505 - width_r) * (ST7735_height*.8 - ST7735_height*.3));
	uint16_t color_list_r_l[count_r_l];
	for (j = 0; j < count_r_l; j++) {
	  color_list_r_l[j] = YELLOW;
	}
	f3d_lcd_pushColor(color_list_r_l, count_r_l);

	f3d_lcd_drawString(5, 0, tilt_angle_str, YELLOW, BLACK);
	//erasing
	f3d_lcd_setAddrWindow(width_r,
			      (int)ST7735_height*.3,
			      (int)ST7735_width*.495, 
			      (int)ST7735_height*.5,
			      MADCTLGRAPHICS);
	count_r_l = (int)((ST7735_width*.495 - width_r) * (ST7735_height*.8 - ST7735_height*.3));
	color_list_r_l[count_r_l];
	for (j = 0; j < count_r_l; j++) {
	  color_list_r_l[j] = BLACK;
	}
	f3d_lcd_pushColor(color_list_r_l, count_r_l);
      }
      //Pitch----------------------------------------------
      int width_p = 0;
      width_p = pitch * 2 / PI * ST7735_width / 2;
      //if ((width_p < (int) (ST7735_width * 0.01)) && (width_p > (int) (ST7735_width* -0.01))) {
      //width_p = (int) (ST7735_width* 0.01);
      //}
      if (width_p >= 0) {
	width_p = width_p + ST7735_width / 2;
	f3d_lcd_setAddrWindow((int)ST7735_width*.495,
			      (int)ST7735_height*.7,
			      width_p, 
			      (int)ST7735_height*.9,
			      MADCTLGRAPHICS);
	int count_p_r = (int)((width_p - ST7735_width*.495) * (ST7735_height*.8 - ST7735_height*.3));
	uint16_t color_list_p_r[count_p_r];
	for (j = 0; j < count_p_r; j++) {
	  color_list_p_r[j] = YELLOW;
	}
	f3d_lcd_pushColor(color_list_p_r, count_p_r);

	f3d_lcd_drawString(5, 0, tilt_angle_str, YELLOW, BLACK);
	//erasing
	f3d_lcd_setAddrWindow((int)ST7735_width*.505,
			      (int)ST7735_height*.7,
			      width_p, 
			      (int)ST7735_height*.9,
			      MADCTLGRAPHICS);
	count_p_r = (int)((width_p - ST7735_width*.505) * (ST7735_height*.8 - ST7735_height*.3));
	color_list_p_r[count_p_r];
	for (j = 0; j < count_p_r; j++) {
	  color_list_p_r[j] = BLACK;
	}
	f3d_lcd_pushColor(color_list_p_r, count_p_r);
      }

      else {
	width_p = width_p + ST7735_width / 2;
	f3d_lcd_setAddrWindow(width_p,
			      (int)ST7735_height*.7,
			      (int)ST7735_width*.505, 
			      (int)ST7735_height*.9,
			      MADCTLGRAPHICS);
	int count_p_l = (int)((ST7735_width*.505 - width_p) * (ST7735_height*.8 - ST7735_height*.3));
	uint16_t color_list_p_l[count_p_l];
	for (j = 0; j < count_p_l; j++) {
	  color_list_p_l[j] = YELLOW;
	}
	f3d_lcd_pushColor(color_list_p_l, count_p_l);

	f3d_lcd_drawString(5, 0, tilt_angle_str, YELLOW, BLACK);
	//erasing
	f3d_lcd_setAddrWindow(width_p,
			      (int)ST7735_height*.7,
			      (int)ST7735_width*.495, 
			      (int)ST7735_height*.9,
			      MADCTLGRAPHICS);
	count_p_l = (int)((ST7735_width*.495 - width_p) * (ST7735_height*.8 - ST7735_height*.3));
	color_list_p_l[count_p_l];
	for (j = 0; j < count_p_l; j++) {
	  color_list_p_l[j] = BLACK;
	}
	f3d_lcd_pushColor(color_list_p_l, count_p_l);
      }
    }
      
      //switching heading and tilt angle
    if (user_btn_read()) {
      f3d_lcd_fillScreen(BLACK);
      i = i * -1;
      //delay_lab8();
    }
  }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);

}
#endif


/* main.c ends here */
