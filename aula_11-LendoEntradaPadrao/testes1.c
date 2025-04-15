#include <stdio.h>

int main(void) {

    int num;

    printf("Digite um número: ");
    int ret = scanf("%d", &num);
    if (ret && ret != EOF) {
        printf("%d x 2 = %d\n", num, num * 2);
    }
    else {
        puts("Entrada inválida!");
        return 1;
    }

    return 0;
}
