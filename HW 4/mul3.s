    .globl mul3
mul3:
    mov     rax, rdi        # rax = a
    imul    rax, rsi        # rax *= b
    imul    rax, rdx        # rax *= c
    ret
