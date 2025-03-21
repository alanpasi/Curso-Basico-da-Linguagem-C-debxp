#include <stdio.h>

int main() {

    int a = 17;
    int b = 25;

    puts("Var  Address        Size Value");

    printf("a -> %p %4zu %5d\n", &a, sizeof(a), a);
    printf("b -> %p %4zu %5d\n", &b, sizeof(b), b);

    return 0;
}
