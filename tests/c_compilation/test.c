#include <stdio.h>

#define NAME "Joca"

int main() {

#if 0
  printf("Hello %s\n", NAME);
#elif 2<1
  printf("Goodbye %s\n", NAME);
#else
  printf("Ok %s\n", NAME);
#endif

}
