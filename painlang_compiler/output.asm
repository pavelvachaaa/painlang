; Profesionální NASM z IR vygenerováno PainGenem  
section .data
    format_int db "%d", 10, 0  ; Formát pro print 

section .bss
    i resq 1
    t0 resq 1
    pavel resq 1
    t1 resq 1

section .text
    global main
    extern printf

main:
    push rbp
    mov rbp, rsp

    ; IR: print 257
    ; Vypiš hodnotu 
    mov rsi, 257
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: i = 0
    ; Načti konstantu 0
    mov rax, 0
    ; Ulož do [i]
    mov [i], rax

    ; IR: L0:
L0:

    ; IR: t0 = i < 10
    ; Načti proměnnou [i]
    mov rax, [i]
    ; Porovnej
    mov rbx, 10
    cmp rax, rbx
    setl al
    movzx rax, al
    ; Ulož do [t0]
    mov [t0], rax

    ; IR: if t0 == 0 goto L1
    ; Skoč když false
    mov rax, [t0]
    cmp rax, 0
    je L1

    ; IR: print pavel
    ; Vypiš hodnotu 
    mov rsi, [pavel]
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: t1 = i + 1
    ; Načti proměnnou [i]
    mov rax, [i]
    ; Sečti konstantu 1
    add rax, 1
    ; Ulož do [t1]
    mov [t1], rax

    ; IR: i = t1
    ; Načti proměnnou [t1]
    mov rax, [t1]
    ; Ulož do [i]
    mov [i], rax

    ; IR: goto L0
    ; Skoč 
    jmp L0

    ; IR: L1:
L1:

    ; IR: print 124
    ; Vypiš hodnotu 
    mov rsi, 124
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; Ukončit program 
    mov rax, 0
    mov rsp, rbp
    pop rbp
    ret
