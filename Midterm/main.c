#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char *src;

// Forward declarations
int expr();
int term();
int factor();

void skip_whitespace() {
    while (*src == ' ') src++;
}

int number() {
    int result = 0;
    skip_whitespace();
    while (isdigit(*src)) {
        result = result * 10 + (*src - '0');
        src++;
    }
    return result;
}

int factor() {
    skip_whitespace();
    if (*src == '(') {
        src++; // skip '('
        int result = expr();
        if (*src == ')') src++; // skip ')'
        return result;
    } else {
        return number();
    }
}

int term() {
    int result = factor();
    while (*src == '*' || *src == '/') {
        char op = *src++;
        int right = factor();
        if (op == '*') result *= right;
        else result /= right;
    }
    return result;
}

int expr() {
    int result = term();
    while (*src == '+' || *src == '-') {
        char op = *src++;
        int right = term();
        if (op == '+') result += right;
        else result -= right;
    }
    return result;
}

int main() {
    char input[256];
    printf("Mini Interpreter (supports + - * / and parentheses)\n");
    printf("Enter expression: ");
    fgets(input, sizeof(input), stdin);
    src = input;
    int result = expr();
    printf("Result: %d\n", result);
    return 0;
}
