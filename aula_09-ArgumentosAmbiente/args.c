#include <stdio.h>

/* Imprime listas de strings */
void print_list(char *list[]);

int main(int argc, char **argv) {

    for (int i = 0; i < argc; i++)
        printf("argv[%d] = %s\n", i, argv[i]);

    printf("\n");

    /* Vetor de elementos do tipo 'ponteiro para char' */
    char *lista[] = {
        "carro",
        "bola",
        "peteca",
        NULL    /* (void *) 0 */
    };

    printf("list[]\n");
    print_list(lista);
    printf("argv[]\n");
    print_list(argv);
    printf("\n");

    return 0;
}

void print_list(char *list[]) {
    int i = 0;
    while (list[i] != NULL) {
        printf("[%d] => %p => %s\n", i, list[i], list[i]);
        i++;
    }
}
