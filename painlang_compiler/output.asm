; Profesionální NASM z IR vygenerováno PainGenem  
section .data
    format_int db "%d", 10, 0  ; Formát pro print 

section .bss
    fuck resq 1
    bra resq 1
    b resq 1
    t0 resq 1
    t1 resq 1
    x resq 1
    y resq 1
    t2 resq 1

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

    ; IR: function fuck(1)
fuck:
    ; Function prologue for fuck with 1 parameters
    push rbp
    mov rbp, rsp
    sub rsp, 64
    push rbx
    push r12
    push r13
    push r14
    push r15
    mov [rbp-8], rdi

    ; IR: print bra
    ; Vypiš hodnotu 
    mov rsi, [bra]
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: print 1
    ; Vypiš hodnotu 
    mov rsi, 1
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: b = 300
    ; Načti konstantu 300
    mov rax, 300
    ; Ulož do [b]
    mov [b], rax

    ; IR: t0 = bra + b
    ; Načti proměnnou [bra]
    mov rax, [bra]
    ; Sečti proměnnou [b]
    add rax, [b]
    ; Ulož do [t0]
    mov [t0], rax

    ; IR: bra = t0
    ; Načti proměnnou [t0]
    mov rax, [t0]
    ; Ulož do [bra]
    mov [bra], rax

    ; IR: return bra
    ; Return from function fuck
    mov rax, bra
    jmp fuck_epilogue

    ; IR: end function fuck
fuck_epilogue:
    ; Function epilogue for fuck
    pop r15
    pop r14
    pop r13
    pop r12
    pop rbx
    mov rsp, rbp
    pop rbp
    ret

    ; IR: L0:
L0:

    ; IR: param 31
    ; Loading parameter 0
    mov rax, 31
    mov rdi, rax

    ; IR: t1 = call fuck, 1
    ; Calling function fuck with 1 parameters
    call fuck
    mov [t1], rax

    ; IR: print b
    ; Vypiš hodnotu 
    mov rsi, [b]
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

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

    ; IR: t2 = x * 1000
    ; Načti proměnnou [x]
    mov rax, [x]
    ; Vynásob konstantu 1000
    mov rbx, 1000
    imul rax, rbx
    ; Ulož do [t2]
    mov [t2], rax

    ; IR: print t2
    ; Vypiš hodnotu 
    mov rsi, [t2]
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; Ukončit program 
    mov rax, 0
    mov rsp, rbp
    pop rbp
    ret
