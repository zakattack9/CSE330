// Zak Sakata
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sem.h"

int main() {
  RunQ = InitQueue(); // init queue in threads.h
  int BUFFER_SIZE;
  int NUM_PRODUCERS;
  int NUM_CONSUMERS;
  int NUM_TIMES_TO_RUN;
  
  Sem* full = mallocSem(); // tracks if buffer is full
  Sem* empty = mallocSem(); // tracks if buffer is empty

  InitSem(full, 0);
  InitSem(empty, BUFFER_SIZE);

  return 0;
}
