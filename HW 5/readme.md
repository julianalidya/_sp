power.c  
執行 power.c

```bash
gcc power.c
./a.exe
```

產生組合語言 .s 檔

```bash
gcc -S power.c
```

產生目的檔 .o 檔

```bash
gcc -c power.c
```

將該目的檔反組譯

```bash
objdump -d power.o
```

```asm
0000000000000000 <power>:
   0:   55                      push   %rbp
   1:   48 89 e5                mov    %rsp,%rbp
   4:   89 7d fc                mov    %edi,-0x4(%rbp)
   7:   89 75 f8                mov    %esi,-0x8(%rbp)
   a:   c7 45 f4 01 00 00 00    movl   $0x1,-0xc(%rbp)
```

印出該目的檔的表頭

```bash
objdump -h power.o
```

```text
Sections:
Idx Name          Size      VMA               LMA               File off  Algn
  0 .text         0000004c  0000000000000000  0000000000000000  00000040  2**4
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
```
