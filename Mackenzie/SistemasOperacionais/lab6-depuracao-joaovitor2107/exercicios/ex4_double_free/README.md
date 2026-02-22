# Exercício 4: Liberação Dupla (Double Free)

## Problema
Tentativa de liberar a mesma região de memória mais de uma vez.

## Contexto de SO
Liberações duplas podem corromper as estruturas de dados internas do gerenciador de memória do sistema operacional. Se isso ocorrer no kernel, pode levar a falhas catastróficas no sistema. Muitos gerenciadores de memória modernos implementam proteções contra liberações duplas.

## Tarefas
1. Execute `original.c` com Valgrind
2. Identifique o erro de liberação dupla
3. Corrija o código removendo a segunda chamada ao `free()`
4. Verifique que o problema foi resolvido

## Comandos Úteis
```bash
gcc -g original.c -o original
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./original > valgrind_original.txt 2>&1

gcc -g corrigido.c -o corrigido
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./corrigido > valgrind_corrigido.txt 2>&1
```