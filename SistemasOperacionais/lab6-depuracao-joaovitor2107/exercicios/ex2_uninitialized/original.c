#include <stdlib.h>
#include <stdio.h>

int main() {
    int *array = (int*) malloc(10 * sizeof(int));
    int soma = 0;

    // Não inicializamos o array!

    // Tentamos usar os valores não inicializados
    for (int i = 0; i < 10; i++) {
        soma += array[i];
    }

    printf("A soma dos elementos é: %d\n", soma);

    free(array);
    return 0;
}
