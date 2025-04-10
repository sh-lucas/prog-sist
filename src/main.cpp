#include "../hfiles/consts.h" // Include the header file where ADD is declared
#include "../hfiles/helpers.h" // Include the header file where str_trim is declared
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
  string filename = argv[1];
  if (argc != 2) {
    cout << "No filename provided. Using default input.asm" << endl;
    filename = "input.asm";
  }

  FILE *file = fopen(filename.c_str(), "r");
  FILE *output = fopen("output.bin", "w+b");

  string line;

  instruction inst;

  int pc = 0;
  while (next_op(file, &inst)) {
    if (!inst.empty) {
      int inst_code = instruction_map.at(string(inst.cmd));

      fprintf(output, "%d ", inst_code);
      fprintf(output, "%s ", inst.op1);
      fprintf(output, "%s ", inst.op2);
      fprintf(output, "%s", inst.op3);
      fprintf(output, "\n");
    }
  }
}