#include "threads.h"

typedef struct Sem {
  int val;
  Queue* SemQ; // holds blocked threads
} Sem;

Sem* mallocSem() {
  return (Sem*) malloc(sizeof(Sem));
}

void InitSem(Sem* semaphore, int value) {
  semaphore->val = value;
}

void P(Sem* semaphore) {
    if (semaphore->val == 0) {
      TCB_t* item = DeleteQueue(RunQ);
      AddQueue(semaphore->SemQ, item);
      yield(); // or use swap context
      // use while loop to keep checking semaphore value
      // while (1) {
      // }
    } else {
      semaphore->val--;
      return;
    }
}

void V(Sem* semaphore) {
  semaphore->val++;
  TCB_t* item = DeleteQueue(semaphore->SemQ);
  AddQueue(RunQ, item);
}