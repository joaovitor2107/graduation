# Exercício 6: Lista Ligada com Gerenciamento de Memória

## Problema
Implementar corretamente a função `freeList()` para liberar toda a memória alocada de uma lista ligada.

## Contexto de SO
Listas ligadas são estruturas de dados fundamentais em sistemas operacionais, usadas para implementar tabelas de processos, gerenciamento de memória e filas de E/S. O gerenciamento correto destas estruturas é crucial para a estabilidade do sistema.

## Tarefas
1. Implemente a função `freeList()` no arquivo `corrigido.c`
2. A função deve percorrer toda a lista e liberar cada nó
3. Chame `freeList(list)` no `main()` antes de retornar
4. Utilizando Valgrind, verifique se sua implementação está livre de vazamentos
5. Teste sua solução com diferentes tamanhos de lista

## Comandos Úteis
```bash
gcc -g original.c -o original
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./original > valgrind_original.txt 2>&1

gcc -g corrigido.c -o corrigido
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./corrigido > valgrind_corrigido.txt 2>&1
```

## Desafio Adicional
Modifique o programa para aceitar entrada do usuário para o tamanho da lista e teste com valores diferentes (ex: 0, 1, 100, 1000).
