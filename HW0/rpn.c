// Won Yong Ha(woha)
// Homework 0

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct CELL *LIST;

struct CELL {
  int val;
  LIST next;
};

//Global Variable
LIST stack;


void push(int val) {
  LIST c = (LIST) malloc(sizeof(struct CELL));
  if (c) {
    c->val = val;
    c->next = stack;
    stack = c;
  }
}

int pop() {
  int val = stack -> val;
  stack = stack -> next;
  return val;
}

void printerror() {
  printf("cd: stack empty\n");
}

int main() {
  stack = NULL;
  char input[999];
  while (*input != 'q' && *input != EOF) {
    scanf("%s", input);
    int isnum = atoi(input);
    int excp0 = strcmp(input, "0");
    //printf ("%d", isnum);
    //printf ("%d\n", 11);

    if (isnum != 0 || excp0 == 0) {
      //printf("Num %s\n", input);
      push(isnum);
    }
    else {
      //printf("Char %s\n", input);
      if (*input == '+') {
	if (stack && stack -> next) {
	  //printf("valid +");
	  int x;
	  int y;
	  x = pop();
	  y = pop();
	  push (x + y);
	}
	else {
	  printerror();
	}
      }
      else if (*input == '-') {
	if (stack && stack -> next) {
	  int x;
	  int y;
	  x = pop();
	  y = pop();
	  push (y - x);
	}
	else
	  printerror();
      }
      else if (*input == '/') {
	if (stack && stack -> next) {
	  int x;
	  int y;
	  x = pop();
	  y = pop();
	  push(y / x);
	}
	else
	  printerror();
      }
      else if (*input == '*') {
	if (stack && stack -> next) {
	  int x;
	  int y;
	  x = pop();
	  y = pop();
	  push(x * y);
	}
	else
	  printerror();
      }
      else if (*input == 'p') {
	if (stack)
	  printf("%d\n", stack -> val);
	else
	  printerror();
      }
      else if (*input ==  'f') {
	LIST i = stack;
	while (i) {
	  printf("%d\n", i->val);
	  i = i -> next;
	}
      }
      else if (*input == 'q')
	break;
      else {
	printf("'%c' is undefined.\n", *input);
      }
    }
  }
  return 0;
}
