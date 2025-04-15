#include <stdio.h>
#include <stdlib.h>     /* exit(), EXIT_FAILURE */
#include <string.h>     /* strcmp() */

#define unsigned long size_t;

void check_ret(int);
void flush_input(void);

#define BUFMAX 10

int main(void) {

    char senha[BUFMAX] = "senha";
    char input[BUFMAX];

    printf("Digite sua senha: ");
    // check_ret(scanf("%9s", input));

    if (fgets(input, BUFMAX, stdin) != NULL) {
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }
        if (strcmp(input, senha) == 0) {
            puts("Você entrou!");
        } else {
            fprintf(stderr, "Senha incorreta!\n");
        }
    } else {
        fprintf(stderr, "Erro de leitura!\n");
    }

    printf("Input: %s\n", input);
    printf("Senha: %s\n", senha);

    return 0;
}

void check_ret(int ret) {
    if (ret == 0 || ret == EOF) {
        fprintf(stderr, "Entrada inválida!\n");
        exit(EXIT_FAILURE);
    }
}

void flush_input(void) {
    char c;
    while ((c = getchar()) != '\n' && c != EOF)
    ;
}
