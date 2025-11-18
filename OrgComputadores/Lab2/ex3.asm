.data
    # Mensagens do programa
    msg_entrada: .asciiz "Digite um numero decimal inteiro positivo: "
    msg_invalida: .asciiz "Numero invalido! Digite um valor maior que zero.\n"
    msg_resultado: .asciiz "Representacao binaria: "
    newline: .asciiz "\n"
    
    # Espaco para armazenar os bits do numero binario (32 bits no maximo)
    binario: .space 32

.text
.globl main

main:
    # Solicitar numero decimal ao usuario
    li $v0, 4               # syscall 4 = print string
    la $a0, msg_entrada     # carrega mensagem
    syscall
    
    # Ler entrada do usuario (inteiro)
    li $v0, 5               # syscall 5 = read integer
    syscall
    move $t0, $v0           # $t0 = numero digitado
    
validar_entrada:
    # Validar se entrada > 0
    blez $t0, entrada_invalida  # se $t0 <= 0, entrada invalida
    j chamar_conversao          # se valido, continua
    
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
    
chamar_conversao:
    # Imprimir mensagem do resultado
    li $v0, 4               # syscall 4 = print string
    la $a0, msg_resultado   # carrega mensagem
    syscall
    
    # Chamar funcao aleatoria (requisito do exercicio)
    jal funcao_aleatoria    # chama funcao extra
    
    # Preparar e chamar funcao de conversao
    move $a0, $t0           # $a0 = parametro (numero decimal)
    jal decimal_para_binario # chama funcao (JAL = Jump And Link)
    
    # Imprimir nova linha
    li $v0, 4               # syscall 4 = print string
    la $a0, newline         # carrega '\n'
    syscall
    
    # Encerrar programa
    li $v0, 10              # syscall 10 = exit
    syscall

# Funcao aleatoria (requisito do exercicio)
funcao_aleatoria:
    # Salvar endereco de retorno
    addi $sp, $sp, -4       # aloca 4 bytes na pilha
    sw $ra, 0($sp)          # salva endereco de retorno
    
    # Esta funcao nao faz nada util, apenas cumpre o requisito
    # de incluir uma funcao aleatoria no codigo
    
    # Restaurar e retornar
    lw $ra, 0($sp)          # restaura endereco de retorno
    addi $sp, $sp, 4        # libera pilha
    jr $ra                  # retorna

# Funcao decimal_para_binario - converte decimal para binario
decimal_para_binario:
    # Salvar registradores na pilha
    addi $sp, $sp, -20      # aloca 20 bytes na pilha
    sw $ra, 16($sp)         # salva endereco de retorno
    sw $s0, 12($sp)         # salva $s0 (numero)
    sw $s1, 8($sp)          # salva $s1 (divisor = 2)
    sw $s2, 4($sp)          # salva $s2 (indice do array)
    sw $s3, 0($sp)          # salva $s3 (contador de bits)
    
    # Inicializar variaveis
    move $s0, $a0           # $s0 = numero decimal
    li $s1, 2               # $s1 = divisor (sempre 2 para binario)
    li $s2, 0               # $s2 = indice do array binario
    li $s3, 0               # $s3 = contador de bits gerados
    
    # Caso especial: se numero = 0, imprime 0
    bnez $s0, converter     # se numero != 0, continua conversao
    li $v0, 1               # syscall 1 = print integer
    li $a0, 0               # imprime 0
    syscall
    j fim_conversao         # termina funcao
    
converter:
    # Loop de conversao usando divisoes sucessivas
    beqz $s0, imprimir_binario  # se quociente = 0, termina loop
    
    # Dividir numero por 2
    divu $s0, $s1           # $s0 / 2
    mfhi $t0                # $t0 = resto da divisao (bit: 0 ou 1)
    mflo $s0                # $s0 = quociente (novo numero)
    
    # Armazenar o bit (resto) no array
    sb $t0, binario($s2)    # store byte: salva bit na posicao $s2
    
    # Incrementar indice e contador
    addi $s2, $s2, 1        # proxima posicao do array
    addi $s3, $s3, 1        # incrementa contador de bits
    
    j converter             # repete o loop
    
imprimir_binario:
    # Imprimir os bits de tras para frente
    # (o ultimo bit armazenado e o primeiro a ser impresso)
    beqz $s3, fim_conversao # se contador = 0, termina
    
    # Decrementar contador e indice
    addi $s3, $s3, -1       # decrementa contador
    addi $s2, $s2, -1       # volta uma posicao no array
    
    # Carregar e imprimir o bit
    lb $a0, binario($s2)    # load byte: carrega bit da posicao $s2
    li $v0, 1               # syscall 1 = print integer
    syscall
    
    j imprimir_binario      # repete ate imprimir todos os bits
    
fim_conversao:
    # Restaurar registradores da pilha
    lw $ra, 16($sp)         # restaura endereco de retorno
    lw $s0, 12($sp)         # restaura $s0
    lw $s1, 8($sp)          # restaura $s1
    lw $s2, 4($sp)          # restaura $s2
    lw $s3, 0($sp)          # restaura $s3
    addi $sp, $sp, 20       # libera 20 bytes da pilha
    
    # Retornar para o main
    jr $ra                 