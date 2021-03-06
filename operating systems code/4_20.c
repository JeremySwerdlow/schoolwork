#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define MIN_PID 300
#define MAX_PID 5000
#define NUM_THREADS 100
static int bit_map[MAX_PID - MIN_PID] = {0};

/* allocate_map: sets the global bit_map to all 0s */
int allocate_map(void){
  int i = 0;
  for (; i <= MAX_PID - MIN_PID; i++){
    bit_map[i] = 0;
  }
  if(bit_map[MAX_PID - MIN_PID - 1] == 0){
    return 0;
  }
    return -1;
}

/* allocate_pid: finds the next available pid. If none available, returns -1 */
int allocate_pid(void){
  int i = 0;
  while (i <= MAX_PID - MIN_PID){
    if (bit_map[i] == 0){
      bit_map[i] = 1;
      return MIN_PID + i;
    }
    i++;
  }
  return -1;
}

/* release_pid: sets the input pid to 0 in the global bit_map array */
void release_pid(int pid){
  bit_map[pid - MIN_PID] = 0;
}

/* NEW FUNCTIONS FOR 4_20 */

void *runner(void *param){
  int pid;
  pid = allocate_pid();
  printf("Allocated pid: %i\n", pid);
  sleep(rand() % 10 + 1);
  release_pid(pid);
  printf("Released pid: %i\n", pid);
}

void test_pid(void){
  time_t t;
  srand((unsigned) time(&t));

  pthread_t tid[NUM_THREADS];
  pthread_attr_t attr;
  int i;
  for (i = 0; i < NUM_THREADS; i++){
    pthread_attr_init(&attr);
    pthread_create(&tid[i], &attr, runner, NULL);
  }
  for (i = 0; i < NUM_THREADS; i++){
    pthread_join(tid[i], NULL);
  }
}

/* main: runs a set of operations to test the above functions capabilities*/
int main(void){
  allocate_map();
  test_pid();
}
