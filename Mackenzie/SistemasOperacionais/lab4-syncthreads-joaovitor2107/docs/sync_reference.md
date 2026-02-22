# Referência Rápida - Mecanismos de Sincronização

## Mutex (Exclusão Mútua)

### Funções Principais
```c
pthread_mutex_t mutex;
pthread_mutex_init(&mutex, NULL);     // Inicializar
pthread_mutex_lock(&mutex);           // Travar
pthread_mutex_unlock(&mutex);         // Destravar
pthread_mutex_destroy(&mutex);        // Destruir
```

### Padrão de Uso
```c
pthread_mutex_lock(&mutex);
// Seção crítica - apenas uma thread por vez
recurso_compartilhado++;
pthread_mutex_unlock(&mutex);
```

### Inicialização Estática
```c
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
```

## Variáveis de Condição

### Funções Principais
```c
pthread_cond_t cond;
pthread_cond_init(&cond, NULL);        // Inicializar
pthread_cond_wait(&cond, &mutex);      // Esperar (libera mutex)
pthread_cond_signal(&cond);            // Acordar uma thread
pthread_cond_broadcast(&cond);         // Acordar todas
pthread_cond_destroy(&cond);           // Destruir
```

### Padrão de Uso - Produtor
```c
pthread_mutex_lock(&mutex);
while (buffer_cheio) {  // SEMPRE use while, não if!
    pthread_cond_wait(&cond_nao_cheio, &mutex);
}
// Adicionar item ao buffer
pthread_cond_signal(&cond_nao_vazio);
pthread_mutex_unlock(&mutex);
```

### Padrão de Uso - Consumidor
```c
pthread_mutex_lock(&mutex);
while (buffer_vazio) {
    pthread_cond_wait(&cond_nao_vazio, &mutex);
}
// Remover item do buffer
pthread_cond_signal(&cond_nao_cheio);
pthread_mutex_unlock(&mutex);
```

## Semáforos

### Funções Principais
```c
#include <semaphore.h>
sem_t sem;
sem_init(&sem, 0, valor_inicial);     // Inicializar
sem_wait(&sem);                       // Decrementar (P)
sem_post(&sem);                       // Incrementar (V)
sem_destroy(&sem);                    // Destruir
```

### Semáforo Binário (Mutex-like)
```c
sem_init(&sem, 0, 1);  // Valor inicial 1
sem_wait(&sem);        // Entrar na seção crítica
// Seção crítica
sem_post(&sem);        // Sair da seção crítica
```

### Semáforo Contador
```c
sem_init(&sem, 0, N);  // N recursos disponíveis
sem_wait(&sem);         // Adquirir um recurso
// Usar recurso
sem_post(&sem);         // Liberar recurso
```

## Padrões Comuns

### Leitores-Escritores (Preferência para Leitores)
```c
// Leitor entrando
pthread_mutex_lock(&mutex_leitores);
leitores_ativos++;
if (leitores_ativos == 1)
    sem_wait(&sem_recurso);  // Primeiro leitor bloqueia escritores
pthread_mutex_unlock(&mutex_leitores);

// Leitura...

// Leitor saindo
pthread_mutex_lock(&mutex_leitores);
leitores_ativos--;
if (leitores_ativos == 0)
    sem_post(&sem_recurso);  // Último leitor libera escritores
pthread_mutex_unlock(&mutex_leitores);

// Escritor
sem_wait(&sem_recurso);
// Escrita exclusiva...
sem_post(&sem_recurso);
```

### Buffer Circular
```c
typedef struct {
    Item items[SIZE];
    int inicio, fim, count;
} Buffer;

// Inserir
buffer.items[buffer.fim] = item;
buffer.fim = (buffer.fim + 1) % SIZE;
buffer.count++;

// Remover
item = buffer.items[buffer.inicio];
buffer.inicio = (buffer.inicio + 1) % SIZE;
buffer.count--;
```