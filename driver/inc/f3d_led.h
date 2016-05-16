/**********************************************************
 * f3d_led.h
 *
 * Declarations for f3d_led.c
 *
 *   Author: Max McLennan (mpmclenn)
 *           Omar White (omawhite)
 *   Date Created: 02/04/2016
 *   Last Modified by: Max McLennan (mpmclenn)
 *   Date Last Modified: 02/11/2016
 *   Assignment: Lab 4
 *   Part of: CS-Spring-2016
 */
#ifndef F3D_LED_H
#define F3D_LED_H

// lowest index of an LED pin
static const int LED_LOWER_BOUND = 0;

// highest index of an LED pin
static const int LED_UPPER_BOUND = 7;

void f3d_led_init(void);

void f3d_led_on(int led);

void f3d_led_off(int led);

void f3d_led_all_on(void);

void f3d_led_all_off(void);

#endif
