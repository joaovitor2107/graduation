[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/9-T2u9XJ)
[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-2972f46106e565e64193e422d61a12cf1da4916b45550586e14ef0a7c637dd04.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=20544390)
# Lab 3: Introdução a Threads com pthreads

## Visão Geral

Este laboratório introduz programação paralela usando a biblioteca POSIX threads (pthreads). Você aprenderá conceitos fundamentais de criação e gerenciamento de threads e comunicação entre threads.

## Objetivos

- Compreender a diferença entre processos e threads
- Dominar as operações básicas da API pthreads
- Implementar programas multi-thread corretos
- Comunicação e sincronização entre threads
- Passagem de argumentos e retorno de valores

## Estrutura do Projeto

```
lab3-introthreads/
├── README.md               # Este arquivo
├── EXERCICIOS.md          # Instruções detalhadas dos exercícios
├── RELATORIO_TEMPLATE.md  # Template para o relatório
├── Makefile               # Sistema de compilação
├── src/                   # Código-fonte dos exercícios
│   ├── ex1_hello_thread.c      # Criação básica de thread
│   ├── ex2_hello_join.c        # Sincronização com pthread_join
│   ├── ex3_multiple_threads.c  # Múltiplas threads
│   ├── ex4_thread_args.c       # Passagem de argumentos
│   ├── ex5_struct_args.c       # Estruturas como argumentos
│   └── ex6_return_value.c      # Valores de retorno
├── docs/                  # Documentação adicional
│   ├── introducao_threads.md   # Conceitos teóricos
│   ├── guia_compilacao.md      # Como compilar programas pthread
│   ├── pthread_reference.md    # Referência rápida da API
│   └── analise_performance.md  # Guia de análise de desempenho
└── traces/                # Saídas e análises
    └── README.md         # Instruções para traces
```

## Quick Start

### 1. Configuração Inicial

```bash
# Clone o repositório
git clone <url-do-repositorio>
cd lab3-introthreads

# Compile todos os exercícios
make all

# Ou compile um exercício específico
make ex1
```

### 2. Executando os Exercícios

```bash
# Exercícios básicos (Parte 1)
./ex1_hello_thread
./ex2_hello_join
./ex3_multiple_threads

# Exercícios de comunicação (Parte 2)
./ex4_thread_args
./ex5_struct_args
./ex6_return_value
```


## Requisitos

- **Sistema Operacional**: Linux/Unix (ou WSL no Windows)
- **Compilador**: GCC com suporte a pthreads
- **Make**: Para compilação automatizada

## Documentação

- [Instruções Detalhadas dos Exercícios](EXERCICIOS.md)
- [Introdução a Threads](docs/introducao_threads.md)
- [Guia de Compilação](docs/guia_compilacao.md)
- [Referência da API pthread](docs/pthread_reference.md)
- [Análise de Performance](docs/analise_performance.md)

## Compilação Manual

Se preferir compilar manualmente sem o Makefile:

```bash
# Para exercícios simples
gcc -pthread -o ex1_hello_thread src/ex1_hello_thread.c
```

## Dicas Importantes

1. **Sempre use -pthread**: Tanto para compilação quanto para linking
2. **Verifique retornos**: Funções pthread retornam códigos de erro
3. **Evite compartilhamento desnecessário**: Minimize o uso de variáveis globais
4. **Teste com diferentes configurações**: Varie o número de threads
5. **Documente seu código**: Explique a lógica de sincronização

## Problemas Comuns

- **Erro de linking**: Esqueceu de adicionar `-pthread`
- **Segmentation fault**: Provável acesso incorreto a ponteiros em threads
- **Threads não terminam**: Esqueceu pthread_join
- **Valores incorretos**: Passagem incorreta de argumentos

## Avaliação

Complete todos os exercícios e preencha o [template de relatório](RELATORIO_TEMPLATE.md) com suas análises e observações. O relatório deve incluir:

- Implementação de todos os exercícios
- Observações sobre comportamento das threads
- Análise de sincronização
- Reflexões sobre programação paralela

## Ajuda e Recursos

- `man pthread_create` - Manual das funções pthread
- [POSIX Threads Programming](https://computing.llnl.gov/tutorials/pthreads/)
- Consulte os arquivos em `docs/` para guias específicos

## Limpeza

```bash
# Remove todos os executáveis e arquivos temporários
make clean
```