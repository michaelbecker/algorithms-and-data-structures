#include <stdio.h>
#include <stdlib.h>


/*
 *  Returns index of value.
 */
int BinaryRecursiveSearch (int *A, int Lower, int Upper, int Value)
{
    int Midpoint;

    if (A == NULL)
        return -1;

    if (Lower <= Upper){

        Midpoint = ((Upper - Lower) / 2) + Lower;

        /* 
         * Uncomment to see the algorithm at work.
         */
        /* printf("(%d, %d, %d)\n", Lower, Midpoint, Upper); */
         
        if ( A[Midpoint] > Value) {
            Upper = Midpoint - 1;
            return BinaryRecursiveSearch(A, Lower, Upper, Value);
        }
        else if ( A[Midpoint] < Value) {
            Lower = Midpoint + 1;
            return BinaryRecursiveSearch(A, Lower, Upper, Value);
        }
        else {
            return Midpoint;
        }
    }
    
    return -1;
}



/* gcc -DTEST_BINARY_RECURSIVE_SEARCH binary-recursive-search.c */
#ifdef TEST_BINARY_RECURSIVE_SEARCH


#define BUILD_TEST(a_, v_)                                 \
    printf("Looking for %d -", v_);                        \
    Index = BinaryRecursiveSearch(a_, 0, sizeof(a_) / sizeof(int) - 1, v_);\
    if (Index >= 0){                                       \
        printf("found it at A[%d] = %d\n", Index, v_);     \
    }                                                      \
    else{                                                  \
        printf("Not there - %d\n", v_);                    \
    }



int main (void)
{
    int Index;
    int Value;

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

