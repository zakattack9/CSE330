#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "threads.h"

// forward declarations
void thread_1();
void thread_2();
void thread_3();

int global_counter = 0;

int main() {
  queue = InitQueue();
  thread_1();
  thread_2();
  thread_3();
  run();

  return 0;
}

void thread_1() {

}

void thread_2() {

}

void thread_3() {

}
