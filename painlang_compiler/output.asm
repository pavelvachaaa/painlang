; Profesionální NASM z IR vygenerováno PainGenem  
section .data
    format_int db "%d", 10, 0  ; Formát pro print 

    format_str db "%s", 10, 0  ; Formát pro řetězce

    str_0 db "Ahoj světe", 0
    str_1 db "Prdel", 0
section .bss
    a resq 1
    t0 resq 1

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

    ; IR: function pavel(1)
pavel:
    push rbp
    mov rbp, rsp
    sub rsp, 64

    ; IR: param a
 ; Parametr a v registru rdi
 mov [a], rdi

    ; IR: t0 = a * a
    ; Načti proměnnou a
    mov rax, a
    ; Vynásob konstantu a
    imul rax, a
    ; Ulož do [t0]
    mov [t0], rax

    ; IR: Neznám tě 20
    ; Načti proměnnou [t0]
    mov rax, [t0]
    ; Return from function
    mov rsp, rbp
    pop rbp
    ret

    ; IR: end function pavel
    ; Function epilogue
    mov rsp, rbp
    pop rbp
    ret

    ; IR: L0:
L0:

    ; IR: print 'str_0'
    ; Vypiš string hodnotu 
    mov rsi, str_0
    mov rdi, format_str
    xor rax, rax
    call printf wrt ..plt

    ; IR: print 'str_1'
    ; Vypiš string hodnotu 
    mov rsi, str_1
    mov rdi, format_str
    xor rax, rax
    call printf wrt ..plt

    ; Ukončit program 
    mov rax, 0
    mov rsp, rbp
    pop rbp
    ret
