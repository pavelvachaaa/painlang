; Profesionální NASM z IR vygenerováno PainGenem  
section .data
    format_int db "%d", 10, 0  ; Formát pro print 

section .bss
    pavel resq 1
    z resq 1
    i resq 1
    t0 resq 1
    t1 resq 1
    x resq 1
    t2 resq 1
    krtek resq 1

section .text
    global main
    extern printf

main:
    push rbp
    mov rbp, rsp

    ; IR: pavel = 0
    ; Načti konstantu 0
    mov rax, 0
    ; Ulož do [pavel]
    mov [pavel], rax

    ; IR: z = 3
    ; Načti konstantu 3
    mov rax, 3
    ; Ulož do [z]
    mov [z], rax

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

    ; IR: t1 = pavel + 1
    ; Načti proměnnou [pavel]
    mov rax, [pavel]
    ; Sečti konstantu 1
    add rax, 1
    ; Ulož do [t1]
    mov [t1], rax

    ; IR: pavel = t1
    ; Načti proměnnou [t1]
    mov rax, [t1]
    ; Ulož do [pavel]
    mov [pavel], rax

    ; IR: print pavel
    ; Vypiš hodnotu 
    mov rsi, [pavel]
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: x = 32
    ; Načti konstantu 32
    mov rax, 32
    ; Ulož do [x]
    mov [x], rax

    ; IR: t2 = i + 1
    ; Načti proměnnou [i]
    mov rax, [i]
    ; Sečti konstantu 1
    add rax, 1
    ; Ulož do [t2]
    mov [t2], rax

    ; IR: i = t2
    ; Načti proměnnou [t2]
    mov rax, [t2]
    ; Ulož do [i]
    mov [i], rax

    ; IR: goto L0
    ; Skoč 
    jmp L0

    ; IR: L1:
L1:

    ; IR: print pavel
    ; Vypiš hodnotu 
    mov rsi, [pavel]
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: krtek = 3
    ; Načti konstantu 3
    mov rax, 3
    ; Ulož do [krtek]
    mov [krtek], rax

    ; Ukončit program 
    mov rax, 0
    mov rsp, rbp
    pop rbp
    ret
