; Profesionální NASM z IR vygenerováno PainGenem  
section .data
    format_int db "%d", 10, 0  ; Formát pro print 

    format_str db "%s", 10, 0  ; Formát pro řetězce

    str_0 db "Ahoj světe", 0
    str_1 db "Prdel", 0
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
