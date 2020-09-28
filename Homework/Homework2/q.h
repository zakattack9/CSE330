#include <stdio.h>
#include <stdlib.h>
#include "TCB.h"

#pragma warning(disable: 4996) // for Visual Studio

typedef struct Queue {
  TCB_t* head;
  TCB_t* tail;
} Queue;

// function forward declarations
TCB_t* NewItem(ucontext_t context);
Queue* InitQueue(TCB_t* qHead);
void AddQueue(Queue* queue, TCB_t* qEl);
TCB_t* DelQueue(Queue* queue);
void RotateQueue(Queue* queue);
void PrintQueue(Queue* queue);
int EmptyQueue(Queue* queue);

TCB_t* NewItem(ucontext_t context) {
  TCB_t* qEl = (TCB_t*) malloc(sizeof(TCB_t));
  qEl->context = context;
  qEl->next = NULL;
  return qEl;
}

Queue* InitQueue(TCB_t* qHead) {
  Queue* queue = (Queue*) malloc(sizeof(Queue));
  queue->head = qHead;
  return queue;
}

void AddQueue(Queue* queue, TCB_t* qEl) {
  if (EmptyQueue(queue)) {
    queue->head = qEl;
    queue->tail = qEl;
  } else {
    queue->tail->next = qEl;
    qEl->prev = queue->tail;
    queue->tail = qEl;
  }
}

TCB_t* DelQueue(Queue* queue) {
  if (!EmptyQueue(queue)) {
    TCB_t* delQEl = queue->head;
    if (queue->head == queue->tail) {
      queue->head = queue->tail = NULL;
    } else {
      queue->head = queue->head->next;
    }
    return delQEl;
  }
}

void RotateQueue(Queue* queue) {
  if (!EmptyQueue(queue)) {
    TCB_t* delQEl = DelQueue(queue);
    AddQueue(queue, delQEl);
  }
}

void PrintQueue(Queue* queue) {
  if (!EmptyQueue(queue)) {
    TCB_t* temp = queue->head;
    while(temp != NULL) {
      // printf("PAYLOAD: %d\n", temp->payload);
      temp = temp->next;
    }
  }
}

int EmptyQueue(Queue* queue) {
  if (queue->head == NULL) return 1;
  else return 0;
}