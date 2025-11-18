#João Vitor de Araújo Trindade
#João Victor de Almeida Reiss

.data
senha:  .word 432               # senha a ser digitada
prompt:  .asciiz "\nDigite a senha: "
output_correct: .asciiz "Senha correta!\n"
output_incorrect: .asciiz "Senha incorreta!"

.text
main:
    lw $t0, senha               # carrega a senha (432) em $t0

#------------CODIGO RODA ATE ESTAR CERTA A SENHA----------------
loop:

    # fazemos essa operacao porque a pilha cresce para baixo, logo estamos
    # reservando o proximo espaco de memoria pra ela
    addi $sp, $sp, -4           # aloca espaço na pilha, -4 = 4bytes (tamanho .word)
    sw $ra, 0($sp)              # salva endereço de retorno para recursão em sp

    jal equal                   # chama função que le e compara senha
    beq $t2, $zero, correct     # se $t2 == 0 (senha correta) desvia para correct

    jal incorrect               # mostra mensagem de erro
    jal loop                    # fazemos um loop recursivo ate beq desviar a branch

#---RECEBEMOS A SENHA DIGITA E VERIFICAMOS SE ESTA CERTO---
equal:
    li $v0, 4                   # syscall para imprimir string
    la $a0, prompt              # carrega mensagem de prompt
    syscall                     # imprime "Digite a senha:"

    li $v0, 5                   # syscall para ler inteiro
    syscall                     # lê entrada do usuário
    move $t1, $v0               # move entrada para $t1

    xor $t2, $t0, $t1           # t2 = 0 se forem iguais, pois XOR entre nums iguais sempre sera 0
    jr $ra                      # retorna para o ponto onde essa funcao foi chamada


#---------PRINTA MENSAGEM DE SENHA INCORRETA--------
incorrect:
    li $v0, 4                   # syscall para imprimir string
    la $a0, output_incorrect    # carrega mensagem de erro
    syscall                     # imprime Senha incorreta!

    jr $ra                      # retorna para onde foi chamada essa funcao inicialmente (nesse caso loop)

#--------PRINTA MENSAGEM DE SENHA CORRETA E FINALIZA------------
correct:
    lw $ra, 0($sp)              # restaura ra para endereço main
    addi $sp, $sp, 4            # limpa pilha

    li $v0, 4                   # syscall para imprimir string
    la $a0, output_correct      # carrega mensagem de sucesso
    syscall                     # imprime Senha correta

    li $v0, 10                  # syscall para terminar programa
    syscall                     # encerra execução
