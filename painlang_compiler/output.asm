; Profesionální NASM z IR vygenerováno PainGenem  
section .data
    bool_l_true  db 1                                

    bool_l_false db 0                                

     format_int db "%d", 10, 0  ; Formát pro print 

    format_str db "%s", 10, 0  ; Formát pro řetězce

    str_0 db "škola", 0
    str_1 db "škola", 0
    str_2 db "Smrdí", 0
    str_3 db "Je super", 0
    str_4 db "hello", 0
    str_5 db "world", 0
    str_6 db "Planet", 0
    str_7 db "Not Planet", 0
    str_8 db "apple", 0
    str_9 db "banana", 0
    str_10 db "Not banana", 0
    str_11 db "Banana", 0
    str_12 db "Exactly 100", 0
    str_13 db "123", 0
    str_14 db "123", 0
    str_15 db "String 123", 0
    str_16 db "Not 123", 0
    str_17 db "False confirmed", 0
    str_18 db "Unexpected true", 0
    str_19 db "false", 0
    str_20 db "false", 0
    str_21 db "String false", 0
    str_22 db "Different string", 0
    t0: db "",0
    t1: db "",0
    t2: db "",0
    t3: db "",0
    t4: db "",0
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

    ; IR: print 123
    ; Vypiš hodnotu 
    mov rsi, 123
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: print 999
    ; Vypiš hodnotu 
    mov rsi, 999
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: if 999 == 0 goto L1
    ; Skoč když false
    mov rax, bool_l_false
    cmp rax, 0
    je L1

    ; IR: print 1
    ; Vypiš hodnotu 
    mov rsi, 1
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: goto L2
    ; Skoč 
    jmp L2

    ; IR: L1:
L1:

    ; IR: print 2
    ; Vypiš hodnotu 
    mov rsi, 2
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: L2:
L2:

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

    ; IR: if t0 == 0 goto L3
    ; Skoč když false
    mov rax, [t0]
    cmp rax, 0
    je L3

    ; IR: print 'str_2'
    ; Vypiš string hodnotu 
    mov rsi, str_2
    mov rdi, format_str
    xor rax, rax
    call printf wrt ..plt

    ; IR: goto L4
    ; Skoč 
    jmp L4

    ; IR: L3:
L3:

    ; IR: print 'str_3'
    ; Vypiš string hodnotu 
    mov rsi, str_3
    mov rdi, format_str
    xor rax, rax
    call printf wrt ..plt

    ; IR: L4:
L4:

    ; IR: print 10
    ; Vypiš hodnotu 
    mov rsi, 10
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: t1 = 'str_4' == 'str_5'
 ; String porovnání
    ; Načti string literal adresu 
    mov rax, str_4
 mov rdi, rax
    ; Načti string literal adresu 
    mov rax, str_5
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

    ; IR: if t1 == 0 goto L5
    ; Skoč když false
    mov rax, [t1]
    cmp rax, 0
    je L5

    ; IR: print 'str_6'
    ; Vypiš string hodnotu 
    mov rsi, str_6
    mov rdi, format_str
    xor rax, rax
    call printf wrt ..plt

    ; IR: goto L6
    ; Skoč 
    jmp L6

    ; IR: L5:
L5:

    ; IR: print 'str_7'
    ; Vypiš string hodnotu 
    mov rsi, str_7
    mov rdi, format_str
    xor rax, rax
    call printf wrt ..plt

    ; IR: L6:
L6:

    ; IR: print 1000
    ; Vypiš hodnotu 
    mov rsi, 1000
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: if 1000 == 0 goto L7
    ; Skoč když false
    mov rax, bool_l_true
    cmp rax, 0
    je L7

    ; IR: print 1
    ; Vypiš hodnotu 
    mov rsi, 1
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: goto L8
    ; Skoč 
    jmp L8

    ; IR: L7:
L7:

    ; IR: print 0
    ; Vypiš hodnotu 
    mov rsi, 0
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: L8:
L8:

    ; IR: print 1234
    ; Vypiš hodnotu 
    mov rsi, 1234
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: t2 = 'str_8' != 'str_9'
 ; String porovnání
    ; Načti string literal adresu 
    mov rax, str_8
 mov rdi, rax
    ; Načti string literal adresu 
    mov rax, str_9
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
 setne al
 movzx rax, al
    ; Ulož do [t2]
    mov [t2], rax

    ; IR: if t2 == 0 goto L9
    ; Skoč když false
    mov rax, [t2]
    cmp rax, 0
    je L9

    ; IR: print 'str_10'
    ; Vypiš string hodnotu 
    mov rsi, str_10
    mov rdi, format_str
    xor rax, rax
    call printf wrt ..plt

    ; IR: goto L10
    ; Skoč 
    jmp L10

    ; IR: L9:
L9:

    ; IR: print 'str_11'
    ; Vypiš string hodnotu 
    mov rsi, str_11
    mov rdi, format_str
    xor rax, rax
    call printf wrt ..plt

    ; IR: L10:
L10:

    ; IR: print 'str_12'
    ; Vypiš string hodnotu 
    mov rsi, str_12
    mov rdi, format_str
    xor rax, rax
    call printf wrt ..plt

    ; IR: t3 = 'str_13' == 'str_14'
 ; String porovnání
    ; Načti string literal adresu 
    mov rax, str_13
 mov rdi, rax
    ; Načti string literal adresu 
    mov rax, str_14
 mov rsi, rax
 ; Loop začátek porovnání
 .str_cmp_loop_12:
 mov al, [rdi]
 mov bl, [rsi]
 cmp al, bl
 jne .str_cmp_different_13
 test al, al
 jz .str_cmp_equal_14
 inc rdi
 inc rsi
 jmp .str_cmp_loop_12
 .str_cmp_different_13:
 mov al, 1
 jmp .str_cmp_done_15
 .str_cmp_equal_14:
 xor al, al
 .str_cmp_done_15:
 sete al
 movzx rax, al
    ; Ulož do [t3]
    mov [t3], rax

    ; IR: if t3 == 0 goto L11
    ; Skoč když false
    mov rax, [t3]
    cmp rax, 0
    je L11

    ; IR: print 'str_15'
    ; Vypiš string hodnotu 
    mov rsi, str_15
    mov rdi, format_str
    xor rax, rax
    call printf wrt ..plt

    ; IR: goto L12
    ; Skoč 
    jmp L12

    ; IR: L11:
L11:

    ; IR: print 'str_16'
    ; Vypiš string hodnotu 
    mov rsi, str_16
    mov rdi, format_str
    xor rax, rax
    call printf wrt ..plt

    ; IR: L12:
L12:

    ; IR: if _ == 0 goto L13
    ; Skoč když false
    mov rax, bool_l_true
    cmp rax, 0
    je L13

    ; IR: print 'str_17'
    ; Vypiš string hodnotu 
    mov rsi, str_17
    mov rdi, format_str
    xor rax, rax
    call printf wrt ..plt

    ; IR: goto L14
    ; Skoč 
    jmp L14

    ; IR: L13:
L13:

    ; IR: print 'str_18'
    ; Vypiš string hodnotu 
    mov rsi, str_18
    mov rdi, format_str
    xor rax, rax
    call printf wrt ..plt

    ; IR: L14:
L14:

    ; IR: t4 = 'str_19' == 'str_20'
 ; String porovnání
    ; Načti string literal adresu 
    mov rax, str_19
 mov rdi, rax
    ; Načti string literal adresu 
    mov rax, str_20
 mov rsi, rax
 ; Loop začátek porovnání
 .str_cmp_loop_16:
 mov al, [rdi]
 mov bl, [rsi]
 cmp al, bl
 jne .str_cmp_different_17
 test al, al
 jz .str_cmp_equal_18
 inc rdi
 inc rsi
 jmp .str_cmp_loop_16
 .str_cmp_different_17:
 mov al, 1
 jmp .str_cmp_done_19
 .str_cmp_equal_18:
 xor al, al
 .str_cmp_done_19:
 sete al
 movzx rax, al
    ; Ulož do [t4]
    mov [t4], rax

    ; IR: if t4 == 0 goto L15
    ; Skoč když false
    mov rax, [t4]
    cmp rax, 0
    je L15

    ; IR: print 'str_21'
    ; Vypiš string hodnotu 
    mov rsi, str_21
    mov rdi, format_str
    xor rax, rax
    call printf wrt ..plt

    ; IR: goto L16
    ; Skoč 
    jmp L16

    ; IR: L15:
L15:

    ; IR: print 'str_22'
    ; Vypiš string hodnotu 
    mov rsi, str_22
    mov rdi, format_str
    xor rax, rax
    call printf wrt ..plt

    ; IR: L16:
L16:

    ; Ukončit program 
    mov rax, 0
    mov rsp, rbp
    pop rbp
    ret
