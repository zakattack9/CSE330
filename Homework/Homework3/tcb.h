#include <ucontext.h>
#include <string.h>

typedef struct TCB_t {
  struct TCB_t* next;
  struct TCB_t* prev;
  ucontext_t context;
  int threadID;
} TCB_t;	

void init_TCB (TCB_t *tcb, void *function, void *stackP, int stack_size, int threadID) {
  memset(tcb, '\0', sizeof(TCB_t)); // allocate memory for a thread control block
  getcontext(&tcb->context); // have to get parent context (info from process that created thread)
  tcb->context.uc_stack.ss_sp = stackP; // tell PCB that stack pointer is stored in stackP
  tcb->context.uc_stack.ss_size = (size_t) stack_size; // tell PCB to set stack size of stack_size
  tcb->threadID = threadID; // store threadID in TCB for access in semaphore P() and V() functions
  makecontext(&tcb->context, function, 1, threadID); // set the function that thread is going to run where 0 indicates the number of arguments in the function
}
