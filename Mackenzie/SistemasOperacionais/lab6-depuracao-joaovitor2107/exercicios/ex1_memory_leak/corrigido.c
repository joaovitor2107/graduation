#include <stdlib.h>
#include <stdio.h>

void funcao_com_vazamento() {
    int *array = (int*) malloc(10 * sizeof(int));

    for (int i = 0; i < 10; i++) {
        array[i] = i * 10;
    }

    free(array);
}

int main() {
    for (int i = 0; i < 5; i++) {
        funcao_com_vazamento();
    }
    printf("Programa executado com sucesso!\n");
    return 0;
}
