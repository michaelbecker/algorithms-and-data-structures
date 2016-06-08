#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define SWAP(a_, b_)    \
    {                   \
        int tmp;        \
        tmp = a_;       \
        a_ = b_;        \
        b_ = tmp;       \
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



void merge(int *A, int size, int midpoint)
{
    int *X;
    int i, j, k;

    /*
     *  Scratch array
     */
    X = malloc(size * sizeof(int));
    memcpy(X, A, size * sizeof(int));

    i = 0;
    j = midpoint; 
    k = 0;

    while ((i < midpoint) && (j < size)){

        if (A[j] < X[i]){
            A[k] = A[j];
            j++;
            k++;
        }
        else{
            A[k] = X[i];
            i++;
            k++;
        }
    }

    while (i < midpoint){
        A[k] = X[i];
        i++;
        k++;
    }

    free(X);
}



/**
 *  Sorts smallest to largest.
 */ 
void merge_sort(int *A, int size)
{
    int midpoint;

    if (size < 2){
        return;
    }

    midpoint = size / 2;
    
    /*
     *  Lower half
     */
    merge_sort(A, midpoint);

    /*
     *  Upper half
     */
    merge_sort(A + midpoint, size - midpoint);
    
    /*
     *  Merge them back together
     */
    merge(A, size, midpoint);
}



/**
 * gcc -DTEST_MERGE_SORT merge-sort.c
 */
#ifdef TEST_MERGE_SORT

#define BUILD_TEST_CASE(a_) \
    merge_sort(a_, sizeof(a_) / sizeof (int)); \
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

