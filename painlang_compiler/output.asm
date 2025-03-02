; Generated NASM code
section .data
    format_int db "%d", 10, 0  ; Format for printf
section .bss
    ; Variables are declared here
    x resq 1
    y resq 1
section .text
    global main
    extern printf

main:
    push rbp
    mov rbp, rsp

    ; Declare variable x
    ; Load constant 128
    mov rax, 128
    mov [x], rax
    ; Declare variable y
    ; Load constant 256
    mov rax, 256
    mov [y], rax
    ; Load constant 123
    mov rax, 123
    ; Print value in rax
    mov rsi, rax
    mov rdi, format_int
    call printf wrt ..plt
    add rsp, 8
    ; Load constant 999
    mov rax, 999
    ; Print value in rax
    mov rsi, rax
    mov rdi, format_int
    call printf wrt ..plt
    add rsp, 8

    ; Return from main
    mov rax, 0
    mov rsp, rbp
    pop rbp
    ret
