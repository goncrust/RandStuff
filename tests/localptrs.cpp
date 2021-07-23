#include <iostream>

void getInt(int *b) {
  printf("%d\n", *b);
}

int main() {

  int a = 3;

  getInt(&a);
}
