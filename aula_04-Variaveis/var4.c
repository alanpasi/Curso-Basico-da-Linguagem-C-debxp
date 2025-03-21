#include <stdio.h>

int main() {

    int a = 25;
    int b = 17;
    int *p = &b;

    printf("Endereço (b)       : %p\n", p);
    printf("Valor              : %d\n", *p);
    printf("Endereço (a)       : %p\n", &a);
    printf("Endereço (p - 1)   : %p\n", p - 1);
    printf("Valor              : %d\n", *(p - 1));

    return 0;
}
