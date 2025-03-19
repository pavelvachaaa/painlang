; Profesionální NASM z IR vygenerováno PainGenem  
section .data
    bool_l_true  db 1                                

    bool_l_false db 0                                

     format_int db "%d", 10, 0  ; Formát pro print 

    format_str db "%s", 10, 0  ; Formát pro řetězce

    str_0 db "Modulo test:", 0
    str_1 db "isEven test:", 0
    str_2 db "isNotEven test:", 0
section .bss
    base resq 1
    exp resq 1
    result resq 1
    i resq 1
    t0 resq 1
    t1 resq 1
    t2 resq 1
    n resq 1
    fact resq 1
    t3 resq 1
    t4 resq 1
    t5 resq 1
    a resq 1
    b resq 1
    t6 resq 1
    t7 resq 1
    t8 resq 1
    t9 resq 1
    t10 resq 1
    t11 resq 1
    t12 resq 1
    t13 resq 1
    x resq 1
    t14 resq 1
    res resq 1
    t15 resq 1
    resVen resq 1
    t16 resq 1
    t17 resq 1
    t18 resq 1
    t19 resq 1
    t20 resq 1

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

    ; IR: L5:
L5:

    ; IR: t3 = i <= n
    ; Načti proměnnou [i]
    mov rax, [i]
    ; Porovnej
    mov rbx, [n]
    cmp rax, rbx
    setle al
    movzx rax, al
    ; Ulož do [t3]
    mov [t3], rax

    ; IR: if t3 == 0 goto L6
    ; Skoč když false
    mov rax, [t3]
    cmp rax, 0
    je L6

    ; IR: t4 = fact * i
    ; Načti proměnnou [fact]
    mov rax, [fact]
    ; Vynásob konstantu [i]
    imul rax, [i]
    ; Ulož do [t4]
    mov [t4], rax

    ; IR: fact = t4
    ; Načti proměnnou [t4]
    mov rax, [t4]
    ; Ulož do [fact]
    mov [fact], rax

    ; IR: t5 = i + 1
    ; Načti proměnnou [i]
    mov rax, [i]
    ; Sečti konstantu 1
    add rax, 1
    ; Ulož do [t5]
    mov [t5], rax

    ; IR: i = t5
    ; Načti proměnnou [t5]
    mov rax, [t5]
    ; Ulož do [i]
    mov [i], rax

    ; IR: goto L5
    ; Skoč 
    jmp L5

    ; IR: L6:
L6:

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

    ; IR: L7:
L7:

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

    ; IR: t6 = a / b
    ; Načti proměnnou [a]
    mov rax, [a]
    ; Vynuluj 
    xor rdx, rdx
    ; Vyděl proměnnou [b]
    mov rbx, [b]
    idiv rbx
    ; Ulož do [t6]
    mov [t6], rax

    ; IR: t7 = t6 * b
    ; Načti proměnnou [t6]
    mov rax, [t6]
    ; Vynásob konstantu [b]
    imul rax, [b]
    ; Ulož do [t7]
    mov [t7], rax

    ; IR: t8 = a - t7
    ; Načti proměnnou [a]
    mov rax, [a]
    ; Odečti proměnnou [t7]
    sub rax, [t7]
    ; Ulož do [t8]
    mov [t8], rax

    ; IR: Neznám tě 23
    ; Načti proměnnou [t8]
    mov rax, [t8]
    ; Return from function
    mov rsp, rbp
    pop rbp
    ret

    ; IR: end function modulo
    ; Function epilogue
    mov rsp, rbp
    pop rbp
    ret

    ; IR: L8:
L8:

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
    mov [t9], rax

    ; IR: t10 = t9 == 0
    ; Načti proměnnou [t9]
    mov rax, [t9]
    ; Porovnej
    mov rbx, 0
    cmp rax, rbx
    sete al
    movzx rax, al
    ; Ulož do [t10]
    mov [t10], rax

    ; IR: if t10 == 0 goto L9
    ; Skoč když false
    mov rax, [t10]
    cmp rax, 0
    je L9

    ; IR: Neznám tě 23
    ; Načtin bool (1 byte) z bool_l_true
    mov al, byte [bool_l_true] 
    ; Return from function
    mov rsp, rbp
    pop rbp
    ret

    ; IR: goto L10
    ; Skoč 
    jmp L10

    ; IR: L9:
L9:

    ; IR: Neznám tě 23
    ; Načtin bool (1 byte) z bool_l_false
    mov al, byte [bool_l_false] 
    ; Return from function
    mov rsp, rbp
    pop rbp
    ret

    ; IR: L10:
L10:

    ; IR: end function isEven
    ; Function epilogue
    mov rsp, rbp
    pop rbp
    ret

    ; IR: L11:
L11:

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
    mov [t11], rax

    ; IR: t12 = t11 != 0
    ; Načti proměnnou [t11]
    mov rax, [t11]
    ; Porovnej
    mov rbx, 0
    cmp rax, rbx
    setne al
    movzx rax, al
    ; Ulož do [t12]
    mov [t12], rax

    ; IR: if t12 == 0 goto L12
    ; Skoč když false
    mov rax, [t12]
    cmp rax, 0
    je L12

    ; IR: Neznám tě 23
    ; Načtin bool (1 byte) z bool_l_true
    mov al, byte [bool_l_true] 
    ; Return from function
    mov rsp, rbp
    pop rbp
    ret

    ; IR: goto L13
    ; Skoč 
    jmp L13

    ; IR: L12:
L12:

    ; IR: Neznám tě 23
    ; Načtin bool (1 byte) z bool_l_false
    mov al, byte [bool_l_false] 
    ; Return from function
    mov rsp, rbp
    pop rbp
    ret

    ; IR: L13:
L13:

    ; IR: end function isOdd
    ; Function epilogue
    mov rsp, rbp
    pop rbp
    ret

    ; IR: L0:
L0:

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
    mov [t13], rax

    ; IR: x = t13
    ; Načti proměnnou [t13]
    mov rax, [t13]
    ; Ulož do [x]
    mov [x], rax

    ; IR: print x
    ; Vypiš hodnotu 
    mov rsi, [x]
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: Neznám tě 24
    ; Načti konstantu 3
    mov rax, 3
     ; Argument 0 v registru rdi
     mov rdi, rax

    ; IR: Neznám tě 24
    ; Načti konstantu 8
    mov rax, 8
     ; Argument 1 v registru rsi
     mov rsi, rax

    ; IR: Neznám tě 22
    ; Align stack 16 bytes 
    ; Call function modulo
    call modulo
    ; Ulož hodnotu z rax
    mov [t14], rax

    ; IR: res = t14
    ; Načti proměnnou [t14]
    mov rax, [t14]
    ; Ulož do [res]
    mov [res], rax

    ; IR: print 'str_0'
    ; Vypiš string hodnotu 
    mov rsi, str_0
    mov rdi, format_str
    xor rax, rax
    call printf wrt ..plt

    ; IR: print res
    ; Vypiš hodnotu 
    mov rsi, [res]
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: print 'str_1'
    ; Vypiš string hodnotu 
    mov rsi, str_1
    mov rdi, format_str
    xor rax, rax
    call printf wrt ..plt

    ; IR: Neznám tě 24
    ; Načti konstantu 1
    mov rax, 1
     ; Argument 0 v registru rdi
     mov rdi, rax

    ; IR: Neznám tě 22
    ; Align stack 16 bytes 
    ; Call function isEven
    call isEven
    ; Ulož hodnotu z rax
    mov [t15], rax

    ; IR: resVen = t15
    ; Načti proměnnou [t15]
    mov rax, [t15]
    ; Ulož do [resVen]
    mov [resVen], rax

    ; IR: print resVen
    ; Vypiš string hodnotu 
    mov rsi, [resVen]
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: Neznám tě 24
    ; Načti konstantu 44
    mov rax, 44
     ; Argument 0 v registru rdi
     mov rdi, rax

    ; IR: Neznám tě 22
    ; Align stack 16 bytes 
    ; Call function isEven
    call isEven
    ; Ulož hodnotu z rax
    mov [t16], rax

    ; IR: resVen = t16
    ; Načti proměnnou [t16]
    mov rax, [t16]
    ; Ulož do [resVen]
    mov [resVen], rax

    ; IR: print resVen
    ; Vypiš string hodnotu 
    mov rsi, [resVen]
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: Neznám tě 24
    ; Načti konstantu 43
    mov rax, 43
     ; Argument 0 v registru rdi
     mov rdi, rax

    ; IR: Neznám tě 22
    ; Align stack 16 bytes 
    ; Call function isEven
    call isEven
    ; Ulož hodnotu z rax
    mov [t17], rax

    ; IR: resVen = t17
    ; Načti proměnnou [t17]
    mov rax, [t17]
    ; Ulož do [resVen]
    mov [resVen], rax

    ; IR: print resVen
    ; Vypiš string hodnotu 
    mov rsi, [resVen]
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: print 'str_2'
    ; Vypiš string hodnotu 
    mov rsi, str_2
    mov rdi, format_str
    xor rax, rax
    call printf wrt ..plt

    ; IR: Neznám tě 24
    ; Načti konstantu 1
    mov rax, 1
     ; Argument 0 v registru rdi
     mov rdi, rax

    ; IR: Neznám tě 22
    ; Align stack 16 bytes 
    ; Call function isOdd
    call isOdd
    ; Ulož hodnotu z rax
    mov [t18], rax

    ; IR: resVen = t18
    ; Načti proměnnou [t18]
    mov rax, [t18]
    ; Ulož do [resVen]
    mov [resVen], rax

    ; IR: print resVen
    ; Vypiš string hodnotu 
    mov rsi, [resVen]
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: Neznám tě 24
    ; Načti konstantu 44
    mov rax, 44
     ; Argument 0 v registru rdi
     mov rdi, rax

    ; IR: Neznám tě 22
    ; Align stack 16 bytes 
    ; Call function isOdd
    call isOdd
    ; Ulož hodnotu z rax
    mov [t19], rax

    ; IR: resVen = t19
    ; Načti proměnnou [t19]
    mov rax, [t19]
    ; Ulož do [resVen]
    mov [resVen], rax

    ; IR: print resVen
    ; Vypiš string hodnotu 
    mov rsi, [resVen]
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: Neznám tě 24
    ; Načti konstantu 43
    mov rax, 43
     ; Argument 0 v registru rdi
     mov rdi, rax

    ; IR: Neznám tě 22
    ; Align stack 16 bytes 
    ; Call function isOdd
    call isOdd
    ; Ulož hodnotu z rax
    mov [t20], rax

    ; IR: resVen = t20
    ; Načti proměnnou [t20]
    mov rax, [t20]
    ; Ulož do [resVen]
    mov [resVen], rax

    ; IR: print resVen
    ; Vypiš string hodnotu 
    mov rsi, [resVen]
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; Ukončit program 
    mov rax, 0
    mov rsp, rbp
    pop rbp
    ret
