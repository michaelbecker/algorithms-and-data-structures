#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"



Queue *CreateQueue(void)
{
    Queue *q;

    q = malloc(sizeof(Queue));

    if (q == NULL)
        return NULL;

    q->Count = 0;
    INIT_NODE(&q->Head);

    return q;
}



//
//  We choose to leak memory if this is not empty.
//
void DestroyQueue(Queue *q)
{
    if (q == NULL)
        return;

    free(q);
}



void Enqueue(Queue *q, DlcList *Node)
{
    if (q == NULL)
        return;

    if (Node == NULL)
        return;

    PushToHead(&q->Head, Node);
    q->Count++;
}



/**
 *  May return NULL if there is nothing in the queue.
 */
DlcList *Dequeue(Queue *q)
{
    DlcList *Node;

    if (q == NULL)
        return;

    if (q->Count){
        Node = PopFromTail(&q->Head);
        q->Count--;
        return Node;
    }
    else{
        return NULL;
    }
}


int GetQueueDepth(Queue *q)
{
    if (q == NULL)
        return -1;

    return q->Count;
}


/* gcc -DTEST_QUEUE queue.c double-linked-circular-list.c */
#ifdef TEST_QUEUE

typedef struct TestData_t_{
    //
    //  If we keep List at the beginning, we can do things 
    //  with typecasting.
    //
    DlcList List;
    int Value;

}TestData_t;



TestData_t *MakeTestData(int value)
{
    TestData_t *Data;

    Data = malloc(sizeof(TestData_t));

    if (Data == NULL)
        return NULL;

    Data->Value = value;

    return Data;
}




int main(void)
{
    Queue *q;
    TestData_t *d;
    int i;
    
    q = CreateQueue();

    for (i = 0; i < 10; i++){
        d = MakeTestData(i);
        Enqueue(q, &d->List);
    }
    
    while (GetQueueDepth(q)){
        d = (TestData_t *)Dequeue(q);
        printf("Dequeue %d\n", d->Value);
    }

    return 0;
}


#endif

