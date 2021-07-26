#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {

  int sum = 0;

  for (int i = 0; i < strlen(argv[1]); i++) {
    sum += (int)argv[1][i];
  }

  if (sum == 1480) {
    printf("Valid key");
  } else {
    printf("Invalid key");
  }
}
