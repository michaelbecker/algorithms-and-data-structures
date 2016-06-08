#include <stdio.h>
#include <stdlib.h>



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




/**
 *  Sorts smallest to largest.
 */ 
void insertion_sort(int *A, int size)
{
    int i, j;
    int tmp;

    if (size < 2){
        return;
    }

    if (A == NULL){
        return;
    }


    for (i = 1; i < size; i++){
        
        j = i;

        while (j > 0){
            
            /*
             *  If out of order, swap and look again.
             */
            if (A[j] < A[j-1]){
                SWAP(A[j], A[j-1]);
                j--;
            }
            /*
             *  Else we are where we need to be.
             */
            else{
                break;
            }
        }
    }
}



/**
 * gcc -DTEST_INSERTION_SORT insertion-sort.c 
 */
#ifdef TEST_INSERTION_SORT

#define BUILD_TEST_CASE(a_) \
    insertion_sort(a_, sizeof(a_) / sizeof (int)); \
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

