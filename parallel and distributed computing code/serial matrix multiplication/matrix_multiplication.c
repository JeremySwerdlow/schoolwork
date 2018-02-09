#include <time.h>
#include <stdlib.h>
#include <stdio.h>

const int print_matrices = 0;
const int print_time = 1;

int main(int argc, char const *argv[]) {
  int n = atoi(argv[1]); /* pulling the size of matrices from command line */
  int a[n][n], b[n][n], c[n][n]; /* our 3 matrices */
  int i, j; /* used for printing */
  int row, col; /* used for identifying current dot product */

  clock_t start, end;
  double total_time;

  /* populate matrices a and b with random numbers */
  srand(time(NULL));
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      a[i][j] = rand() % 10;
      b[i][j] = rand() % 10;
    }
  }

  start = clock();

  /* populate array c with multiplication of matrices a and b */
  for (row = 0; row < n; row++){ /* for each row of matrix a */
    for (col = 0; col < n; col++) { /* and each col of matrix b */
      for (i = 0; i < n; i++){ /* multiply each number in row by each in col */
        c[row][col] += a[row][i] * b[i][col]; /* add it to the column spot */
      }
    }
  }

  end = clock();

  if (print_time) {
    total_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("time taken for multiplying two %d x %d matrices: ", n, n);
    printf("%f seconds\n", total_time);
  }

  /***********
    prints out matrices a, b, and c; this is only run if
      debugging constant is set to 1 (true)
                                              ***********/
  if (print_matrices) {
    printf("matrix a:\n");
    for(i = 0; i < n; i++) {
      for(j = 0; j < n; j++) {
          printf("%d ", a[i][j]);
      }
      printf("\n");
    }

    printf("\nmatrix b:\n");
    for(i = 0; i < n; i++) {
      for(j = 0; j < n; j++) {
          printf("%d ", b[i][j]);
      }
      printf("\n");
    }

    printf("\nmatrix c:\n");
    for(i = 0; i < n; i++) {
      for(j = 0; j < n; j++) {
          printf("%d ", c[i][j]);
      }
      printf("\n");
    }
  }

  return 0;
}
