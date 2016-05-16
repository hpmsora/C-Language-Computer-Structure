/* f3d_systick.c 
 *
 * Tinkers with LEDs when interrupts happen
 * Also manages the UART queue
 * 
 * Filename: f3d_systick.c
 * Description: 
 * Author: Bryce Himebaugh
 * Maintainer: 
 * Created: Thu Nov 14 07:57:37 2013
 * Last-Updated: 4/5/2016
 *           By: Max McLennan (mpmclenn)
 *               Won Yong Ha  (woha)
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

/* Copyright (c) 2004-2007 The Trustees of Indiana University and 
 * Indiana University Research and Technology Corporation.  
 * 
 * All rights reserved. 
 * 
 * Additional copyrights may follow 
 */

/* Code: */

#include <f3d_systick.h>
#include <f3d_led.h> 
#include <f3d_user_btn.h>
#include <f3d_uart.h>
#include <queue.h>

volatile int systick_flag = 0;
static int current_led = 0;

void f3d_systick_init(void) {
  SysTick_Config(SYSTICK_LED_SPEED_FAST);
}

void SysTick_Handler(void) {
  if (user_btn_read()) {
    // user button is pressed down
    SysTick_Config(SYSTICK_LED_SPEED_SLOW);
  } else {
    SysTick_Config(SYSTICK_LED_SPEED_FAST);
  }
  f3d_led_off(current_led);
  current_led = (current_led + 1) % 9;
  f3d_led_on(current_led);

  if (!queue_empty(&txbuf)) {
    flush_uart();
  }
}

/* f3d_systick.c ends here */
