#include <stdio.h>

/* Protótipo */
int quadrado(int);

int main(void) {
    int num = 5;

    printf("%d^2 = %d\n", num, quadrado(num));

    return 0;
}

/* Função */
int quadrado(int base) {
    return base * base;
}
