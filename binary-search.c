#include <stdio.h>
#include <stdlib.h>


/*
 *  Returns index of value.
 */
int BinarySearch (int *A, int Size, int Value)
{
    int Midpoint;
    int Upper;
    int Lower;
    
    if (Size <= 0)
        return -1;

    if (A == NULL)
        return -1;

    Lower = 0;
    Upper = Size - 1;

    while (Lower <= Upper){

        Midpoint = (Upper + Lower) / 2;

        /* 
         * Uncomment to see the algorithm at work.
         */
         /* printf("(%d, %d, %d)\n", Lower, Midpoint, Upper); */
         
        if ( A[Midpoint] > Value) {
            Upper = Midpoint - 1;
        }
        else if ( A[Midpoint] < Value) {
            Lower = Midpoint + 1;
        }
        else {
            return Midpoint;
        }
    }
    
    return -1;
}



/* gcc -DTEST_BINARY_SEARCH binary-search.c */
#ifdef TEST_BINARY_SEARCH


#define BUILD_TEST(a_, v_)                                 \
    printf("Looking for %d -", v_);                        \
    Index = BinarySearch(a_, sizeof(a_) / sizeof(int), v_);\
    if (Index >= 0){                                       \
        printf("found it at A[%d] = %d\n", Index, v_);     \
    }                                                      \
    else{                                                  \
        printf("Not there - %d\n", v_);                    \
    }


int main (void)
{
    int Index;

    int Test1[] = 
    {1, 3, 5, 10, 11, 12, 15, 20, 30, 100};
    int Test2[] = 
    {1, 3, 5, 10, 11, 12, 15, 20, 30};
    int Test3[] = 
    {1};
    int *Test4 = NULL;

    BUILD_TEST(Test1, 10);
    BUILD_TEST(Test2, 10);

    BUILD_TEST(Test1, 11);
    BUILD_TEST(Test2, 11);

    BUILD_TEST(Test1, 1);
    BUILD_TEST(Test2, 1);

    BUILD_TEST(Test1, 100);
    BUILD_TEST(Test2, 30);


    BUILD_TEST(Test1, -1);
    BUILD_TEST(Test1, 101);
    BUILD_TEST(Test1, 25);

    BUILD_TEST(Test2, -1);
    BUILD_TEST(Test2, 101);
    BUILD_TEST(Test2, 25);

    BUILD_TEST(Test3, 1);
    BUILD_TEST(Test3, -1);
    BUILD_TEST(Test3, 2);
    
    BUILD_TEST(Test4, 1);
    BUILD_TEST(Test4, -1);
    BUILD_TEST(Test4, 2);

    return 0;
}


#endif

