; Profesionální NASM z IR vygenerováno PainGenem  
section .data
    bool_l_true  db 1                                

    bool_l_false db 0                                

     format_int db "%d", 10, 0  ; Formát pro print 

    format_str db "%s", 10, 0  ; Formát pro řetězce

    str_0 db "pavel", 0
    str_1 db "pavel", 0
    str_2 db "kauba", 0
    str_3 db "kuba", 0
    str_4 db "a je pavel a b je kuba", 0
    str_5 db "a je pavel a b není kuba", 0
    str_6 db "A je pavel", 0
    str_7 db "kauba", 0
    str_8 db "kuba", 0
    str_9 db "a je kuba a b je kuba", 0
    str_10 db "a je kuba a b není kuba", 0
    str_11 db "A není kuba", 0
    t0: db "",0
    t1: db "",0
    t2: db "",0
section .bss

section .text
    global main
    extern printf

main:
    push rbp
    mov rbp, rsp

    ; IR: goto L0
    ; Skoč 
    jmp L0

    ; IR: L0:
L0:

    ; IR: t0 = 'str_0' == 'str_1'
 ; String porovnání
    ; Načti string literal adresu 
    mov rax, str_0
 mov rdi, rax
    ; Načti string literal adresu 
    mov rax, str_1
 mov rsi, rax
 ; Loop začátek porovnání
 .str_cmp_loop_0:
 mov al, [rdi]
 mov bl, [rsi]
 cmp al, bl
 jne .str_cmp_different_1
 test al, al
 jz .str_cmp_equal_2
 inc rdi
 inc rsi
 jmp .str_cmp_loop_0
 .str_cmp_different_1:
 mov al, 1
 jmp .str_cmp_done_3
 .str_cmp_equal_2:
 xor al, al
 .str_cmp_done_3:
 sete al
 movzx rax, al
    ; Ulož do [t0]
    mov [t0], rax

    ; IR: if t0 == 0 goto L1
    ; Skoč když false
    mov rax, [t0]
    cmp rax, 0
    je L1

    ; IR: t1 = 'str_2' == 'str_3'
 ; String porovnání
    ; Načti string literal adresu 
    mov rax, str_2
 mov rdi, rax
    ; Načti string literal adresu 
    mov rax, str_3
 mov rsi, rax
 ; Loop začátek porovnání
 .str_cmp_loop_4:
 mov al, [rdi]
 mov bl, [rsi]
 cmp al, bl
 jne .str_cmp_different_5
 test al, al
 jz .str_cmp_equal_6
 inc rdi
 inc rsi
 jmp .str_cmp_loop_4
 .str_cmp_different_5:
 mov al, 1
 jmp .str_cmp_done_7
 .str_cmp_equal_6:
 xor al, al
 .str_cmp_done_7:
 sete al
 movzx rax, al
    ; Ulož do [t1]
    mov [t1], rax

    ; IR: if t1 == 0 goto L3
    ; Skoč když false
    mov rax, [t1]
    cmp rax, 0
    je L3

    ; IR: print 'str_4'
    ; Vypiš string hodnotu 
    mov rsi, str_4
    mov rdi, format_str
    xor rax, rax
    call printf wrt ..plt

    ; IR: goto L4
    ; Skoč 
    jmp L4

    ; IR: L3:
L3:

    ; IR: print 'str_5'
    ; Vypiš string hodnotu 
    mov rsi, str_5
    mov rdi, format_str
    xor rax, rax
    call printf wrt ..plt

    ; IR: L4:
L4:

    ; IR: print 'str_6'
    ; Vypiš string hodnotu 
    mov rsi, str_6
    mov rdi, format_str
    xor rax, rax
    call printf wrt ..plt

    ; IR: goto L2
    ; Skoč 
    jmp L2

    ; IR: L1:
L1:

    ; IR: t2 = 'str_7' == 'str_8'
 ; String porovnání
    ; Načti string literal adresu 
    mov rax, str_7
 mov rdi, rax
    ; Načti string literal adresu 
    mov rax, str_8
 mov rsi, rax
 ; Loop začátek porovnání
 .str_cmp_loop_8:
 mov al, [rdi]
 mov bl, [rsi]
 cmp al, bl
 jne .str_cmp_different_9
 test al, al
 jz .str_cmp_equal_10
 inc rdi
 inc rsi
 jmp .str_cmp_loop_8
 .str_cmp_different_9:
 mov al, 1
 jmp .str_cmp_done_11
 .str_cmp_equal_10:
 xor al, al
 .str_cmp_done_11:
 sete al
 movzx rax, al
    ; Ulož do [t2]
    mov [t2], rax

    ; IR: if t2 == 0 goto L5
    ; Skoč když false
    mov rax, [t2]
    cmp rax, 0
    je L5

    ; IR: print 'str_9'
    ; Vypiš string hodnotu 
    mov rsi, str_9
    mov rdi, format_str
    xor rax, rax
    call printf wrt ..plt

    ; IR: goto L6
    ; Skoč 
    jmp L6

    ; IR: L5:
L5:

    ; IR: print 'str_10'
    ; Vypiš string hodnotu 
    mov rsi, str_10
    mov rdi, format_str
    xor rax, rax
    call printf wrt ..plt

    ; IR: L6:
L6:

    ; IR: print 'str_11'
    ; Vypiš string hodnotu 
    mov rsi, str_11
    mov rdi, format_str
    xor rax, rax
    call printf wrt ..plt

    ; IR: L2:
L2:

    ; Ukončit program 
    mov rax, 0
    mov rsp, rbp
    pop rbp
    ret
