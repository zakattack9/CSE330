#include "q.h"

Queue* RunQ;

// creates a thread stack and its to the queue
void start_thread(void (*function)(int, int), int threadID) {
  int stack_size = 8192; // set stack size
  void* stackP = malloc(stack_size); // allocate a stack (via malloc) of a certain size
  TCB_t* tcb = (TCB_t*) malloc(sizeof(TCB_t)); // allocate a TCB (via malloc)
  init_TCB(tcb, function, stackP, stack_size, threadID); // call init_TCB with appropriate arguments
  AddQueue(RunQ, tcb); // call addQ to add this TCB into the “RunQ” which is a global header pointer
}

// runs first thread in queue
void run() {
  ucontext_t parent; // place to store the main context
  getcontext(&parent); // stores process' context in parent var
  swapcontext(&parent, &(RunQ->head->context)); // saves current context (state of stack pointer, function, etc.) and loads next context from thread queue then runs thread
}

// runs next thread in queue and moves current thread to back of queue
void yield() {
  ucontext_t* prev = &(RunQ->head->context); // stores current thread context
  RotateQueue(RunQ); // moves current thread to back of queue and shifts queue forwards
  ucontext_t* next = &(RunQ->head->context); // stores new thread context at head of queue
  swapcontext(prev, next); // swap the context, from previous thread to new thread at head of queue
}
