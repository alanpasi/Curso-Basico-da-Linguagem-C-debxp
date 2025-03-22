#include <stdio.h>

int main(void) {

    /* Estruturas de repetição ("loops") */

    /* for */
    printf("'for'\n");
    for (int i = 0; i < 10; i++) {
        printf("%d = %d\n", i, i * 10);
    }

    /* while */
    printf("'while'\n");
    int i = 0;
    while (i < 10) {
        printf("%d\n", i);
        i += 2;
    }

    /* do..while */
    printf("'do..while'\n");
    do {
        printf("%d\n", i);
        i--;
    }while (i > 0);

    return 0;
}
