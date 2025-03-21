#include <stdio.h>

int c = 17;             /* Variável de escopo global */

int soma10(int num) {
    int b = 10;         /* Variável de escopo local ('b' e 'num') da função 'soma10' */
    return b + num;
}

int main() {

    int a = 25;         /* Variável de escopo local da função 'main' */

    printf("a = %d\nb = %d\nc = %d\nnum = %d\n", a, b, c, num);
        /* clang: Use of undeclared identifier 'b' */
        /* clang: Use of undeclared identifier 'num' */

    return 0;
}
