```bash
$ gcc -std=c99 mul3main.c mul3.s
mul3.s:7: Warning: end of file not at end of a line; newline inserted
/usr/bin/ld: warning: /tmp/ccXXXX.o: missing .note.GNU-stack section implies executable stack
/usr/bin/ld: NOTE: This behaviour is deprecated and will be removed in a future version of the linker

$ ./a.out
mul3(3,2,5)=30

# note: Using gcc -O3 enables optimization. Add -O3 for better performance if needed.
