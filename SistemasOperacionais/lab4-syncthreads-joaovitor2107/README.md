[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/SSfoVwUH)
[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-2972f46106e565e64193e422d61a12cf1da4916b45550586e14ef0a7c637dd04.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=20585497)
# Lab 4: Sincronização de Threads

## Visão Geral
Laboratório focado em mecanismos de sincronização para coordenação entre threads: **mutex**, **variáveis de condição** e **semáforos**.

## Objetivos
- Aplicar exclusão mútua com mutex em recursos compartilhados
- Implementar comunicação entre threads com variáveis de condição
- Resolver problemas clássicos: produtor-consumidor e leitores-escritores
- Identificar e prevenir condições de corrida

## Estrutura
```
lab4-syncthreads/
├── src/                      # Códigos-fonte
│   ├── ex1_contador_mutex.c    # Contador com mutex
│   ├── ex2_pedidos_prodcons.c  # Produtor-consumidor
│   └── ex3_cache_leitores_escritores.c # Leitores-escritores
├── docs/                     # Documentação
│   └── sync_reference.md    # Referência rápida de sincronização
├── EXERCICIOS.md            # Descrição detalhada dos exercícios
└── RELATORIO_TEMPLATE.md   # Template para relatório
```

## Compilação
```bash
# Compilar exercícios (apos resolucao)
gcc -pthread src/ex1_contador_mutex.c -o ex1
gcc -pthread src/ex2_pedidos_prodcons.c -o ex2
gcc -pthread src/ex3_cache_leitores_escritores.c -o ex3

# Executar
./ex1
./ex2
./ex3
```

## Dicas Importantes

### Mutex
- Sempre destravar após travar: `pthread_mutex_lock()` → seção crítica → `pthread_mutex_unlock()`
- Evite esquecer de destravar em caminhos de erro
- Inicialize com `pthread_mutex_init()` ou `PTHREAD_MUTEX_INITIALIZER`

### Variáveis de Condição
- Use sempre com mutex associado
- Espera em loop: `while(condição) pthread_cond_wait(&cond, &mutex)`
- `signal` acorda uma thread, `broadcast` acorda todas

### Semáforos
- `sem_wait()` decrementa (bloqueia se 0)
- `sem_post()` incrementa (libera threads esperando)
- Útil para controlar número de recursos disponíveis

## Exercícios
1. **Contador com Mutex**: Sistema de likes em rede social
2. **Produtor-Consumidor**: Processamento de pedidos online
3. **Leitores-Escritores**: Cache de dados compartilhado

Consulte `EXERCICIOS.md` para descrições completas.