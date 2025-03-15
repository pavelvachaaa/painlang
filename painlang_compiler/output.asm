; Profesionální NASM z IR vygenerováno PainGenem  
section .data
    bool_l_true  db 1                                

    bool_l_false db 0                                

     format_int db "%d", 10, 0  ; Formát pro print 

    format_str db "%s", 10, 0  ; Formát pro řetězce

    str_0 db "Jednička", 0
    str_1 db "Nula", 0
    str_2 db "Trojčičkaaa", 0
    str_3 db "Nějaká jiná prasárna", 0
    str_4 db "Ano", 0
    str_5 db "Ne", 0
    str_6 db "nebavyyyyy", 0
    str_7 db "Pavel je v prdeli", 0
    a: db "",0
    promenna_str: db "Pavel je v prdeli",0
    vysledek: db "",0
    t14: db "",0
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
    input resq 1
    t6 resq 1
    t7 resq 1
    t8 resq 1
    t9 resq 1
    b resq 1
    c resq 1
    t10 resq 1
    t11 resq 1
    neco resq 1
    t12 resq 1
    druhe_neco resq 1
    promenna_num resq 1
    promenna_bool resq 1
    z resq 1
    t13 resq 1
    p resq 1

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

    ; IR: function convertNumberToString(1)
convertNumberToString:
    push rbp
    mov rbp, rsp
    sub rsp, 64

    ; IR: param input
 ; Parametr input v registru rdi
 mov [input], rdi

    ; IR: t6 = input == 1
    ; Načti proměnnou [input]
    mov rax, [input]
    ; Porovnej
    mov rbx, 1
    cmp rax, rbx
    sete al
    movzx rax, al
    ; Ulož do [t6]
    mov [t6], rax

    ; IR: if t6 == 0 goto L8
    ; Skoč když false
    mov rax, [t6]
    cmp rax, 0
    je L8

    ; IR: Neznám tě 23
    ; Načti string literal adresu 
    mov rax, str_0
    ; Return from function
    mov rsp, rbp
    pop rbp
    ret

    ; IR: L8:
L8:

    ; IR: t7 = input == 0
    ; Načti proměnnou [input]
    mov rax, [input]
    ; Porovnej
    mov rbx, 0
    cmp rax, rbx
    sete al
    movzx rax, al
    ; Ulož do [t7]
    mov [t7], rax

    ; IR: if t7 == 0 goto L10
    ; Skoč když false
    mov rax, [t7]
    cmp rax, 0
    je L10

    ; IR: Neznám tě 23
    ; Načti string literal adresu 
    mov rax, str_1
    ; Return from function
    mov rsp, rbp
    pop rbp
    ret

    ; IR: L10:
L10:

    ; IR: t8 = input == 3
    ; Načti proměnnou [input]
    mov rax, [input]
    ; Porovnej
    mov rbx, 3
    cmp rax, rbx
    sete al
    movzx rax, al
    ; Ulož do [t8]
    mov [t8], rax

    ; IR: if t8 == 0 goto L12
    ; Skoč když false
    mov rax, [t8]
    cmp rax, 0
    je L12

    ; IR: Neznám tě 23
    ; Načti string literal adresu 
    mov rax, str_2
    ; Return from function
    mov rsp, rbp
    pop rbp
    ret

    ; IR: L12:
L12:

    ; IR: Neznám tě 23
    ; Načti string literal adresu 
    mov rax, str_3
    ; Return from function
    mov rsp, rbp
    pop rbp
    ret

    ; IR: end function convertNumberToString
    ; Function epilogue
    mov rsp, rbp
    pop rbp
    ret

    ; IR: L14:
L14:

    ; IR: function isZero(1)
isZero:
    push rbp
    mov rbp, rsp
    sub rsp, 64

    ; IR: param input
 ; Parametr input v registru rdi
 mov [input], rdi

    ; IR: t9 = input == 0
    ; Načti proměnnou [input]
    mov rax, [input]
    ; Porovnej
    mov rbx, 0
    cmp rax, rbx
    sete al
    movzx rax, al
    ; Ulož do [t9]
    mov [t9], rax

    ; IR: if t9 == 0 goto L15
    ; Skoč když false
    mov rax, [t9]
    cmp rax, 0
    je L15

    ; IR: print 'str_4'
    ; Vypiš string hodnotu 
    mov rsi, str_4
    mov rdi, format_str
    xor rax, rax
    call printf wrt ..plt

    ; IR: Neznám tě 23
    ; Načtin bool (1 byte) z bool_l_true
    mov al, byte [bool_l_true] 
    ; Return from function
    mov rsp, rbp
    pop rbp
    ret

    ; IR: L15:
L15:

    ; IR: print 'str_5'
    ; Vypiš string hodnotu 
    mov rsi, str_5
    mov rdi, format_str
    xor rax, rax
    call printf wrt ..plt

    ; IR: Neznám tě 23
    ; Načtin bool (1 byte) z bool_l_false
    mov al, byte [bool_l_false] 
    ; Return from function
    mov rsp, rbp
    pop rbp
    ret

    ; IR: end function isZero
    ; Function epilogue
    mov rsp, rbp
    pop rbp
    ret

    ; IR: L17:
L17:

    ; IR: function printer(3)
printer:
    push rbp
    mov rbp, rsp
    sub rsp, 64

    ; IR: param a
 ; Parametr a v registru rdi
 mov [a], rdi

    ; IR: param b
 ; Parametr b v registru rsi
 mov [b], rsi

    ; IR: param c
 ; Parametr c v registru rdx
 mov [c], rdx

    ; IR: print a
    ; Vypiš string hodnotu 
    mov rsi, [a]
    mov rdi, format_str
    xor rax, rax
    call printf wrt ..plt

    ; IR: t10 = b + 28
    ; Načti proměnnou [b]
    mov rax, [b]
    ; Sečti konstantu 28
    add rax, 28
    ; Ulož do [t10]
    mov [t10], rax

    ; IR: print t10
    ; Vypiš hodnotu 
    mov rsi, [t10]
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: Neznám tě 23
    ; Načti string literal adresu 
    mov rax, str_6
    ; Return from function
    mov rsp, rbp
    pop rbp
    ret

    ; IR: end function printer
    ; Function epilogue
    mov rsp, rbp
    pop rbp
    ret

    ; IR: L0:
L0:

    ; IR: Neznám tě 24
    ; Načti konstantu 5
    mov rax, 5
     ; Argument 0 v registru rdi
     mov rdi, rax

    ; IR: Neznám tě 22
    ; Align stack 16 bytes 
    ; Call function factorial
    call factorial
    ; Ulož hodnotu z rax
    mov [t11], rax

    ; IR: neco = t11
    ; Načti proměnnou [t11]
    mov rax, [t11]
    ; Ulož do [neco]
    mov [neco], rax

    ; IR: print neco
    ; Vypiš hodnotu 
    mov rsi, [neco]
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
    mov [t12], rax

    ; IR: druhe_neco = t12
    ; Načti proměnnou [t12]
    mov rax, [t12]
    ; Ulož do [druhe_neco]
    mov [druhe_neco], rax

    ; IR: print druhe_neco
    ; Vypiš hodnotu 
    mov rsi, [druhe_neco]
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: promenna_str = 'str_7'
    ; Přiřadit string address
    mov rax, str_7
    mov [promenna_str], rax

    ; IR: promenna_num = 23
    ; Načti konstantu 23
    mov rax, 23
    ; Ulož do [promenna_num]
    mov [promenna_num], rax

    ; IR: promenna_bool = 23
    ; Načtin bool (1 byte) z bool_l_true
    mov al, byte [bool_l_true] 
    ; Ulož do [promenna_bool]
    mov [promenna_bool], rax

    ; IR: z = 23
    ; Načtin bool (1 byte) z bool_l_false
    mov al, byte [bool_l_false] 
    ; Ulož do [z]
    mov [z], rax

    ; IR: Neznám tě 24
    ; Načti konstantu 0
    mov rax, 0
     ; Argument 0 v registru rdi
     mov rdi, rax

    ; IR: Neznám tě 22
    ; Align stack 16 bytes 
    ; Call function isZero
    call isZero
    ; Ulož hodnotu z rax
    mov [t13], rax

    ; IR: p = t13
    ; Načti proměnnou [t13]
    mov rax, [t13]
    ; Ulož do [p]
    mov [p], rax

    ; IR: print p
    ; Vypiš string hodnotu 
    mov rsi, [p]
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: Neznám tě 24
    ; Načti konstantu 2
    mov rax, 2
     ; Argument 0 v registru rdi
     mov rdi, rax

    ; IR: Neznám tě 22
    ; Align stack 16 bytes 
    ; Call function convertNumberToString
    call convertNumberToString
    ; Ulož hodnotu z rax
    mov [t14], rax

    ; IR: vysledek = t14
    ; Načti proměnnou [t14]
    mov rax, [t14]
    ; Ulož do [vysledek]
    mov [vysledek], rax

    ; IR: print vysledek
    ; Vypiš string hodnotu 
    mov rsi, [vysledek]
    mov rdi, format_str
    xor rax, rax
    call printf wrt ..plt

    ; Ukončit program 
    mov rax, 0
    mov rsp, rbp
    pop rbp
    ret
