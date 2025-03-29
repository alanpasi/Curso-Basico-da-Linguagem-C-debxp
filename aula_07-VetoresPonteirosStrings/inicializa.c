
int main(void) {

    /* Formas de Inicialização de vetores */
        /* Inicialização do vetor */
    int vetor[3] = {1, 2, 3};
        /* Inicialização sem número de elementos */
    char c[] = {65, 66, 67, 68, 69};
    char str[] = "string";  /* O último elemento é '\0' (null) */
    char str2[] = {'s', 't', 'r', 'i', 'n', 'g', '\0'};
        /* Inicialização parcial */
    int n[6] = {1, 2, 3};   /* = {1, 2, 3, 0, 0, 0} */
        /* Inicialização com zeros */
    int z[5] = {0}; /* = {0, 0, 0, 0, 0} */
        /* Inicialização com elementos de mesmo valor */
    int r[4] = {23};    /* = {23, 0, 0, 0} */
    for (int i = 0; i < 4; i++)     /* = {23, 23, 23, 23} */
        r[i] = 23;

    return 0;
}
