#include <stdio.h>
#include <string.h>

int main(void) {

    /* Vetor de caracteres com terminador nulo */
    char vstr[] = "banana";

    /* Ponteiro para vetor char[7] armazenada em sessão .rodata */
    char *pstr = "cabana";

    for (int i = 0; i < sizeof(vstr); i++)
        printf("vstr[%d] => %c\n", i, vstr[i]);

    puts("===============");

    for (int i = 0; i < strlen(pstr); i++)
        printf("*(pstr + %d) => %c\n", i, *(pstr + i));

    return 0;
}
