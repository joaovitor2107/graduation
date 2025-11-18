#João Vitor de Araújo Trindade
#João Victor de Almeida Reiss
.data
array:        .word 0,-2,-3,4,5,6,7,8,9,10    # Array estatico
size:         .word 10
head_par:     .word 0                       # Ponteiro para head dos pares
head_impar:   .word 0                       # Ponteiro para head dos impares

prompt1:      .asciiz "\n Numeros Pares \n"
prompt2:      .asciiz "\n Numeros Impares \n"
espaco:       .asciiz " "

.text
main:
    la $s0, array                           # $s0 = endereco inicial do array
    li $s1, 0                               # $s1 = iterador
    lw $s2, size                            # $s2 = tamanho do array 
    
loop_array:
    bge $s1, $s2, end_loop                  # se o iterador for igual ou maior que o tamanho array pulamos para o proximo passo

    lw $t3, 0($s0)                          # elemento atual do array para o registrador t3

    andi $t4, $t3, 1                        # fazendo operacao AND entre t3(elemento atual array) e 1 para verificar paridade

    beq $t4, 1, is_impar                    # caso o resultado do teste de paridade seja 1, pulamos para funcao impar
    j is_par                                # caso nao seja impar pulamos para funcao par

is_par:
    move $a0, $t3
    la $a1, head_par                        # endereco da variavel head

    jal inserir_final                       # pulamos para a funcao que vai inserir o elemento no final da lista (nesse caso a lista par)

    j prox_elem                             # pulamos para a funcao prox_elemento

is_impar:
    move $a0, $t3
    la $a1, head_impar                      # endereco da variavel head

    jal inserir_final                       # pulamos para a funcao que vai inserir o elemento no final da lista (nesse caso a lista impar)

    j prox_elem                             # pulamos para a funcao prox_elemento

prox_elem:
    addi $s0, $s0, 4                        # adcionamos mais quatro no endereco (AGORA PRESERVADO!)
    addi $s1, $s1, 1                        # adcionamos 1 em s1

    j loop_array                            # voltamos para o loop mas um elemento a frente

inserir_final:
    addi $sp, $sp, -12                      # reserva espaço na pilha (para 3)
    sw $ra, 0($sp)                          # salva endereço de retorno
    sw $s0, 4($sp)                          # salva $s0
    sw $s1, 8($sp)                          # salva $s1

    move $s0, $a0                           # $s0 = valor (guardar)
    move $s1, $a1                           # $s1 = endereco head (guardar)

    li $v0, 9                               # syscall de sbrk para alocar memoria
    li $a0, 8                               # tamanho alocado
    syscall                                 # v0 esta com endereco alocado

    move $t0, $v0                           # endereco do novo no alocado

    sw $s0, 0($t0)                          # passando o valor atual para o no (no->valor = $s0)
    sw $zero, 4($t0)                        # passando 0 para o proximo no (no->proximo = NULL)

    lw $t1, 0($s1)                          # passando a head para t1
    beqz $t1, lista_vazia                   # verificando caso esta vazia a lista
    j lista_nao_vazia                       # seguimos para lista nao vazia

lista_nao_vazia:
    move $t2, $t1                           # passamos head para t2, pois queremos percorrer ate o final

percorrer:
    lw $t3, 4($t2)                          # passamos para o proximo elemento da lista
    beqz $t3, final                         # caso esse elemento seja null vamos para final (usamos o t2 e t3 para que nao percamos o ultimo elemento nao nulo ao percorrer)
    move $t2, $t3                           # movemos o valor de t3 para t2 (basicamente atual = atual->prox)
    j percorrer

final:
    sw $t0, 4($t2)                          # escrevemos no proximo do ultimo valor encontrado o valor atual a ser adcionado (atual->proximo = novo_no)
    j fim_inserir                           # pulamos para fim_inserir

lista_vazia:
    sw $t0, 0($s1)                          # adcionamos o novo no como primeiro elemento, adcionamos em head o novo elemento

fim_inserir:
    lw $ra, 0($sp)                          # restaurando registrador $ra para valor inicial antes de inserir_final
    lw $s0, 4($sp)                          # restaurando registrador $s0 para valor inicial antes de inserir_final
    lw $s1, 8($sp)                          # restaurando registrador $s1 para valor inicial antes de inserir_final
    addi $sp, $sp, 12                       # restaurando a pilha
    jr $ra                                  # voltando para onde jal inserir_final foi chamado



end_loop:
    #imprimir lista pares
    li $v0, 4                               # codigo 4 indica syscall write string
    la $a0, prompt1                         # carregando prompt1 para a0, para ser usada na syscall
    syscall

    lw $a0, head_par                        # carrega head_par para a0
    jal imprimir_lista                      # chamamos a funcao imprimir_lista

    #imprimir lista impares
    li $v0, 4                               # codigo 4 indica syscall write string
    la $a0, prompt2                         # carregando prompt1 para a0, para ser usada na syscall
    syscall

    lw $a0, head_impar                      # carrega head_impar para a0
    jal imprimir_lista                      # chamamos a funcao imprimir lista

    li $v0, 10                              # codigo 10 indica que vamos finalizar programa
    syscall


imprimir_lista:
    addi $sp, $sp, -8                       # para salvar os registradores sem perder
    sw $ra, 0($sp)                          # salvando o $ra atual na pilha
    sw $s0, 4($sp)                          # salvando o $s0 atual na pilha

    move $s0, $a0                           # guardando head em s0

loop_imprimir:
    beqz $s0, fim_imprimir                  # se atual == NULL, termina

    lw $a0, 0($s0)                          # passando o dado atual para a0
    li $v0, 1                               # codigo 0 representa syscall print integer
    syscall

    li $v0, 4                               # codigo 4 indica syscall write string
    la $a0, espaco                          # imprimindo o espaco
    syscall

    lw $s0, 4($s0)                          # mudando o atual para o proximo (atual = atual->prox)
    j loop_imprimir                         # segue loop


fim_imprimir:
    lw $ra, 0($sp)                          # restaurando registrador $ra para valor inicial antes de imprimir lista
    lw $s0, 4($sp)                          # restaurando registrador $s0 para valor inicial antes de imprimir lista

    addi $sp, $sp, 8                        # restaurando pilha para valor inicial

    jr $ra

