; Profesionální NASM z IR vygenerováno PainGenem  
section .data
    format_int db "%d", 10, 0  ; Formát pro print 

section .bss
    x resq 1
    y resq 1
    t0 resq 1

section .text
    global main
    extern printf

main:
    push rbp
    mov rbp, rsp

    ; IR: x = 128
    ; Načti konstantu 128
    mov rax, 128
    ; Ulož do [x]
    mov [x], rax

    ; IR: y = 256
    ; Načti konstantu 256
    mov rax, 256
    ; Ulož do [y]
    mov [y], rax

    ; IR: print 123
    ; Vypiš hodnotu 
    mov rsi, 123
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: x = 323
    ; Načti konstantu 323
    mov rax, 323
    ; Ulož do [x]
    mov [x], rax

    ; IR: t0 = x * 1000
    ; Načti proměnnou [x]
    mov rax, [x]
    ; Vynásob konstantu 1000
    mov rbx, 1000
    imul rax, rbx
    ; Ulož do [t0]
    mov [t0], rax

    ; IR: print t0
    ; Vypiš hodnotu 
    mov rsi, [t0]
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; Ukončit program 
    mov rax, 0
    mov rsp, rbp
    pop rbp
    ret
