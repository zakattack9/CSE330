// Zak Sakata
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sem.h"

int buffer;
int in, out;

int BUFFER_SIZE;
int NUM_PRODUCERS;
int NUM_CONSUMERS;
int NUM_TIMES_TO_RUN;

int main() {
  RunQ = InitQueue(); // init queue in threads.h
  

  Sem* full = mallocSem(); // tracks if buffer is full
  Sem* empty = mallocSem(); // tracks if buffer is empty

  InitSem(full, 0);
  InitSem(empty, BUFFER_SIZE);

  return 0;
}

void producer(Sem *full, Sem *empty) {
  P(empty);
  // buffer[in] = 
  in = ++in % BUFFER_SIZE;
  V(full);
  yield();
}

void consumer(Sem *full, Sem *empty) {
  P(full);
  // int item = buffer[out];
  out = ++out % BUFFER_SIZE;
  V(empty);
  yield();
}