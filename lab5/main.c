/* main.c --- 
 * 
 * Filename: main.c
 * Description: 
 * Author: 
 * Maintainer: 
 * Created: Thu Jan 10 11:23:43 2013
 * Last-Updated: 
 *           By: 
 *     Update #: 0
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
/* Code: */

#include <f3d_uart.h>
#include <stdio.h>
#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_led.h>     // Pull in include file for the local drivers

// Simple looping delay function
void delay(void) {
  int i = 2000000;
  while (i-- > 0) {
    asm("nop"); /* This stops it optimising code out */
  }
}

int main(void) {
  f3d_uart_init();

  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  
  while(1) {
    
    printf("Hello World");
    //putchar('a');
    //putchar(getchar());
    int chs = 0;
    int wds = 0;
    int lns = 0;
    
    //Declare one Int variable
    //count how many time in 'while' loop
    int count = 0;
    
    //Declare one Int variable
    //for saving the first variable
    int c;
    
    //Declare one Int variable
    //for saving previous variable
    int pre_c;
    while (c = getchar()) {
      // printf('a');
      //Last break point
      if (c == 0x1b) {
    	chs++;
    	if (count == 0)
    	  break;
    	else {
    	  //printf("%c\n", pre_c);
    	  if (pre_c == ' ' || pre_c == '\t' || pre_c == '\r' || pre_c == '\n' || pre_c == '\f' || pre_c == '\v')
    	    break;
    	  else {
    	    wds++;
    	    break;
    	  }
    	}
      }
      
    //prefixing the variables
      if(count == 0) {
    	lns = 1;
      pre_c = c;
      }
      
      //if statement
      // when it is nextline
      if (c == '\n') {
    	wds++;
    	lns++;
      }
      
      //counting every single character
      chs++;
      
      //if statment
      // when it is whitespaces
      if (c == ' ' || c == '\t' || c == '\r' || c == '\f' || c == '\v')
    	wds++;
      
      //checking overlapped
      if (pre_c == c && count != 0) {
	
    	//testing printing
    	//printf ("--------");
	
    	if (c == ' ' || c == '\t' || c == 'r' || c == '\f' || c == '\v')
    	  wds--;
    	if (c == '\n') {
    	  wds--;
    	}
      }
      
      //counting every single steps
      count++;
      
      //testing printing
      // printf("%c\n", c);
      //printf("chs: %d\n", chs);
      //printf("wds: %d\n", wds);
      //printf("lns: %d\n", lns);
      
      //changing pre_c varialbe
      pre_c = c;
    }
    
    //printing thre result
    printf(" %d %d %d\n", lns, wds, chs);
    return 0;
    
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
