#pragma once

#include <iostream>
#include <string>

using namespace std;

string str_trim(string str);

typedef struct {
  char cmd[10];
  char op1[10];
  char op2[10];
  char op3[10];
  bool empty;
} instruction;

bool next_op(FILE* file, instruction* inst);