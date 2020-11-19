#include <ucontext.h>
#include <string.h>

typedef struct TCB_t {
  struct TCB_t* next;
  struct TCB_t* prev;
  ucontext_t context;
} TCB_t;	

void init_TCB (TCB_t *tcb, void *function, void *stackP, int stack_size) {
  memset(tcb, '\0', sizeof(TCB_t)); // allocate memory for a thread control block
  getcontext(&tcb->context); // have to get parent context (info from process that created thread)
  tcb->context.uc_stack.ss_sp = stackP; // tell PCB that stack pointer is stored in stackP
  tcb->context.uc_stack.ss_size = (size_t) stack_size; // tell PCB to set stack size of stack_size
  makecontext(&tcb->context, function, 1); // set the function that thread is going to run where 0 indicates the number of arguments in the function
}
