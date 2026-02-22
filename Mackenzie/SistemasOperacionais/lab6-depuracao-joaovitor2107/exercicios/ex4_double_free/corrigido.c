#include <stdlib.h>
#include <stdio.h>

int main() {
    int *ptr = (int*) malloc(sizeof(int));
    *ptr = 42;

    printf("Valor: %d\n", *ptr);

    printf("Memória liberada uma vez\n");

    free(ptr);
    printf("Tentativa de liberar memória novamente\n");

    return 0;
}
