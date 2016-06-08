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
    int NumNodes;
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
    h->NumNodes = 0;

    return h;
}


/**
 *  For a binary heap implemented as an array.
 *  - integer division is automatically floor()
 */
#define GET_PARENT(n_)          (((n_) - 1) / 2)  
#define GET_LEFT_CHILD(n_)      ((2 * (n_)) + 1)
#define GET_RIGHT_CHILD(n_)     ((2 * (n_)) + 2)


#define SWAP(a_, b_)    \
    {                   \
        Node tmp;       \
        tmp = (a_);     \
        (a_) = (b_);    \
        (b_) = tmp;     \
    }



// 
//  For Max Heap
//  i = start, j = end, inclusive
//
void sift_up(Node *A, int i, int j)
{
    int child, parent;

    child = j;

    while (child > i){

        parent = GET_PARENT(child);

        if (A[parent].Key < A[child].Key) {
            SWAP(A[parent], A[child]);
            child = parent;
        }
        else {
            return;
        }
    }
}


// 
//  For Max Heap - recursive
//  i = start, j = end, inclusive
//
void sift_down_recursive(Node *A, int i, int j)
{
    int left_child, right_child, parent;
    int max;

    parent = i;
    left_child =  GET_LEFT_CHILD(parent);
    right_child = GET_RIGHT_CHILD(parent);
    max = parent;    

    if ( (left_child <= j) && (A[left_child].Key > A[max].Key) )
        max = left_child;
    
    if ( (right_child <= j) && (A[right_child].Key > A[max].Key) )
        max = right_child;

    if (max != parent){
        SWAP(A[max], A[parent]);
        sift_down_recursive(A, max, j);
    }
}


// 
//  For Max Heap - iterative
//  i = start, j = end, inclusive
//
void sift_down_iterative(Node *A, int i, int j)
{
    int left_child, right_child, parent;
    int max;

    parent = i;
    max = parent;    

    while (1) {

        left_child =  GET_LEFT_CHILD(parent);
        right_child = GET_RIGHT_CHILD(parent);

        if ( (left_child <= j) && (A[left_child].Key > A[max].Key) )
            max = left_child;
        
        if ( (right_child <= j) && (A[right_child].Key > A[max].Key) )
            max = right_child;

        if (max != parent){
            SWAP(A[max], A[parent]);
            parent = max;
        }
        else {
            return;
        }
    }
}


/*
 *  @returns 0 on success, -1 on failure.
 */
int Insert (Heap *h, int Key, int Data)
{
    int j;

    if ((h->NumNodes + 1) > h->MaxNodes)
        return -1;
    
    //  Insert at end
    j = h->NumNodes;
    h->Nodes[j].Key = Key;
    h->Nodes[j].Data = Data;

    h->NumNodes++;

    sift_up(h->Nodes, 0, j);

    return 0;
}



int Remove(Heap *h, int *Key, int *Data)
{
    if (h == NULL)
        return -1;

    if (h->NumNodes <= 0)
        return -1;

    *Key = h->Nodes[0].Key;
    *Data = h->Nodes[0].Data;

    h->NumNodes--;

    SWAP(h->Nodes[0], h->Nodes[h->NumNodes]);

    sift_down_recursive(h->Nodes, 0, h->NumNodes - 1);
    //sift_down_iterative(h->Nodes, 0, h->NumNodes - 1);

    return 0;
}



void PrintHeap(Heap *h)
{
    printf("\nNumNodes: %d\n", h->NumNodes);
    int i;

    for (i = 0; i < h->NumNodes; i++){
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


