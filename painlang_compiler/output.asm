; Generated NASM code
section .data
    format_int db "%d", 10, 0  ; Format for printf
section .bss
    ; Variables are declared here
    x resq 1
section .text
    global main
    extern printf

main:
    push rbp
    mov rbp, rsp

    ; Declare variable x
    ; Load constant 0
    mov rax, 0
    mov [x], rax
    ; Load variable x
    mov rax, [x]
    push rax
    ; Load constant 1
    mov rax, 1
    mov rbx, rax
    pop rax
    cmp rax, rbx
    jg L0
    jmp L1
L0:
    ; Load constant 1
    mov rax, 1
    ; Print value in rax
    mov rsi, rax
    mov rdi, format_int
    call printf wrt ..plt
    add rsp, 8
    jmp L2
L1:
    ; Load constant 2
    mov rax, 2
    ; Print value in rax
    mov rsi, rax
    mov rdi, format_int
    call printf wrt ..plt
    add rsp, 8
L2:

    ; Return from main
    mov rax, 0
    mov rsp, rbp
    pop rbp
    ret
