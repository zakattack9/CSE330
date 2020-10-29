#include "threads.h"

typedef struct Sem {
  int val;
  Queue* runQ;
} Sem;

Sem* mallocSem() {
  return (Sem*) malloc(sizeof(Sem));
}

void InitSem(Sem* semaphore, int value) {
  semaphore->val = value;
}

void P(Sem* semaphore) {
  if (semaphore->val > 0) {
    semaphore->val--;
    return;
  } else {

  }
}

void V(Sem* semaphore) {
  semaphore->val++;
}