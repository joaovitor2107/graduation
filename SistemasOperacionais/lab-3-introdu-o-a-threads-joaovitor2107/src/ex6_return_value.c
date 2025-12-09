#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

// TODO: Implemente a função que calcula e retorna um resultado
void* calculate_square(void* arg) {
    int num = *(int*)arg;
    
    // TODO: Aloque memória no heap para o resultado
    // int* result = ...;
    int *result = (int*)malloc(sizeof(int));
    
    // TODO: Verifique se a alocação foi bem-sucedida
    // if (result == NULL) { ... }
    if(result == NULL){
        perror("malloc");
        return NULL;
    }
    
    
    // TODO: Calcule o quadrado e armazene no resultado
    // *result = ...;
    *result = num*num;
    
    printf("Thread %d: Calculando %d^2\n", num, num);
    
    return result;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];
    
    printf("Main: Criando threads para calcular quadrados\n\n");
    
    // Criar threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_args[i] = i + 1; // Valores: 1, 2, 3, 4, 5
        
        if (pthread_create(&threads[i], NULL, calculate_square, &thread_args[i]) != 0) {
            perror("pthread_create");
            return 1;
        }
    }
    
    printf("\nMain: Coletando resultados\n");
    
    // TODO: Coletar resultados das threads
    for (int i = 0; i < NUM_THREADS; i++) {
        // TODO: Declare uma variável para receber o resultado
        void *return_value;
        // TODO: Use pthread_join para obter o valor de retorno
        pthread_join(threads[i], &return_value);
        if(return_value == NULL){
            return 1;
        }
        // TODO: Converta o resultado para int* e imprima
        int res = *(int*)return_value;
        printf("Resultado %d\n", res);
        // TODO: Libere a memória alocada pela thread
        free(return_value);
    }
    
    printf("\nMain: Todos os cálculos completados\n");
    
    return 0;
}
