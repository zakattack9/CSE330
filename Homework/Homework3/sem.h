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
  if (semaphore->val == 0) {
    TCB_t* delQEl = DelQueue(RunQ);
    if (delQEl->threadID > 0) {
			printf("\nProducer %d is waiting\n", delQEl->threadID);
		} else if (delQEl->threadID < 0) {
			printf("\nConsumer %d is waiting\n", -delQEl->threadID);
		}
    AddQueue(semaphore->SemQ, delQEl);
    swapcontext(&(delQEl->context), &(RunQ->head->context)); // must do swapcontext since yield would rotate the new thread to the back of queue
  } else {
    semaphore->val--;
    return;
  }
}

void V(Sem* semaphore) {
  semaphore->val++;
  if (semaphore->val == 0) {
    TCB_t* delQEl = DelQueue(semaphore->SemQ);
    AddQueue(RunQ, delQEl);
  }
  // if (isQueueEmpty(RunQ)) exit(1); // an empty RunQ indicates that all producers or consumers are blocked
  // else yield(); // call yield since no items were deleted from head of RunQ and execute next thread
  yield();
}