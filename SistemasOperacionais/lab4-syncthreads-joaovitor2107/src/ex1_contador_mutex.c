#include <bits/types/clock_t.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 100
#define INCREMENTOS_POR_THREAD 1000

// Variáveis globais
int contador_likes = 0;
int contador_sem_mutex = 0;
pthread_mutex_t mutex_contador;

// Função executada pelas threads COM mutex
void* incrementar_likes(void* arg) {
    int thread_id = *(int*)arg;

    pthread_mutex_lock(&mutex_contador);
    for (int i = 0; i < INCREMENTOS_POR_THREAD; i++) {
        // TODO: Adicionar sincronização
        contador_likes++;

        // Simulando algum processamento
        if (i % 100 == 0) {
            usleep(1);
        }
    }
    pthread_mutex_unlock(&mutex_contador);

    printf("Thread %d: Terminei de processar os %d likes\n", thread_id, INCREMENTOS_POR_THREAD);
    return NULL;
}

// Função executada pelas threads SEM mutex (para comparação)
void* incrementar_sem_mutex(void* arg) {
    int thread_id = *(int*)arg;
    
    for (int i = 0; i < INCREMENTOS_POR_THREAD; i++) {
    
        contador_sem_mutex++;
        
        if (i % 100 == 0) {
            usleep(1);
        }
    }
    
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    
    printf("=== Sistema de Likes - Rede Social ===\n");
    printf("Threads: %d | Incrementos por thread: %d\n", NUM_THREADS, INCREMENTOS_POR_THREAD);
    printf("Total esperado: %d\n\n", NUM_THREADS * INCREMENTOS_POR_THREAD);
    
    // TODO: Inicializar o mutex
    // Teste COM mutex
    pthread_mutex_init(&mutex_contador, NULL);
    printf("--- Teste COM Mutex ---\n");
    contador_likes = 0;
    
    // Criar threads
    clock_t inicio = clock();
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        if (pthread_create(&threads[i], NULL, incrementar_likes, &thread_ids[i]) != 0) {
            perror("Erro ao criar thread");
            exit(1);
        }
    }

    // Aguardar threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    clock_t fim = clock();
    double tempo = ((double)fim-inicio)/CLOCKS_PER_SEC;

    printf("Contador final COM mutex: %d\n", contador_likes);
    printf("Correto? %s\n",
           (contador_likes == NUM_THREADS * INCREMENTOS_POR_THREAD) ? "SIM" : "NÃO");
    printf("Tempo de execução: %f\n\n",tempo);


    // Teste SEM mutex (para comparação)
    printf("--- Teste SEM Mutex (comparação) ---\n");
    contador_sem_mutex = 0;
    
    // Criar threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        if (pthread_create(&threads[i], NULL, incrementar_sem_mutex, &thread_ids[i]) != 0) {
            perror("Erro ao criar thread");
            exit(1);
        }
    }
    
    // Aguardar threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("Contador final SEM mutex: %d\n", contador_sem_mutex);
    printf("Correto? %s\n", 
           (contador_sem_mutex == NUM_THREADS * INCREMENTOS_POR_THREAD) ? "SIM" : "NÃO");
    printf("Diferença: %d\n", 
           (NUM_THREADS * INCREMENTOS_POR_THREAD) - contador_sem_mutex);
    
    // TODO: Destruir o mutex
    pthread_mutex_destroy(&mutex_contador);

    printf("\n=== Análise ===\n");
    printf("O mutex garantiu a consistência do contador?\n");
    printf("Qual foi o impacto da condição de corrida sem mutex?\n");
    
    return 0;
}
