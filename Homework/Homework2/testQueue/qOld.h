#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable: 4996) // for Visual Studio

typedef struct qElement {
  int payload;
  struct qElement* next;
} qElement;

typedef struct Queue {
  qElement* head;
} Queue;

// function forward declarations
qElement* NewItem(int payload);
Queue* InitQueue(qElement* qHead);
void AddQueue(Queue* queue, qElement* qEl);
qElement* DelQueue(Queue* queue);
void RotateQueue(Queue* queue);
void PrintQueue(Queue* queue);
int EmptyQueue(Queue* queue);

qElement* NewItem(int payload) {
  qElement* qEl = (qElement*) malloc(sizeof(qElement));
  qEl->payload = payload;
  qEl->next = NULL;
  return qEl;
}

Queue* InitQueue(qElement* qHead) {
  Queue* queue = (Queue*) malloc(sizeof(Queue));
  queue->head = qHead;
  return queue;
}

void AddQueue(Queue* queue, qElement* qEl) {
  if (!EmptyQueue(queue)) {
    qElement* currQEl = queue->head;
    while (currQEl->next != NULL) {
      currQEl = currQEl->next;
    }
    qEl->next = NULL;
    currQEl->next = qEl;
  }
}

qElement* DelQueue(Queue* queue) {
  if (!EmptyQueue(queue)) {
    qElement* delQEl = queue->head;
    queue->head = queue->head->next;
    return delQEl;
  }
}

void RotateQueue(Queue* queue) {
  if (!EmptyQueue(queue)) {
    qElement* delQEl = DelQueue(queue);
    AddQueue(queue, delQEl);
  }
}

void PrintQueue(Queue* queue) {
  if (!EmptyQueue(queue)) {
    qElement* temp = queue->head;
    while(temp != NULL) {
      printf("PAYLOAD: %d\n", temp->payload);
      temp = temp->next;
    }
  }
}

int EmptyQueue(Queue* queue) {
  if (queue->head == NULL) return 1;
  else return 0;
}