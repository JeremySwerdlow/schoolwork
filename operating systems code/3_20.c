#include <stdio.h>

#define MIN_PID 300
#define MAX_PID 5000
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

/* main: runs a set of operations to test the above functions capabilities*/
int main(void){
  printf("Allocating map. Return value: %i\n", allocate_map());
  int i = 0;
  int pid;
  printf("Allocating 10 new pids:\n");
  for (; i<10; i++){
    pid = allocate_pid();
    printf("\tnew pid: %i\n", pid);
  }
  printf("Setting all values of the bit_map to 1\n");
  for (i = 0; i <= MAX_PID - MIN_PID; i++){
    bit_map[i] = 1;
  }
  printf("Attempting to allocate new pid. Return value: %i\n", allocate_pid());
  printf("Releaseing pid 509\n");
  release_pid(509);
  printf("Attempting to allocate new pid. Return value: %i\n", allocate_pid());
  return 0;
}
