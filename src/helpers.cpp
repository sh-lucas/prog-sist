#include <string.h>
#include <string>

using namespace std;

string hello = "4";

string str_trim(string str) {
  if (str.back() == '\n')
    str.pop_back();

  while (str.back() == ' ')
    str.pop_back();
  while (str.front() == ' ')
    str.erase(0, 1);

  return str;
}

typedef struct {
  char cmd[10];
  char op1[10];
  char op2[10];
  char op3[10];
  bool empty;
} instruction;

bool next_op(FILE *file, instruction *inst) {
  inst->empty = 0;
  char buffer[40];
  if (!fgets(buffer, 40, file))
    return 0;

  string line = str_trim(string(buffer));

  if (line.empty() || line.front() == ';' || line.front() == '#') {
    // no instruction, but works
    inst->empty = 1;
    return 1;
  }

  string command = line.substr(0, line.find(' '));
  line = line.substr(line.find(' ') + 1);

  string ops[3];
  int opc = 0;

  // gets the operands in order
  while (line.find(' ') != string::npos) {
    ops[opc++] = line.substr(0, line.find(' '));
    line = line.substr(line.find(' ') + 1);
  }
  if (opc == 3) {
    exit(1);
  }
  // to get the last arg (there is space in the end)
  ops[opc++] = line.substr(0, line.find('\0'));
  line = line.substr(line.find('\0') + 1);

  ops[2].pop_back();

  strcpy(inst->cmd, command.c_str());
  strcpy(inst->op1, ops[0].c_str());
  strcpy(inst->op2, ops[1].c_str());
  strcpy(inst->op3, ops[2].c_str());

  return 1;
}