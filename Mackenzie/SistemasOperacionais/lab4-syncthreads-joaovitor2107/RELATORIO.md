# Relatório - Lab 4: Sincronização de Threads

**Nome:** [Seu nome]  
**Data:** [Data de entrega]

## Exercício 1: Contador com Mutex

### Implementação
- [x] Mutex inicializado corretamente
- [x] Lock/unlock implementados na função incrementar_likes
- [x] Mutex destruído ao final

### Resultados Observados
**Com Mutex:**
- Valor final: 100000
- Tempo de execução: 0.044858

**Sem Mutex:**
- Valor final: 92929
- Diferença observada: 7071

### Análise
Descreva o comportamento observado e explique por que o mutex é necessário:

O mutex é necessário quando duas (ou mais) threads utilizam da mesma variavel, pois com ele conseguimos garantir que ambas não vão a alterar simultaneamente.

## Exercício 2: Produtor-Consumidor

### Implementação
- [x] Mutex e variáveis de condição inicializados
- [x] Função adicionar_pedido com sincronização
- [x] Função processar_pedido com sincronização
- [x] While loops corretos com pthread_cond_wait
- [x] Estruturas destruídas ao final

### Resultados Observados
- Total de pedidos produzidos: 15
- Total de pedidos consumidos: 15
- Situações de buffer cheio observadas: 2
- Situações de buffer vazio observadas: 4

### Análise
Como as variáveis de condição melhoram a eficiência comparado a busy-waiting?

Com variáveis de condição o programa tem um uso mais eficiente da CPU, quando não conseguimos fazer a operação solicitada pausamos a thread, e realizamos outra operação até a thread ter como realizar aquela, assim não temos a CPU sendo gasta com ociosidade.

## Exercício 3: Leitores-Escritores

### Implementação
- [x] Semáforo e mutex inicializados
- [x] Controle de leitores implementado
- [x] Controle de escritores implementado
- [x] Primeiro/último leitor gerencia semáforo
- [x] Estruturas destruídas ao final

### Resultados Observados
- Máximo de leitores simultâneos observado: 5
- Tempo médio de espera dos escritores: 0.002463
- Ocorrências de starvation: 1 

### Análise
A solução implementada favorece leitores ou escritores? Justifique:

Favorece leitores, sempre que tivermos um leitor para ler ele vai ter prioridade sobre o leitor, pois temos que quando iniciamos o primeiro leitor ativo ele pausa o semaforo do escritor e so libera quando todos leitores tiverem lido. Por exemplo temos aqui um caso que para o escritor 1 conseguir escrever ele tem que esperar 5 leitores terminarem. 
