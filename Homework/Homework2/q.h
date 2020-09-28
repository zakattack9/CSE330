#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable: 4996) // for Visual Studio

struct qElement {
  int payload;
  qElement* next;
};

// function forward declarations
qElement* newItem();
qElement* InitQueue(qElement* head);
void AddQueue(int payload);

// global vars
qElement* qHead;

qElement* newItem() {
  qElement* q = malloc(sizeof(qElement));
  return q;
}

qElement* InitQueue() {
  qHead = malloc(sizeof(qElement));
  qHead->payload = 0;
  qHead->next = NULL;
}

void AddQueue(int payload) {
  qElement* q = malloc(sizeof(qElement));
  q->payload = payload;

  qElement* currQEl = head;
  while (currQEl->next != NULL) {
    currQEl = currQEl->next;
  }
  currQEl->next = q;
}

void DelQueue(qElement* )