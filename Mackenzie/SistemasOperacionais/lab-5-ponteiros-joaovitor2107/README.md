[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/RA-zW2gy)
[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-2972f46106e565e64193e422d61a12cf1da4916b45550586e14ef0a7c637dd04.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=20990085)
# Lab 5: Revisão de Ponteiros

## Visão Geral
Laboratório focado em conceitos fundamentais de **ponteiros em C**: manipulação de memória, aritmética de ponteiros, alocação dinâmica e passagem por referência.

## Objetivos
- Entender o conceito de ponteiros e endereços de memória
- Praticar aritmética de ponteiros e manipulação de arrays
- Implementar funções usando passagem por referência
- Trabalhar com alocação dinâmica de memória (malloc/free)
- Manipular strings usando ponteiros

## Exercícios
Consulte o arquivo `RevisaoPonteiros.pdf` para descrições completas dos exercícios.

## Compilação
```bash
# Compilar exercícios (após resolução)
gcc src/ex1_swap.c -o ex1
gcc src/ex2_strcpy.c -o ex2
gcc src/ex3_vetordinamico.c -o ex3
gcc src/ex4_matrizdinamica.c -o ex4
gcc src/ex5_listaligada.c -o ex5

# Executar
./ex1
./ex2
./ex3
./ex4
./ex5
```

## Conceitos Importantes

### Ponteiros Básicos
- **Declaração**: `int *ptr;` - ponteiro para inteiro
- **Endereço**: `&variavel` - obtém o endereço de uma variável
- **Desreferenciação**: `*ptr` - acessa o valor apontado
- **NULL**: ponteiro que não aponta para nada válido

### Aritmética de Ponteiros
- `ptr + 1` avança para o próximo elemento (não necessariamente +1 byte)
- `ptr++` incrementa o ponteiro
- `ptr - outro_ptr` calcula distância entre ponteiros
- Funciona automaticamente com o tipo do ponteiro

### Ponteiros e Arrays
- Nome do array é um ponteiro para o primeiro elemento
- `arr[i]` é equivalente a `*(arr + i)`
- Pode-se usar aritmética de ponteiros para navegar arrays

### Ponteiros e Strings
- Strings em C são arrays de `char` terminados com `'\0'`
- `const char *str` - ponteiro para string constante
- Strings literais não devem ser modificadas

### Alocação Dinâmica
- `malloc(tamanho)` - aloca memória na heap
- `free(ptr)` - libera memória alocada
- Sempre verificar se `malloc` retornou `NULL`
- Sempre liberar memória alocada (evitar memory leak)

### Ponteiros para Ponteiros
- `int **pptr` - ponteiro para ponteiro
- Usado para matrizes dinâmicas e funções que modificam ponteiros
- Requer desreferenciação dupla: `**pptr`

## Dicas Importantes

### Erros Comuns
- **Ponteiro não inicializado**: sempre inicialize ponteiros ou use NULL
- **Dangling pointer**: não use ponteiro após `free()`
- **Memory leak**: sempre libere memória alocada
- **Buffer overflow**: respeite limites de arrays
- **Esquecer `\0`**: strings devem terminar com caractere nulo

### Boas Práticas
- Sempre verificar retorno de `malloc()`
- Inicializar ponteiros com `NULL` se não tiverem valor inicial
- Liberar memória na ordem inversa da alocação
- Usar `const` para ponteiros que não devem modificar dados
- Evitar aritmética de ponteiros complexa quando índices são mais claros

### Debugging
- Use `printf` com `%p` para imprimir endereços
- Compile com `-g` e use `gdb` para debugar
- Use `valgrind` para detectar problemas de memória:
  ```bash
  gcc -g src/ex5_matriz_ponteiros.c -o ex5
  valgrind --leak-check=full ./ex5
  ```

## Material de Referência
- `RevisaoPonteiros.pdf` - slides da aula
- `docs/sync_reference.md` - referência rápida
- Manual do C: `man malloc`, `man free`, `man string.h`
