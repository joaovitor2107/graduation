# Exercício 2: Uso de Memória Não Inicializada

## Problema
Tentativa de usar valores em um array alocado dinamicamente sem inicialização prévia.

## Contexto de SO
Em sistemas operacionais, usar memória não inicializada pode revelar dados de outros processos (violação de segurança) ou levar a comportamentos imprevisíveis. É por isso que sistemas modernos como Linux, ao alocar memória para um novo processo, geralmente a preenche com zeros ou valores aleatórios por questões de segurança.

## Tarefas
1. Compile e execute `original.c` com Valgrind
2. Identifique o problema reportado sobre valores não inicializados
3. Corrija o código inicializando o array corretamente
4. Verifique que o problema foi resolvido

## Comandos Úteis
```bash
gcc -g original.c -o original
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./original > valgrind_original.txt 2>&1

gcc -g corrigido.c -o corrigido
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./corrigido > valgrind_corrigido.txt 2>&1
```
