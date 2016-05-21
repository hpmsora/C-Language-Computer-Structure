//
// dump.c
//
#include <stdio.h>
#include <float.h>

void dump_memory(void *p, int len)
{
  int i;

  for (i = 0; i < len; i++) {

    if (*(unsigned char*)(p + i) >= 32 && *(unsigned char *)(p + i) < 127) {
      if (i % 8 == 0)
	printf("%8p\t%02c\t0x%02x\t+%hu\t+%d\t+%e\t+%e\n", p + i, *(unsigned char *)(p + i), *(unsigned char *)(p + i), *(unsigned short *)(p + i), *(unsigned int *)(p + i), *(float *) (p + i), *(double *) (p + i));
      else if (i % 4 == 0)
	printf("%8p\t%02c\t0x%02x\t+%hu\t+%d\t+%e\n", p + i, *(unsigned char *)(p + i), *(unsigned char *)(p + i), *(unsigned short *)(p + i), *(unsigned int *)(p + i), *(float *) (p + i));
      else if (i % 2 == 0)
	printf("%8p\t%02c\t0x%02x\t+%hu\n", p + i, *(unsigned char *)(p + i), *(unsigned char *)(p + i), *(unsigned short *)(p + i));
      else
	printf("%8p\t%02c\t0x%02x\n", p + i, *(unsigned char *)(p + i), *(unsigned char *)(p + i));
    }
    else {
       if (i % 8 == 0)
	printf("%8p\t ?\t0x%02x\t+%hu\t+%d\t+%e\t+%e\n", p + i, *(unsigned char *)(p + i), *(unsigned char *)(p + i), *(unsigned short *)(p + i), *(unsigned int *)(p + i), *(float *) (p + i), *(double *) (p + i));
      else if (i % 4 == 0)
	printf("%8p\t ?\t0x%02x\t+%hu\t+%d\t+%e\n", p + i, *(unsigned char *)(p + i), *(unsigned char *)(p + i), *(unsigned short *)(p + i), *(unsigned int *)(p + i), *(float *) (p + i));
      else if (i % 2 == 0)
	printf("%8p\t ?\t0x%02x\t+%hu\n", p + i, *(unsigned char *)(p + i), *(unsigned char *)(p + i), *(unsigned short *)(p + i));
      else
	printf("%8p\t ?\t0x%02x\n", p + i, *(unsigned char *)(p + i), *(unsigned char *)(p + i));
    }
  }
}
