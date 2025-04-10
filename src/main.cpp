#include <iostream>
#include <string>
#include "../hfiles/consts.h" // Include the header file where ADD is declared
#include "../hfiles/helpers.h" // Include the header file where str_trim is declared

using namespace std;

int main(int argc, char* argv[]) {
  string filename = argv[1];
  if(argc != 2) {
    cout << "No filename provided. Using default input.asm" << endl;
    filename = "input.asm";
  }
  
  FILE *file = fopen(filename.c_str(), "r");
  
  string line;
  char buffer[40];
  int linecount = 0;
  while(fgets(buffer, sizeof(buffer), file)) {
    linecount++;
    line = str_trim(string(buffer));
    
    if(line.empty() || line.front() == ';' || line.front() == '#') {
      continue;
    }

    string command = line.substr(0, line.find(' '));
    line = line.substr(line.find(' ') + 1);


    string ops[3];
    int opc = 0;

    // gets the operands in order
    while(line.find(' ') != string::npos) {
      ops[opc++] = line.substr(0, line.find(' '));
      line = line.substr(line.find(' ') + 1);
    }
    if (opc == 3) {
      cout << "Erro : Too many operands on line " << linecount << endl;
      exit(1);
    }
    // to get the last arg (there is space in the end)
    ops[opc++] = line.substr(0, line.find('\0'));
    line = line.substr(line.find('\0') + 1);

    cout << "Op1:" << ops[0] << " Op2:" << ops[1] << " Op3:" << ops[2] << endl;
  }
}