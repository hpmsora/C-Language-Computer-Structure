/* main.c --- 
 * 
 * Filename: main.c
 * Description: 
 * Author: 
 * Maintainer: 
 * Created: Thu Jan 10 11:23:43 2013
/* Code: */

#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_led.h>     // Pull in include file for the local drivers
#include <f3d_uart.h>
#include <f3d_gyro.h>
#include <f3d_lcd_sd.h>
#include <stdio.h>

#define TIMER 20000

int main(void) { 
  // If you have your inits set up, this should turn your LCD screen red
  f3d_lcd_init();
  f3d_uart_init();
  f3d_gyro_init();

  //Init stuff for printf
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  f3d_lcd_fillScreen2(WHITE);

  while(1){
    //init a with some random floats
    float a[3] = {1.23,1.24,1.25};
    
    //Get Data
    f3d_gyro_getdata(a);
    
    //Generate axis values
    char x[100];
    char y[100];
    char z[100];
    sprintf(x, "X: %f", a[0]);
    sprintf(y, "Y: %f", a[1]);
    sprintf(z, "Z: %f", a[2]);

    f3d_lcd_drawString(10,5,"Axis Values",BLACK,WHITE);
    f3d_lcd_drawString(10,ST7735_height*.3,x, BLACK, WHITE);
    f3d_lcd_drawString(10,ST7735_height*.6,y, BLACK, WHITE);
    f3d_lcd_drawString(10,ST7735_height*.9,z, BLACK, WHITE);

    int axisMax = 300;

    //x
    int xBarHeightMin = ST7735_height * .10;
    int xBarHeightMax = ST7735_height * .25;
    if(a[0] > 0){
      int count = ST7735_width * .50 + a[0]/axisMax*ST7735_width * .50;
      while(ST7735_width * .50 <= count){
	int count2 = xBarHeightMin;
	while(count2 < xBarHeightMax){
	  f3d_lcd_drawPixel(count, count2, BLUE);
	  count2++;
	}
	count--;
      }
    } else {
      int count = ST7735_width * .50 + a[0]/axisMax*ST7735_width * .50;
      while(ST7735_width * .50 >= count){
	int count2 = xBarHeightMin;
	while(count2 < xBarHeightMax){
	  f3d_lcd_drawPixel(count, count2, BLUE);
	  count2++;
	}
	count++;
      }
    }

    //y
    int yBarHeightMin = ST7735_height * .40;
    int yBarHeightMax = ST7735_height * .55;
    if(a[1] > 0){
      int count = ST7735_width * .50 + a[1]/axisMax*ST7735_width * .50;
      while(ST7735_width * .50 <= count){
	int count2 = yBarHeightMin;
	while(count2 < yBarHeightMax){
	  f3d_lcd_drawPixel(count, count2, RED);
	  count2++;
	}
	count--;
      }
    } else {
      int count = ST7735_width * .50 + a[1]/axisMax*ST7735_width * .50;
      while(ST7735_width * .50 >= count){
	int count2 = yBarHeightMin;
	while(count2 < yBarHeightMax){
	  f3d_lcd_drawPixel(count, count2, RED);
	  count2++;
	}
	count++;
      }
    }

    //z
    int zBarHeightMin = ST7735_height * .70;
    int zBarHeightMax = ST7735_height * .85;
    if(a[2] > 0){
      int count = ST7735_width * .50 + a[2]/axisMax*ST7735_width * .50;
      while(ST7735_width * .50 <= count){
	int count2 = zBarHeightMin;
	while(count2 < zBarHeightMax){
	  f3d_lcd_drawPixel(count, count2, GREEN);
	  count2++;
	}
	count--;
      }
    } else {
      int count = ST7735_width * .50 + a[2]/axisMax*ST7735_width * .50;
      while(ST7735_width * .50 >= count){
	int count2 = zBarHeightMin;
	while(count2 < zBarHeightMax){
	  f3d_lcd_drawPixel(count, count2, GREEN);
	  count2++;
	}
	count++;
      }
    }
    

    //Reset Axis
    int count;
    //Pos X
    count = ST7735_width * .50 + a[0]/axisMax*ST7735_width * .50;
    while(ST7735_width * .50 < count){
      int count2 = xBarHeightMin;
      while(count2 < xBarHeightMax){
	f3d_lcd_drawPixel(count, count2, WHITE);
	count2++;
      }
      count--;
    }
    //Neg X
    count = ST7735_width * .50 + a[0]/axisMax*ST7735_width * .50;
    while(ST7735_width * .50 > count){
      int count2 = xBarHeightMin;
      while(count2 < xBarHeightMax){
	f3d_lcd_drawPixel(count, count2, WHITE);
	count2++;
      }
      count++;
    }
    //Pos Y
    count = ST7735_width * .50 + a[1]/axisMax*ST7735_width * .50;
    while(ST7735_width * .50 < count){
      int count2 = yBarHeightMin;
      while(count2 < yBarHeightMax){
	f3d_lcd_drawPixel(count, count2, WHITE);
	count2++;
      }
      count--;
    }
    //Neg Y
    count = ST7735_width * .50 + a[1]/axisMax*ST7735_width * .50;
    while(ST7735_width * .50 > count){
      int count2 = yBarHeightMin;
      while(count2 < yBarHeightMax){
	f3d_lcd_drawPixel(count, count2, WHITE);
	count2++;
      }
      count++;
    }
    //Pos Z
    count = ST7735_width * .50 + a[2]/axisMax*ST7735_width * .50;
    while(ST7735_width * .50 < count){
      int count2 = zBarHeightMin;
      while(count2 < zBarHeightMax){
	f3d_lcd_drawPixel(count, count2, WHITE);
	count2++;
      }
      count--;
    }
    //Neg Z
    count = ST7735_width * .50 + a[2]/axisMax*ST7735_width * .50;
    while(ST7735_width * .50 > count){
      int count2 = zBarHeightMin;
      while(count2 < zBarHeightMax){
	f3d_lcd_drawPixel(count, count2, WHITE);
	count2++;
      }
      count++;
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
