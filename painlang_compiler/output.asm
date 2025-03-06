; Profesionální NASM z IR vygenerováno PainGenem  
section .data
    format_int db "%d", 10, 0  ; Formát pro print 

section .bss
    x resq 1
    y resq 1
    i resq 1
    t0 resq 1
    j resq 1
    t1 resq 1
    k resq 1
    t2 resq 1
    t3 resq 1
    t4 resq 1
    t5 resq 1
    t6 resq 1
    t7 resq 1
    t8 resq 1

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

    ; IR: j = 0
    ; Načti konstantu 0
    mov rax, 0
    ; Ulož do [j]
    mov [j], rax

    ; IR: L2:
L2:

    ; IR: t1 = j < 10
    ; Načti proměnnou [j]
    mov rax, [j]
    ; Porovnej
    mov rbx, 10
    cmp rax, rbx
    setl al
    movzx rax, al
    ; Ulož do [t1]
    mov [t1], rax

    ; IR: if t1 == 0 goto L3
    ; Skoč když false
    mov rax, [t1]
    cmp rax, 0
    je L3

    ; IR: k = 0
    ; Načti konstantu 0
    mov rax, 0
    ; Ulož do [k]
    mov [k], rax

    ; IR: L4:
L4:

    ; IR: t2 = k < 10
    ; Načti proměnnou [k]
    mov rax, [k]
    ; Porovnej
    mov rbx, 10
    cmp rax, rbx
    setl al
    movzx rax, al
    ; Ulož do [t2]
    mov [t2], rax

    ; IR: if t2 == 0 goto L5
    ; Skoč když false
    mov rax, [t2]
    cmp rax, 0
    je L5

    ; IR: t3 = i * j
    ; Načti proměnnou [i]
    mov rax, [i]
    ; Vynásob konstantu [j]
    imul rax, [j]
    ; Ulož do [t3]
    mov [t3], rax

    ; IR: t4 = t3 - k
    ; Načti proměnnou [t3]
    mov rax, [t3]
    ; Odečti proměnnou [k]
    sub rax, [k]
    ; Ulož do [t4]
    mov [t4], rax

    ; IR: print t4
    ; Vypiš hodnotu 
    mov rsi, [t4]
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: t5 = k + 1
    ; Načti proměnnou [k]
    mov rax, [k]
    ; Sečti konstantu 1
    add rax, 1
    ; Ulož do [t5]
    mov [t5], rax

    ; IR: k = t5
    ; Načti proměnnou [t5]
    mov rax, [t5]
    ; Ulož do [k]
    mov [k], rax

    ; IR: goto L4
    ; Skoč 
    jmp L4

    ; IR: L5:
L5:

    ; IR: t6 = j + 1
    ; Načti proměnnou [j]
    mov rax, [j]
    ; Sečti konstantu 1
    add rax, 1
    ; Ulož do [t6]
    mov [t6], rax

    ; IR: j = t6
    ; Načti proměnnou [t6]
    mov rax, [t6]
    ; Ulož do [j]
    mov [j], rax

    ; IR: goto L2
    ; Skoč 
    jmp L2

    ; IR: L3:
L3:

    ; IR: t7 = i + 1
    ; Načti proměnnou [i]
    mov rax, [i]
    ; Sečti konstantu 1
    add rax, 1
    ; Ulož do [t7]
    mov [t7], rax

    ; IR: i = t7
    ; Načti proměnnou [t7]
    mov rax, [t7]
    ; Ulož do [i]
    mov [i], rax

    ; IR: goto L0
    ; Skoč 
    jmp L0

    ; IR: L1:
L1:

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

    ; IR: t8 = x * 1000
    ; Načti proměnnou [x]
    mov rax, [x]
    ; Vynásob konstantu 1000
    mov rbx, 1000
    imul rax, rbx
    ; Ulož do [t8]
    mov [t8], rax

    ; IR: print t8
    ; Vypiš hodnotu 
    mov rsi, [t8]
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; Ukončit program 
    mov rax, 0
    mov rsp, rbp
    pop rbp
    ret
