#include <stdio.h>
#include <stdlib.h> /* exit() e EXIT_FAILURE */

/* Prototype */
void check_ret(int);

int main(void) {

    char prod[15];
    char uni[3];
    int qtd;
    float val;

    check_ret(scanf("%14s %2s %d %f", prod, uni, &qtd, &val));

    printf("Produto: %s\n", prod);
    printf("Unidade: %s\n", uni);
    printf("Qtd.: %d\n", qtd);
    printf("Preço: %f\n", val);
    printf("Total: %f\n", val * qtd);

    return 0;
}

void check_ret(int ret) {
    if (ret == 0 || ret == EOF) {
        fprintf(stderr, "Entrada inválida!\n");
        exit(EXIT_FAILURE);
    }
}
