#include <stdio.h>

int main(void) {

    /* Estruturas de decisão */

    /* if .. else if .. else */
    for (int i = 1; i <= 20; i++) {
        if (i % 2 == 0) {   /* Módulo -> Resto de uma divisão */
            printf("%d é par\n", i);
        } else if (i % 15 == 0) {
            printf("%d é impar e divisível por 3 e 5\n", i);
        } else {
            printf("%d é impar\n", i);
        }
    }
}
