; Profesionální NASM z IR vygenerováno PainGenem  
section .data
    bool_l_true  db 1                                

    bool_l_false db 0                                

     format_int db "%d", 10, 0  ; Formát pro print 

    format_str db "%s", 10, 0  ; Formát pro řetězce

    str_0 db "Jednička", 0
    str_1 db "Nula", 0
    str_2 db "Trojčičkaaa", 0
    str_3 db "Nějaká jiná prasárna", 0
    str_4 db "Ano", 0
    str_5 db "Ne", 0
    str_6 db "nebavyyyyy", 0
    a: db "",0
    vysledek: db "",0
    t6: db "",0
section .bss
    input resq 1
    t0 resq 1
    t1 resq 1
    t2 resq 1
    t3 resq 1
    b resq 1
    c resq 1
    t4 resq 1
    t5 resq 1
    p resq 1

section .text
    global main
    extern printf

main:
    push rbp
    mov rbp, rsp

    ; IR: goto L0
    ; Skoč 
    jmp L0

    ; IR: L1:
L1:

    ; IR: function convertNumberToString(1)
convertNumberToString:
    push rbp
    mov rbp, rsp
    sub rsp, 64

    ; IR: param input
 ; Parametr input v registru rdi
 mov [input], rdi

    ; IR: t0 = input == 1
    ; Načti proměnnou [input]
    mov rax, [input]
    ; Porovnej
    mov rbx, 1
    cmp rax, rbx
    sete al
    movzx rax, al
    ; Ulož do [t0]
    mov [t0], rax

    ; IR: if t0 == 0 goto L2
    ; Skoč když false
    mov rax, [t0]
    cmp rax, 0
    je L2

    ; IR: Neznám tě 23
    ; Načti string literal adresu 
    mov rax, str_0
    ; Return from function
    mov rsp, rbp
    pop rbp
    ret

    ; IR: L2:
L2:

    ; IR: t1 = input == 0
    ; Načti proměnnou [input]
    mov rax, [input]
    ; Porovnej
    mov rbx, 0
    cmp rax, rbx
    sete al
    movzx rax, al
    ; Ulož do [t1]
    mov [t1], rax

    ; IR: if t1 == 0 goto L4
    ; Skoč když false
    mov rax, [t1]
    cmp rax, 0
    je L4

    ; IR: Neznám tě 23
    ; Načti string literal adresu 
    mov rax, str_1
    ; Return from function
    mov rsp, rbp
    pop rbp
    ret

    ; IR: L4:
L4:

    ; IR: t2 = input == 3
    ; Načti proměnnou [input]
    mov rax, [input]
    ; Porovnej
    mov rbx, 3
    cmp rax, rbx
    sete al
    movzx rax, al
    ; Ulož do [t2]
    mov [t2], rax

    ; IR: if t2 == 0 goto L6
    ; Skoč když false
    mov rax, [t2]
    cmp rax, 0
    je L6

    ; IR: Neznám tě 23
    ; Načti string literal adresu 
    mov rax, str_2
    ; Return from function
    mov rsp, rbp
    pop rbp
    ret

    ; IR: L6:
L6:

    ; IR: Neznám tě 23
    ; Načti string literal adresu 
    mov rax, str_3
    ; Return from function
    mov rsp, rbp
    pop rbp
    ret

    ; IR: end function convertNumberToString
    ; Function epilogue
    mov rsp, rbp
    pop rbp
    ret

    ; IR: L8:
L8:

    ; IR: function isZero(1)
isZero:
    push rbp
    mov rbp, rsp
    sub rsp, 64

    ; IR: param input
 ; Parametr input v registru rdi
 mov [input], rdi

    ; IR: t3 = input == 0
    ; Načti proměnnou [input]
    mov rax, [input]
    ; Porovnej
    mov rbx, 0
    cmp rax, rbx
    sete al
    movzx rax, al
    ; Ulož do [t3]
    mov [t3], rax

    ; IR: if t3 == 0 goto L9
    ; Skoč když false
    mov rax, [t3]
    cmp rax, 0
    je L9

    ; IR: print 'str_4'
    ; Vypiš string hodnotu 
    mov rsi, str_4
    mov rdi, format_str
    xor rax, rax
    call printf wrt ..plt

    ; IR: Neznám tě 23
    ; Načtin bool (1 byte) z bool_l_true
    mov al, byte [bool_l_true] 
    ; Return from function
    mov rsp, rbp
    pop rbp
    ret

    ; IR: L9:
L9:

    ; IR: print 'str_5'
    ; Vypiš string hodnotu 
    mov rsi, str_5
    mov rdi, format_str
    xor rax, rax
    call printf wrt ..plt

    ; IR: Neznám tě 23
    ; Načtin bool (1 byte) z bool_l_false
    mov al, byte [bool_l_false] 
    ; Return from function
    mov rsp, rbp
    pop rbp
    ret

    ; IR: end function isZero
    ; Function epilogue
    mov rsp, rbp
    pop rbp
    ret

    ; IR: L11:
L11:

    ; IR: function printer(3)
printer:
    push rbp
    mov rbp, rsp
    sub rsp, 64

    ; IR: param a
 ; Parametr a v registru rdi
 mov [a], rdi

    ; IR: param b
 ; Parametr b v registru rsi
 mov [b], rsi

    ; IR: param c
 ; Parametr c v registru rdx
 mov [c], rdx

    ; IR: print a
    ; Vypiš string hodnotu 
    mov rsi, [a]
    mov rdi, format_str
    xor rax, rax
    call printf wrt ..plt

    ; IR: t4 = b + 28
    ; Načti proměnnou [b]
    mov rax, [b]
    ; Sečti konstantu 28
    add rax, 28
    ; Ulož do [t4]
    mov [t4], rax

    ; IR: print t4
    ; Vypiš hodnotu 
    mov rsi, [t4]
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: Neznám tě 23
    ; Načti string literal adresu 
    mov rax, str_6
    ; Return from function
    mov rsp, rbp
    pop rbp
    ret

    ; IR: end function printer
    ; Function epilogue
    mov rsp, rbp
    pop rbp
    ret

    ; IR: L0:
L0:

    ; IR: Neznám tě 24
    ; Načti konstantu 0
    mov rax, 0
     ; Argument 0 v registru rdi
     mov rdi, rax

    ; IR: Neznám tě 22
    ; Align stack 16 bytes 
    ; Call function isZero
    call isZero
    ; Ulož hodnotu z rax
    mov [t5], rax

    ; IR: p = t5
    ; Načti proměnnou [t5]
    mov rax, [t5]
    ; Ulož do [p]
    mov [p], rax

    ; IR: print p
    ; Vypiš string hodnotu 
    mov rsi, [p]
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: Neznám tě 24
    ; Načti konstantu 2
    mov rax, 2
     ; Argument 0 v registru rdi
     mov rdi, rax

    ; IR: Neznám tě 22
    ; Align stack 16 bytes 
    ; Call function convertNumberToString
    call convertNumberToString
    ; Ulož hodnotu z rax
    mov [t6], rax

    ; IR: vysledek = t6
    ; Načti proměnnou [t6]
    mov rax, [t6]
    ; Ulož do [vysledek]
    mov [vysledek], rax

    ; IR: print vysledek
    ; Vypiš string hodnotu 
    mov rsi, [vysledek]
    mov rdi, format_str
    xor rax, rax
    call printf wrt ..plt

    ; Ukončit program 
    mov rax, 0
    mov rsp, rbp
    pop rbp
    ret
