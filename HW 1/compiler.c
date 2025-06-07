#include <assert.h>
#include "compiler.h"

int E();
void STMT();
void IF();
void BLOCK();

int tempIdx = 0, labelIdx = 0;

#define nextTemp() (tempIdx++)
#define nextLabel() (labelIdx++)
#define emit printf

int isNext(char *set) {
  char eset[SMAX], etoken[SMAX];
  sprintf(eset, " %s ", set);
  sprintf(etoken, " %s ", tokens[tokenIdx]);
  return (tokenIdx < tokenTop && strstr(eset, etoken) != NULL);
}

int isEnd() {
  return tokenIdx >= tokenTop;
}

char *next() {
  return tokens[tokenIdx++];
}

char *skip(char *set) {
  if (isNext(set)) {
    return next();
  } else {
    printf("skip(%s) got %s fail!\n", set, next());
    assert(0);
  }
}

// F = (E) | Number | Id
int F() {
  int f;
  if (isNext("(")) {
    next(); // (
    f = E();
    skip(")");
  } else {
    f = nextTemp();
    char *item = next();
    if (isdigit(*item)) {
      emit("t%d = %s\n", f, item);
    } else {
      if (isNext("++")) {
        next();
        emit("%s = %s + 1\n", item, item);
      }
      emit("t%d = %s\n", f, item);
    }
  }
  return f;
}

// E = F (op E)*
int E() {
  int i1 = F();
  while (isNext("+ - * / < > == != <= >= = & |")) {
    char *op = next();
    int i2 = E();
    int i = nextTemp();
    emit("t%d = t%d %s t%d\n", i, i1, op, i2);
    i1 = i;
  }
  return i1;
}

// ASSIGN = id = E;
void ASSIGN() {
  char *id = next();
  skip("=");
  int e = E();
  skip(";");
  emit("%s = t%d\n", id, e);
}

// WHILE = while (E) STMT
void WHILE() {
  int L1 = nextLabel();
  int L2 = nextLabel();
  emit("(L%d)\n", L1);
  skip("while");
  skip("(");
  int e = E();
  skip(")");
  emit("if not T%d goto L%d\n", e, L2);
  STMT();
  emit("goto L%d\n", L1);
  emit("(L%d)\n", L2);
}

// DOWHILE = do STMT while (E);
void DOWHILE() {
  int L1 = nextLabel();
  emit("(L%d)\n", L1);
  skip("do");
  STMT();
  skip("while");
  skip("(");
  int e = E();
  skip(")");
  skip(";");
  emit("if T%d goto L%d\n", e, L1);
}

// IF = if (E) STMT (else STMT)?
void IF() {
  skip("if");
  skip("(");
  int e = E();
  skip(")");
  int Lelse = nextLabel();
  int Lend = nextLabel();
  emit("if not T%d goto L%d\n", e, Lelse);
  STMT();
  if (isNext("else")) {
    emit("goto L%d\n", Lend);
    emit("(L%d)\n", Lelse);
    skip("else");
    STMT();
    emit("(L%d)\n", Lend);
  } else {
    emit("(L%d)\n", Lelse);
  }
}

// FOR = for (ASSIGN E; ASSIGN) STMT
void FOR() {
  skip("for");
  skip("(");
  ASSIGN(); // init
  int L1 = nextLabel();
  int L2 = nextLabel();
  emit("(L%d)\n", L1);
  int e = E(); // condition
  skip(";");
  emit("if not T%d goto L%d\n", e, L2);

  // simpan index start increment
  int incStart = tokenIdx;
  while (!isNext(")")) next();
  int incEnd = tokenIdx;

  tokenIdx = incStart;
  int tmp = nextTemp();
  emit("// increment\n");
  while (tokenIdx < incEnd) {
    char *id = next();
    if (strcmp(id, "=") == 0) {
      char *var = tokens[tokenIdx - 2];
      int val = E();
      emit("%s = t%d\n", var, val);
    }
  }

  skip(")");
  STMT();
  emit("goto L%d\n", L1);
  emit("(L%d)\n", L2);
}

// STMT = WHILE | DOWHILE | FOR | IF | BLOCK | ASSIGN
void STMT() {
  if (isNext("while"))
    WHILE();
  else if (isNext("do"))
    DOWHILE();
  else if (isNext("for"))
    FOR();
  else if (isNext("if"))
    IF();
  else if (isNext("{"))
    BLOCK();
  else
    ASSIGN();
}

// STMTS = STMT*
void STMTS() {
  while (!isEnd() && !isNext("}")) {
    STMT();
  }
}

// BLOCK = { STMTS }
void BLOCK() {
  skip("{");
  STMTS();
  skip("}");
}

// PROG = STMTS
void PROG() {
  STMTS();
}

void parse() {
  printf("============ parse =============\n");
  tokenIdx = 0;
  PROG();
}
