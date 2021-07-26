#include <stdio.h>
#include <stdlib.h>

int count(char *key) {
  int sum = 0;

  for (int i = 0; i < strlen(key); i++) {
    sum += (int) key[i];
  }

  return sum;
}

int main() {
  
  char key[20];
  int keySum = 0;
  char chars[] = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
 
  int i = 0;
  while (1) {
    if (i > 20) {
      i = 0;
      memset(key, 0, strlen(key));
    }

    key[i] = chars[random() % (strlen(chars) - 0 + 1)];

    keySum = count(key);

    if (keySum == 1480) {
      printf("%s\n", key);
      i = 0;
      memset(key, 0, strlen(key));
    } else if (keySum < 1480) {
      i++;
    } else {
      i = 0;
      memset(key, 0, strlen(key));
    }

  }
}
