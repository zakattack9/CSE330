// Zak Sakata
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sem.h"

void philosopher(int philosopherID);

int NUM_PHILOSOPHERS;
int NUM_ENTRIES;

Sem** Chopsticks;

int main() {
  RunQ = InitQueue();
  scanf("%d, %d", &NUM_PHILOSOPHERS, &NUM_ENTRIES);
  Chopsticks = (Sem**) malloc(NUM_PHILOSOPHERS * sizeof(Sem));

  for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
    Chopsticks[i] = InitSem(1);
  }

  for (int i = 0; i < NUM_ENTRIES; i++) {
    int threadID;
    scanf("%d", &threadID);
    void* function = philosopher;
    start_thread(function, threadID);
  }
  run();

  return 0;
}


void philosopher(int philosopherID) {
  int leftChopstick = (philosopherID - 1) % NUM_PHILOSOPHERS;
  int rightChopstick = philosopherID % NUM_PHILOSOPHERS;

  P(Chopsticks[leftChopstick]);
  yield();
  P(Chopsticks[rightChopstick]);
  yield();
  
  printf("\n Philosopher %d is eating \n", philosopherID);
  V(Chopsticks[leftChopstick]);
  V(Chopsticks[rightChopstick]);

  TCB_t* item = DelQueue(RunQ);
  if (!isQueueEmpty(RunQ)) {
    swapcontext(&(item->context), &(RunQ->head->context));
  }
}
