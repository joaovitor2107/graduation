#include <stdlib.h>
#include <stdio.h>

int main() {
    int *ptr = (int*) malloc(sizeof(int));
    *ptr = 42;

    printf("Valor inicial: %d\n", *ptr);

    free(ptr);

    // Uso após liberação!
    *ptr = 100;
    printf("Valor após liberação: %d\n", *ptr);

    return 0;
}
