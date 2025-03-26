; Profesionální NASM z IR vygenerováno PainGenem  
section .data
    bool_l_true  db 1                                

    bool_l_false db 0                                

     format_int db "%d", 10, 0  ; Formát pro print 

    format_str db "%s", 10, 0  ; Formát pro řetězce

    str_0 db "jednicka", 0
    str_1 db "dvojka", 0
    str_2 db "other", 0
    x: db "",0
    t2: db "",0
section .bss
    a resq 1
    t0 resq 1
    t1 resq 1

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

    ; IR: function numToString(1)
numToString:
    push rbp
    mov rbp, rsp
    sub rsp, 64

    ; IR: param a
 ; Parametr a v registru rdi
 mov [a], rdi

    ; IR: t0 = a == 1
    ; Načti proměnnou [a]
    mov rax, [a]
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

    ; IR: L3:
L3:

    ; IR: t1 = a == 2
    ; Načti proměnnou [a]
    mov rax, [a]
    ; Porovnej
    mov rbx, 2
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

    ; IR: L5:
L5:

    ; IR: Neznám tě 23
    ; Načti string literal adresu 
    mov rax, str_2
    ; Return from function
    mov rsp, rbp
    pop rbp
    ret

    ; IR: end function numToString
    ; Function epilogue
    mov rsp, rbp
    pop rbp
    ret

    ; IR: L0:
L0:

    ; IR: Neznám tě 24
    ; Načti konstantu 39
    mov rax, 39
     ; Argument 0 v registru rdi
     mov rdi, rax

    ; IR: Neznám tě 22
    ; Align stack 16 bytes 
    ; Call function numToString
    call numToString
    ; Ulož hodnotu z rax
    mov [t2], rax

    ; IR: x = t2
    ; Načti proměnnou [t2]
    mov rax, [t2]
    ; Ulož do [x]
    mov [x], rax

    ; IR: print x
    ; Vypiš string hodnotu 
    mov rsi, [x]
    mov rdi, format_str
    xor rax, rax
    call printf wrt ..plt

    ; Ukončit program 
    mov rax, 0
    mov rsp, rbp
    pop rbp
    ret
