// #include "../hfiles/consts.h" // Include the header file where ADD is
// declared
#include "../hfiles/consts.h" // Include the header file where ADD is declared
#include "../hfiles/helpers.h" // Include the header file where str_trim is declared
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iostream>
// #include <sstream>
#include <string>

using namespace std;

uint16_t pc = 0; // Contador de Programa (Program Counter)
extern unordered_map<string, uint16_t>
    symbol_map; // Garanta que o mapa de símbolos está acessível

void resolute(const std::string &filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Erro: Não foi possível abrir o arquivo " << filename
              << std::endl;
    // Idealmente, o programa deveria parar aqui se o arquivo não abrir.
    return;
  }

  std::string line;
  uint16_t current_address = 0;

  while (std::getline(file, line)) {
    string trimmed_line = str_trim(line);

    if (trimmed_line.empty() || trimmed_line[0] == '#') {
      continue;
    }

    // Verifica se a linha é uma declaração de label (ex: "loop:")
    if (trimmed_line.back() == ':') {
      std::string label_name =
          trimmed_line.substr(0, trimmed_line.length() - 1);
      symbol_map[label_name] = current_address;
    } else {
      current_address++;
    }
  }
  file.close();
}

int main(int argc, char *argv[]) {
  string filename = "input.asm"; // Valor padrão
  if (argc == 2) {
    filename = argv[1];
  } else {
    cout << "Uso: ./montador <arquivo.asm>. Usando 'input.asm' por padrão."
         << endl;
  }

  // Primeira passada
  resolute(filename);

  // Segunda passada
  FILE *file = fopen(filename.c_str(), "r");
  if (!file) {
    cerr << "Erro fatal: Não foi possível reabrir o arquivo " << filename
         << " para a segunda passada." << endl;
    return 1;
  }

  FILE *output = fopen("output.bin", "w+b");
  if (!output) {
    cerr
        << "Erro fatal: Não foi possível criar o arquivo de saída 'output.bin'."
        << endl;
    fclose(file);
    return 1;
  }

  instruction inst;
  // Processa o arquivo novamente, desta vez gerando o código.
  while (next_op(file, &inst)) {
    if (!inst.empty) {
      fwrite(&inst.cmd, sizeof(uint16_t), 1, output);
      fwrite(&inst.op1, sizeof(uint16_t), 1, output);
      fwrite(&inst.op2, sizeof(uint16_t), 1, output);
      fwrite(&inst.op3, sizeof(uint16_t), 1, output);
    }
  }

  cout << "Arquivo 'output.bin' gerado com sucesso." << endl;

  // Fecha os arquivos
  fclose(file);
  fclose(output);

  return 0;
}
