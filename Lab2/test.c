//Test file.
//Won Yong Ha (woha)

#include <stdio.h>

//Getting 'myprintf' class
extern void myprintf(const char *, ...);

//main Method
int main() {

  //printing
  myprintf("Nothing much\n");
  myprintf("The letter %c\n", 'A');
  myprintf("A string: %s\n", "Splash!");
  myprintf("The number %d\n", 11);
  myprintf("The number %x in hexadecimal\n", 11);
  myprintf("%d is a negative number\n", -5);
  myprintf("The number %d\n", 'A');
  myprintf("The number %x in hexadecimal\n", 'A');

  return 0;
}
