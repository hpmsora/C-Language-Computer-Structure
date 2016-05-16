/**********************************************************
 * f3d_uart.c
 *
 * Contains the initialization basic i/o functions for UART
 *
 * Author: Max McLennan (mpmclenn)
 *         Broadmore Tung (btung)
 * Date Created: 2/11/16
 * Last Modified by: Max McLennan
 * Date Last Modified: 2/11/16
 * Assignment: Lab 5
 * Part of: CS-Spring-2016
 */
#include <stm32f30x.h>
#include <f3d_uart.h>
#include <string.h>
//the initialization function to call
void f3d_uart_init(void) {
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

  // TX Pin init
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  // RX Pin init
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  GPIO_PinAFConfig(GPIOC, 4, GPIO_AF_7);
  GPIO_PinAFConfig(GPIOC, 5, GPIO_AF_7);

  // Init UART
  USART_InitTypeDef USART_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
  
  USART_StructInit(&USART_InitStructure);
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART1, &USART_InitStructure);
  USART_Cmd(USART1, ENABLE);

}
//sends a character
int putchar(int c) {
  while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == (uint16_t) RESET);
  USART_SendData(USART1, c);
  return 0;
} 
//gets a character
int getchar(void) {
  while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == (uint16_t) RESET);
  return USART_ReceiveData(USART1);
}
//sends a string
void putstring(char *s) {
  int i;
  for (i = 0; i < strlen(s); i++) {
    putchar(s[i]);
  }
}



/* f3d_uart.c ends here */
