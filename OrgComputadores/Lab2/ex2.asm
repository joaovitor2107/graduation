.data
    # Mensagens do programa
    msg_entrada: .asciiz "Digite a quantidade de termos da sequencia de Fibonacci: "
    msg_invalida: .asciiz "Numero invalido! Digite um valor maior que zero.\n"
    virgula: .asciiz ", "
    newline: .asciiz "\n"

.text
.globl main

main:
    # Solicitar quantidade de termos ao usuario
    li $v0, 4               # syscall 4 = print string
    la $a0, msg_entrada     # carrega endereco da mensagem
    syscall
    
    # Ler entrada do usuario (inteiro)
    li $v0, 5               # syscall 5 = read integer
    syscall
    move $t0, $v0           # $t0 = quantidade de termos informada
    
validar_entrada:
    # Validar se entrada > 0
    blez $t0, entrada_invalida  # se $t0 <= 0, pede nova entrada
    j chamar_fibonacci          # se valido, continua
    
entrada_invalida:
    # Mostrar mensagem de erro
    li $v0, 4               # syscall 4 = print string
    la $a0, msg_invalida    # carrega mensagem de erro
    syscall
    
    # Solicitar novamente ao usuario
    li $v0, 4
    la $a0, msg_entrada
    syscall
    
    # Ler nova entrada
    li $v0, 5               # syscall 5 = read integer
    syscall
    move $t0, $v0           # armazena nova entrada
    j validar_entrada       # volta para validar
    
chamar_fibonacci:
    # Preparar e chamar funcao Fibonacci
    move $a0, $t0           # $a0 = parametro (quantidade de termos)
    jal fibonacci           # chama funcao (JAL = Jump And Link)
    
    # Imprimir nova linha apos a sequencia
    li $v0, 4               # syscall 4 = print string
    la $a0, newline         # carrega '\n'
    syscall
    
    # Encerrar programa
    li $v0, 10              # syscall 10 = exit
    syscall

# Funcao Fibonacci - gera e imprime a sequencia
fibonacci:
    # Salvar registradores na pilha (para preservar valores)
    addi $sp, $sp, -16      # aloca 16 bytes na pilha
    sw $ra, 12($sp)         # salva endereco de retorno
    sw $s0, 8($sp)          # salva $s0 (F(n-2))
    sw $s1, 4($sp)          # salva $s1 (F(n-1))
    sw $s2, 0($sp)          # salva $s2 (contador)
    
    # Inicializar variaveis
    move $s2, $a0           # $s2 = quantidade de termos (parametro)
    li $s0, 0               # $s0 = F(n-2) = 0 (primeiro termo)
    li $s1, 1               # $s1 = F(n-1) = 1 (segundo termo)
    li $t1, 0               # $t1 = contador de termos impressos
    
    # Verificar se quantidade = 0
    beqz $s2, fim_fibonacci # se quantidade = 0, termina
    
imprimir_primeiro:
    # Imprimir F(0) = 0 (primeiro termo)
    li $v0, 1               # syscall 1 = print integer
    move $a0, $s0           # $a0 = 0
    syscall
    
    addi $t1, $t1, 1        # incrementa contador
    beq $t1, $s2, fim_fibonacci  # se imprimiu todos, termina
    
    # Imprimir virgula apos o primeiro termo
    li $v0, 4               # syscall 4 = print string
    la $a0, virgula         # carrega ", "
    syscall
    
imprimir_segundo:
    # Imprimir F(1) = 1 (segundo termo)
    li $v0, 1               # syscall 1 = print integer
    move $a0, $s1           # $a0 = 1
    syscall
    
    addi $t1, $t1, 1        # incrementa contador
    beq $t1, $s2, fim_fibonacci  # se imprimiu todos, termina
    
loop_fibonacci:
    # Imprimir virgula antes de cada novo termo
    li $v0, 4               # syscall 4 = print string
    la $a0, virgula         # carrega ", "
    syscall
    
    # Calcular proximo termo: F(n) = F(n-1) + F(n-2)
    add $t2, $s0, $s1       # $t2 = $s0 + $s1
    
    # Imprimir F(n)
    li $v0, 1               # syscall 1 = print integer
    move $a0, $t2           # $a0 = termo calculado
    syscall
    
    # Atualizar valores para proxima iteracao
    move $s0, $s1           # F(n-2) recebe F(n-1)
    move $s1, $t2           # F(n-1) recebe F(n)
    
    addi $t1, $t1, 1        # incrementa contador
    blt $t1, $s2, loop_fibonacci  # se contador < quantidade, continua loop
    
fim_fibonacci:
    # Restaurar registradores
    lw $ra, 12($sp)
    lw $s0, 8($sp)
    lw $s1, 4($sp)
    lw $s2, 0($sp)
    addi $sp, $sp, 16
    
    # Retornar
    jr $ra