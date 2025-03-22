#include <stdio.h>

int main(void) {
    /* switch .. case .. default */
    int flag;

    for (int i = 1; i <= 20; i++) {
        flag = 0;
        flag += (i % 2) ? 0 : 1;    /* Operação ternária */
        flag += (i % 3) ? 0 : 2;

        switch (flag) {
            case 1:
                printf("%d é divisível por 2\n", i);
                break;
            case 2:
                printf("%d é divisível por 3\n", i);
                break;
            case 3:
                printf("%d é divisível por 2 e 3\n", i);
                break;
            default:
                printf("%d\n", i);
        }
    }

    return 0;
}
