#include <stdio.h>

int main(void) {

    char str1[] = "carro";
    char str2[] = "bola";
    char str3[] = "peteca";

    char *lista[] = {str1, str2, str3};

    int elements = sizeof(lista) / sizeof(lista[0]);
    printf("*lista[]: %d elements\n", elements);
    printf("*(lista + 1) => %s\n", *(lista + 1));
    for (int i = 0; i < (sizeof(lista) / sizeof(lista[0])); i++) {
        printf("%d => %s\n", i, *(lista + i));
    }

    char *pstr1 = str1;
    char **plista = lista;

    return 0;
}
