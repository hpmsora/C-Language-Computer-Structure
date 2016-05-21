
#include <stdio.h>
#include <unistd.h>

int x = 0;

int quiting() {
  return 0;
}

void sleeping() {
  if( x == 0)
    quiting();
  else {
    printf("Hello World!\n");  
    sleep(3);
    sleeping();
  }
}

main()
{
  int num = 0;
  printf("How many \"Hello!! World!!\"?\n");
  scanf("%d", &num);
  int i =0;
  for(i = 0; i < num; i++) {
    printf("Hello!!  ");
    printf("World!!\n");
  }
  x = 0;
  int c = 1;
  while(c != 0) {
    printf("Now,\nPress \"0\" to start infinite loop\nPress \"1\" to quit\n");
    scanf("%d", &c);
    if (c == 0)
      x = 1;
    if (c == 1)
      break;
  }
  sleeping();
}
