#include <stdio.h>

int main(void) {

    char str[] = "banana";
    printf("Tamanho de 'str': %zu\n", sizeof(str));
    char *pstr = "cabanana";
    printf("Tamanho de 'pstr': %zu\n", sizeof(pstr));
    /* O operador sizeof avaliou 8 bytes porque é o tamanho de um endereço. */

    return 0;
}
