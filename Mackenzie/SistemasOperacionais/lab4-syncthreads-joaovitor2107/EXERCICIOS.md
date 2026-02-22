# Exercícios - Lab 4: Sincronização de Threads

## Exercício 1: Contador Compartilhado com Mutex

### Contexto
Você está desenvolvendo um sistema de likes para uma rede social. Múltiplas threads representam usuários clicando simultaneamente no botão de like de uma publicação.

### Problema
Sem sincronização adequada, o contador de likes pode apresentar valores incorretos devido a condições de corrida quando múltiplas threads tentam incrementá-lo simultaneamente.

### Objetivos
- Implementar um contador thread-safe usando mutex
- Demonstrar a diferença entre acesso com e sem sincronização
- Verificar a consistência do valor final

### Tarefas
1. Complete a função `incrementar_likes()` usando mutex para proteger o acesso ao contador
2. Implemente versão sem mutex para comparação
3. Execute com diferentes números de threads (10, 100, 1000) e observe os resultados
4. Analise o impacto no desempenho

### Dicas de Implementação
- Use `pthread_mutex_lock()` antes de acessar o contador
- Não esqueça `pthread_mutex_unlock()` após a operação
- Incremente o contador múltiplas vezes por thread para aumentar probabilidade de condição de corrida
- Compare tempo de execução com e sem mutex

---

## Exercício 2: Sistema de Pedidos Online (Produtor-Consumidor)

### Contexto
Um e-commerce precisa processar pedidos de clientes. Threads produtoras representam clientes fazendo pedidos, enquanto threads consumidoras representam o sistema processando esses pedidos.

### Problema
Implementar um buffer circular thread-safe que armazena pedidos. Produtores devem esperar quando o buffer está cheio, e consumidores devem esperar quando está vazio.

### Objetivos
- Implementar buffer circular com capacidade limitada
- Usar variáveis de condição para sincronização sem busy-waiting
- Garantir que nenhum pedido seja perdido ou processado duplicadamente

### Tarefas
1. Complete a função `adicionar_pedido()` com sincronização adequada
2. Complete a função `processar_pedido()` com sincronização adequada
3. Use `pthread_cond_wait()` quando buffer cheio/vazio
4. Use `pthread_cond_signal()` para acordar threads esperando
5. Teste com diferentes proporções de produtores/consumidores

### Dicas de Implementação
- Padrão para espera: `while(buffer_cheio) pthread_cond_wait(&cond_nao_cheio, &mutex)`
- Sempre use `while` ao invés de `if` com `pthread_cond_wait()`
- Sinalize após inserir/remover item do buffer
- Considere usar duas variáveis de condição: uma para cheio, outra para vazio

---

## Exercício 3: Cache de Dados (Leitores-Escritores)

### Contexto
Um sistema de cache permite que múltiplos processos leiam dados simultaneamente, mas apenas um processo pode escrever por vez. Este é um cenário comum em bancos de dados e sistemas de arquivos.

### Problema
Implementar sincronização que permite múltiplos leitores simultâneos, mas garante exclusão mútua para escritores. Leitores não devem bloquear outros leitores, mas escritores devem ter acesso exclusivo.

### Objetivos
- Permitir leitura concorrente por múltiplas threads
- Garantir escrita exclusiva
- Evitar starvation de escritores
- Implementar solução com preferência para leitores

### Tarefas
1. Complete `iniciar_leitura()` e `terminar_leitura()` com controle de leitores ativos
2. Complete `iniciar_escrita()` e `terminar_escrita()` com exclusão mútua
3. Use semáforo para controlar acesso ao recurso
4. Use mutex para proteger contador de leitores
5. Teste com diferentes proporções de leitores/escritores

### Dicas de Implementação
- Primeiro leitor bloqueia escritores com `sem_wait()`
- Último leitor libera escritores com `sem_post()`
- Use contador para rastrear número de leitores ativos
- Proteja contador de leitores com mutex separado
- Escritores sempre fazem `sem_wait()` e `sem_post()`

---

## Observações Gerais

### Testando Seus Programas
- Execute múltiplas vezes - bugs de sincronização podem ser intermitentes
- Varie o número de threads para estressar o sistema

### Erros Comuns
1. **Deadlock**: threads esperando umas pelas outras indefinidamente
2. **Condição de corrida**: resultado depende da ordem de execução
3. **Starvation**: algumas threads nunca conseguem executar
4. **Esquecer unlock**: deixar mutex travado permanentemente

### Métricas para Análise
- Corretude: resultado final está correto?
- Desempenho: qual o impacto da sincronização?
- Fairness: todas as threads têm chance de executar?
- Escalabilidade: como fica o comportamento com muitas threads?