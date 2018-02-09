#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "funcs.h"

/*
    part2.c - estimated integral using trapezoidal rule in parallel using MPI
      this program reads in from the command line a number 'f' correlating to
      a function in funcs.h, values a & b, denoting the section of the curve
      which should be calculated on, and n, the number of sections into
      which the section from a to b should be divided
    author - Jeremy Swerdlow
*/

/* return the y value calculated by feeding the input x to function which_fxn */
double func_res(int which_fxn, double x) {
  double ret_val;
  switch (which_fxn) {
    case 1:
      ret_val = func1(x);
      break;
    case 2:
      ret_val = func2(x);
      break;
    case 3:
      ret_val = func3(x);
      break;
    case 4:
      ret_val = func4(x);
      break;
    default:
      ret_val = func5(x);
      break;
  }

  return ret_val;
}

/* calculates the value of each trapezoidal slice */
double trap_calc(int fxn, double a, double b, double h) {
  double area;
  double ay, by;

  ay = func_res(fxn, a);
  by = func_res(fxn, b);
  area = (ay + by) / 2 * h;

  return area;
}

int main(int argc, char const *argv[]) {
  int func_num;
  double a, b, n, h;
  int rank, comm_sz;
  double loc_a, loc_b;
  double loc_tot, glob_tot;
  int slice_per;

  /* initialize MPI world */
  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  /* prompt user for the inputs */
  if (rank == 0) {
    printf("please enter your inputs in the format: func_num a b n\n");
    scanf("%d %lf %lf %lf", &func_num, &a, &b, &n);
  }

  /* broadcast the variables to every process */
  MPI_Bcast(&func_num, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(&a, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  MPI_Bcast(&b, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  MPI_Bcast(&n, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  /* calculate the number of slices, and the height */
  slice_per = n / comm_sz;
  h = (b - a) / n;

  /* calculate the local total of summing the trapezoidal slices */
  loc_tot = 0;
  for (int i = 0; i < slice_per; i++) {
    loc_a = a + rank * slice_per * h + i * h;
    loc_b = loc_a + h;
    double area = trap_calc(func_num, loc_a, loc_b, h);
    loc_tot += area;
  }

  /* reduce the local totals of each process into the global total on p 0 */
  MPI_Reduce(&loc_tot, &glob_tot, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

  /* print the estimated integral */
  if (rank == 0) {
    printf("estimated integral from %f to %f with %f slices: %f\n",
    a, b, n, glob_tot);
  }

  /* finish off MPI */
  MPI_Finalize();
  return 0;
}
