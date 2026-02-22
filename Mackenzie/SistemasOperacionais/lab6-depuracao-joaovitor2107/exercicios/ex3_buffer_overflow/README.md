# Exercício 3: Acesso Fora dos Limites (Buffer Overflow)

## Problema
Acesso a posições de memória além dos limites do array alocado.

## Contexto de SO
Os buffer overflows são uma das vulnerabilidades mais comuns em sistemas operacionais e aplicações. Eles podem levar a corrupção de dados, crashes do sistema e até exploração por software malicioso. Muitos ataques históricos a sistemas operacionais exploraram esse tipo de vulnerabilidade.

## Tarefas
1. Execute `original.c` com Valgrind
2. Identifique o problema de acesso inválido à memória
3. Corrija o código ajustando os limites do loop
4. Verifique que não há mais acessos inválidos

## Comandos Úteis
```bash
gcc -g original.c -o original
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./original > valgrind_original.txt 2>&1

gcc -g corrigido.c -o corrigido
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./corrigido > valgrind_corrigido.txt 2>&1
```