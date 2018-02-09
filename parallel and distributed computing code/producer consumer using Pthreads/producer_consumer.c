#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

/*
  implementation of circular queue, thanks to following link:
  https://stackoverflow.com/questions/20619234/circular-queue-implementation
*/

pthread_mutex_t mutex;
pthread_cond_t enq;
pthread_cond_t deq;
struct circqueue* queue;

struct circqueue {
  int front, rear;
  int capacity;
  int *array;
};

struct circqueue *q(int size) {
  struct circqueue *q = malloc(sizeof(struct circqueue));
  if (!q) {
    return NULL;
  }
  q->capacity = size;
  q->front = -1;
  q->rear = -1;
  q->array = malloc(q->capacity * sizeof(int));
  if (!q->array) {
    return NULL;
  }
  return q;
}

/* functions to check the status of the queue */
/* isemptyqueue - checks if the queue has anything in it */
int isemptyqueue(struct circqueue *q) {
  return(q->front == -1);
}

/* isfullqueue - checks if there's space to add more to queue */
int isfullqueue(struct circqueue *q) {
  return((q->rear + 1) % q->capacity == q->rear);
}

/* returns the value of how many items exist in the queue */
int queuesize(struct circqueue *q) {
  return(q->capacity - q->rear + q->front + 1) % q->capacity;
}

/* returns the first element of the queue without removing it */
int peek(struct circqueue *q){
  int data = 0;
  if (queuesize(q) == 0) {
    printf("nothing in queue\n");
    return 0;
  } else {
    pthread_mutex_lock(&mutex);
    data = q->array[q->front];
    pthread_mutex_unlock(&mutex);
    return data;
  }
}


/* functions to add or remove elements from the queue */
/* enqueue - adds an element to the end of the queue if queue isn't full */
void enqueue(struct circqueue *q, int x) {
  pthread_mutex_lock(&mutex);
  if(isfullqueue(q)){
    printf("queue is full. waiting on dequeue.\n");
    pthread_cond_wait(&deq, &mutex);
  }
  q->rear=(q->rear + 1) % q->capacity;
  q->array[q->rear] = x;
  if(q->front == -1) {
    q->front = q->rear;
  }
  pthread_cond_signal(&enq);
  pthread_mutex_unlock(&mutex);
}

/* dequeue - removes the first element of the queue if queue isn't empty */
int dequeue(struct circqueue *q) {
  int data;
  pthread_mutex_lock(&mutex);
  if(isemptyqueue(q)) {
    printf("queue is empty. waiting on enqueue.\n");
    pthread_cond_wait(&enq, &mutex);
  }
  data = q->array[q->front];
  if(q->front == q->rear){
    q->front = q->rear = -1;
  } else {
    q->front = (q->front + 1) % q->capacity;
  }
  pthread_cond_signal(&deq);
  pthread_mutex_unlock(&mutex);
  return data;
}

void* producer(void *p_num){
  int num = (int) p_num;
  srand(time(NULL) * (num + 1));
  int r = rand() % 100;

  enqueue(queue, r);
  printf("thread %d has enqueued %d\n", num, r);

  return NULL;
}

void* consumer(void *c_num){
  int num = (int) c_num;
  int r;
  r = dequeue(queue);
  printf("thread %d has dequeued %d\n", num, r);

  return NULL;
}


int main(int argc, char const *argv[]) {
  long thread;
  int q_size;
  pthread_t* threads;

  /* set up our number of threads */
  threads = malloc((4)*sizeof(pthread_t));

  /* set up our mutex lock for enqueue & dequeue */
  pthread_mutex_init(&mutex, NULL);

  /* set up the condition variables */
  pthread_cond_init(&enq, NULL);
  pthread_cond_init(&deq, NULL);

  /* set up our circular queue */
  q_size = 1;
  queue = q(q_size);

  printf("---------------------------------------------------\n");
  printf("Test example for pthreads producer consumer problem\n");
  printf("Queue size: %d, Producers: 2, Consumers: 2\n", q_size);
  printf("---------------------------------------------------\n");
  printf("Results:\n");

  /* create a producer thread */
  pthread_create(&threads[0], NULL, producer, (void*) 0);
  pthread_create(&threads[1], NULL, producer, (void*) 1);

  /* create a consumer thread */
  pthread_create(&threads[2], NULL, consumer, (void*) (2));
  pthread_create(&threads[3], NULL, consumer, (void*) (3));



  /* wait until all threads have finished */
  for (int thread = 0; thread < 4; thread++) {
    pthread_join(threads[thread], NULL);
  }

  /* now that everything is done using mutex, destroy it again */
  free(threads);
  free(queue);
  pthread_cond_destroy(&enq);
  pthread_cond_destroy(&deq);
  pthread_mutex_destroy(&mutex);
  return 0;
}
