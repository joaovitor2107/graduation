# Exercício 5: Uso Após Liberação (Use-After-Free)

## Problema
Uso de um ponteiro após a memória apontada ter sido liberada.

## Contexto de SO
Vulnerabilidades do tipo use-after-free são comuns em drivers de dispositivos e no próprio kernel dos sistemas operacionais. Quando a memória é liberada, ela pode ser realocada para outro propósito, mas se o código original continuar a usá-la, pode interferir com o novo uso, causando comportamentos imprevisíveis.

## Tarefas
1. Execute `original.c` com Valgrind
2. Identifique o problema de uso após liberação
3. Corrija o código removendo o uso do ponteiro após o `free()`
4. Verifique que o problema foi resolvido

## Comandos Úteis
```bash
gcc -g original.c -o original
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./original > valgrind_original.txt 2>&1

gcc -g corrigido.c -o corrigido
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./corrigido > valgrind_corrigido.txt 2>&1
```
