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
 *  This is a simple-stupid way to pick.
 */
int choose_pivot(int *A, int low, int high)
{
    int pivot_index;

    pivot_index = (low + high) / 2;

    return pivot_index;
}



int partition(int *A, int i, int j)
{
    int pivot_index;
    int pivot_value;

    pivot_index = choose_pivot(A, i, j);
    pivot_value = A[pivot_index];

    while (1) {

        while (A[i] < pivot_value){
            i++;
        }

        while (A[j] > pivot_value){
            j--;
        }

        if (i < j){
            SWAP(A[i], A[j]);
        }
        else{
            break;
        }
    }

    /**
     *  Return i or j here.
     */
    return i;
}



/**
 *  Sorts smallest to largest.
 *
 *  @param A,   The Array to be sorted
 *  @param i,   The low index
 *  @param j,   The high index
 *
 *  This is recursive! 
 *
 *  To start, call "quick_sort(A, 0, sizeof(A) - 1);"
 */ 
void quick_sort(int *A, int i, int j)
{
    int p;

    if (i < j){
        p = partition(A, i, j);
        quick_sort(A, i, p - 1);
        quick_sort(A, p + 1, j);
    }
}



/**
 * gcc -DTEST_QUICK_SORT quick-sort.c 
 */
#ifdef TEST_QUICK_SORT

#define BUILD_TEST_CASE(a_) \
    quick_sort(a_, 0, (sizeof(a_) / sizeof (int)) - 1); \
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
    int a8[] = { 100, 1, 2, 3, 4, 5, 6 };
    int a9[] = { 1, 2, 3, 4, 5, 6, 7, 0 };
    int a10[]= { 1, 2, 3, 4, 5, 6, 0 };

    BUILD_TEST_CASE(a1);
    BUILD_TEST_CASE(a2);
    BUILD_TEST_CASE(a3);
    BUILD_TEST_CASE(a4);
    BUILD_TEST_CASE(a5);
    BUILD_TEST_CASE(a6);
    BUILD_TEST_CASE(a7);
    BUILD_TEST_CASE(a8);
    BUILD_TEST_CASE(a9);
    BUILD_TEST_CASE(a10);

    return 0;
}

#endif

