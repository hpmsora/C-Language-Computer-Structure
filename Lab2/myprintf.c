//Won Yong Ha(woha)
//making printf function

#include <stdarg.h>
#include <stdio.h>


//printing function
void printint(int x) {
  if(x < 0) {
    putchar(45);
    x = -1*x;
    if (x == 0) {
      putchar(0);
    }
    else {
      int i = 0;
      i = x % 10 + 48;
      printint(x/10);
      putchar(i);
    }
  }
  else {
    if (x == 0) {
      putchar(0);
    }
    else {
      int i = 0;
      i = x % 10 + 48;
      printint(x/10);
      putchar(i);
    }
  }
}

/*
void printstring (char x[])

  int k = 0;

while (x[k] != NULL) {

  putchar(x[k]);
  k++;
  }*/
void printstring(char *x) {
  char capd[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char lowd[26] = "abcdefghijklmnopqrstuvwxyz";

  int i = 0;
  int count = 0;
  int curr = 0;

  while(x[count] != NULL) {
    char c = x[count];
    if(c == ' ')
      curr = 32;
    if(c == '\t')
      curr = 11;
    if(c == '\r')
      curr = 13;
    if(c == '\n')
      curr = 10;
    if(c == '\f')
      curr = 12;
    if(c == '\v')
      curr = 11;
    if(c == '!')
      curr = 33;
    if(c == '?')
      curr = 63;
    if(c == '#')
      curr = 35;
    if(c == '(')
      curr = 40;
    if(c == ')')
      curr = 41;
    for(i; i <= 25; i++) {
      if(c == capd[i])
	curr = 65 + i;
      if(c == lowd[i])
	curr = 97 + i;
    }
    i = 0;
    putchar(curr);
    count++;
  }
}

//printhex function
void printhex(int x) {
  if (x == 0)
    putchar(0);
  else {
    int digit = x % 16;
    printhex(x/16);
    if(digit == 10)
      putchar(97);
    else if(digit == 11)
      putchar(98);
    else if(digit == 12)
      putchar(99);
    else if(digit == 13)
      putchar(100);
    else if(digit == 14)
      putchar(101);
    else if(digit == 15)
      putchar(102);
    else
      putchar(digit + 48);
  }
}

//myprintf function
void myprintf(const char *fmt, ...) {
  const char *p;
  va_list argp;
  int i;
  char *s;

  va_start(argp, fmt);
  
  //for loop
  for (p = fmt; *p != '\0'; p++) {
    if (*p != '%') {
      putchar(*p);
      continue;
    }
    switch (*++p) {
      
      //c
    case 'c':
      i = va_arg(argp, int);
      putchar(i);
      break;

      //d
    case 'd':
      i = va_arg(argp, int);
      printint(i);
      break;

      //s
    case 's':
      s = va_arg(argp, char *);
      printstring(s);
      break;

      //x
    case 'x':
      i = va_arg(argp, int);
      printhex(i);
      break;

      //%
    case '%':
      putchar('%');
      break;
    }
  }
  va_end(argp);
}
