#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define APGL_HINT 0x4c475041
#define BLAU_HINT 0x55414c42

int bss_var;
int data_var = APGL_HINT;
const int ro_data = BLAU_HINT;

int func(void) {
    return 42;
}

int main(int argc, char **argv, char **envp) {

    static int lsni_var;
    static int lsi_var = BLAU_HINT;

    int lni_var;
    int li_var = APGL_HINT;

    char *str_ptr = "Salve!";

    void *heap_ptr = malloc(16);

    puts("[stack]");
    printf("%p             início do vetor envp (%s)\n", *envp, *envp);
    printf("%p             início do vetor argv (%s)\n", *argv, *argv);
    printf("%p  envp       ponteiro para envp (%p)\n", envp, *envp);
    printf("%p  argv       ponteiro para argv (%p)\n", argv, *argv);
    printf("%p  lni_var    variável não inicializada\n", &lni_var);
    printf("%p  li_var     variável inicializada\n", &li_var);
    printf("%p  &str_ptr   ponteiro com endereço da string (%p)\n", &str_ptr, "Salve!");
    printf("%p  &heap_ptr  ponteiro com endereço na heap (%p)\n", &heap_ptr, heap_ptr);
    printf("%p  argc       quantidade de argumentos (%d)\n", &argc, argc);

    puts("[mmap]");
    printf("%p  malloc()   função da glibc\n", (void *)malloc);
    printf("%p  printf()   função da glibc\n", (void *)printf);

    puts("[heap]");
    printf("%p  heap_ptr   espaço alocado dinamicamente na heap\n", heap_ptr);

    puts("[.bss]");
    printf("%p  lsni_var   variável local estática não inicializada\n", &lsni_var);
    printf("%p  bss_var    variável global não inicializada\n", &bss_var);

    puts("[.data]");
    printf("%p  lsi_var    variável local estática inicializada\n", &lsi_var);
    printf("%p  data_var   variável global inicializada\n", &data_var);

    puts("[.rodata]");
    printf("%p  str_ptr    endereço de uma string (%s)\n", str_ptr, str_ptr);
    printf("%p  ro_data    constante global\n", &ro_data);

    puts("[.text]");
    printf("%p  main()     função main\n", (void *)main);
    printf("%p  func()     função func\n", (void *)func);

    free(heap_ptr);

    sleep(300);

    return EXIT_SUCCESS;
}
