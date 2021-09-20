#include <stdio.h>

int main() {

  volatile int change_this;
  char c[64];

  change_this = 0;
  gets(c);

  if (change_this != 0) {
    printf("win\n");
  }
  else {
    printf("lose\n");
  }

}
