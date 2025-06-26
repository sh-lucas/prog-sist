# ADD                a0 = a1 + a2;
# SUB                a0 = a1 - a2;
# MUL                a0 = a1 * a2;
# DIV                a0 = a1 / a2;
# MV  op1 op2        regs[op1] = mem[op2];
# ST  op1 op2        mem[op1] = regs[op2];
# JMP op1            pc = op1;
# JEQ op1 op2 op3    op1 == op2 --> pc = op3;
# JGT op1 op2 op3    op1 > op2  --> pc = op3;
# JLT op1 op2 op3    op1 < op2  --> pc = op3;
# W   op1            prints mem[op1] to cout;
# R   op1            reads cin to mem[op1];
# STP                stops the machine;

# loop até que input > 10:
LOOP:
  R num1          # le input
  MV r1 num1      # move input para r1
  W num1          # printa input
  MVI r2 10       # move 10 para r2
  JGT r1 r2 END   # se r1 > r2, pula para END
  JMP LOOP        # volta para LOOP
  STP

END:
  STP

# seção de dados:
num1: