; Profesionální NASM z IR vygenerováno PainGenem  
section .data
    format_int db "%d", 10, 0  ; Formát pro print 

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
    prev1 resq 1
    prev2 resq 1
    t4 resq 1
    t5 resq 1
    t6 resq 1
    curr resq 1
    t7 resq 1
    t8 resq 1
    t9 resq 1
    fact resq 1
    t10 resq 1
    t11 resq 1
    t12 resq 1
    fact1 resq 1
    t13 resq 1
    fr1 resq 1
    t14 resq 1
    fr2 resq 1
    t15 resq 1
    t16 resq 1
    vysledek resq 1
    t17 resq 1
    vysledek2 resq 1
    t18 resq 1
    t19 resq 1
    t20 resq 1
    factVyledek resq 1
    t21 resq 1
    cFRes resq 1

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

    ; IR: Neznám tě 20
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

    ; IR: function printFib(1)
printFib:
    push rbp
    mov rbp, rsp
    sub rsp, 64

    ; IR: param n
 ; Parametr n v registru rdi
 mov [n], rdi

    ; IR: t3 = n < 1
    ; Načti proměnnou [n]
    mov rax, [n]
    ; Porovnej
    mov rbx, 1
    cmp rax, rbx
    setl al
    movzx rax, al
    ; Ulož do [t3]
    mov [t3], rax

    ; IR: if t3 == 0 goto L5
    ; Skoč když false
    mov rax, [t3]
    cmp rax, 0
    je L5

    ; IR: Neznám tě 20
    ; Načti konstantu 0
    mov rax, 0
    ; Return from function
    mov rsp, rbp
    pop rbp
    ret

    ; IR: L5:
L5:

    ; IR: prev1 = 1
    ; Načti konstantu 1
    mov rax, 1
    ; Ulož do [prev1]
    mov [prev1], rax

    ; IR: prev2 = 0
    ; Načti konstantu 0
    mov rax, 0
    ; Ulož do [prev2]
    mov [prev2], rax

    ; IR: i = 1
    ; Načti konstantu 1
    mov rax, 1
    ; Ulož do [i]
    mov [i], rax

    ; IR: L7:
L7:

    ; IR: t4 = i <= n
    ; Načti proměnnou [i]
    mov rax, [i]
    ; Porovnej
    mov rbx, [n]
    cmp rax, rbx
    setle al
    movzx rax, al
    ; Ulož do [t4]
    mov [t4], rax

    ; IR: if t4 == 0 goto L8
    ; Skoč když false
    mov rax, [t4]
    cmp rax, 0
    je L8

    ; IR: t5 = i > 2
    ; Načti proměnnou [i]
    mov rax, [i]
    ; Porovnej
    mov rbx, 2
    cmp rax, rbx
    setg al
    movzx rax, al
    ; Ulož do [t5]
    mov [t5], rax

    ; IR: if t5 == 0 goto L9
    ; Skoč když false
    mov rax, [t5]
    cmp rax, 0
    je L9

    ; IR: t6 = prev1 + prev2
    ; Načti proměnnou [prev1]
    mov rax, [prev1]
    ; Sečti proměnnou [prev2]
    add rax, [prev2]
    ; Ulož do [t6]
    mov [t6], rax

    ; IR: curr = t6
    ; Načti proměnnou [t6]
    mov rax, [t6]
    ; Ulož do [curr]
    mov [curr], rax

    ; IR: prev2 = prev1
    ; Načti proměnnou [prev1]
    mov rax, [prev1]
    ; Ulož do [prev2]
    mov [prev2], rax

    ; IR: prev1 = curr
    ; Načti proměnnou [curr]
    mov rax, [curr]
    ; Ulož do [prev1]
    mov [prev1], rax

    ; IR: print curr
    ; Vypiš hodnotu 
    mov rsi, [curr]
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: goto L10
    ; Skoč 
    jmp L10

    ; IR: L9:
L9:

    ; IR: t7 = i == 1
    ; Načti proměnnou [i]
    mov rax, [i]
    ; Porovnej
    mov rbx, 1
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

    ; IR: print prev1
    ; Vypiš hodnotu 
    mov rsi, [prev1]
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: goto L12
    ; Skoč 
    jmp L12

    ; IR: L11:
L11:

    ; IR: t8 = i == 2
    ; Načti proměnnou [i]
    mov rax, [i]
    ; Porovnej
    mov rbx, 2
    cmp rax, rbx
    sete al
    movzx rax, al
    ; Ulož do [t8]
    mov [t8], rax

    ; IR: if t8 == 0 goto L13
    ; Skoč když false
    mov rax, [t8]
    cmp rax, 0
    je L13

    ; IR: print prev2
    ; Vypiš hodnotu 
    mov rsi, [prev2]
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: L13:
L13:

    ; IR: L12:
L12:

    ; IR: L10:
L10:

    ; IR: t9 = i + 1
    ; Načti proměnnou [i]
    mov rax, [i]
    ; Sečti konstantu 1
    add rax, 1
    ; Ulož do [t9]
    mov [t9], rax

    ; IR: i = t9
    ; Načti proměnnou [t9]
    mov rax, [t9]
    ; Ulož do [i]
    mov [i], rax

    ; IR: goto L7
    ; Skoč 
    jmp L7

    ; IR: L8:
L8:

    ; IR: end function printFib
    ; Function epilogue
    mov rsp, rbp
    pop rbp
    ret

    ; IR: L15:
L15:

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

    ; IR: L16:
L16:

    ; IR: t10 = i <= n
    ; Načti proměnnou [i]
    mov rax, [i]
    ; Porovnej
    mov rbx, [n]
    cmp rax, rbx
    setle al
    movzx rax, al
    ; Ulož do [t10]
    mov [t10], rax

    ; IR: if t10 == 0 goto L17
    ; Skoč když false
    mov rax, [t10]
    cmp rax, 0
    je L17

    ; IR: t11 = fact * i
    ; Načti proměnnou [fact]
    mov rax, [fact]
    ; Vynásob konstantu [i]
    imul rax, [i]
    ; Ulož do [t11]
    mov [t11], rax

    ; IR: fact = t11
    ; Načti proměnnou [t11]
    mov rax, [t11]
    ; Ulož do [fact]
    mov [fact], rax

    ; IR: t12 = i + 1
    ; Načti proměnnou [i]
    mov rax, [i]
    ; Sečti konstantu 1
    add rax, 1
    ; Ulož do [t12]
    mov [t12], rax

    ; IR: i = t12
    ; Načti proměnnou [t12]
    mov rax, [t12]
    ; Ulož do [i]
    mov [i], rax

    ; IR: goto L16
    ; Skoč 
    jmp L16

    ; IR: L17:
L17:

    ; IR: Neznám tě 20
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

    ; IR: L18:
L18:

    ; IR: function combineFunction(3)
combineFunction:
    push rbp
    mov rbp, rsp
    sub rsp, 64

    ; IR: param base
 ; Parametr base v registru rdi
 mov [base], rdi

    ; IR: param fact1
 ; Parametr fact1 v registru rsi
 mov [fact1], rsi

    ; IR: param exp
 ; Parametr exp v registru rdx
 mov [exp], rdx

    ; IR: Neznám tě 21
    ; Načti proměnnou [base]
    mov rax, [base]
     ; Argument 0 v registru rdi
     mov rdi, rax

    ; IR: Neznám tě 21
    ; Načti proměnnou [exp]
    mov rax, [exp]
     ; Argument 1 v registru rsi
     mov rsi, rax

    ; IR: Neznám tě 19
    ; Align stack 16 bytes 
    ; Call function pow
    call pow
    ; Ulož hodnotu z rax
    mov [t13], rax

    ; IR: fr1 = t13
    ; Načti proměnnou [t13]
    mov rax, [t13]
    ; Ulož do [fr1]
    mov [fr1], rax

    ; IR: Neznám tě 21
    ; Načti proměnnou [fact1]
    mov rax, [fact1]
     ; Argument 0 v registru rdi
     mov rdi, rax

    ; IR: Neznám tě 19
    ; Align stack 16 bytes 
    ; Call function factorial
    call factorial
    ; Ulož hodnotu z rax
    mov [t14], rax

    ; IR: fr2 = t14
    ; Načti proměnnou [t14]
    mov rax, [t14]
    ; Ulož do [fr2]
    mov [fr2], rax

    ; IR: t15 = fr1 * fr2
    ; Načti proměnnou [fr1]
    mov rax, [fr1]
    ; Vynásob konstantu [fr2]
    imul rax, [fr2]
    ; Ulož do [t15]
    mov [t15], rax

    ; IR: Neznám tě 20
    ; Načti proměnnou [t15]
    mov rax, [t15]
    ; Return from function
    mov rsp, rbp
    pop rbp
    ret

    ; IR: end function combineFunction
    ; Function epilogue
    mov rsp, rbp
    pop rbp
    ret

    ; IR: L0:
L0:

    ; IR: Neznám tě 21
    ; Načti konstantu 2
    mov rax, 2
     ; Argument 0 v registru rdi
     mov rdi, rax

    ; IR: Neznám tě 21
    ; Načti konstantu 6
    mov rax, 6
     ; Argument 1 v registru rsi
     mov rsi, rax

    ; IR: Neznám tě 19
    ; Align stack 16 bytes 
    ; Call function pow
    call pow
    ; Ulož hodnotu z rax
    mov [t16], rax

    ; IR: vysledek = t16
    ; Načti proměnnou [t16]
    mov rax, [t16]
    ; Ulož do [vysledek]
    mov [vysledek], rax

    ; IR: Neznám tě 21
    ; Načti konstantu 2
    mov rax, 2
     ; Argument 0 v registru rdi
     mov rdi, rax

    ; IR: Neznám tě 21
    ; Načti konstantu 6
    mov rax, 6
     ; Argument 1 v registru rsi
     mov rsi, rax

    ; IR: Neznám tě 19
    ; Align stack 16 bytes 
    ; Call function pow
    call pow
    ; Ulož hodnotu z rax
    mov [t17], rax

    ; IR: vysledek2 = t17
    ; Načti proměnnou [t17]
    mov rax, [t17]
    ; Ulož do [vysledek2]
    mov [vysledek2], rax

    ; IR: t18 = vysledek + vysledek2
    ; Načti proměnnou [vysledek]
    mov rax, [vysledek]
    ; Sečti proměnnou [vysledek2]
    add rax, [vysledek2]
    ; Ulož do [t18]
    mov [t18], rax

    ; IR: print t18
    ; Vypiš hodnotu 
    mov rsi, [t18]
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: Neznám tě 21
    ; Načti konstantu 10
    mov rax, 10
     ; Argument 0 v registru rdi
     mov rdi, rax

    ; IR: Neznám tě 19
    ; Align stack 16 bytes 
    ; Call function printFib
    call printFib
    ; Ulož hodnotu z rax
    mov [t19], rax

    ; IR: Neznám tě 21
    ; Načti konstantu 5
    mov rax, 5
     ; Argument 0 v registru rdi
     mov rdi, rax

    ; IR: Neznám tě 19
    ; Align stack 16 bytes 
    ; Call function factorial
    call factorial
    ; Ulož hodnotu z rax
    mov [t20], rax

    ; IR: factVyledek = t20
    ; Načti proměnnou [t20]
    mov rax, [t20]
    ; Ulož do [factVyledek]
    mov [factVyledek], rax

    ; IR: print factVyledek
    ; Vypiš hodnotu 
    mov rsi, [factVyledek]
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; IR: Neznám tě 21
    ; Načti konstantu 2
    mov rax, 2
     ; Argument 0 v registru rdi
     mov rdi, rax

    ; IR: Neznám tě 21
    ; Načti konstantu 5
    mov rax, 5
     ; Argument 1 v registru rsi
     mov rsi, rax

    ; IR: Neznám tě 21
    ; Načti konstantu 3
    mov rax, 3
     ; Argument 2 v registru rdx
     mov rdx, rax

    ; IR: Neznám tě 19
    ; Align stack 16 bytes 
    ; Call function combineFunction
    call combineFunction
    ; Ulož hodnotu z rax
    mov [t21], rax

    ; IR: cFRes = t21
    ; Načti proměnnou [t21]
    mov rax, [t21]
    ; Ulož do [cFRes]
    mov [cFRes], rax

    ; IR: print cFRes
    ; Vypiš hodnotu 
    mov rsi, [cFRes]
    mov rdi, format_int
    xor rax, rax
    call printf wrt ..plt

    ; Ukončit program 
    mov rax, 0
    mov rsp, rbp
    pop rbp
    ret
