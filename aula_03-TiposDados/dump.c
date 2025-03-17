#include <stdio.h>

void print_bytes(char *label, void *addr, size_t size);

int main(void) {

    int num = 100000;

    int sqr_int = num * num;
    unsigned long sqr_long = (unsigned long)num * num;

    print_bytes("num     ", &num, sizeof(num));
    printf("-> %d\n", num);

    print_bytes("sqr_int ", &sqr_int, sizeof(sqr_int));
    printf("-> %d\n", sqr_int);

    print_bytes("sqr_long", &sqr_long, sizeof(sqr_long));
    printf("-> %lu\n", sqr_long);

    return 0;
}

void print_bytes(char *label, void *addr, size_t size) {

    unsigned char *bytes = (unsigned char *)addr;

    printf("%p - %s - ", bytes, label);

    for (size_t i = 0; i < 8; i++)
        printf("%02x ", i > (size - 1) ? 0 : bytes[i]);
}
