/**********************************************************
 * f3d_user_btn.c
 *
 * Contains the init and read functions for the User Button
 *
 *   Author: Max McLennan (mpmclenn)
 *           Omar White (omawhite)
 *   Date Created: 02/04/2016
 *   Last Modified by: Max McLennan (mpmclenn)
 *   Date Last Modified: 02/11/2016
 *   Assignment: Lab 4
 *   Part of: CS-Spring-2016
 */
#include <stm32f30x.h>
#include <stm32f30x_gpio.h>
#include <stm32f30x_rcc.h>


/*Initialization of the UserButton*/
void f3d_user_btn_init(void){
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_StructInit(&GPIO_InitStructure);

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/*reads the User Button*/
int user_btn_read(void){
  return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
}
