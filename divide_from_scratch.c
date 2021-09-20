#include <stdio.h>

#define FIRST32 0b1111111111111111111111111111111100000000000000000000000000000000
#define LAST32  0b0000000000000000000000000000000011111111111111111111111111111111

#define DIVIDEND 5679

int main() {

  //printf("%d", sizeof(long));
  //printf("%d", sizeof(int));
  int result[2];
  divide(DIVIDEND, 7, result);
  divide(3, 10, result);

  char nums[5];
  nums[4] = '\n';

  divide(DIVIDEND, 10, result);
  nums[3] = '0' + result[1];

  for (int i = 2; i >= 0; i--) {

    divide(result[0], 10, result);
    nums[i] = '0' + result[1];

  }

  printf("%s", nums);

}

void divide(unsigned int dividend, unsigned int divisor, int *result) {

  unsigned long dividend_l = dividend;

  unsigned int quotient = 0;
  long remainder = 0;

  for (int i = 0; i < 32; i++) {

    dividend_l <<= 1;

    remainder = (dividend_l & FIRST32) >> 32;
    remainder = remainder - divisor;

    quotient <<= 1;
    if (remainder >= 0) {
      quotient |= 1;

      dividend_l &= LAST32;
      dividend_l |= (remainder << 32);

    }

  }

  if (remainder < 0) {
    remainder = (dividend_l & FIRST32) >> 32;
  }

  printf("\n%d, %d\n", quotient, remainder);
  result[0] = quotient;
  result[1] = remainder;

}

void print_b(long num) {

  char finals[65];
  finals[64] = '\0';
  int i = 63;

  while (num) {
    if (num & 1) {
      finals[i] = '1';
    } else {
      finals[i] = '0';
    }

    num >>= 1;
    i--;
  }

  while (i >= 0) {

    finals[i] = '0';
    i--;

  }

  printf("%s", finals);

}

