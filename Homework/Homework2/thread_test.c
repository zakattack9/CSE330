// Zak Sakata
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "threads.h"

// forward declarations
void thread();

int global_counter = 0;

int main() {
  RunQ = InitQueue();

  int numThreads; // number of thread to execute
  int execThread; // number of times to execute each thread
  char comma;
  scanf("%d", &numThreads);
  scanf("%c", &comma);
  scanf("%d", &execThread);

  if (numThreads == 0) {
    printf("\nNo Threads\n");
    return 0;
  }

  for (int i = 1; i <= numThreads; i++) {
    start_thread(thread, i, execThread);
  }
  run();

  return 0;
}

void thread(int threadID, int execCount) {
  int local_counter = 0;
  while (local_counter < execCount) {
    global_counter += threadID;
    local_counter++;

    printf("\nThis is %d th execution of thread %d with global var value % d\n", local_counter, threadID, global_counter);
    // sleep(1);
    yield();
  }
}
