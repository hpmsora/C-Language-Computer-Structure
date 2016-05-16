/* main.c --- 
 * 
 * Filename: main.c
 * Description: Main Method
 * Author: Won Yong Ha
 * Maintainer: 
 * Created: 18 March 2016
 * Last-Updated: 
 *           By: Won Yong Ha
 *     Update #: 1
 * Keywords: Main Method
 * 
 */

/* Commentary: 
 *  None
 * 
 * 
 */

/* Change log:
 *  None
 * 
 */

/* Copyright (c) 2015 The Trustees of Indiana University and 
 * Indiana University Research and Technology Corporation.  
 * 
 * All rights reserved. 
 * 
 * Additional copyrights may follow 
 */

/* Code: */
#include <stdio.h> 
#include <stddef.h> 
#include <stdint.h>
#include <string.h> 
#include "testvector.h"
#include "machine.h"
#include "flags.h"

uint32_t reg[16];
uint32_t psr;

int main(int argc, char *argv[]) {
  // Argument to test_instructions can be ALL to run all of tests or a specific
  // instruction can be tested by passing the name. 
  // ADCS, ADDS, SUBS, ANDS, BICS, LSLS, ASRS
  // To run the instruction tests for all of the instructions, pass ALL

  char* x = argv[1];
  char* y = argv[2];
  char mx[18];
  char my[18];
  char mmx[16];
  char mmy[16];
  strcpy(mx, x);
  strcpy(my, y);
  int i = 2;
  for (i; i < 18; i++) {
    mmx[i-2] = mx[i];
    mmy[i-2] = my[i];
  }
  int32_t v1 = 0;
  int32_t v2 = 0;
  int32_t v3 = 0;
  int32_t v4 = 0;
  char v1arr[8];
  char v2arr[8];
  char v3arr[8];
  char v4arr[8];
  i = 0;
  for (i; i < 8; i++) {
    v1arr[i] = mmx[i];
    v2arr[i] = mmx[i + 8];
    v3arr[i] = mmy[i];
    v4arr[i] = mmy[i + 8];
  }
  v1 = strtol(v1arr, NULL, 16);
  v2 = strtol(v2arr, NULL, 16);
  v3 = strtol(v3arr, NULL, 16);
  v4 = strtol(v4arr, NULL, 16);
  reg[0] = v1;
  reg[1] = v2;
  reg[2] = v3;
  reg[3] = v4;
  adds(reg[1], reg[3]);
  adcs(reg[0], reg[2]);
  (reg[0] >> 32) + reg[1];
  printf("0x%08x%08x\n", reg[1], reg[0]);
  test_instructions(ANDS);
  test_instructions(ADCS);
  test_instructions(ADDS);
  test_instructions(BICS);
  test_instructions(LSLS);
  test_instructions(ASRS);
  return (0);
}

void ands(int rn, int rm) {
  // Include your code to emulate the "and" instruction:
  // subs rn, rm
  // rn = index where operand1 is located in reg[], also destination for result
  // rm = index where operand2 is located in reg[]

  reg[rn] &= reg[rm];

  // Negative Flag 
  if (reg[rn]&0x80000000) SET_N;
  else CLEAR_N;
 
  // Zero Flag 
  if (!reg[rn]) SET_Z;
  else CLEAR_Z;
 }

void adcs(int rn, int rm) {
  // Include your code to emulate the "adc" instruction:
  // adcs rn, rm
  // rn = index where operand1 is located in reg[], also destination for result
  // rm = index where operand2 is located in reg[]
  //reg[rn] &= reg[rm];

  int c = reg[rn];
  if (psr == 0x20000000) reg[rn] += reg[rm] + 1;
  else reg[rn] += reg[rm];
  int i = 0;
  int xrn = reg[rn];
  int xrm = reg[rm];
  psr = 0;
  if (reg[rn] == 0) {
    if (c > reg[rn]) {
      SET_C;
      SET_Z;
    }
    else
      SET_Z;
  }
  
  //negative
  if (reg[rn] & 0x80000000) {
    SET_N;
  }

  //carry
  if(c > reg[rn]) {
    SET_C;
  }
  
  //overflow
  if (c > 0 && xrm > 0)
    if (xrn < 0)
      SET_V;
}

void adds(int rn, int rm) {
  // Include your code to emulate the "add" instruction:
  // adds rn, rm
  // rn = index where operand1 is located in reg[], also destination for result
  // rm = index where operand2 is located in reg[]
  //reg[rn] &= reg[rm];

  int c = reg[rn];
  reg[rn] += reg[rm];
  psr = 0;

  //zero
  if (reg[rn] == 0) {
    if (c > reg[rn]) {
      SET_C;
      SET_Z;
    }
    else
      SET_Z;
  }
  
  //negative
  if (reg[rn] & 0x80000000) {
    SET_N;
  }

  //carry
  if(c > reg[rn]) {
    SET_C;
  }

  //overflow
  int xrn = reg[rn];
  int xrm = reg[rm];
  if (c > 0 && xrm > 0)
    if (xrn < 0)
      SET_V;
}

void bics(int rn, int rm) {
  // Include your code to emulate the "bics" instruction:
  // subs rn, rm
  // rn = index where operand1 is located in reg[], also destination for result
  // rm = index where operand2 is located in reg[]
  //reg[rn] &= reg[rm];

  int xrn = reg[rn];
  int xrm = reg[rm];
  int xrn_c = xrn;
  int xrm_c = xrm;
  int xrnarr[32];
  int xrmarr[32];
  int ii = 0;

  for (ii; ii < 32; ii++) {
    xrnarr[ii] = 0;
    xrmarr[ii] = 0;
  }
  if (xrn_c >= 0) {
    int i = 31;
    for (i; i >= 0; i--) {
      xrnarr[i] = xrn_c % 2;
      xrn_c = xrn_c / 2;
    }
  }
  else {
    int i = 31;
    xrn_c = -1 * xrn_c;
    xrn_c = xrn_c - 1;
    for(i; i >= 0; i--) {
      xrnarr[i] = xrn_c % 2;
      xrn_c = xrn_c / 2;
    }
    i = 0;
    for(i; i < 32; i++) {
      if (xrnarr[i] == 0)
	xrnarr[i] = 1;
      else
	xrnarr[i] = 0;
    }
  }
    if (xrm_c >= 0) {
      int i = 31;
      for (i; i >= 0; i--) {
	xrmarr[i] = xrm_c % 2;
	xrm_c = xrm_c / 2;
      }
    }
    else {
      int i = 31;
      xrm_c = -1 * xrm_c;
      xrm_c = xrm_c - 1;
      for(i; i >= 0; i--) {
	xrmarr[i] = xrm_c % 2;
	xrm_c = xrm_c / 2;
      }
      i = 0;
      for(i; i < 32; i++) {
	if (xrmarr[i] == 0)
	  xrmarr[i] = 1;
	else
	  xrmarr[i] = 0;
      }
    }
    int result[32];
    int i = 0;
    for (i; i < 32; i++) {
      if((xrnarr[i] == 1) && (xrmarr[i] == 0))
	result[i] = 1;
      else
	result[i] = 0;
    }
    int re = 0;
    int pow = 1;
    i = 31;
    for (i; i >= 0; i--) {
      re = re + pow * result[i];
      pow = pow * 2;
    }
    reg[rn] = re;
    int c = reg[rn];

    //negative
    if (reg[rn] & 0x80000000) {
      SET_N;
    }

    //zero
    if (reg[rn] == 0) {
      if (c > reg[rn]) {
	SET_C;
	SET_Z;
      }
      else
	SET_Z;
    }
}

void lsls(int rn, int rm) {
  // Include your code to emulate the "lsls" instruction:
  // subs rn, rm
  // rn = index where operand1 is located in reg[], also destination for result
  // rm = index where operand2 is located in reg[]
  //reg[rn] &= reg[rm];

  int xrn = reg[rn];
  int xrm = reg[rm];
  int c = reg[rn];
  int x = 0;
  int rem = 0;
  int cc = 0;
  int ccc = 0;

  //positive
  if (xrm > 0) {
    if (xrm % 32 == 0) {
      if (xrm == 32)
	x = 0;
      else if (xrm <= 128) {
	ccc = 1;
	x = 0;
      }
      else
	x = reg[rn];
    }
    else {
      rem = xrm % 32;
      if (rem == 31) {
	ccc = 1;
	x = 0;
      }
      else {
	x = reg[rn] << rem;
      }
    }
    
  }

  //negative
  else {
    if (xrm == -2147483648) {
      x = reg[rn];
      //printf("AAAAAAAAAA");
    }
    else {
    x = 0;
    ccc = 1;
    }
  }

  reg[rn] = x;
  psr = 0;

  //zero
  if (reg[rn] == 0) {
    if (c > reg[rn]) {
      if (ccc == 0)
	SET_C;
      SET_Z;
    }
    else
      SET_Z;
  }

  //negative
  if (reg[rn] & 0x80000000) {
    SET_N;
  }

  //carry
  if((cc == 1 || c > reg[rn]) && ccc == 0) {
    SET_C;
  }

}

void asrs(int rn, int rm) {
  // Include your code to emulate the "asrs" instruction:
  // subs rn, rm
  // rn = index where operand1 is located in reg[], also destination for result
  // rm = index where operand2 is located in reg[]
  //reg[rn] &= reg[rm];

  int xrn = reg[rn];
  int xrm = reg[rm];
  int xrn_m1 = xrn >> (xrm - 1);
  int ca = 0;
  if (xrn_m1 >= 0) {
    if (xrn_m1 % 2 == 1)
      ca = 1;
  }
  else {
    int temp_xrn = xrn * -1;
    if (temp_xrn % 2 == 1)
      ca = 1;
  }
  int c = reg[rn];
  int ccc = 1;
  int cc = 0;
  if(xrm == -2147483648 || xrn == -1) {
    reg[rn] = c;
    cc = 1;
  }
  else if (xrm < 0) {
    reg[rn] = 0;
    ccc = 1;
  }
  else {
    xrn = xrn >> xrm;
    reg[rn] = xrn;
    xrn = reg[rn];
    if (xrm < 32) {
      if ((ca == 1) || xrn < -1) {
	if (xrn == -2147483648) {
	  ccc = 0;
	}
	else
	  cc = 1;
      }
      else {
	if (xrn != -2147483648)
	  cc = 0;
      }
    }
    if (xrm <= 128) {
      if (xrm % 32 == 0)
	reg[rn] = 0;
    }
  }
  psr = 0;
  //zero
  if (reg[rn] == 0) {
    if (c > reg[rn]) {
      if (ccc == 0)
	SET_C;
      SET_Z;
    }
    else
      SET_Z;
  }

  //negative
  if (reg[rn] & 0x80000000) {
    SET_N;
  }

  //carry
  if ((c == -2147483648) || (xrm == -2147483648)) {
    cc = 0;
  }
  else if ((c < 0)) {
    if (((c < reg[rn]) && (ccc == 0)) || (cc == 1)) {
      SET_C;
    }
  }
  else {
    if (((c > reg[rn]) && (ccc == 0)) || (cc == 1)) {
      SET_C;
    }
  }

}

/* main.c ends here */
