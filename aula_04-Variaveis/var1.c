#include <stdio.h>

int main() {

    int a = 10; /* Variável declarada e inicializada (definida) */
    int b;      /* Variável declarada, mas não inicializada */

    printf("a = %d\n", a);
    printf("b = %d\n", b);  /* warning: ‘b’ is used uninitialized [-Wuninitialized] */
    printf("a + b = %d\n", a + b);

    return 0;
}
