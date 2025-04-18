#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    if (argc != 2) {
        fprintf(stderr, "Uso: %s ARQUIVO\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *file = argv[1];   /* String do nome do arquivo */

    FILE *fstr = fopen(file, "r");  /* Abre arquivo para leitura ("r") */
    if (!fstr) {
        perror("fopen");    /* Imprime a descrição padrão do último erro em stderr */
        return EXIT_FAILURE;    /* Termina com erro */
    }

    char line[BUFSIZ];  /* Buffer para acumular uma linha lida */
    // fgets(line, BUFSIZ, fstr);  /* Lê uma linha até '\n', EOF ou LIMITE-1 */
    // printf("%s", line); /* Impressão da linha em stdout */
    // fgets(line, BUFSIZ, fstr);  /* Lê uma linha até '\n', EOF ou LIMITE-1 */
    // printf("%s", line); /* Impressão da linha em stdout */
    while (fgets(line, BUFSIZ, fstr) != NULL) {
        printf("%s", line);
    }

    fclose(fstr);   /* Fecha o arquivo */

    return EXIT_SUCCESS;    /* Termina com sucesso */
}
