
#include <stdlib.h>
#include <stdio.h>

int main() {
    int *array = (int*) malloc(5 * sizeof(int));

    for (int i = 0; i < 5; i++) {
        array[i] = i;
    }

    // Acesso fora dos limites!
    for (int i = 0; i < 5; i++) {
        printf("array[%d] = %d\n", i, array[i]);
    }

    free(array);
    return 0;
}
