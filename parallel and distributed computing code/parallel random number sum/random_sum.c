#include <stdio.h>
#include <mpi.h>
#include <limits.h>

/*
    part1.c - random number sum in parallel using MPI
      this program takes as its argument an integer n,
      then parallely generates n random numbers, and
      sums them using MPI_Reduce
    author - Jeremy Swerdlow
*/

/* generate and sum n values within the range of 0 to max_val */
int random_local_sum(int num_elems, int max_val, int my_rank, int comm_sz) {
  int local_sum;
  int i;

  /* generate the random seed */
  srand((unsigned)time(NULL) * (my_rank + comm_sz));
  for (i = 0; i < num_elems; i++) {
    /* sum up each random number */
    local_sum += rand() % max_val;
  }
  /* lets you see local sum */
  printf("local sum of process %d: %d\n", my_rank, local_sum);
  return local_sum;
}

int main(int argc, char const *argv[]) {
  int comm_sz;
  int my_rank;
  int total_elems = atoi(argv[1]);
  int local_sum;
  int global_sum;
  int max_val = INT_MAX / total_elems;

  /* initialize MPI */
  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  int num_per_proc = total_elems / comm_sz;
  int mod = total_elems % comm_sz;

  /* handle even distribution of work, as close as possible */
  if (my_rank < mod) {
    local_sum = random_local_sum(num_per_proc + 1, max_val, my_rank, comm_sz);
  }
  else {
    local_sum = random_local_sum(num_per_proc, max_val, my_rank, comm_sz);
  }

  /* sum together all the local sums to the global one */
  MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  /* print the global sum */
  if (my_rank == 0) {
    printf("global sum of n random numbers: %d\n", global_sum);
  }


  /* wrap up MPI */
  MPI_Finalize();
  return 0;
}
