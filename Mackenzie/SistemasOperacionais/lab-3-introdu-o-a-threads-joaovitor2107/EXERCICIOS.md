# Exercícios - Laboratório de Threads

## Parte 1: Fundamentos de Threads

### Exercício 1: Hello Thread

**Objetivo**: Criar sua primeira thread usando pthread_create.

**Arquivo**: `src/ex1_hello_thread.c`

**Descrição**: 
Implemente um programa que cria uma thread para imprimir "Hello from thread!". A thread principal deve imprimir "Hello from main!" e criar a thread filha.

**Tarefas**:
1. Implemente a função `print_hello` que será executada pela thread
2. Use `pthread_create` para criar a thread
3. Observe o comportamento sem sincronização

**Compilação e Execução**:
```bash
make ex1
./ex1_hello_thread
```

**Questões para Análise**:
- O que acontece se você executar o programa várias vezes?
- A ordem das mensagens é sempre a mesma?
- Por que isso ocorre?

---

### Exercício 2: Sincronização com pthread_join

**Objetivo**: Aprender a sincronizar threads usando pthread_join.

**Arquivo**: `src/ex2_hello_join.c`

**Descrição**:
Modifique o exercício anterior para garantir que a thread principal espere a thread filha terminar antes de encerrar o programa.

**Tarefas**:
1. Adicione `pthread_join` após criar a thread
2. Compare o comportamento com o exercício anterior
3. Entenda por que pthread_join é importante

**Compilação e Execução**:
```bash
make ex2
./ex2_hello_join
```

**Questões para Análise**:
- Qual a diferença no comportamento comparado ao exercício 1?
- O que pthread_join está fazendo?
- O que aconteceria sem pthread_join em um programa maior?

---

### Exercício 3: Múltiplas Threads

**Objetivo**: Gerenciar múltiplas threads simultaneamente.

**Arquivo**: `src/ex3_multiple_threads.c`

**Descrição**:
Crie um programa que lança N threads (definido por uma constante), onde cada thread imprime seu ID único.

**Tarefas**:
1. Defina `NUM_THREADS` como 5
2. Crie um array de `pthread_t` para armazenar os IDs das threads
3. Use um loop para criar todas as threads
4. Use outro loop para fazer join em todas as threads
5. Cada thread deve imprimir seu número de identificação

**Compilação e Execução**:
```bash
make ex3
./ex3_multiple_threads
```

**Questões para Análise**:
- A ordem de execução das threads é determinística?
- Como você garantiria uma ordem específica de execução?
- O que acontece se aumentar NUM_THREADS para 100 ou 1000?

---

## Parte 2: Comunicação entre Threads

### Exercício 4: Passagem de Argumentos

**Objetivo**: Passar argumentos únicos para cada thread corretamente.

**Arquivo**: `src/ex4_thread_args.c`

**Descrição**:
Aprenda a passar argumentos individuais para cada thread. Cada thread deve receber um ID único e realizar algum processamento baseado nesse ID.

**Tarefas**:
1. Declare um array para armazenar os argumentos de cada thread
2. Inicialize cada elemento com um valor único (1 a NUM_THREADS)
3. Passe o endereço de cada elemento para sua respectiva thread
4. Dentro da thread, converta o void* para int* e use o valor
5. Faça cada thread imprimir seu ID e realizar algum cálculo simples

**Compilação e Execução**:
```bash
make ex4
./ex4_thread_args
```

**Questões para Análise**:
- Por que precisamos de um array para armazenar os argumentos?
- O que aconteceria se usássemos uma única variável para todas as threads?
- Como o cast de void* para int* funciona?

---

### Exercício 5: Passando Estruturas

**Objetivo**: Passar dados complexos para threads usando estruturas.

**Arquivo**: `src/ex5_struct_args.c`

**Descrição**:
Crie uma estrutura com múltiplos campos e passe para cada thread. Cada thread deve processar seus dados únicos.

**Tarefas**:
1. Defina uma estrutura `thread_data` com campos: id, name, value
2. Aloque memória para cada estrutura
3. Inicialize com dados únicos para cada thread
4. Passe as estruturas para as threads
5. Libere a memória apropriadamente

**Compilação e Execução**:
```bash
make ex5
./ex5_struct_args
```

**Questões para Análise**:
- Por que usamos alocação dinâmica para as estruturas?
- O que aconteceria se usássemos variáveis locais?
- Quando é seguro liberar a memória?

---

### Exercício 6: Valores de Retorno

**Objetivo**: Obter valores de retorno das threads.

**Arquivo**: `src/ex6_return_value.c`

**Descrição**:
Implemente threads que calculam valores e retornam resultados para a thread principal.

**Tarefas**:
1. Cada thread calcula o quadrado de seu ID
2. Aloque memória para o resultado no heap
3. Retorne o ponteiro para o resultado
4. A thread principal coleta e imprime todos os resultados
5. Libere a memória apropriadamente

**Compilação e Execução**:
```bash
make ex6
./ex6_return_value
```

**Questões para Análise**:
- Por que o resultado deve ser alocado no heap? Porque obtemos ele por meio do endereço de memória dele, se ele existisse na stack, assim que a função em que ele esta acabasse ele poderia ser sobescrito.
- O que aconteceria se retornássemos endereço de variável local? O comportamento iria ser indefinido, assim que a função acabasse a memoria dessa variavel poderia ser sobescrita e teriamos como retorno valores aleatorios.
- Como pthread_join obtém o valor de retorno? Ele permite que a thread principal acessa dados criados pela thread filha, nesse caso ela adciona o valor retornado pela função no segundo paramatro.

---

## Parte 3: Análise e Reflexão

## Questões de Reflexão

1. **Sincronização**: Por que pthread_join é necessário?

2. **Passagem de Argumentos**: Qual a diferença entre passar valores e ponteiros?

3. **Compartilhamento de Memória**: O que as threads compartilham e o que é privativo?

4. **Ordem de Execução**: Por que a ordem de execução das threads é não-determinística?

5. **Alocação de Memória**: Por que devemos alocar no heap para retornar valores?

6. **Aplicabilidade**: Quando vale a pena usar threads em vez de processos?

---

## Entrega

1. Complete todos os exercícios (1-6)
2. Preencha o relatório com suas observações e análises
3. Documente problemas encontrados e soluções
