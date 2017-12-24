/* -------------------------------------------------------------
  Dining philosophers problem solution using pthread.
  Collaborated on the assignment with Maniz Shrestha
------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

enum {THINKING, HUNGRY, EATING} state[5];
int philosophers[5]={0,1,2,3,4};

pthread_t threads[5];
pthread_mutex_t mutex;
pthread_cond_t cond_vars[5];
time_t t;

/* Checks if both neighbors aren't eating, if they're not, starts to eat */
void test(int i){
  if ((state[(i + 4) % 5] != EATING) &&
      (state[(i + 1) % 5] != EATING) &&
      (state[i] == HUNGRY))
  {
    state[i] = EATING;
    pthread_cond_signal(&cond_vars[i]);
  }
}

/* Locks the mutex, sets state to HUNGRY, then calls test to try and eat */
void pickup_forks(int i)
{
  pthread_mutex_lock(&mutex);
  state[i] = HUNGRY;
  test(i);
  if (state[i] != EATING)
  {
    printf("Philosopher %i can't pick up both forks.\n", i);
    pthread_cond_wait(&cond_vars[i], &mutex);
  }
  pthread_mutex_unlock(&mutex);
}

/* Locks the mutex, returns to THINKING, then calls test for neighbors */
void return_forks(int i)
{
  pthread_mutex_lock(&mutex);
  state[i] = THINKING;

  test((i + 4) % 5);
  test((i + 1) % 5);
  pthread_mutex_unlock(&mutex);
}

/* Overall code for each thread. Thinks then eats 3 times each.*/
void *philosopher(void *_i)
{
  int *i = _i; //reassign so you can show which philosopher is acting
  int st;
  int j;

  for(j = 0; j < 3; j++)
  {
    st = (rand() % 3) + 1;
    printf("Philosopher %i is thinking for %i seconds.\n", *i, st);
    sleep(st);
    pickup_forks(*i);

    st = (rand() % 3) + 1;
    printf("Philosopher %i is eating for %i seconds.\n", *i, st);
    sleep(st);
    return_forks(*i);
  }
  return NULL;
}

/* main func: creates thread for each philosopher, waits for all to finish */
int main()
{
  int i;
  srand((unsigned) time(&t));
  pthread_mutex_init(&mutex, NULL);

  printf("---------------------------------------\n");
  printf("There's a table with five open spots. \n");
  printf("---------------------------------------\n");

  /* Creating each philosopher thread */
  for(i = 0; i < 5; i++)
  {
    pthread_cond_init(&cond_vars[i], NULL);
    state[i] = THINKING;
    pthread_create(&threads[i], NULL, philosopher, &philosophers[i]);
    printf("Philosopher %i has sat down at the table.\n", i);
  }

  /* Waits for each philosopher thread to complete */
  for(i = 0; i < 5; i++)
  {
    pthread_join(threads[i], NULL);
  }

  printf("---------------------------------------\n");
  printf("Five philosophers have finished eating.\n");
  printf("---------------------------------------\n");
  pthread_mutex_destroy(&mutex);
  return 0;
}
