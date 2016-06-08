#include <stdio.h>
#include <stdlib.h>



#define SWAP(a_, b_)    \
    {                   \
        int tmp;        \
        tmp = (a_);     \
        (a_) = (b_);    \
        (b_) = tmp;     \
    }



/**
 *  Helper
 */
void print_array(int *A, int size)
{
    int i;
    printf("Array [%d]: ", size);

    for (i = 0; i < size; i++){
        printf("%d ", A[i]);
    }

    printf("\n\n");
}



/**
 *  For a binary heap implemented as an array.
 *  - integer division is automatically floor()
 */
#define GET_PARENT(n_)          (((n_) - 1) / 2)  
#define GET_LEFT_CHILD(n_)      ((2 * (n_)) + 1)
#define GET_RIGHT_CHILD(n_)     ((2 * (n_)) + 2)


// 
//  For Max Heap
//  i = start, j = end, inclusive
//
void sift_up(int *A, int i, int j)
{
    int child, parent;

    child = j;

    while (child > i){

        parent = GET_PARENT(child);

        if (A[parent] < A[child]) {
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
void sift_down_recursive(int *A, int i, int j)
{
    int left_child, right_child, parent;
    int max;

    parent = i;
    left_child =  GET_LEFT_CHILD(parent);
    right_child = GET_RIGHT_CHILD(parent);
    max = parent;    

    if ( (left_child <= j) && (A[left_child] > A[max]) )
        max = left_child;
    
    if ( (right_child <= j) && (A[right_child] > A[max]) )
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
void sift_down_iterative(int *A, int i, int j)
{
    int left_child, right_child, parent;
    int max;

    parent = i;
    max = parent;    

    while (1) {

        left_child =  GET_LEFT_CHILD(parent);
        right_child = GET_RIGHT_CHILD(parent);

        if ( (left_child <= j) && (A[left_child] > A[max]) )
            max = left_child;
        
        if ( (right_child <= j) && (A[right_child] > A[max]) )
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



void heapify(int *A, int size)
{
    int last_node;
    int parent;

    last_node = size - 1;
    parent = GET_PARENT(last_node); // turns into "(size - 2) / 2"

    while (parent >= 0){
        // the j index is inclusive
        sift_down_iterative(A, parent, size - 1);
        parent = parent - 1;
    }
}



void heap_sort(int *A, int size)
{
    int j;

    heapify(A, size);

    j = size - 1;

    while (j > 0){
        // Biggest at end
        SWAP(A[0], A[j]);
        j = j - 1;
        sift_down_iterative(A, 0, j);
        //sift_down_recursive(A, 0, j);
    }
}




/**
 * gcc -DTEST_HEAP_SORT heap-sort.c
 */
#ifdef TEST_HEAP_SORT

#define BUILD_TEST_CASE(a_) \
    heap_sort(a_, sizeof(a_) / sizeof (int)); \
    print_array(a_, sizeof(a_) / sizeof (int)); \



int main(void)
{
    int a1[] = { 1, 4, 3, 2};
    int a2[] = { 1, 2, 3, 4};
    int a3[] = { 4, 3, 2, 1};
    int a4[] = { 25 };
    int a5[] = { 9, 8, 7, 6, 5, 4, 3, 2, 100 };
    int a6[] = { 1, 8, 7, 6, 5, 4, 3, 2 };
    int a7[] = { 100, 1, 2, 3, 4, 5, 6, 7 };

    BUILD_TEST_CASE(a1);
    BUILD_TEST_CASE(a2);
    BUILD_TEST_CASE(a3);
    BUILD_TEST_CASE(a4);
    BUILD_TEST_CASE(a5);
    BUILD_TEST_CASE(a6);
    BUILD_TEST_CASE(a7);

    return 0;
}

#endif

