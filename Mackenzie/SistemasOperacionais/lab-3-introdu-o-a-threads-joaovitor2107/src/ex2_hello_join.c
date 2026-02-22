#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* print_hello(void* arg) {
    printf("Hello da thread!\n");
    return NULL;
}

int main() {
    pthread_t thread;
    
    printf("Hello da main!\n");
    
    // Criar a thread
    if (pthread_create(&thread, NULL, print_hello, NULL) != 0) {
        perror("pthread_create");
        return 1;
    }
    
    // TODO: Adicione pthread_join para esperar a thread terminar
    // Parâmetros:
    // 1. thread - a thread para esperar
    // 2. NULL - não queremos o valor de retorno
    pthread_join(thread, NULL);
    
    
    printf("Main: thread terminou\n");
    
    return 0;
}
