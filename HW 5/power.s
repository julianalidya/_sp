.file   "power.c"
.text
.globl  power
.type   power, @function
power:
    pushq   %rbp
    movq    %rsp, %rbp
    movl    %edi, -4(%rbp)
    movl    %esi, -8(%rbp)
    movl    $1, -12(%rbp)
    movl    $0, -16(%rbp)
.L2:
    cmpl    -8(%rbp), -16(%rbp)
    jge     .L3
    movl    -12(%rbp), %eax
    imull   -4(%rbp), %eax
    movl    %eax, -12(%rbp)
    addl    $1, -16(%rbp)
    jmp     .L2
.L3:
    movl    -12(%rbp), %eax
    popq    %rbp
    ret
