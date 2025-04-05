#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    // Chamada fork...
    pid_t pid = fork();

    // Se o fork falhar...
    if (pid < 0) {
        perror("fork falhou");
        exit(EXIT_FAILURE);
    }

    /*
    Um segundo processo é criado e o código seguinte será executado
    por ambos os processos (eles são idênticos!), mas com valores
    de pid diferentes:
    - Para o processo filho, pid == 0
    - Para o processo pai, pid === PID do processo filho

    Por isso temos essa estrutura if...
    */

    if (pid == 0) {
        // Processo filho...
        printf("[Filho] PID: %d, iniciado.\n", getpid());
        char *args[] = {"ls", "-l", NULL};
        // Chamada exec (execvp)...
        execvp(args[0], args);
        // Se execvp falhar...
        perror("execvp falhou");
        exit(EXIT_FAILURE);
    } else {
        // Processo pai...
        printf("[Pai] PID: %d, criou filho PID: %d\n", getpid(), pid);
        printf("[Pai] Aguardando termino do filho...\n");
        int status;
        waitpid(pid, &status, 0);
        printf("[Pai] Processo filho %d terminou com status %d\n", pid, WEXITSTATUS(status));
        printf("[Pai] Voltando ao controle.\n");
    }
    return 0;
}
