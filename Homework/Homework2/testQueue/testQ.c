#include <stdio.h>
#include "qOld.h"

int main() {
  qElement* qEl1 = NewItem(1);
  Queue* queue = InitQueue(qEl1);

  qElement* qEl2 = NewItem(2);
  AddQueue(queue, qEl2);

  qElement* qEl3 = NewItem(3);
  AddQueue(queue, qEl3);

  DelQueue(queue);

  qElement* qEl4 = NewItem(4);
  AddQueue(queue, qEl4);
  RotateQueue(queue);

  PrintQueue(queue);

  return 0;
}