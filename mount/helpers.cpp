#include "../hfiles/consts.h"
#include <cstdint>
#include <cstdio>
#include <cstdlib>
// #include <sstream>
#include <cstdlib>
// #include <iostream>
#include <cstring>
#include <string>
#include <unordered_map>

using namespace std;

string str_trim(string str) {
  while (!str.empty() &&
         (str.back() == '\n' || str.back() == '\r' || isspace(str.back())))
    str.pop_back();
  while (!str.empty() && isspace(str.front()))
    str.erase(0, 1);
  return str;
}

typedef struct {
  uint16_t cmd;
  uint16_t op1;
  uint16_t op2;
  uint16_t op3;
  bool empty;
} instruction;

extern unordered_map<string, uint16_t> symbol_map;

// the "heap" is compile-time only, and defines variables
int heapPointer = 319;
uint16_t getCodeFromSymbol(string command) {
  if (command.empty()) {
    return 0;
  }

  uint16_t cmd = 0;
  // if it's present in the symbols table
  if (symbol_map.count(command)) {
    cmd = symbol_map[command];
  } else {
    cmd = atoi(command.c_str());
    if (cmd == 0 && command != "0") {
      // if the command is not a number and not in the symbols table
      // we assume it's a variable and return the heap pointer
      cmd = heapPointer--;
      symbol_map[command] = cmd; // add to the symbols table for later use
    }
  }

  return cmd;
}

bool next_op(FILE *file, instruction *inst) {
  inst->empty = false;
  inst->cmd = 0;
  inst->op1 = 0;
  inst->op2 = 0;
  inst->op3 = 0;

  char buffer[100];
  if (!fgets(buffer, sizeof(buffer), file)) {
    inst->empty = true;
    return false;
  }

  string line = str_trim(string(buffer));
  if (line.empty() || line[0] == '#') {
    inst->empty = true;
    return true;
  }

  const char *lineStr = line.c_str();

  // Use a temporary copy to tokenize
  char temp[100];
  strncpy(temp, lineStr, sizeof(temp));
  temp[sizeof(temp) - 1] = '\0'; // ensure null-termination

  // split into 4 different variables
  char word1[100], word2[100], word3[100], word4[100];
  word1[0] = word2[0] = word3[0] = word4[0] = '\0';

  char *token = strtok(temp, " ");
  if (token)
    strncpy(word1, token, 100);
  token = strtok(nullptr, " ");
  if (token)
    strncpy(word2, token, 100);
  token = strtok(nullptr, " ");
  if (token)
    strncpy(word3, token, 100);
  token = strtok(nullptr, " ");
  if (token)
    strncpy(word4, token, 100);

  // assign the variables to the instruction.
  // the function also uses atoi or returns 0 if nothing is present.
  inst->cmd = getCodeFromSymbol(word1);
  inst->op1 = getCodeFromSymbol(word2);
  inst->op2 = getCodeFromSymbol(word3);
  inst->op3 = getCodeFromSymbol(word4);

  // valores que não foram lidos permanecem zero
  return true;
}