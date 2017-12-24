#include <stdio.h>
#include <unistd.h>

#define MAX_DIGS 10

/* collatz: Prompts for an integer, and then prints out the sequence generated
    by the Collatz conjecture.  */
void collatz(void){
  /* prompt for the input from the command line, and check if it is correct */
  char c[MAX_DIGS];
  int n;
  while (1){
    printf("Enter a positive integer: ");
    fgets(c, MAX_DIGS, stdin);
    n = atoi(c);
    if (n > 0) break;
    else printf("The input entered wasn't a positive integer. Try again.\n");
  }

  /* fork, and have the child process and print the sequence as parent waits */
  int pid = fork();
  if (pid == 0){
    printf("Generated Sequence:\n");
    while (n != 1){
      printf("%i, ", n);
      if (n % 2 == 0) n = n / 2;
      else n = 3 * n + 1;
    }
    printf("1\n");
  }
  else {
    wait();
  }
}

/* main: calls collatz method, then returns 0. */
int main(void){
  collatz();
  return 0;
}
