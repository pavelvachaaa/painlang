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

    ; IR: print _
    ; Vypiš string hodnotu 
    movzx rsi, byte [bool_l_true] 
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; Ukončit program 
    mov rax, 0
    mov rsp, rbp
    pop rbp
    ret
