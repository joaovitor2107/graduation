# Exercício 1: Vazamento de Memória (Memory Leak)

## Problema
Função aloca memória dinamicamente mas esquece de liberá-la, causando vazamento de memória.

## Contexto de SO
Similar ao que pode ocorrer em um sistema operacional quando um driver de dispositivo aloca memória para operações de E/S mas não a libera corretamente, levando a degradação gradual do desempenho do sistema.

## Tarefas
1. Compile o programa `original.c` com flags de depuração
2. Execute-o com Valgrind e salve o relatório em `valgrind_original.txt`
3. Identifique quantos bytes foram vazados e em quantos blocos
4. Corrija o problema criando `corrigido.c`
5. Execute Valgrind novamente e salve em `valgrind_corrigido.txt`
6. Verifique que não há mais vazamentos

## Comandos Úteis
```bash
gcc -g original.c -o original
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./original > valgrind_original.txt 2>&1

gcc -g corrigido.c -o corrigido
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./corrigido > valgrind_corrigido.txt 2>&1
```