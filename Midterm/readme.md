```
# Mini Arithmetic Interpreter

## Project Description
This project is a simple interpreter written in C. It can parse and evaluate basic arithmetic expressions such as addition, subtraction, multiplication, and division.

Example expression:
```
3 + 5 * (2 - 1)
```
Output:
```
8
```

## Features
- Supports `+`, `-`, `*`, `/` operators
- Supports multi-digit numbers
- Supports parentheses `( )` for precedence
- Uses a simple recursive descent parser

## Files
- `main.c` — the main source code of the interpreter

## How to Run
1. Compile the program:
```bash
gcc -o mini_interpreter main.c
```

2. Run the program:
```bash
./mini_interpreter
```

3. Enter an expression:
```
(4 + 5) * 3
```
Output:
```
27
```

## Component Explanation
- `expr()`: Evaluates expressions using `+` and `-` operators
- `term()`: Evaluates expressions using `*` and `/` operators
- `factor()`: Evaluates numbers or sub-expressions inside parentheses

## Originality
- 100% written independently without AI or copying from other projects
- No external parsing libraries used
- Created as an exercise to understand interpreter functionality

## Additional Documentation
For further explanation, comments are included within the source code.
```
