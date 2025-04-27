; Profesionální NASM z IR vygenerováno PainGenem  
section .data
    bool_l_true  db 1                                

    bool_l_false db 0                                

     format_int db "%d", 10, 0  ; Formát pro print 

    format_str db "%s", 10, 0  ; Formát pro řetězce

section .bss
    a resq 1
    b resq 1
    c resq 1

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

    ; IR: print 11
    ; Vypiš hodnotu 
    mov rsi, 11
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: print 21
    ; Vypiš hodnotu 
    mov rsi, 21
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: print 7
    ; Vypiš hodnotu 
    mov rsi, 7
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: print -5
    ; Vypiš hodnotu 
    mov rsi, -5
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: print 4
    ; Vypiš hodnotu 
    mov rsi, 4
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: print 24
    ; Vypiš hodnotu 
    mov rsi, 24
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: print 12
    ; Vypiš hodnotu 
    mov rsi, 12
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: print 10
    ; Vypiš hodnotu 
    mov rsi, 10
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: print -5
    ; Vypiš hodnotu 
    mov rsi, -5
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: print -15
    ; Vypiš hodnotu 
    mov rsi, -15
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: a = 5
    ; Načti konstantu 5
    mov rax, 5
    ; Ulož do [a]
    mov [a], rax

    ; IR: b = 2
    ; Načti konstantu 2
    mov rax, 2
    ; Ulož do [b]
    mov [b], rax

    ; IR: c = 7
    ; Načti konstantu 7
    mov rax, 7
    ; Ulož do [c]
    mov [c], rax

    ; IR: print 9
    ; Vypiš hodnotu 
    mov rsi, 9
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: print -9
    ; Vypiš hodnotu 
    mov rsi, -9
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: print -49
    ; Vypiš hodnotu 
    mov rsi, -49
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: print 17
    ; Vypiš hodnotu 
    mov rsi, 17
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: print -45
    ; Vypiš hodnotu 
    mov rsi, -45
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: print 0
    ; Vypiš hodnotu 
    mov rsi, 0
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: print 25
    ; Vypiš hodnotu 
    mov rsi, 25
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: print 4
    ; Vypiš hodnotu 
    mov rsi, 4
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; Ukončit program 
    mov rax, 0
    mov rsp, rbp
    pop rbp
    ret
