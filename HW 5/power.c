#include <stdio.h>

int power(int base, int exp) {
    int result = 1;
    for (int i = 0; i < exp; ++i) {
        result *= base;
    }
    return result;
}

int main() {
    int result = power(2, 3);
    printf("2^3 = %d\n", result);
    return 0;
}
