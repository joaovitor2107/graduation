# Referência Rápida - pthread API

## Funções Principais

### pthread_create
```c
int pthread_create(pthread_t *thread,
                   const pthread_attr_t *attr,
                   void *(*start_routine)(void *),
                   void *arg);
```

**Descrição**: Cria uma nova thread

**Parâmetros**:
- `thread`: Ponteiro para armazenar o ID da thread criada
- `attr`: Atributos da thread (NULL para padrão)
- `start_routine`: Função que a thread executará
- `arg`: Argumento passado para a função

**Retorno**: 0 em sucesso, código de erro em falha

**Exemplo**:
```c
pthread_t thread;
int ret = pthread_create(&thread, NULL, worker_function, &data);
if (ret != 0) {
    fprintf(stderr, "Erro ao criar thread: %d\n", ret);
}
```

---

### pthread_join
```c
int pthread_join(pthread_t thread, void **retval);
```

**Descrição**: Aguarda uma thread terminar

**Parâmetros**:
- `thread`: ID da thread para aguardar
- `retval`: Ponteiro para receber o valor de retorno (pode ser NULL)

**Retorno**: 0 em sucesso, código de erro em falha

**Exemplo**:
```c
void *result;
int ret = pthread_join(thread, &result);
if (ret != 0) {
    fprintf(stderr, "Erro no join: %d\n", ret);
}
```

---

### pthread_exit
```c
void pthread_exit(void *retval);
```

**Descrição**: Termina a thread chamadora

**Parâmetros**:
- `retval`: Valor de retorno da thread

**Nota**: Não retorna ao chamador

**Exemplo**:
```c
void *worker(void *arg) {
    int *result = malloc(sizeof(int));
    *result = 42;
    pthread_exit(result);
}
```

---

### pthread_self
```c
pthread_t pthread_self(void);
```

**Descrição**: Retorna o ID da thread chamadora

**Retorno**: ID da thread atual

**Exemplo**:
```c
pthread_t my_id = pthread_self();
printf("Thread ID: %lu\n", (unsigned long)my_id);
```

---

### pthread_equal
```c
int pthread_equal(pthread_t t1, pthread_t t2);
```

**Descrição**: Compara dois IDs de thread

**Parâmetros**:
- `t1`, `t2`: IDs das threads para comparar

**Retorno**: Não-zero se iguais, 0 se diferentes

**Exemplo**:
```c
if (pthread_equal(thread1, thread2)) {
    printf("São a mesma thread\n");
}
```

## Tipos de Dados

### pthread_t
- Tipo opaco que representa o ID de uma thread
- Não assuma que é um inteiro
- Use pthread_equal() para comparar

### pthread_attr_t
- Atributos de uma thread
- Tamanho do stack, política de escalonamento, etc.
- Use NULL para valores padrão

## Função de Thread

### Assinatura
```c
void* function_name(void* arg)
```

**Requisitos**:
- Deve aceitar `void*` como parâmetro
- Deve retornar `void*`
- Pode usar `pthread_exit()` ou `return`

**Exemplo**:
```c
void* worker_thread(void* arg) {
    int* data = (int*)arg;
    printf("Processando: %d\n", *data);
    
    int* result = malloc(sizeof(int));
    *result = (*data) * 2;
    
    return result;  // ou pthread_exit(result);
}
```

## Padrões de Uso

### Criação Básica
```c
pthread_t thread;
pthread_create(&thread, NULL, function, NULL);
pthread_join(thread, NULL);
```

### Passando Argumentos
```c
int data = 42;
pthread_t thread;
pthread_create(&thread, NULL, function, &data);
pthread_join(thread, NULL);
```

### Recebendo Retorno
```c
pthread_t thread;
pthread_create(&thread, NULL, function, NULL);

void* retval;
pthread_join(thread, &retval);
int* result = (int*)retval;
printf("Resultado: %d\n", *result);
free(result);
```

### Múltiplas Threads
```c
#define NUM_THREADS 5
pthread_t threads[NUM_THREADS];
int thread_data[NUM_THREADS];

// Criar
for (int i = 0; i < NUM_THREADS; i++) {
    thread_data[i] = i;
    pthread_create(&threads[i], NULL, function, &thread_data[i]);
}

// Aguardar
for (int i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], NULL);
}
```

## Códigos de Erro Comuns

| Código | Nome | Descrição |
|--------|------|------------|
| EAGAIN | Resource temporarily unavailable | Sistema sem recursos para criar thread |
| EINVAL | Invalid argument | Parâmetro inválido |
| EPERM | Operation not permitted | Sem permissão para definir atributos |
| ESRCH | No such process | Thread especificada não existe |
| EDEADLK | Resource deadlock avoided | Deadlock detectado |

## Verificação de Erros

```c
#include <errno.h>
#include <string.h>

int ret = pthread_create(&thread, NULL, function, NULL);
if (ret != 0) {
    fprintf(stderr, "pthread_create: %s\n", strerror(ret));
    exit(1);
}
```

## Dicas Importantes

1. **Sempre verifique retornos**
   - Funções pthread retornam 0 em sucesso
   - Não definem errno, retornam o código diretamente

2. **Join ou Detach**
   - Toda thread deve ser joined ou detached
   - Senão haverá vazamento de recursos

3. **Cuidado com variáveis locais**
   - Não passe endereço de variáveis que saem de escopo
   - Use alocação dinâmica ou variáveis globais/estáticas

4. **Retorno de threads**
   - Use malloc para valores de retorno
   - Lembre de fazer free após pthread_join

5. **Conversão de tipos (Cast)**
   - Sempre faça cast explícito de void*
   - Verifique alinhamento e tamanho

## Conversão de Tipos (Cast) - Explicação Detalhada

### Por que void*?

As threads POSIX foram projetadas para serem genéricas e trabalhar com qualquer tipo de dado. Por isso, usam `void*` - um ponteiro genérico que pode apontar para qualquer tipo. Isso permite flexibilidade máxima, mas requer conversões explícitas (cast).

### Cast na Entrada (Argumentos)

#### Passando um inteiro
```c
// ERRADO - não pode passar valor diretamente
pthread_create(&thread, NULL, func, 42);  // ❌ Erro de compilação

// CORRETO - passar endereço
int value = 42;
pthread_create(&thread, NULL, func, &value);  // ✓

// Dentro da thread - converter de void* para int*
void* func(void* arg) {
    int* ptr = (int*)arg;      // Cast de void* para int*
    int value = *ptr;           // Dereferencia para obter o valor
    printf("Valor: %d\n", value);
    return NULL;
}
```

#### Passando uma estrutura
```c
typedef struct {
    int id;
    char name[50];
} Data;

Data data = {1, "Thread-1"};
pthread_create(&thread, NULL, func, &data);

// Dentro da thread
void* func(void* arg) {
    Data* data = (Data*)arg;    // Cast de void* para Data*
    printf("ID: %d, Nome: %s\n", data->id, data->name);
    return NULL;
}
```

### Cast na Saída (Retorno)

#### Retornando um inteiro
```c
void* func(void* arg) {
    // ERRADO - variável local some quando função termina
    int result = 42;
    return &result;  // ❌ Endereço inválido após retorno
    
    // CORRETO - alocar no heap
    int* result = malloc(sizeof(int));
    *result = 42;
    return result;   // Cast implícito de int* para void*
}

// Coletando o resultado
void* retval;
pthread_join(thread, &retval);
int* result = (int*)retval;     // Cast de void* para int*
printf("Resultado: %d\n", *result);
free(result);                    // Importante: liberar memória
```

### Por que o Cast é Necessário?

1. **Segurança de tipos**: C é fortemente tipado. void* é genérico, mas para usar os dados, precisamos dizer ao compilador qual é o tipo real.

2. **Aritmética de ponteiros**: void* não tem tamanho definido, então não pode fazer aritmética:
```c
void* ptr = ...;
ptr++;           // ❌ Erro - quanto bytes avançar?

int* iptr = (int*)ptr;
iptr++;          // ✓ Avança sizeof(int) bytes
```

3. **Acesso aos dados**: Não podemos derefernciar void* diretamente:
```c
void* ptr = ...;
int value = *ptr;        // ❌ Erro - tipo desconhecido

int* iptr = (int*)ptr;
int value = *iptr;       // ✓ Agora sabemos o tipo
```

### Tabela de Conversões Comuns

| De | Para | Exemplo |
|----|------|------|
| `int*` | `void*` | `void* arg = &value;` (implícito) |
| `void*` | `int*` | `int* ptr = (int*)arg;` (explícito) |
| `struct*` | `void*` | `void* arg = &data;` (implícito) |
| `void*` | `struct*` | `Data* ptr = (Data*)arg;` (explícito) |
| `char[]` | `void*` | `void* arg = string;` (implícito) |
| `void*` | `char*` | `char* str = (char*)arg;` (explícito) |

### Regras Importantes

1. **Cast implícito TO void***: Qualquer ponteiro pode ser convertido para void* automaticamente
2. **Cast explícito FROM void***: Sempre necessário ao converter void* para tipo específico
3. **Preserve o tipo original**: O cast deve ser para o mesmo tipo que foi passado
4. **Cuidado com lifetime**: Não retorne endereços de variáveis locais

### Exemplo Prático Completo

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int input;
    int* output;  // Ponteiro para resultado
} ThreadData;

void* worker(void* arg) {
    // Cast de entrada: void* -> ThreadData*
    ThreadData* data = (ThreadData*)arg;
    
    // Processar
    int result = data->input * data->input;
    
    // Alocar resultado no heap
    data->output = malloc(sizeof(int));
    *data->output = result;
    
    // Retornar (cast implícito para void*)
    return data->output;
}

int main() {
    pthread_t thread;
    ThreadData data = {5, NULL};
    
    // Passar estrutura (cast implícito para void*)
    pthread_create(&thread, NULL, worker, &data);
    
    // Receber resultado
    void* retval;
    pthread_join(thread, &retval);
    
    // Cast de saída: void* -> int*
    int* result = (int*)retval;
    printf("5^2 = %d\n", *result);
    
    free(result);
    return 0;
}
```

## Exemplo Completo

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int input;
    int output;
} ThreadData;

void* process_data(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    
    // Processar
    data->output = data->input * 2;
    
    printf("Thread processou: %d -> %d\n", 
           data->input, data->output);
    
    return NULL;
}

int main() {
    const int NUM_THREADS = 3;
    pthread_t threads[NUM_THREADS];
    ThreadData data[NUM_THREADS];
    
    // Criar threads
    for (int i = 0; i < NUM_THREADS; i++) {
        data[i].input = i + 1;
        
        int ret = pthread_create(&threads[i], NULL, 
                                process_data, &data[i]);
        if (ret != 0) {
            fprintf(stderr, "Erro ao criar thread %d\n", i);
            exit(1);
        }
    }
    
    // Aguardar threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
        printf("Main: Thread %d retornou %d\n", 
               i, data[i].output);
    }
    
    return 0;
}
```