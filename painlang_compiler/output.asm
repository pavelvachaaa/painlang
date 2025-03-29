; Profesionální NASM z IR vygenerováno PainGenem  
section .data
    bool_l_true  db 1                                

    bool_l_false db 0                                

     format_int db "%d", 10, 0  ; Formát pro print 

    format_str db "%s", 10, 0  ; Formát pro řetězce

section .bss
    base resq 1
    exp resq 1
    result resq 1
    i resq 1
    t0 resq 1
    t1 resq 1
    t2 resq 1
    n resq 1
    t3 resq 1
    t4 resq 1
    t5 resq 1
    t6 resq 1
    t7 resq 1
    t8 resq 1
    fact resq 1
    t9 resq 1
    t10 resq 1
    t11 resq 1
    a resq 1
    b resq 1
    t12 resq 1
    t13 resq 1
    t14 resq 1
    t15 resq 1
    t16 resq 1
    t17 resq 1
    t18 resq 1
    bi resq 1
    t19 resq 1
    t20 resq 1
    t21 resq 1
    t22 resq 1
    res1 resq 1
    t23 resq 1
    t24 resq 1

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

    ; IR: function pow(2)
pow:
    push rbp
    mov rbp, rsp
    sub rsp, 64

    ; IR: param base
 ; Parametr base v registru rdi
 mov [base], rdi

    ; IR: param exp
 ; Parametr exp v registru rsi
 mov [exp], rsi

    ; IR: result = 1
    ; Načti konstantu 1
    mov rax, 1
    ; Ulož do [result]
    mov [result], rax

    ; IR: i = 0
    ; Načti konstantu 0
    mov rax, 0
    ; Ulož do [i]
    mov [i], rax

    ; IR: L2:
L2:

    ; IR: t0 = i < exp
    ; Načti proměnnou [i]
    mov rax, [i]
    ; Porovnej
    mov rbx, [exp]
    cmp rax, rbx
    setl al
    movzx rax, al
    ; Ulož do [t0]
    mov [t0], rax

    ; IR: if t0 == 0 goto L3
    ; Skoč když false
    mov rax, [t0]
    cmp rax, 0
    je L3

    ; IR: t1 = result * base
    ; Načti proměnnou [result]
    mov rax, [result]
    ; Vynásob konstantu [base]
    imul rax, [base]
    ; Ulož do [t1]
    mov [t1], rax

    ; IR: result = t1
    ; Načti proměnnou [t1]
    mov rax, [t1]
    ; Ulož do [result]
    mov [result], rax

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

    ; IR: goto L2
    ; Skoč 
    jmp L2

    ; IR: L3:
L3:

    ; IR: Neznám tě 23
    ; Načti proměnnou [result]
    mov rax, [result]
    ; Return from function
    mov rsp, rbp
    pop rbp
    ret

    ; IR: end function pow
    ; Function epilogue
    mov rsp, rbp
    pop rbp
    ret

    ; IR: L4:
L4:

    ; IR: function isPrime(1)
isPrime:
    push rbp
    mov rbp, rsp
    sub rsp, 64

    ; IR: param n
 ; Parametr n v registru rdi
 mov [n], rdi

    ; IR: t3 = n <= 1
    ; Načti proměnnou [n]
    mov rax, [n]
    ; Porovnej
    mov rbx, 1
    cmp rax, rbx
    setle al
    movzx rax, al
    ; Ulož do [t3]
    mov [t3], rax

    ; IR: if t3 == 0 goto L5
    ; Skoč když false
    mov rax, [t3]
    cmp rax, 0
    je L5

    ; IR: Neznám tě 23
    ; Načtin bool (1 byte) z bool_l_false
    mov al, byte [bool_l_false] 
    ; Return from function
    mov rsp, rbp
    pop rbp
    ret

    ; IR: L5:
L5:

    ; IR: L6:
L6:

    ; IR: i = 2
    ; Načti konstantu 2
    mov rax, 2
    ; Ulož do [i]
    mov [i], rax

    ; IR: L7:
L7:

    ; IR: t4 = i * i
    ; Načti proměnnou [i]
    mov rax, [i]
    ; Vynásob konstantu [i]
    imul rax, [i]
    ; Ulož do [t4]
    mov [t4], rax

    ; IR: t5 = t4 <= n
    ; Načti proměnnou [t4]
    mov rax, [t4]
    ; Porovnej
    mov rbx, [n]
    cmp rax, rbx
    setle al
    movzx rax, al
    ; Ulož do [t5]
    mov [t5], rax

    ; IR: if t5 == 0 goto L8
    ; Skoč když false
    mov rax, [t5]
    cmp rax, 0
    je L8

    ; IR: Neznám tě 24
    ; Načti proměnnou [n]
    mov rax, [n]
     ; Argument 0 v registru rdi
     mov rdi, rax

    ; IR: Neznám tě 24
    ; Načti proměnnou [i]
    mov rax, [i]
     ; Argument 1 v registru rsi
     mov rsi, rax

    ; IR: Neznám tě 22
    ; Align stack 16 bytes 
    ; Call function modulo
    call modulo
    ; Ulož hodnotu z rax
    mov [t6], rax

    ; IR: t7 = t6 == 0
    ; Načti proměnnou [t6]
    mov rax, [t6]
    ; Porovnej
    mov rbx, 0
    cmp rax, rbx
    sete al
    movzx rax, al
    ; Ulož do [t7]
    mov [t7], rax

    ; IR: if t7 == 0 goto L11
    ; Skoč když false
    mov rax, [t7]
    cmp rax, 0
    je L11

    ; IR: Neznám tě 23
    ; Načtin bool (1 byte) z bool_l_false
    mov al, byte [bool_l_false] 
    ; Return from function
    mov rsp, rbp
    pop rbp
    ret

    ; IR: L11:
L11:

    ; IR: L12:
L12:

    ; IR: t8 = i + 1
    ; Načti proměnnou [i]
    mov rax, [i]
    ; Sečti konstantu 1
    add rax, 1
    ; Ulož do [t8]
    mov [t8], rax

    ; IR: i = t8
    ; Načti proměnnou [t8]
    mov rax, [t8]
    ; Ulož do [i]
    mov [i], rax

    ; IR: goto L7
    ; Skoč 
    jmp L7

    ; IR: L8:
L8:

    ; IR: Neznám tě 23
    ; Načtin bool (1 byte) z bool_l_true
    mov al, byte [bool_l_true] 
    ; Return from function
    mov rsp, rbp
    pop rbp
    ret

    ; IR: end function isPrime
    ; Function epilogue
    mov rsp, rbp
    pop rbp
    ret

    ; IR: L13:
L13:

    ; IR: function factorial(1)
factorial:
    push rbp
    mov rbp, rsp
    sub rsp, 64

    ; IR: param n
 ; Parametr n v registru rdi
 mov [n], rdi

    ; IR: fact = 1
    ; Načti konstantu 1
    mov rax, 1
    ; Ulož do [fact]
    mov [fact], rax

    ; IR: i = 1
    ; Načti konstantu 1
    mov rax, 1
    ; Ulož do [i]
    mov [i], rax

    ; IR: L14:
L14:

    ; IR: t9 = i <= n
    ; Načti proměnnou [i]
    mov rax, [i]
    ; Porovnej
    mov rbx, [n]
    cmp rax, rbx
    setle al
    movzx rax, al
    ; Ulož do [t9]
    mov [t9], rax

    ; IR: if t9 == 0 goto L15
    ; Skoč když false
    mov rax, [t9]
    cmp rax, 0
    je L15

    ; IR: t10 = fact * i
    ; Načti proměnnou [fact]
    mov rax, [fact]
    ; Vynásob konstantu [i]
    imul rax, [i]
    ; Ulož do [t10]
    mov [t10], rax

    ; IR: fact = t10
    ; Načti proměnnou [t10]
    mov rax, [t10]
    ; Ulož do [fact]
    mov [fact], rax

    ; IR: t11 = i + 1
    ; Načti proměnnou [i]
    mov rax, [i]
    ; Sečti konstantu 1
    add rax, 1
    ; Ulož do [t11]
    mov [t11], rax

    ; IR: i = t11
    ; Načti proměnnou [t11]
    mov rax, [t11]
    ; Ulož do [i]
    mov [i], rax

    ; IR: goto L14
    ; Skoč 
    jmp L14

    ; IR: L15:
L15:

    ; IR: Neznám tě 23
    ; Načti proměnnou [fact]
    mov rax, [fact]
    ; Return from function
    mov rsp, rbp
    pop rbp
    ret

    ; IR: end function factorial
    ; Function epilogue
    mov rsp, rbp
    pop rbp
    ret

    ; IR: L16:
L16:

    ; IR: function modulo(2)
modulo:
    push rbp
    mov rbp, rsp
    sub rsp, 64

    ; IR: param a
 ; Parametr a v registru rdi
 mov [a], rdi

    ; IR: param b
 ; Parametr b v registru rsi
 mov [b], rsi

    ; IR: t12 = a / b
    ; Načti proměnnou [a]
    mov rax, [a]
    ; Vynuluj 
    xor rdx, rdx
    ; Vyděl proměnnou [b]
    mov rbx, [b]
    idiv rbx
    ; Ulož do [t12]
    mov [t12], rax

    ; IR: t13 = t12 * b
    ; Načti proměnnou [t12]
    mov rax, [t12]
    ; Vynásob konstantu [b]
    imul rax, [b]
    ; Ulož do [t13]
    mov [t13], rax

    ; IR: t14 = a - t13
    ; Načti proměnnou [a]
    mov rax, [a]
    ; Odečti proměnnou [t13]
    sub rax, [t13]
    ; Ulož do [t14]
    mov [t14], rax

    ; IR: Neznám tě 23
    ; Načti proměnnou [t14]
    mov rax, [t14]
    ; Return from function
    mov rsp, rbp
    pop rbp
    ret

    ; IR: end function modulo
    ; Function epilogue
    mov rsp, rbp
    pop rbp
    ret

    ; IR: L17:
L17:

    ; IR: function isEven(1)
isEven:
    push rbp
    mov rbp, rsp
    sub rsp, 64

    ; IR: param n
 ; Parametr n v registru rdi
 mov [n], rdi

    ; IR: Neznám tě 24
    ; Načti proměnnou [n]
    mov rax, [n]
     ; Argument 0 v registru rdi
     mov rdi, rax

    ; IR: Neznám tě 24
    ; Načti konstantu 2
    mov rax, 2
     ; Argument 1 v registru rsi
     mov rsi, rax

    ; IR: Neznám tě 22
    ; Align stack 16 bytes 
    ; Call function modulo
    call modulo
    ; Ulož hodnotu z rax
    mov [t15], rax

    ; IR: t16 = t15 == 0
    ; Načti proměnnou [t15]
    mov rax, [t15]
    ; Porovnej
    mov rbx, 0
    cmp rax, rbx
    sete al
    movzx rax, al
    ; Ulož do [t16]
    mov [t16], rax

    ; IR: if t16 == 0 goto L18
    ; Skoč když false
    mov rax, [t16]
    cmp rax, 0
    je L18

    ; IR: Neznám tě 23
    ; Načtin bool (1 byte) z bool_l_true
    mov al, byte [bool_l_true] 
    ; Return from function
    mov rsp, rbp
    pop rbp
    ret

    ; IR: goto L19
    ; Skoč 
    jmp L19

    ; IR: L18:
L18:

    ; IR: Neznám tě 23
    ; Načtin bool (1 byte) z bool_l_false
    mov al, byte [bool_l_false] 
    ; Return from function
    mov rsp, rbp
    pop rbp
    ret

    ; IR: L19:
L19:

    ; IR: end function isEven
    ; Function epilogue
    mov rsp, rbp
    pop rbp
    ret

    ; IR: L20:
L20:

    ; IR: function isOdd(1)
isOdd:
    push rbp
    mov rbp, rsp
    sub rsp, 64

    ; IR: param n
 ; Parametr n v registru rdi
 mov [n], rdi

    ; IR: Neznám tě 24
    ; Načti proměnnou [n]
    mov rax, [n]
     ; Argument 0 v registru rdi
     mov rdi, rax

    ; IR: Neznám tě 24
    ; Načti konstantu 2
    mov rax, 2
     ; Argument 1 v registru rsi
     mov rsi, rax

    ; IR: Neznám tě 22
    ; Align stack 16 bytes 
    ; Call function modulo
    call modulo
    ; Ulož hodnotu z rax
    mov [t17], rax

    ; IR: t18 = t17 != 0
    ; Načti proměnnou [t17]
    mov rax, [t17]
    ; Porovnej
    mov rbx, 0
    cmp rax, rbx
    setne al
    movzx rax, al
    ; Ulož do [t18]
    mov [t18], rax

    ; IR: if t18 == 0 goto L21
    ; Skoč když false
    mov rax, [t18]
    cmp rax, 0
    je L21

    ; IR: Neznám tě 23
    ; Načtin bool (1 byte) z bool_l_true
    mov al, byte [bool_l_true] 
    ; Return from function
    mov rsp, rbp
    pop rbp
    ret

    ; IR: goto L22
    ; Skoč 
    jmp L22

    ; IR: L21:
L21:

    ; IR: Neznám tě 23
    ; Načtin bool (1 byte) z bool_l_false
    mov al, byte [bool_l_false] 
    ; Return from function
    mov rsp, rbp
    pop rbp
    ret

    ; IR: L22:
L22:

    ; IR: end function isOdd
    ; Function epilogue
    mov rsp, rbp
    pop rbp
    ret

    ; IR: L0:
L0:

    ; IR: bi = 0
    ; Načti konstantu 0
    mov rax, 0
    ; Ulož do [bi]
    mov [bi], rax

    ; IR: L23:
L23:

    ; IR: t19 = bi < 10
    ; Načti proměnnou [bi]
    mov rax, [bi]
    ; Porovnej
    mov rbx, 10
    cmp rax, rbx
    setl al
    movzx rax, al
    ; Ulož do [t19]
    mov [t19], rax

    ; IR: if t19 == 0 goto L24
    ; Skoč když false
    mov rax, [t19]
    cmp rax, 0
    je L24

    ; IR: Neznám tě 24
    ; Načti konstantu 2
    mov rax, 2
     ; Argument 0 v registru rdi
     mov rdi, rax

    ; IR: Neznám tě 24
    ; Načti konstantu 10
    mov rax, 10
     ; Argument 1 v registru rsi
     mov rsi, rax

    ; IR: Neznám tě 22
    ; Align stack 16 bytes 
    ; Call function pow
    call pow
    ; Ulož hodnotu z rax
    mov [t20], rax

    ; IR: t21 = 2 * t20
    ; Načti konstantu 2
    mov rax, 2
    ; Vynásob konstantu [t20]
    imul rax, [t20]
    ; Ulož do [t21]
    mov [t21], rax

    ; IR: t22 = t21 * bi
    ; Načti proměnnou [t21]
    mov rax, [t21]
    ; Vynásob konstantu [bi]
    imul rax, [bi]
    ; Ulož do [t22]
    mov [t22], rax

    ; IR: res1 = t22
    ; Načti proměnnou [t22]
    mov rax, [t22]
    ; Ulož do [res1]
    mov [res1], rax

    ; IR: print res1
    ; Vypiš hodnotu 
    mov rsi, [res1]
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: t23 = bi + 1
    ; Načti proměnnou [bi]
    mov rax, [bi]
    ; Sečti konstantu 1
    add rax, 1
    ; Ulož do [t23]
    mov [t23], rax

    ; IR: bi = t23
    ; Načti proměnnou [t23]
    mov rax, [t23]
    ; Ulož do [bi]
    mov [bi], rax

    ; IR: goto L23
    ; Skoč 
    jmp L23

    ; IR: L24:
L24:

    ; IR: print -15
    ; Vypiš hodnotu 
    mov rsi, -15
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: print -15
    ; Vypiš hodnotu 
    mov rsi, -15
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: print 15
    ; Vypiš hodnotu 
    mov rsi, 15
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: print -4
    ; Vypiš hodnotu 
    mov rsi, -4
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: print 0
    ; Vypiš hodnotu 
    mov rsi, 0
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: Neznám tě 24
    ; Načti konstantu 2
    mov rax, 2
     ; Argument 0 v registru rdi
     mov rdi, rax

    ; IR: Neznám tě 24
    ; Načti konstantu 10
    mov rax, 10
     ; Argument 1 v registru rsi
     mov rsi, rax

    ; IR: Neznám tě 22
    ; Align stack 16 bytes 
    ; Call function pow
    call pow
    ; Ulož hodnotu z rax
    mov [t24], rax

    ; IR: print t24
    ; Vypiš hodnotu 
    mov rsi, [t24]
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; Ukončit program 
    mov rax, 0
    mov rsp, rbp
    pop rbp
    ret
