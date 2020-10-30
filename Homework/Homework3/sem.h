#include "threads.h"

typedef struct Sem {
  int val;
  Queue* SemQ; // holds blocked threads
} Sem;

Sem* InitSem(int value) {
  Sem* semaphore = (Sem*) malloc(sizeof(Sem));
  semaphore->val = value;
  semaphore->SemQ = InitQueue();
  return semaphore;
}

void P(Sem* semaphore) {
  while (1) {
    if (semaphore->val <= 0) {
      TCB_t* item = DelQueue(RunQ);
      if (item->threadID > 0) {
        printf("\nProducer %d is waiting\n", item->threadID);
      } else if (item->threadID < 0) {
        printf("\nConsumer %d is waiting\n", -item->threadID);
      }
      // PrintQueue(RunQ);
      AddQueue(semaphore->SemQ, item);
      swapcontext(&(item->context), &(RunQ->head->context)); // must do swapcontext since yield would rotate the new thread to the back of queue
    } else {
      semaphore->val--;
      return;
    }
  }
}

void V(Sem* semaphore) {
  if (semaphore->val <= 0 && !isQueueEmpty(semaphore->SemQ)) {
    TCB_t* item = DelQueue(semaphore->SemQ);
    AddQueue(RunQ, item);
  }
  semaphore->val++;
  // yield(); // call yield since no items were deleted from head of RunQ and execute next thread
}