#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 100

// TODO: Implemente a função que cada thread executará
// A função deve:
// 1. Converter o argumento void* para int* e depois para int
// 2. Imprimir "Thread X: Hello!" onde X é o ID da thread
// 3. Retornar NULL
void* thread_function(void* arg) {
    // TODO: Implemente aqui
    // Dica: int thread_id = *(int*)arg;
    int thread_id = *(int*)arg;
    printf("Thread %d: Hello!\n", thread_id);

    return NULL;
}

int main() {
    // TODO: Declare um array de pthread_t para armazenar os IDs das threads
    pthread_t threads[NUM_THREADS];
    // TODO: Declare um array de inteiros para armazenar os IDs únicos
    int id[NUM_THREADS];
    
    printf("Main: Criando %d threads\n", NUM_THREADS);
    
    // TODO: Use um loop para criar todas as threads
    // Para cada thread:
    // 1. Defina thread_ids[i] = i
    // 2. Crie a thread passando &thread_ids[i] como argumento
    // 3. Verifique erros com pthread_create
    
    for (int i = 0; i < NUM_THREADS; i++) {
        id[i] = i;

        if (pthread_create(&threads[i], NULL, thread_function, &id[i]) != 0) {
            perror("pthread_create");
            return 1;
        }
    }

    
    // TODO: Use outro loop para fazer join em todas as threads
    // Isto garante que main espera todas as threads terminarem
    
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    
    printf("Main: Todas as threads terminaram\n");
    
    return 0;
}
