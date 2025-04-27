; Profesionální NASM z IR vygenerováno PainGenem  
section .data
    bool_l_true  db 1                                

    bool_l_false db 0                                

     format_int db "%d", 10, 0  ; Formát pro print 

    format_str db "%s", 10, 0  ; Formát pro řetězce

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

    ; IR: print -5
    ; Vypiš hodnotu 
    mov rsi, -5
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; Ukončit program 
    mov rax, 0
    mov rsp, rbp
    pop rbp
    ret
