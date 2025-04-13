#include "../hfiles/machine.h"

#include <functional>
#include <vector>

#include <iostream>

void ADD(machine *m) {
  /* ADD operation */
  std::cout << "ADD" << std::endl;
}

void SUB(machine *m) {
  /* SUB operation */
  std::cout << "SUB" << std::endl;
}

void MUL(machine *m) {
  /* MUL operation */
  std::cout << "MUL" << std::endl;
}

void DIV(machine *m) {
  /* DIV operation */
  std::cout << "DIV" << std::endl;
}

void MV(machine *m) {
  /* MV operation */
  std::cout << "MV" << std::endl;
}

void ST(machine *m) {
  /* ST operation */
  std::cout << "ST" << std::endl;
}

void JMP(machine *m) {
  /* JMP operation */
  std::cout << "JMP" << std::endl;
}

void JEQ(machine *m) {
  /* JEQ operation */
  std::cout << "JEQ" << std::endl;
}

void JGT(machine *m) {
  /* JGT operation */
  std::cout << "JGT" << std::endl;
}

void JLT(machine *m) {
  /* JLT operation */
  std::cout << "JLT" << std::endl;
}

void W(machine *m) {
  /* W operation */
  std::cout << "W" << std::endl;
}

void R(machine *m) {
  /* R operation */
  std::cout << "R" << std::endl;
}

void STP(machine *m) {
  /* STP operation */
  std::cout << "STP" << std::endl;
}

std::vector<std::function<void(machine *)>> instruction_set = {
    ADD, SUB, MUL, DIV, MV, ST, JMP, JEQ, JGT, JLT, W, R, STP};