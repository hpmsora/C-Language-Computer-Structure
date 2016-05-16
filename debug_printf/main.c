/************************** 
 *main.c 
 * debug_printf main.c

 * partners: Ryder McMinn, Wonyong Ha 
****************************/ 


#include <f3d_uart.h>
#include <stdio.h>
#include <f3d_gyro.h>
#include <f3d_led.h>
#include <f3d_user_btn.h>

// Simple looping delay function
void delay(void) {
  int i = 2000000;
  while (i-- > 0) {
    asm("nop"); /* This stops it optimising code out */
  }
}


int main(void){
  f3d_led_init();
  f3d_uart_init();
  f3d_user_btn_init();
    
  //Init stuff for printf
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  int x = 0;
  int btnState = 0;

  while(1){
    
    //Button Polling (Change axis with button)
    if (user_btn_read()) {
        if (btnState == 0) {
	  btnState = 1;
	  printf("Switching to state 1");
        } else {
          btnState = 0;
	  printf("Switching to state 0");
        }
    }

    if(btnState == 0){
      //LED's without printf
      while(x < 8){
	f3d_led_on(x);
	delay();
	f3d_led_off(x);
	x++;
      }
      x = 0;
    } else if(btnState == 1){
      //LED's with printf
      while(x < 8){
	f3d_led_on(x);
	delay();
	printf("Prepping LED %d\n",x);
	printf("Activating LED %d\n", x);
	printf("Turning on LED %d\n", x);
	printf("Prepping to turn off %d\n", x);
	printf("Thinking about turning off %d\n", x);
	f3d_led_off(x);
	x++;
      }
      x = 0;
    }
  }
}

void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
