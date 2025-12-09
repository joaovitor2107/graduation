# Guia de Compilação para Programas com pthreads

## Flag -pthread

Ao compilar programas que usam threads POSIX, é essencial usar a flag `-pthread`:

```bash
gcc -pthread programa.c -o programa
```

### O que a flag -pthread faz?

1. **Define macros do preprocessador**
   - Define `_REENTRANT` e `_THREAD_SAFE`
   - Habilita versões thread-safe de funções

2. **Linka a biblioteca pthread**
   - Equivalente a adicionar `-lpthread`
   - Mas também faz configurações adicionais

3. **Configura o compilador**
   - Ativa otimizações específicas para threads
   - Garante geração de código thread-safe

## Compilação Básica

### Programa simples
```bash
gcc -pthread -o meu_programa meu_programa.c
```

### Com warnings e debug
```bash
gcc -pthread -Wall -Wextra -g -o meu_programa meu_programa.c
```

### Com otimização
```bash
gcc -pthread -O2 -o meu_programa meu_programa.c
```

## Compilação com Múltiplos Arquivos

### Arquivos separados
```bash
# Compilar arquivos objeto
gcc -pthread -c -o main.o main.c
gcc -pthread -c -o worker.o worker.c
gcc -pthread -c -o utils.o utils.c

# Linkar
gcc -pthread -o programa main.o worker.o utils.o
```

### Comando único
```bash
gcc -pthread -o programa main.c worker.c utils.c
```

## Flags Úteis

### Warnings importantes
```bash
-Wall           # Warnings comuns
-Wextra         # Warnings extras
-Werror         # Tratar warnings como erros
-Wno-unused     # Ignorar variáveis não usadas
```

### Debug
```bash
-g              # Informações de debug
-ggdb           # Debug específico para GDB
-O0             # Sem otimização (melhor para debug)
```

### Otimização
```bash
-O0             # Sem otimização
-O1             # Otimização básica
-O2             # Otimização padrão
-O3             # Otimização agressiva
-Os             # Otimizar tamanho
```

### Sanitizers (detecção de erros)
```bash
-fsanitize=thread       # Thread sanitizer
-fsanitize=address      # Address sanitizer
-fsanitize=undefined    # Undefined behavior
```

## Problemas Comuns

### Erro: undefined reference to `pthread_create`

**Causa**: Esqueceu de adicionar `-pthread`

**Solução**:
```bash
gcc -pthread programa.c -o programa
```

### Erro: segmentation fault em threads

**Possíveis causas**:
- Acesso a ponteiros inválidos
- Stack overflow em thread
- Race conditions

**Debug**:
```bash
# Compilar com debug
gcc -pthread -g -O0 programa.c -o programa

# Executar com valgrind
valgrind --tool=helgrind ./programa

# Ou com thread sanitizer
gcc -pthread -fsanitize=thread -g programa.c -o programa
./programa
```

### Warning: variável pode ser usada não inicializada

**Causa comum em threads**: Passar endereço de variável local

**Solução**: Use variáveis globais, alocação dinâmica ou arrays

## Makefile para pthreads

### Makefile básico
```makefile
CC = gcc
CFLAGS = -pthread -Wall -Wextra -g
TARGET = programa
SRCS = main.c worker.c utils.c
OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
```

## Verificação da Instalação

### Verificar suporte a pthreads
```bash
# Verificar biblioteca
ldconfig -p | grep pthread

# Verificar headers
ls /usr/include/pthread.h

# Teste simples
echo '#include <pthread.h>
int main() { return 0; }' | gcc -pthread -x c -
```

## Dicas de Performance

### Compilação para produção
```bash
gcc -pthread -O2 -march=native -mtune=native programa.c -o programa
```

### Profile-guided optimization
```bash
# Passo 1: Compilar com profiling
gcc -pthread -fprofile-generate programa.c -o programa

# Passo 2: Executar com dados representativos
./programa input.data

# Passo 3: Recompilar com perfil
gcc -pthread -fprofile-use -O3 programa.c -o programa
```

## Ferramentas de Análise

### Valgrind Helgrind
```bash
valgrind --tool=helgrind ./programa
```
Detecta race conditions e problemas de sincronização

### Thread Sanitizer
```bash
gcc -pthread -fsanitize=thread -g programa.c -o programa
./programa
```
Detecta data races em tempo de execução

### GDB para threads
```bash
gdb ./programa
(gdb) info threads          # Lista threads
(gdb) thread 2              # Muda para thread 2
(gdb) thread apply all bt   # Backtrace de todas
```

## Exemplo Completo

```bash
# Desenvolvimento
gcc -pthread -Wall -Wextra -g -O0 programa.c -o programa_debug

# Teste com sanitizer
gcc -pthread -fsanitize=thread -g programa.c -o programa_tsan

# Produção
gcc -pthread -O2 -march=native programa.c -o programa_prod

# Análise
valgrind --tool=helgrind ./programa_debug
```