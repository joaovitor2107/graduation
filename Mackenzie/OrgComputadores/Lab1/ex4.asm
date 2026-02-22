#João Vitor de Araújo Trindade
#João Victor de Almeida Reiss
.data
prompt:     .asciiz "Digite um número inteiro: "
msg_par:    .asciiz "O número é PAR!\n"
msg_impar:  .asciiz "O número é ÍMPAR!\n"

.text
main:
    jal ler_numero        # lê número do usuário
    move $t0, $v0         # salva número em $t0

    jal verificar_paridade # verifica se é par ou ímpar

    li $v0, 10            # termina programa
    syscall


ler_numero:
    li $v0, 4             # syscall para imprimir string
    la $a0, prompt        # carrega mensagem
    syscall               # imprime prompt

    li $v0, 5             # syscall para ler inteiro
    syscall               # lê número ($v0 = número lido)
    jr $ra

verificar_paridade:
    # fazemos and no ultimo lsb para verificar se e par ou impar
    # se lsb == 0 (par), se lsb == 1 (impar)
    andi $t1, $t0, 1      # and entre t0 e 1, resultado armazenado em t1

    beq $t1, $zero, imprimir_par # desviamos para imprimir_par caso t1 == 0
    beq $t1, 1, imprimir_impar # desviamos para imprimir_impar  caso t1 == 0
    jr $ra

imprimir_par:
    li $v0, 4             # syscall para imprimir string
    la $a0, msg_par       # carrega mensagem "PAR"
    syscall

    jr $ra

imprimir_impar:
    li $v0, 4             # syscall para imprimir string
    la $a0, msg_impar     # carrega mensagem "ÍMPAR"
    syscall

    jr $ra
