#include "../hfiles/consts.h"
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <sstream>
// #include <iostream>
// #include <cstring>
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
  // varible or reserved word?
  if (symbol_map.count(command)) {
    cmd = symbol_map[command];
  } else {
    cmd = atoi(command.c_str());
    // if it's not a number, declare a new variable
    if (cmd == 0 && command != "0") {
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

  char buffer[256];
  if (!fgets(buffer, sizeof(buffer), file)) {
    inst->empty = true;
    return false; // Fim do arquivo
  }

  string line = str_trim(string(buffer));

  if (line.empty() || line[0] == '#' || line.back() == ':') {
    inst->empty = true;
    return true;
  }

  // streams são complicadas '-'
  std::istringstream iss(line);
  string word1, word2, word3, word4;

  // Extrai até 4 palavras da linha
  iss >> word1 >> word2 >> word3 >> word4;

  // converte para os números =)
  inst->cmd = getCodeFromSymbol(word1);
  inst->op1 = getCodeFromSymbol(word2);
  inst->op2 = getCodeFromSymbol(word3);
  inst->op3 = getCodeFromSymbol(word4);

  return true;
}
