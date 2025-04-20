#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    if (argc != 2) {
        fprintf(stderr, "Uso: %s ARQUIVO\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *file = argv[1];
    FILE *fstr = fopen(file, "a");  /* Abre arquivo para escrita: se não existir, ele é creado */
    if (!fstr) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    char line[BUFSIZ];  /* Buffer para receber a linha lida (8192 bytes) */
    fgets(line, BUFSIZ, stdin); /* Leitura da digitação no terminal */
    fprintf(fstr, "%s", line);  /* Inserção da linha lida no arquivo */

    fclose(fstr);   /* Fecha arquivo */

    return EXIT_SUCCESS;    /* Termina com sucesso */
}
