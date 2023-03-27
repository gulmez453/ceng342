#include <stdio.h>

void calculate(int a, int b, double **array, double *vector, double *total) {
  for (int i = 0; i < a; i++) {
    total[i] = 0.0;
    for (int j = 0; j < b; j++) {

      total[i] += array[i][j] * vector[i];

    }

  }

  return;
}
