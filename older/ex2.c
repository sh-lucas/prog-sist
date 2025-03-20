#include <iostream>
#include <string.h>

#define size 3

using namespace std;

void printMatrix(int matrix[size][size]) {
  printf("\n");
  for(int i = 0; i < size; i++) {
    for(int j = 0; j < size; j++) {
      printf("%4d |", matrix[i][j]);
    }
    printf("\n");
  }
}

void readMatrix(int matrix[size][size]) {
  printf("Fill the matrix: \n");
  int num;

  for(int i = 0; i < size; i++) {
    for(int j = 0; j < size; j++) {
      printf("\n%dx%d: ", i, j);
      scanf("%d", &num);
      matrix[i][j] = num;   
    }
  }
}

int countBiggerThen(int matrix[size][size], int bigger) {
  int count = 0;
  for(int i = 0; i < size; i++) {
    for(int j = 0; j < size; j++) {
      if(matrix[i][j] > bigger) {
        count++;
      }
    }
  }
  return count;
}

void substitute(int matrix[size][size]) {
  for(int i = 0; i < size; i++) {
    if(matrix[1][i] > 20)
      matrix[1][i] = 5;
  }
}

int main () {
  int matrix[size][size];
  readMatrix(matrix);

  printf("Final matrix: ");
  printMatrix(matrix);

  // contar a quantidade de valores
  int biggerCount = countBiggerThen(matrix, 20);
  printf("\nValues bigger then 20: %d", biggerCount);

  printf("\n");
  substitute(matrix);

  printMatrix(matrix);

  // substituir os valores negativos na 2ª linha
}