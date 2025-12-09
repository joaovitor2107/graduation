# Introdução a Threads

## Processos vs Threads

### Processos
- Unidade de execução independente com seu próprio espaço de endereçamento
- Isolamento completo entre processos
- Comunicação através de IPC (pipes, sockets, memória compartilhada)
- Maior overhead de criação e troca de contexto
- Maior uso de memória

### Threads
- Unidades de execução dentro de um processo
- Compartilham o mesmo espaço de endereçamento
- Comunicação direta através de memória compartilhada
- Menor overhead de criação e troca de contexto
- Menor uso de memória

## O que as Threads Compartilham

### Recursos Compartilhados:
- **Espaço de endereçamento**: Código, dados globais, heap
- **Descritores de arquivo**: Arquivos abertos, sockets
- **Sinais**: Handlers de sinais
- **Diretório de trabalho**
- **User e group IDs**

### Recursos Privativos de Cada Thread:
- **Stack**: Variáveis locais, parâmetros de função
- **Registradores**: Incluindo program counter e stack pointer
- **Thread ID**: Identificador único
- **Errno**: Variável de erro
- **Máscara de sinais**: Quais sinais estão bloqueados
- **Prioridade de escalonamento**

## Vantagens das Threads

1. **Performance**
   - Criação mais rápida que processos
   - Troca de contexto mais eficiente
   - Comunicação direta via memória

2. **Compartilhamento de Recursos**
   - Acesso direto a dados compartilhados
   - Sem necessidade de serialização/deserialização

3. **Responsividade**
   - Interface pode permanecer responsiva
   - Processamento em background

4. **Escalabilidade**
   - Aproveita múltiplos cores/processadores
   - Paralelismo real em sistemas multicore

## Desafios da Programação com Threads

1. **Sincronização**
   - Coordenar acesso a recursos compartilhados
   - Evitar condições de corrida (race conditions)

2. **Deadlocks**
   - Threads esperando umas pelas outras indefinidamente
   - Requer design cuidadoso

3. **Debugging**
   - Comportamento não-determinístico
   - Difícil reproduzir bugs

4. **Complexidade**
   - Raciocínio sobre execução concorrente
   - Gerenciamento de estado compartilhado

## Modelos de Threading

### 1. Boss/Worker (Master/Slave)
- Thread principal distribui trabalho
- Threads trabalhadoras processam tarefas
- Usado em servidores web, pools de threads

### 2. Pipeline
- Cada thread processa uma etapa
- Dados fluem de uma thread para outra
- Útil para processamento em estágios

### 3. Peer (Simétrico)
- Todas as threads são iguais
- Dividem trabalho igualmente

## POSIX Threads (pthreads)

### O que é pthreads?
- Padrão POSIX para threads (IEEE 1003.1c)
- API em C para criar e gerenciar threads
- Portabilidade entre sistemas Unix-like
- Suporte nativo no Linux

### Principais Características
- Threads de nível kernel (1:1)
- Escalonamento pelo sistema operacional
- Paralelismo real em multicore
- Biblioteca linkada com -pthread

## Conceitos de Paralelismo

### Concorrência vs Paralelismo
- **Concorrência**: Múltiplas tarefas em progresso
- **Paralelismo**: Múltiplas tarefas executando simultaneamente

### Speedup
- Razão entre tempo serial e tempo paralelo
- Speedup = T_serial / T_paralelo
- Ideal: Speedup linear (= número de threads)
- Real: Limitado por overhead e partes sequenciais

### Lei de Amdahl
- Speedup máximo limitado pela parte sequencial
- Se 10% do código é sequencial, speedup máximo é 10x
- Importante para entender limites do paralelismo

### Eficiência
- Eficiência = Speedup / Número_de_threads
- Mede quão bem os recursos são utilizados
- 100% = uso perfeito, < 100% = overhead

## Padrões Comuns

### Fork-Join
```
Main thread
    |
    | fork
   /|\
  / | \
 T1 T2 T3  (execução paralela)
  \ | /
   \|/
    | join
    |
Main thread continua
```

### Produtor-Consumidor
- Threads produtoras geram dados
- Threads consumidoras processam dados
- Requer sincronização (filas, buffers)

### Barrier
- Todas as threads esperam em um ponto
- Continuam quando todas chegam
- Útil para sincronização de fases

## Conversão de Tipos em Threads

### O Problema do void*

As funções pthread usam `void*` para serem genéricas, mas isso cria a necessidade de conversões explícitas:

```c
// Função de thread sempre recebe void* e retorna void*
void* thread_function(void* arg);
```

### Fluxo de Dados

```
   Main Thread                Thread Function
        |                           |
   Tipo original               void* arg
        |                           |
    Cast para void*          Cast para tipo original  
   (implícito)                 (explícito)
        |                           |
  pthread_create  --------->   Processar dados
        |                           |
        |                      Preparar retorno
        |                           |
        |                     Cast para void*
        |                       (implícito)  
        |                           |
  pthread_join    <---------    return valor
        |
   Cast de void*
   (explícito)
        |
   Tipo original
```

### Exemplo Prático

```c
// 1. Preparar dados na main
int data = 42;

// 2. Passar para thread (cast implícito int* -> void*)
pthread_create(&thread, NULL, func, &data);

// 3. Dentro da thread (cast explícito void* -> int*)
void* func(void* arg) {
    int* value = (int*)arg;  // CAST NECESSÁRIO
    // usar *value...
}
```