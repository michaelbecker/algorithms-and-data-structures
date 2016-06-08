#ifndef QUEUE_H__
#define QUEUE_H__

#include "double-linked-circular-list.h"


typedef struct Queue_ {

    int Count;
    DlcList Head;

}Queue;


Queue *CreateQueue(void);

void DestroyQueue(Queue *q);

void Enqueue(Queue *q, DlcList *Node);

DlcList *Dequeue(Queue *q);

int GetQueueDepth(Queue *q);


#endif


