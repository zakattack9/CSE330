// Zak Sakata
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sem.h"

int i = 0;
int wwc; // writer waiting
int wc; // writer in scratchpad*
int rwc; // reader waiting
int rc; // reader in scratchpad*
// *scratchpad is like critical section

int NUM_READERS;
int NUM_WRITERS;

Sem* R_Sem;
Sem* W_Sem;

void reader(int readerID);
void writer(int writerID);

int main() {
  RunQ = InitQueue();
  R_Sem = InitSem(0);
  W_Sem = InitSem(0);
  scanf("%d, %d", &NUM_READERS, &NUM_WRITERS);

  for (int i = 0; i < NUM_READERS + NUM_WRITERS; i++) {
    int threadID;
    scanf("%d", &threadID);
    void* function = threadID > 0 ? reader : writer;
    if (threadID < 0) threadID *= -1;
    start_thread(function, threadID);
  }
  run();

  return 0;
}

void reader(int readerID) {
  if (wwc > 0 || wc > 0) {
    rwc++;
    P(R_Sem);
    rwc--;
  }
  rc++;

  printf("\n This is the %d th reader reading value i = %d for the first time \n", readerID, i );
  yield();
  printf("\n This is the %d th reader reading value i = %d for the second time \n", readerID, i );

  rc--;
  if (rc == 0 && wwc > 0) {
    V(W_Sem);
  }

  TCB_t* item = DelQueue(RunQ);
  if (!isQueueEmpty(RunQ)) {
    swapcontext(&(item->context), &(RunQ->head->context));
  }
}

void writer(int writerID) {
  if (rc > 0 || wc > 0 || rwc > 0 || wwc > 0) {
    wwc++;
    P(W_Sem);
    wwc--;
  }
  wc++;

  i++;
  printf("\n This is the %d th writer writing value i = %d \n", writerID, i );
  yield();
  printf("\n This is the %d th writer verifying value i = %d \n", writerID, i );

  wc--;
  if (rwc > 0) {
    for (int j = 0; j < rwc; j++) V(R_Sem);
  } else if (wwc > 0) {
    V(W_Sem);
  }

  TCB_t* item = DelQueue(RunQ);
  if (!isQueueEmpty(RunQ)) {
    swapcontext(&(item->context), &(RunQ->head->context));
  }
}

/* 
HOW IT WORKS:
- multiple readers in scratchpad
- multiple writers not allowed in scratchpad
- if writers are in scratchpad then readers are not allowed
- if readers are in scratchpad then writers are not allowed

For Readers:
- upon reader entry, it should check if there are any writers or any waiting writers; if there are any writers or waiting writers then wait, else enter scratchpad
- once a reader exits scratchpad, it prioritizes allowing waiting writers to execute to prevent starvation of writers by multiple readers

For Writers:
- upon writer entry, checks for any readers or writers in the scratchpad as well as any readers or writers that are waiting; if any of these conditions are true then the writer waits, else it enters the scratchpad
- once a writer exits scratchpad, it prioritizes allowing ALL waiting readers to execute effectively unblocking all waiting readers from execution; this id done to prevent starvation of readers
*/