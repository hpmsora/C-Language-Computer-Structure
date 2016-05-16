//Won Yong Ha
//Lab6
//Start: Feb 18 2016
//End: Feb 25

//--------------------------------------------------------

//main.c for lab6
#include <f3d_uart.h>
#include <stdio.h>
#include <f3d_gyro.h>
#include <f3d_led.h>
#include <f3d_user_btn.h>
#include <stm32f30x.h>

//delay function around .2 second
//Method from Lab5
void delay(void) {
  int i = 2000000;
  while (i-- > 0) {
    asm("nop"); /* This stops it optimising code out */
  }
}

int main(void){

  //initializing
  f3d_uart_init();
  f3d_gyro_init();
  f3d_led_init();
  f3d_user_btn_init();

  //printf
  //adding components for printf
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  //temp float array
  float val[3];

  //axis
  int axis = 0;
  int x = 0;

  //---------------------------------------------
  //getting characters for keyboard
  int c = getcharNoStop();
  char cur_c = 'x';
  //---------------------------------------------

  while(1) {
    //button_state = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0);
    //if statement

    //Getting data from gyro.h
    f3d_gyro_getdata(val);

    /*printf("a\n");
    float example[10] = {1.2, 1.3, 1.5, 2.4, 3.5, 2.1, 6.3, 4.3, 3.4, 4.2};
    printf("1\n");
    f3d_gyro_getdata(example);
    printf("2\n");
    printf("s%f\n"  ,example[0]);*/

    //Initializing LED
    f3d_led_all_off();

    //Start if statment
    // for getting characters from key board
    if(c = getcharNoStop())
      {
  	// x
  	if (c == 'x') {
  	  axis = 0;
  	  cur_c = 'x';
  	  //printing
  	  printf("Change to x-axis\n");
  	}
  	// y
  	else if (c == 'y') {
  	  axis = 1;
  	  cur_c = 'y';
  	  //printing
  	  printf("Change to y-axis\n");
  	}
  	// z
  	else if (c == 'z') {
  	  axis = 2;
  	  cur_c = 'z';
  	  //printing
  	  printf("Change to z-axis\n");
  	}
  	cur_c = c;

  	//delaying for Testing
  	//delay();
      }//------------------------------------

    //Start if statment
    if (user_btn_read()) {
      // 0 -> x
      if ((x % 3) == 0) {
  	axis = 0;
  	cur_c = 'x';
  	printf("Change to x-axis\n");
  	f3d_led_all_off();
  	//delaying for Testing
  	//delay();
      }
      // 1 -> y
      else if((x % 3) == 1) {
  	axis = 1;
  	cur_c = 'y';
  	printf("Change to y-axis\n");
  	f3d_led_all_off();
  	//delaying for Testing
  	//delay();
      }
      // else(2) -> z
      else if((x % 3) == 2) {
  	axis = 2;
  	cur_c = 'z';
  	printf("Change to z-axis\n");
  	f3d_led_all_off();
  	//delay();
      }
      //else for nothing
      else {}
      x++;
    }
    //f3d_led_on(2);

    //Starting if statment
    // for LED
    //--------------------Positive------------------
    if (val[axis] > 350) {
      f3d_led_on(5);
      f3d_led_on(6);
      f3d_led_on(7);
      f3d_led_on(0);
      f3d_led_on(1);
    }
    if (val[axis] > 300) {
      //printf("300");
      f3d_led_on(6);
      f3d_led_on(7);
      f3d_led_on(0);
      f3d_led_on(1);
    }
    else if (val[axis] > 200) {
      f3d_led_on(7);
      f3d_led_on(0);
      f3d_led_on(1);
    }
    else if (val[axis] > 100) {
      f3d_led_on(0);
      f3d_led_on(1);
    }
    else if (val[axis] > 5) {
      f3d_led_on(1);
    } //---------------negative--------------------------------
    else if (val[axis] < -350) {
      //printf("-300");
      f3d_led_on(5);
      f3d_led_on(4);
      f3d_led_on(3);
      f3d_led_on(2);
      f3d_led_on(1);
    }
    else if (val[axis] < -300) {
      //printf("-300");
      f3d_led_on(4);
      f3d_led_on(3);
      f3d_led_on(2);
      f3d_led_on(1);
    }
    else if (val[axis] < -200) {
      //printf("-200");
      f3d_led_on(3);
      f3d_led_on(2);
      f3d_led_on(1);
    }
    else if (val[axis] < -100) {
      //printf("-100");
      f3d_led_on(2);
      f3d_led_on(1);
    }
    else if (val[axis] < -5) {
      //printf("-5");
      f3d_led_on(1);
    }
    //else for nothing
    else {}

    //printing values
    printf("x: %f  y: %f  z: %f\n", val[0], val[1], val[2]);
    /*if(cur_c == 'x')
      printf("X : %f\n", val[0]);
    else if(cur_c == 'y')
      printf("Y : %f\n", val[1]);
    else
    printf("Z : %f\n", val[2]);*/

  }
}

void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
