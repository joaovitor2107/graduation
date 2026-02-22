#João Vitor de Araújo Trindade
#João Victor de Almeida Reiss
.data
prompt1:    .asciiz "Digite o 1º número: "
prompt2:    .asciiz "Digite o 2º número: "
prompt3:    .asciiz "Digite o 3º número: "
output1:    .asciiz "\nMaior valor: "
output2:    .asciiz "\nValor intermediário: "
output3:    .asciiz "\nMenor valor: "
newline:    .asciiz "\n"

.text
main:
    #----------PRINTAR PROMPT1 E LER PRIMEIRO NUMERO--------
    li $v0, 4                   # codigo 4 indica syscall write string
    la $a0, prompt1             # carregando prompt1 para a0, para ser usada na syscall
    syscall                     # chama sistema para imprimir string

    li $v0, 5                   # codigo 5 indica syscall read int
    syscall                     # chama sistema para ler inteiro
    move $t0, $v0               # movendo numero lido para t0

    #--------PRINTAR PROMPT2 E LER SEGUNDO NUMERO------
    li $v0, 4                   # codigo 4 indica syscall write string
    la $a0, prompt2             # carregando prompt2 para ser escrita
    syscall                     # chama sistema para imprimir string

    li $v0, 5                   # codigo 5 indica syscall de read int
    syscall                     # chama sistema para ler inteiro
    move $t1, $v0               # movendo numero lido para t1

    #---------PRINTAR PROMPT3 E LER TERCEIRO NUMERO---------
    li $v0, 4                   # codigo 4 indica syscall write string
    la $a0, prompt3             # carregando prompt3 para ser escrita
    syscall                     # chama sistema para imprimir string
    li $v0, 5                   # codigo 5 indica syscall de read int
    syscall                     # chama sistema para ler inteiro
    move $t2, $v0               # movendo numero lido para t2


    #CODIGO PARA COMPARAR E ORDENAR OS TRES NUMEROS
    #PRIMEIRA COMPARACAO: t0 vs t1
    move $t3, $t0               # copiando t0 para t3 (funcao troca usa t3 e t4)
    move $t4, $t1               # copiando t1 para t4 (funcao troca usa t3 e t4)
    bge $t3, $t4, troca1        # se t3 >= t4, vai para troca1
    j continua1                 # se t3 < t4, pula a troca

troca1:
    jal troca                   # chama funcao troca para trocar t3 e t4

continua1:
    move $t0, $t3               # voltando valores ordenados de t3 para t0
    move $t1, $t4               # voltando valores ordenados de t4 para t1

    #SEGUNDA COMPARACAO: t0 vs t2
    move $t3, $t0               # copiando t0 para t3 (funcao troca usa t3 e t4)
    move $t4, $t2               # copiando t2 para t4 (funcao troca usa t3 e t4)
    bge $t3, $t4, troca2        # se t3 >= t4, vai para troca2
    j continua2                 # se t3 < t4, pula a troca

troca2:
    jal troca                   # chama funcao troca para trocar t3 e t4

continua2:
    move $t0, $t3               # voltando valores ordenados de t3 para t0
    move $t2, $t4               # voltando valores ordenados de t4 para t2

    #TERCEIRA COMPARACAO: t1 vs t2
    move $t3, $t1               # copiando t1 para t3 (funcao troca usa t3 e t4)
    move $t4, $t2               # copiando t2 para t4 (funcao troca usa t3 e t4)
    bge $t3, $t4, troca3        # se t3 >= t4, vai para troca3
    j continua3                 # se t3 < t4, pula a troca

troca3:
    jal troca                   # chama funcao troca para trocar t3 e t4

continua3:
    move $t1, $t3               # voltando valores ordenados de t3 para t1
    move $t2, $t4               # voltando valores ordenados de t4 para t2

    #----------------PRINTAR MAIOR-------------------
    li $v0, 4 #indica syscall write string
    la $a0, output1 #carregando prompt 1 para a0, para ser usada na syscall
    syscall

    li $v0, 1
    move $a0, $t2
    syscall

    #----------------PRINTAR MEDIO-------------------
    li $v0, 4 #indica syscall write string
    la $a0, output2 #carregando prompt 1 para a0, para ser usada na syscall
    syscall

    li $v0, 1
    move $a0, $t1
    syscall

    #----------------PRINTAR MENOR-------------------
    li $v0, 4 #indica syscall write string
    la $a0, output3 #carregando prompt 1 para a0, para ser usada na syscall
    syscall

    li $v0, 1
    move $a0, $t0
    syscall
    #----------------------------------------------

    #NEWLINE
    li $v0, 4 #indica syscall write string
    la $a0, newline #carregando prompt 1 para a0, para ser usada na syscall
    syscall

    li $v0, 10# sistema usa codigo 10 para finalizar
    syscall# syscall para realizar acao relativa a v0

troca:
    #alteramos as posicoes de t3 e t4, para garantir que t3 sempre seja o menor
    move $t5, $t3
    move $t3, $t4
    move $t4, $t5
    jr $ra
