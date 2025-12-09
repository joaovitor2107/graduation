# Análise de Performance

## Medindo Tempo de Execução

### Comando time

```bash
time ./programa
```

Retorna três medidas:
- **real**: Tempo total (wall clock)
- **user**: Tempo de CPU em modo usuário
- **sys**: Tempo de CPU em modo kernel

#### Exemplo de Saída
```
real    0m2.543s
user    0m8.234s
sys     0m0.123s
```

#### Interpretação
- Se `user > real`: Paralelismo efetivo (múltiplos cores)
- Se `user ≈ real`: Execução principalmente serial
- Se `real >> user`: Programa esperando I/O ou sincronização

### Medindo no Código

#### Usando clock()
```c
#include <time.h>

clock_t start = clock();
// ... código a medir ...
clock_t end = clock();

double cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;
printf("Tempo: %.3f segundos\n", cpu_time);
```

#### Usando gettimeofday()
```c
#include <sys/time.h>

struct timeval start, end;

gettimeofday(&start, NULL);
// ... código a medir ...
gettimeofday(&end, NULL);

double elapsed = (end.tv_sec - start.tv_sec) + 
                 (end.tv_usec - start.tv_usec) / 1000000.0;
printf("Tempo: %.3f segundos\n", elapsed);
```

## Métricas de Performance

### Speedup

**Definição**: Razão entre tempo serial e tempo paralelo

```
Speedup = T_serial / T_paralelo
```

**Interpretação**:
- Speedup = 1: Sem melhoria
- Speedup = N: N vezes mais rápido
- Speedup > N threads: Super-linear (raro, geralmente cache)
- Speedup < 1: Piora de performance

### Eficiência

**Definição**: Quão bem os recursos são utilizados

```
Eficiência = Speedup / Número_de_threads
```

**Interpretação**:
- 100%: Uso perfeito dos recursos
- 50-80%: Bom uso, overhead aceitável
- < 50%: Overhead significativo ou gargalos

### Escalabilidade

**Forte (Strong Scaling)**: Problema fixo, aumenta threads
- Mede redução do tempo
- Limitada pela Lei de Amdahl

**Fraca (Weak Scaling)**: Problema cresce com threads
- Mantém trabalho/thread constante
- Ideal: tempo constante

## Lei de Amdahl

### Fórmula

```
Speedup_max = 1 / (S + P/N)
```

Onde:
- S = Fração serial (não parallelizável)
- P = Fração paralela (1 - S)
- N = Número de processadores/threads

### Exemplo

Se 10% do código é serial (S = 0.1):
- Com 2 threads: Speedup_max = 1.82x
- Com 4 threads: Speedup_max = 3.08x
- Com 8 threads: Speedup_max = 4.71x
- Com ∞ threads: Speedup_max = 10x

## Identificando Gargalos

### 1. Overhead de Criação de Threads

**Sintomas**:
- Performance pior com muitas threads pequenas
- Tempo real > tempo de processamento

**Teste**:
```bash
# Varie o tamanho da entrada
for size in 10 100 1000 10000; do
    echo "Tamanho: $size"
    time ./programa input_${size}.data
done
```

### 2. Contenção de Recursos

**Sintomas**:
- Speedup satura rapidamente
- Alto tempo de sistema (sys)

**Teste**:
```bash
# Varie número de threads
for threads in 1 2 4 8 16; do
    echo "Threads: $threads"
    time ./programa input.data $threads
done
```

### 3. Desbalanceamento de Carga

**Sintomas**:
- Algumas threads terminam muito antes
- Eficiência baixa

**Diagnóstico**:
```c
// Adicione timing por thread
void* worker(void* arg) {
    clock_t start = clock();
    // ... trabalho ...
    clock_t end = clock();
    printf("Thread %d: %.3fs\n", id, 
           ((double)(end-start))/CLOCKS_PER_SEC);
}
```

### 4. False Sharing

**Sintomas**:
- Performance pior que serial
- Alto tráfego de cache

**Solução**:
```c
// Evite estruturas compactas
struct alignas(64) ThreadData {  // Alinha com linha de cache
    int value;
    char padding[60];  // Evita false sharing
};
```

## Experimentos Sistemáticos

### Script de Benchmark

```bash
#!/bin/bash

# benchmark.sh
echo "Threads,Iteracoes,Tempo,Speedup"

# Programa de teste que aceita número de threads e iterações
for iterations in 1000 10000 100000 1000000; do
    # Tempo serial (baseline) - 1 thread
    serial_time=$(./benchmark_program 1 $iterations 2>&1 | 
                  grep "Tempo" | awk '{print $2}')
    
    for threads in 1 2 4 8; do
        # Tempo paralelo
        par_time=$(./benchmark_program $threads $iterations 2>&1 | 
                   grep "Tempo" | awk '{print $2}')
        
        # Calcular speedup
        speedup=$(echo "scale=2; $serial_time / $par_time" | bc)
        
        echo "$threads,$iterations,$par_time,$speedup"
    done
done
```

### Visualização (Python)

```python
import matplotlib.pyplot as plt
import pandas as pd

# Ler dados
df = pd.read_csv('benchmark.csv')

# Gráfico de speedup
for iterations in df['Iteracoes'].unique():
    data = df[df['Iteracoes'] == iterations]
    plt.plot(data['Threads'], data['Speedup'], 
             marker='o', label=f'{iterations} iter')

plt.xlabel('Número de Threads')
plt.ylabel('Speedup')
plt.legend()
plt.grid(True)
plt.show()
```

## Profiling

### gprof

```bash
# Compilar com profiling
gcc -pg -pthread programa.c -o programa

# Executar
./programa

# Analisar
gprof programa gmon.out > analise.txt
```

### perf

```bash
# Gravar execução
perf record ./programa

# Analisar
perf report

# Estatísticas
perf stat ./programa
```

## Otimizações Comuns

### 1. Granularidade Adequada

```c
// Ruim: trabalho muito pequeno
for (int i = 0; i < 1000000; i++) {
    create_thread_for_one_item(i);
}

// Bom: chunks de trabalho
int chunk_size = total_work / num_threads;
for (int i = 0; i < num_threads; i++) {
    create_thread_for_chunk(i * chunk_size, chunk_size);
}
```

### 2. Minimizar Sincronização

```c
// Ruim: sincronização frequente
for (int i = start; i < end; i++) {
    pthread_mutex_lock(&mutex);
    shared_counter++;
    pthread_mutex_unlock(&mutex);
}

// Bom: acumular localmente
int local_count = 0;
for (int i = start; i < end; i++) {
    local_count++;
}
pthread_mutex_lock(&mutex);
shared_counter += local_count;
pthread_mutex_unlock(&mutex);
```

### 3. Localidade de Cache

```c
// Ruim: acesso aleatório
for (int i = 0; i < n; i++) {
    process(data[random_index()]);
}

// Bom: acesso sequencial
for (int i = start; i < end; i++) {
    process(data[i]);
}
```
