# Makefile para Lab 3 - Introdução a Threads
# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -g -pthread

# Diretórios
SRC_DIR = src
BUILD_DIR = build

# Arquivos fonte dos exercícios
EX1_SRC = $(SRC_DIR)/ex1_hello_thread.c
EX2_SRC = $(SRC_DIR)/ex2_hello_join.c
EX3_SRC = $(SRC_DIR)/ex3_multiple_threads.c
EX4_SRC = $(SRC_DIR)/ex4_thread_args.c
EX5_SRC = $(SRC_DIR)/ex5_struct_args.c
EX6_SRC = $(SRC_DIR)/ex6_return_value.c

# Executáveis
EX1 = ex1_hello_thread
EX2 = ex2_hello_join
EX3 = ex3_multiple_threads
EX4 = ex4_thread_args
EX5 = ex5_struct_args
EX6 = ex6_return_value

# Lista de todos os executáveis
TARGETS = $(EX1) $(EX2) $(EX3) $(EX4) $(EX5) $(EX6)

# Regra padrão
.PHONY: all
all: $(TARGETS)
	@echo "Todos os exercícios foram compilados com sucesso!"
	@echo "Execute os programas individualmente:"
	@echo "  ./ex1_hello_thread"
	@echo "  ./ex2_hello_join"
	@echo "  ./ex3_multiple_threads"
	@echo "  ./ex4_thread_args"
	@echo "  ./ex5_struct_args"
	@echo "  ./ex6_return_value"

# Exercícios básicos (Parte 1)
$(EX1): $(EX1_SRC)
	$(CC) $(CFLAGS) -o $@ $<

$(EX2): $(EX2_SRC)
	$(CC) $(CFLAGS) -o $@ $<

$(EX3): $(EX3_SRC)
	$(CC) $(CFLAGS) -o $@ $<

# Exercícios de comunicação (Parte 2)
$(EX4): $(EX4_SRC)
	$(CC) $(CFLAGS) -o $@ $<

$(EX5): $(EX5_SRC)
	$(CC) $(CFLAGS) -o $@ $<

$(EX6): $(EX6_SRC)
	$(CC) $(CFLAGS) -o $@ $<

# Compilar apenas exercícios básicos
.PHONY: basic
basic: $(EX1) $(EX2) $(EX3)
	@echo "Exercícios básicos compilados!"

# Compilar apenas exercícios de comunicação
.PHONY: comm
comm: $(EX4) $(EX5) $(EX6)
	@echo "Exercícios de comunicação compilados!"

# Executar testes básicos
.PHONY: test-basic
test-basic: $(EX1) $(EX2) $(EX3)
	@echo "=== Testando Exercício 1 ==="
	./$(EX1)
	@echo ""
	@echo "=== Testando Exercício 2 ==="
	./$(EX2)
	@echo ""
	@echo "=== Testando Exercício 3 ==="
	./$(EX3)

# Executar testes de comunicação
.PHONY: test-comm
test-comm: $(EX4) $(EX5) $(EX6)
	@echo "=== Testando Exercício 4 ==="
	./$(EX4)
	@echo ""
	@echo "=== Testando Exercício 5 ==="
	./$(EX5)
	@echo ""
	@echo "=== Testando Exercício 6 ==="
	./$(EX6)

# Limpar apenas executáveis
.PHONY: clean
clean:
	rm -f $(TARGETS)
	@echo "Executáveis removidos."

# Criar estrutura de diretórios se necessário
.PHONY: setup
setup:
	@mkdir -p $(SRC_DIR)
	@mkdir -p traces
	@mkdir -p docs
	@echo "Estrutura de diretórios criada."

# Ajuda
.PHONY: help
help:
	@echo "Makefile para Lab 3 - Introdução a Threads"
	@echo ""
	@echo "Comandos disponíveis:"
	@echo "  make all          - Compila todos os exercícios"
	@echo "  make basic        - Compila apenas exercícios básicos (1-3)"
	@echo "  make comm         - Compila apenas exercícios de comunicação (4-6)"
	@echo "  make ex1          - Compila exercício 1"
	@echo "  make ex2          - Compila exercício 2"
	@echo "  make ex3          - Compila exercício 3"
	@echo "  make ex4          - Compila exercício 4"
	@echo "  make ex5          - Compila exercício 5"
	@echo "  make ex6          - Compila exercício 6"
	@echo "  make test-basic   - Executa testes dos exercícios básicos"
	@echo "  make test-comm    - Executa testes de comunicação"
	@echo "  make clean        - Remove executáveis"
	@echo "  make setup        - Cria estrutura de diretórios"
	@echo "  make help         - Mostra esta mensagem"

# Regras individuais para cada exercício
.PHONY: ex1 ex2 ex3 ex4 ex5 ex6
ex1: $(EX1)
ex2: $(EX2)
ex3: $(EX3)
ex4: $(EX4)
ex5: $(EX5)
ex6: $(EX6)

# Prevenir remoção de arquivos intermediários
.PRECIOUS: %.o