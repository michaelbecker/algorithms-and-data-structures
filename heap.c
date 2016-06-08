#include <stdio.h>
#include <stdlib.h>

/*
 *  This is really a binary heap.
 *
 *  http://en.wikipedia.org/wiki/Binary_heap
 */

typedef struct Node_ {

    int Key;
    int Data; // Could change...

}Node;


typedef struct Heap_ {

    int MaxNodes;
    int CurNodes;
    Node *Nodes;    // Array of Nodes, 

}Heap;


/*
 *  @returns pointer to heap, or NULL on error.
 */
Heap *CreateHeap (int MaxNodes)
{
    Heap *h;

    h = malloc(sizeof(Heap));
    if (h == NULL)
        return NULL;

    h->Nodes = malloc(sizeof(Node) * MaxNodes);
    if (h->Nodes == NULL){
        free(h);
        return NULL;
    }
    
    h->MaxNodes = MaxNodes;
    h->CurNodes = 0;

    return h;
}


/*
    Given index i:

        Parent(i) = floor( (i-1) / 2 )
        LeftChild(1) = 2*i + 1
        RightChild(1) = 2*i + 2
 */

#define SWAP_NODES(n1_, n2_)    \
            {                   \
                Node tmp;       \
                tmp = (n1_);    \
                (n1_) = (n2_);  \
                (n2_) = tmp;    \
            }


/*
 *  @returns 0 on success, -1 on failure.
 */
int Insert (Heap *h, int Key, int Data)
{
    int i;
    int parent;

    if ((h->CurNodes + 1) > h->MaxNodes)
        return -1;
    
    i = h->CurNodes;

    h->Nodes[i].Key = Key;
    h->Nodes[i].Data = Data;
    h->CurNodes++;

    do {

        parent = (i - 1) / 2;    // Natural floor.
        
        // Max-heap
        if (h->Nodes[parent].Key >= h->Nodes[i].Key){
            break;
        }
        else{
            SWAP_NODES(h->Nodes[parent], h->Nodes[i]);
        }

        i = parent;

    } while (parent > 0);

    return 0;
}



void MaxHeapify(Heap *h, int i)
{
    int left;
    int right;
    int largest;

    largest = i;
    left  = (i * 2) + 1;
    right = (i * 2) + 2;

    if ( (left < h->CurNodes) && (h->Nodes[left].Key > h->Nodes[largest].Key) ) {
        largest = left;
    }

    if ( (right < h->CurNodes) && (h->Nodes[right].Key > h->Nodes[largest].Key) ) {
        largest = right;
    }

    if (i != largest){
        SWAP_NODES(h->Nodes[i], h->Nodes[largest]);
        MaxHeapify(h, largest);
    }
}



void IterativeMaxHeapify(Heap *h, int i)
{
    int left;
    int right;
    int largest;

    while (1) {

        largest = i;
        left  = (i * 2) + 1;
        right = (i * 2) + 2;

        if ( (left < h->CurNodes) && (h->Nodes[left].Key > h->Nodes[largest].Key) ) {
            largest = left;
        }

        if ( (right < h->CurNodes) && (h->Nodes[right].Key > h->Nodes[largest].Key) ) {
            largest = right;
        }

        if (i != largest){
            SWAP_NODES(h->Nodes[i], h->Nodes[largest]);
            //MaxHeapify(h, largest);
            i = largest;
        }
        else{
            return;
        }
    }
}





int Remove(Heap *h, int *Key, int *Data)
{
    int i;

    if (h == NULL)
        return -1;

    if (h->CurNodes <= 0)
        return -1;

    *Key = h->Nodes[0].Key;
    *Data = h->Nodes[0].Data;

    h->CurNodes--;

    SWAP_NODES(h->Nodes[0], h->Nodes[h->CurNodes]);

    //MaxHeapify(h, 0);
    IterativeMaxHeapify(h, 0);

    return 0;
}



void PrintHeap(Heap *h)
{
    printf("\nCurNodes: %d\n", h->CurNodes);
    int i;
    //int left, right;

    for (i = 0; i < h->CurNodes; i++){
        printf("%d => (%d, %d)\n", i, h->Nodes[i].Key, h->Nodes[i].Data);
    }
}



int main (void)
{
    Heap *heap;
    int i;
    int rc;
    int TestKey[] = {
        10, 1, 20, 2, 30, 3, 40 , 4, 50 };
    int TestCount = sizeof(TestKey) / sizeof(int);
    int Key, Data;


    heap = CreateHeap(20);
    if (heap == NULL){
        printf("Failed CreateHeap()\n");
        return -1;
    }

    for (i = 0; i < TestCount; i++){
        rc = Insert(heap, TestKey[i], TestKey[i] + 1000);
        if (rc != 0){
            printf("Failed Insert()\n");
            return -1;
        }
        //PrintHeap(heap);
    }

    //PrintHeap(heap);

    for (i = 0; i < (TestCount + 1); i++){

        rc = Remove(heap, &Key, &Data);
        if (rc != 0){
            printf("Failed removing data!\n");
        }
        else{
            printf("Removed: %d => %d\n", Key, Data);
        }
        //PrintHeap(heap);
    }

    return 0;
}


