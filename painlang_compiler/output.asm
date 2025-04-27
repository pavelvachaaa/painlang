; Profesionální NASM z IR vygenerováno PainGenem  
section .data
    bool_l_true  db 1                                

    bool_l_false db 0                                

     format_int db "%d", 10, 0  ; Formát pro print 

    format_str db "%s", 10, 0  ; Formát pro řetězce

section .bss
    z resq 1
    pavel resq 1

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

    ; IR: print -9
    ; Vypiš string hodnotu 
    movzx rsi, byte [bool_l_true] 
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: print -9
    ; Vypiš string hodnotu 
    movzx rsi, byte [bool_l_false] 
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: print -9
    ; Vypiš string hodnotu 
    movzx rsi, byte [bool_l_true] 
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: print -9
    ; Vypiš string hodnotu 
    movzx rsi, byte [bool_l_true] 
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: z = 4
    ; Načti konstantu 4
    mov rax, 4
    ; Ulož do [z]
    mov [z], rax

    ; IR: print 4
    ; Vypiš hodnotu 
    mov rsi, 4
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: z = 3
    ; Načti konstantu 3
    mov rax, 3
    ; Ulož do [z]
    mov [z], rax

    ; IR: z = 2
    ; Načti konstantu 2
    mov rax, 2
    ; Ulož do [z]
    mov [z], rax

    ; IR: print 2
    ; Vypiš hodnotu 
    mov rsi, 2
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: pavel = 8
    ; Načti konstantu 8
    mov rax, 8
    ; Ulož do [pavel]
    mov [pavel], rax

    ; IR: print 8
    ; Vypiš hodnotu 
    mov rsi, 8
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: pavel = 0
    ; Načti konstantu 0
    mov rax, 0
    ; Ulož do [pavel]
    mov [pavel], rax

    ; IR: print 0
    ; Vypiš hodnotu 
    mov rsi, 0
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: pavel = 1
    ; Načti konstantu 1
    mov rax, 1
    ; Ulož do [pavel]
    mov [pavel], rax

    ; IR: pavel = 7
    ; Načti konstantu 7
    mov rax, 7
    ; Ulož do [pavel]
    mov [pavel], rax

    ; IR: print 7
    ; Vypiš hodnotu 
    mov rsi, 7
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; Ukončit program 
    mov rax, 0
    mov rsp, rbp
    pop rbp
    ret
