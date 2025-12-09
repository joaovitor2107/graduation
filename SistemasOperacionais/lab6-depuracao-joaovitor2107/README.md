[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/iPbA-B1-)
[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-2972f46106e565e64193e422d61a12cf1da4916b45550586e14ef0a7c637dd04.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=21326395)
# Lab 6: Depuração e Análise de Vazamento de Memória

**Disciplina**: Sistemas Operacionais
**Professor**: Lucas Cerqueira Figueiredo
**Semestre**: 2º/2025

## Visão Geral

Laboratório focado no uso de ferramentas de depuração e análise de vazamento de memória em programas C, com ênfase no **Valgrind**. Este laboratório é essencial para desenvolver habilidades de detecção e correção de problemas de memória, críticos no contexto de sistemas operacionais.

## Ambiente de Desenvolvimento

**IMPORTANTE**: Este laboratório deve ser realizado utilizando o **GitHub Codespaces**, que fornece um ambiente de desenvolvimento completo na nuvem, com todas as ferramentas necessárias (gcc, Valgrind, git) já instaladas e configuradas.

### Como acessar o Codespaces

1. Acesse seu repositório no GitHub
2. Clique em **Code** > **Codespaces** > **Create codespace on main**
3. Aguarde a inicialização do ambiente (pode levar alguns minutos na primeira vez)
4. Use o terminal integrado para compilar e executar os programas
5. Faça commits e push diretamente do Codespaces

**Não é necessário instalar nada localmente!**

## Objetivos

- Compreender os principais problemas de memória em C (vazamentos, acessos inválidos, etc.)

- Aprender a usar o Valgrind para detecção de problemas de memória

- Interpretar relatórios do Valgrind

- Corrigir problemas de gerenciamento de memória

- Relacionar estes conceitos com o contexto de sistemas operacionais

## Material de Estudo

Consulte os seguintes arquivos para o conteúdo teórico completo:

- `LISTA_DEPURACAO.pdf` - Documento principal com breve teoria e exercícios

## Fundamentos

### Problemas Comuns de Memória

1. **Vazamento de Memória (Memory Leak)**: Memória alocada mas não liberada

2. **Acesso Inválido (Invalid Access)**: Leitura/escrita fora dos limites

3. **Liberação Dupla (Double Free)**: Liberar a mesma memória mais de uma vez

4. **Uso Após Liberação (Use-After-Free)**: Usar memória já liberada

5. **Uso de Variáveis Não Inicializadas**: Usar valores sem inicialização

### Valgrind - Uso Básico

No GitHub Codespaces, o Valgrind já está instalado e pronto para uso. Para utilizá-lo:

```bash
# Compilar com flags de depuração
gcc -g programa.c -o programa

# Executar com Valgrind
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./programa
```

**Principais opções**:

- `--leak-check=full`: Detalhamento completo dos vazamentos

- `--show-leak-kinds=all`: Mostra todos os tipos de vazamento

- `--track-origins=yes`: Rastreia a origem de valores não inicializados

## Estrutura do Repositório

```
lab6-depuracao/
├── README.md                      # Este arquivo
├── LISTA_DEPURACAO.pdf           # Material teórico completo
├── depuracao.tex                  # Fonte LaTeX
├── .gitignore                     # Arquivos a ignorar
└── exercicios/
    ├── ex1_memory_leak/
    │   ├── original.c             # Código com problema
    │   ├── corrigido.c            # Código corrigido (sua solução)
    │   ├── valgrind_original.txt  # Saída do Valgrind (código original)
    │   └── valgrind_corrigido.txt # Saída do Valgrind (código corrigido)
    ├── ex2_uninitialized/
    │   ├── original.c
    │   ├── corrigido.c
    │   ├── valgrind_original.txt
    │   └── valgrind_corrigido.txt
    ├── ex3_buffer_overflow/
    │   ├── original.c
    │   ├── corrigido.c
    │   ├── valgrind_original.txt
    │   └── valgrind_corrigido.txt
    ├── ex4_double_free/
    │   ├── original.c
    │   ├── corrigido.c
    │   ├── valgrind_original.txt
    │   └── valgrind_corrigido.txt
    ├── ex5_use_after_free/
    │   ├── original.c
    │   ├── corrigido.c
    │   ├── valgrind_original.txt
    │   └── valgrind_corrigido.txt
    └── ex6_linked_list/
        ├── original.c
        ├── corrigido.c
        ├── valgrind_original.txt
        └── valgrind_corrigido.txt
```

## Exercícios

### Exercício 1: Vazamento de Memória

**Problema**: Função aloca memória mas não a libera

**Contexto SO**: Similar a drivers de dispositivo que não liberam memória de operações de E/S

### Exercício 2: Memória Não Inicializada

**Problema**: Uso de valores em array não inicializado

**Contexto SO**: Pode revelar dados de outros processos (violação de segurança)

### Exercício 3: Buffer Overflow

**Problema**: Acesso fora dos limites do array alocado

**Contexto SO**: Vulnerabilidade comum que pode levar a exploits

### Exercício 4: Liberação Dupla

**Problema**: Tentativa de liberar a mesma memória duas vezes

**Contexto SO**: Pode corromper estruturas do gerenciador de memória

### Exercício 5: Use-After-Free

**Problema**: Uso de ponteiro após a memória ter sido liberada

**Contexto SO**: Comum em drivers e pode causar comportamentos imprevisíveis

### Exercício 6: Lista Ligada

**Problema**: Implementar função para liberar corretamente toda uma lista ligada

**Contexto SO**: Estruturas fundamentais em kernels (tabelas de processos, filas de E/S)

## Workflow de Resolução

Para cada exercício, siga este workflow:

### 1. Analisar o Código Original
```bash
cd exercicios/ex1_memory_leak
cat original.c
```

### 2. Compilar e Executar com Valgrind
```bash
gcc -g original.c -o original
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./original > valgrind_original.txt 2>&1
```

### 3. Analisar o Relatório
```bash
cat valgrind_original.txt
# Identifique: quantos bytes vazados? em quantos blocos? qual linha do código?
```

### 4. Corrigir o Código
```bash
# Copie original.c para corrigido.c e faça as correções
cp original.c corrigido.c
nano corrigido.c  # ou seu editor preferido
```

### 5. Verificar a Correção
```bash
gcc -g corrigido.c -o corrigido
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./corrigido > valgrind_corrigido.txt 2>&1
cat valgrind_corrigido.txt
# Verifique: "All heap blocks were freed -- no leaks are possible"
```

### 6. Fazer Commit das Alterações
```bash
git add exercicios/ex1_memory_leak/
git commit -m "Resolve exercício 1: corrige vazamento de memória"
```

## Entrega via GitHub

### Formato de Entrega

**IMPORTANTE**: A entrega deste laboratório é feita exclusivamente via GitHub.

Para cada exercício, você deve incluir no repositório:
1. `original.c` - Código fornecido com o problema
2. `corrigido.c` - Sua solução corrigida
3. `valgrind_original.txt` - Saída completa do Valgrind para o código original
4. `valgrind_corrigido.txt` - Saída completa do Valgrind para o código corrigido

### Instruções de Entrega

1. **Abra o GitHub Codespaces**:
   - Acesse seu repositório no GitHub
   - Clique em **Code** > **Codespaces** > **Create codespace on main**
   - O ambiente será configurado automaticamente

2. **Verifique a branch de trabalho** (normalmente você já estará na branch correta):
   ```bash
   git branch  # Verifica em qual branch você está
   ```

3. **Resolva os exercícios** seguindo o workflow descrito acima

4. **Faça commits incrementais**:
   ```bash
   # Após completar cada exercício
   git add exercicios/ex1_memory_leak/
   git commit -m "Resolve exercício 1: vazamento de memória"

   git add exercicios/ex2_uninitialized/
   git commit -m "Resolve exercício 2: memória não inicializada"
   # ... e assim por diante
   ```

5. **Push para o GitHub**:
   ```bash
   git push
   ```

6. **Verificação Final**: Acesse o GitHub e confirme que todos os arquivos foram enviados corretamente

### Dicas Importantes

- Sempre compile com `-g` para obter informações de debug

- Leia **toda** a saída do Valgrind, não apenas o sumário

- Para cada `malloc()` deve haver um `free()` correspondente

- Após `free(ptr)`, faça `ptr = NULL` para evitar uso acidental

- Verifique limites de arrays antes de acessá-los

- Sempre inicialize variáveis antes de usá-las

## Boas Práticas de Gerenciamento de Memória

1. **Sempre inicialize variáveis** antes de usá-las

2. **Para cada malloc(), deve haver um free()** correspondente

3. **Verifique o retorno de malloc()** para garantir sucesso na alocação

4. **Use NULL após liberar**:
   ```c
   free(ptr);
   ptr = NULL;
   ```

5. **Verifique os limites de arrays** antes de acessá-los

6. **Compile com flags de depuração** (`-g`) para relatórios detalhados

## Interpretando a Saída do Valgrind

### Tipos de Vazamento

- **Definitivamente perdido**: Memória não liberada e sem referência (ERRO GRAVE)

- **Indiretamente perdido**: Perdido devido a outro vazamento

- **Possivelmente perdido**: Valgrind não tem certeza se há referência

- **Ainda acessível**: Memória não liberada, mas ainda referenciada

### Exemplo de Saída Ideal

```
==12345== HEAP SUMMARY:
==12345==     in use at exit: 0 bytes in 0 blocks
==12345==   total heap usage: 5 allocs, 5 frees, 200 bytes allocated
==12345==
==12345== All heap blocks were freed -- no leaks are possible
```

## Recursos Adicionais

- [Documentação oficial do Valgrind](http://valgrind.org/)

- TANENBAUM, A. S. *Sistemas Operacionais Modernos*. 3ª ed. Pearson, 2010

- SILBERSCHATZ, A., GALVIN, P.B, GAGNE, G. *Fundamentos de Sistemas Operacionais*. 8ª ed. LTC, 2010

- ARPACI-DUSSEAU, R. H.; ARPACI-DUSSEAU, A. C. *Operating Systems: Three Easy Pieces*

## Dúvidas

Em caso de dúvidas:

1. Consulte o PDF `LISTA_DEPURACAO.pdf`

2. Revise os exemplos de saída do Valgrind

3. Entre em contato com o professor
