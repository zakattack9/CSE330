// Zak Sakata
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sem.h"

int i = 0;
int numReaders;
int numWriters;

Sem* R_Sem;
Sem* W_Sem;

void reader();
void writer();

int main() {
  RunQ = InitQueue();

  R_Sem = InitSem(0);
  W_Sem = InitSem(0);

  scanf("%d, %d", &numReaders, &numWriters);
  for (int i = 0; i < numReaders + numWriters; i++) {

  }

  return 0;
}

void reader() {
  // wwc = any writer waiting (writer wait count)
  // wc = any w inside (wait count)
  if (wwc > 0 || wc > 0) {
    rwc++; // reader wait count
    P(R_Sem);
    rwc--;
  }
  rc++;

  Printf("\n This is the %d th reader reading value i = %d for the first time \n", readerID, i );
  yield();
  Printf("\n This is the %d th reader reading value i = %d for the second time \n", readerID, i );

  rc--;
  if (rc == 0 && wwc > 0) {
    V(W_Sem);
  }

  TCB_t* item = DelQueue(RunQ);
  if (!isQueueEmpty(RunQ)) {
    swapcontext(&(item->context), &(RunQ->head->context));
  }
}

void writer() {
  if (rc > 0 || wc > 0 || rwc > 0 || wwc > 0) {
    wwc++;
    P(W_Sem);
    wwc--;
  }
  wc++;

  i++;
  Printf("\n This is the %d th writer writing value i = %d \n", writerID, i );
  yield();
  Printf("\n This is the %d th writer verifying value i = %d \n", writerID, i );

  wc--;
  if (rwc > 0) {
    for (int j = 0; j < rwc; j++) {
      V(R_Sem);
    }
  } else if (wwc > 0) {
    V(W_Sem);
  }

  TCB_t* item = DelQueue(RunQ);
  if (!isQueueEmpty(RunQ)) {
    swapcontext(&(item->context), &(RunQ->head->context));
  }
}
