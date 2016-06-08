/**
 *  Sorts smallest to largest.
 */ 
void bubble_sort(int *A, int size)
{
    int i;
    int swapped;

    do {
        swapped = 0;

        for (i = 0; i < (size-1); i++){

            if (A[i] > A[i+1]){
                swapped = 1;
                SWAP(A[i], A[i+1]);
            }
        }

    } while (swapped);
}

