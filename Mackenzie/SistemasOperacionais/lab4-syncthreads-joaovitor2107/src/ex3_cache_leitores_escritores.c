#include <bits/types/clock_t.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define NUM_LEITORES 5
#define NUM_ESCRITORES 2
#define OPERACOES_POR_THREAD 3

// Estrutura do cache
typedef struct {
    int dados[10];
    int versao;
} Cache;

// Variáveis globais
Cache cache;
int leitores_ativos = 0;
pthread_mutex_t mutex_leitores;
sem_t sem_recurso;
int total_leituras = 0;
int total_escritas = 0;

// Inicializar estruturas de sincronização
void inicializar_sincronizacao() {
    // Inicializar cache
    for (int i = 0; i < 10; i++) {
        cache.dados[i] = i;
    }
    cache.versao = 0;
    
    // TODO: Inicializar mutex e semáforo
    pthread_mutex_init(&mutex_leitores, NULL);
    sem_init(&sem_recurso, 0, 1);
}

// Função para iniciar leitura
void iniciar_leitura(int leitor_id) {
    // TODO: Implementar controle de entrada para leitores
    // Passos:
    // 1. Travar mutex_leitores
    // 2. Incrementar leitores_ativos
    // 3. Se for o primeiro leitor, fazer sem_wait no sem_recurso
    // 4. Destravar mutex_leitores
    pthread_mutex_lock(&mutex_leitores);
    if(leitores_ativos == 0) sem_wait(&sem_recurso);
    leitores_ativos++;

    printf("Leitor %d: Iniciando leitura (leitores ativos: %d)\n", 
           leitor_id, leitores_ativos);
    pthread_mutex_unlock(&mutex_leitores);
}

// Função para terminar leitura
void terminar_leitura(int leitor_id) {
    // TODO: Implementar controle de saída para leitores
    // Passos:
    // 1. Travar mutex_leitores
    // 2. Decrementar leitores_ativos
    // 3. Se for o último leitor, fazer sem_post no sem_recurso
    // 4. Destravar mutex_leitores

    pthread_mutex_lock(&mutex_leitores);
    printf("Leitor %d: Terminando leitura (leitores ativos: %d)\n", 
           leitor_id, leitores_ativos);
    if(leitores_ativos == 1) sem_post(&sem_recurso);
    leitores_ativos--;
    pthread_mutex_unlock(&mutex_leitores);
}

// Função para iniciar escrita
void iniciar_escrita(int escritor_id) {
    // TODO: Implementar controle de entrada para escritores
    // Passo único: sem_wait no sem_recurso

    printf("Escritor %d: Solicitando acesso exclusivo...\n", escritor_id);
    sem_wait(&sem_recurso);

    printf("Escritor %d: Acesso exclusivo obtido\n", escritor_id);
}

// Função para terminar escrita
void terminar_escrita(int escritor_id) {
    // TODO: Implementar controle de saída para escritores
    // Passo único: sem_post no sem_recurso
    sem_post(&sem_recurso);
    
    printf("Escritor %d: Liberando acesso\n", escritor_id);
}

// Thread leitora
void* leitor(void* arg) {
    int leitor_id = *(int*)arg;
    
    for (int i = 0; i < OPERACOES_POR_THREAD; i++) {
        // Simula trabalho antes de ler
        usleep(rand() % 100000);
        
        iniciar_leitura(leitor_id);
        
        // SEÇÃO CRÍTICA: Leitura do cache
        int soma = 0;
        for (int j = 0; j < 10; j++) {
            soma += cache.dados[j];
        }
        printf("Leitor %d: Li versão %d, soma = %d\n", 
               leitor_id, cache.versao, soma);
        total_leituras++;
        
        // Simula tempo de leitura
        usleep(rand() % 50000);
        
        terminar_leitura(leitor_id);
    }
    
    printf("Leitor %d: Finalizei minhas leituras\n", leitor_id);
    return NULL;
}

// Thread escritora
void* escritor(void* arg) {
    int escritor_id = *(int*)arg;
    
    for (int i = 0; i < OPERACOES_POR_THREAD; i++) {
        // Simula trabalho antes de escrever
        usleep(rand() % 200000);
        
        iniciar_escrita(escritor_id);
        
        // SEÇÃO CRÍTICA: Escrita no cache
        cache.versao++;
        for (int j = 0; j < 10; j++) {
            cache.dados[j] = cache.versao * 10 + j;
        }
        printf("Escritor %d: Atualizei cache para versão %d\n", 
               escritor_id, cache.versao);
        total_escritas++;
        
        // Simula tempo de escrita
        usleep(rand() % 100000);
        
        terminar_escrita(escritor_id);
    }
    
    printf("Escritor %d: Finalizei minhas escritas\n", escritor_id);
    return NULL;
}

int main() {
    pthread_t threads_leitores[NUM_LEITORES];
    pthread_t threads_escritores[NUM_ESCRITORES];
    int ids_leitores[NUM_LEITORES];
    int ids_escritores[NUM_ESCRITORES];
    
    srand(time(NULL));
    
    printf("=== Sistema de Cache (Leitores-Escritores) ===\n");
    printf("Leitores: %d | Escritores: %d\n", NUM_LEITORES, NUM_ESCRITORES);
    printf("Operações por thread: %d\n\n", OPERACOES_POR_THREAD);
    
    inicializar_sincronizacao();
    
    // Criar threads leitoras e escritoras intercaladas
    clock_t inicio = clock();
    for (int i = 0; i < NUM_LEITORES || i < NUM_ESCRITORES; i++) {
        if (i < NUM_LEITORES) {
            ids_leitores[i] = i;
            pthread_create(&threads_leitores[i], NULL, leitor, &ids_leitores[i]);
        }
        if (i < NUM_ESCRITORES) {
            ids_escritores[i] = i;
            pthread_create(&threads_escritores[i], NULL, escritor, &ids_escritores[i]);
        }
    }
    
    // Aguardar todas as threads
    for (int i = 0; i < NUM_LEITORES; i++) {
        pthread_join(threads_leitores[i], NULL);
    }
    clock_t fim = clock();
    for (int i = 0; i < NUM_ESCRITORES; i++) {
        pthread_join(threads_escritores[i], NULL);
    }
    
    // TODO: Destruir mutex e semáforo
    pthread_mutex_destroy(&mutex_leitores);
    sem_destroy(&sem_recurso);
    double time = ((double)fim - inicio)/CLOCKS_PER_SEC;
    time /= NUM_ESCRITORES;

    printf("\n=== Resultados ===\n");
    printf("Total de leituras: %d (esperado: %d)\n", 
           total_leituras, NUM_LEITORES * OPERACOES_POR_THREAD);
    printf("Total de escritas: %d (esperado: %d)\n", 
           total_escritas, NUM_ESCRITORES * OPERACOES_POR_THREAD);
    printf("Versão final do cache: %d\n", cache.versao);
    printf("\nObservações:\n");
    printf("- Múltiplos leitores puderam acessar simultaneamente?\n");
    printf("- Escritores tiveram acesso exclusivo?\n");
    printf("- Houve starvation de escritores?\n");
    printf("Tempo espera medio escritores: %f", time);
    
    return 0;
}
