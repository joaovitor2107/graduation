#João Vitor de Araújo Trindade
#João Victor de Almeida Reiss
.data
buffer:         .space 24                    # 6 floats * 4 bytes = 24 bytes

prompt_ax:      .asciiz "Digite Ax: "
prompt_ay:      .asciiz "Digite Ay: "
prompt_az:      .asciiz "Digite Az: "
prompt_bx:      .asciiz "Digite Bx: "
prompt_by:      .asciiz "Digite By: "
prompt_bz:      .asciiz "Digite Bz: "

msg_soma:       .asciiz "\n\n===== SOMA VETORIAL R = A + B =====\n"
msg_rx:         .asciiz "Rx = "
msg_ry:         .asciiz "\nRy = "
msg_rz:         .asciiz "\nRz = "

msg_dot:        .asciiz "\n\n===== PRODUTO ESCALAR A · B =====\n"
msg_p:          .asciiz "p = "

msg_mag:        .asciiz "\n\n===== MAGNITUDE DE A =====\n"
msg_m:          .asciiz "|A| = "

msg_norm:       .asciiz "\n\n===== VETOR NORMALIZADO DE A =====\n"
msg_anx:        .asciiz "Âx = "
msg_any:        .asciiz "\nÂy = "
msg_anz:        .asciiz "\nÂz = "

.text
main:
    # Leitura de Ax
    li $v0, 4                               # print string
    la $a0, prompt_ax                       # carrega mensagem
    syscall
    
    li $v0, 6                               # read float
    syscall
    
    la $t0, buffer                          # endereço do buffer
    s.s $f0, 0($t0)                         # salva Ax no buffer[0]
    
    # Leitura de Ay
    li $v0, 4                               # print string
    la $a0, prompt_ay
    syscall
    
    li $v0, 6                               # read float
    syscall
    
    la $t0, buffer
    s.s $f0, 4($t0)                         # salva Ay no buffer[1]
    
    # Leitura de Az
    li $v0, 4                               # print string
    la $a0, prompt_az
    syscall
    
    li $v0, 6                               # read float
    syscall
    
    la $t0, buffer
    s.s $f0, 8($t0)                         # salva Az no buffer[2]
    
    # Leitura de Bx
    li $v0, 4                               # print string
    la $a0, prompt_bx
    syscall
    
    li $v0, 6                               # read float
    syscall
    
    la $t0, buffer
    s.s $f0, 12($t0)                        # salva Bx no buffer[3]
    
    # Leitura de By
    li $v0, 4                               # print string
    la $a0, prompt_by
    syscall
    
    li $v0, 6                               # read float
    syscall
    
    la $t0, buffer
    s.s $f0, 16($t0)                        # salva By no buffer[4]
    
    # Leitura de Bz
    li $v0, 4                               # print string
    la $a0, prompt_bz
    syscall
    
    li $v0, 6                               # read float
    syscall
    
    la $t0, buffer
    s.s $f0, 20($t0)                        # salva Bz no buffer[5]
    
    # Carregar componentes do buffer para registradores FPU
    la $t0, buffer                          # endereço base do buffer
    
    l.s $f1, 0($t0)                         # $f1 = Ax
    l.s $f2, 4($t0)                         # $f2 = Ay
    l.s $f3, 8($t0)                         # $f3 = Az
    
    l.s $f4, 12($t0)                        # $f4 = Bx
    l.s $f5, 16($t0)                        # $f5 = By
    l.s $f6, 20($t0)                        # $f6 = Bz
    
    # Soma Vetorial: R = A + B
    add.s $f7, $f1, $f4                     # $f7 = Rx = Ax + Bx
    add.s $f8, $f2, $f5                     # $f8 = Ry = Ay + By
    add.s $f9, $f3, $f6                     # $f9 = Rz = Az + Bz
    
    # Imprimir Soma
    li $v0, 4
    la $a0, msg_soma
    syscall
    
    li $v0, 4
    la $a0, msg_rx
    syscall
    li $v0, 2                               # print float
    mov.s $f12, $f7                         # move Rx para $f12
    syscall
    
    li $v0, 4
    la $a0, msg_ry
    syscall
    li $v0, 2
    mov.s $f12, $f8                         # move Ry para $f12
    syscall
    
    li $v0, 4
    la $a0, msg_rz
    syscall
    li $v0, 2
    mov.s $f12, $f9                         # move Rz para $f12
    syscall
    
    # Produto Escalar: p = A · B = Ax*Bx + Ay*By + Az*Bz
    mul.s $f10, $f1, $f4                    # $f10 = Ax * Bx
    mul.s $f11, $f2, $f5                    # $f11 = Ay * By
    mul.s $f12, $f3, $f6                    # $f12 = Az * Bz
    
    add.s $f13, $f10, $f11                  # $f13 = (Ax*Bx) + (Ay*By)
    add.s $f13, $f13, $f12                  # $f13 = soma total = produto escalar
    
    # Imprimir Produto Escalar
    li $v0, 4
    la $a0, msg_dot
    syscall
    
    li $v0, 4
    la $a0, msg_p
    syscall

    li $v0, 2
    mov.s $f12, $f13                        # move produto escalar para $f12
    syscall
    
    # Magnitude: |A| = √(Ax² + Ay² + Az²)
    mul.s $f14, $f1, $f1                    # $f14 = Ax²
    mul.s $f15, $f2, $f2                    # $f15 = Ay²
    mul.s $f16, $f3, $f3                    # $f16 = Az²
    
    add.s $f17, $f14, $f15                  # $f17 = Ax² + Ay²
    add.s $f17, $f17, $f16                  # $f17 = Ax² + Ay² + Az²
    
    sqrt.s $f18, $f17                       # $f18 = √(Ax² + Ay² + Az²) = |A|
    
    # Imprimir Magnitude
    li $v0, 4
    la $a0, msg_mag
    syscall
    
    li $v0, 4
    la $a0, msg_m
    syscall
    li $v0, 2
    mov.s $f12, $f18                        # move magnitude para $f12
    syscall
    
    # Normalização: Â = A/|A|
    div.s $f19, $f1, $f18                   # $f19 = Âx = Ax / |A|
    div.s $f20, $f2, $f18                   # $f20 = Ây = Ay / |A|
    div.s $f21, $f3, $f18                   # $f21 = Âz = Az / |A|
    
    # Imprimir Vetor Normalizado
    li $v0, 4
    la $a0, msg_norm
    syscall
    
    li $v0, 4
    la $a0, msg_anx
    syscall

    li $v0, 2
    mov.s $f12, $f19                        # move Âx para $f12
    syscall
    
    li $v0, 4
    la $a0, msg_any
    syscall

    li $v0, 2
    mov.s $f12, $f20                        # move Ây para $f12
    syscall
    
    li $v0, 4
    la $a0, msg_anz
    syscall

    li $v0, 2
    mov.s $f12, $f21                        # move Âz para $f12
    syscall
    
    # Encerrar programa
    li $v0, 10                              # exit
    syscall
