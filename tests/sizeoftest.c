#include <stdio.h>
#include <stdlib.h>

int *ola() {
    int e[] = {1, 2, 3, 4};

    return e;
}

int main() {
    int a[] = {1, 2, 3};
    printf("a[]: %zu\n", sizeof(a));

    int b = 1;
    printf("b: %zu\n", sizeof(b));

    int *c = (int*)malloc(4*sizeof(int));
    printf("*c: %zu\n", sizeof(c));

    int d[5];
    printf("d[5]: %zu\n", sizeof(d));

    printf("%p %p %p %p\n\n\n", a, &b, c, d);

    int *retorno = ola();
    printf("%p", retorno);
}
