/**
 *  Sorts smallest to largest.
 */ 
void selection_sort(int *A, int size)
{
    int i, j, min_idx;

    for (i = 0; i < (size-1); i++) {
        
        min_idx = i;

        for (j = i+1; j < size; j++) {

            if ( A[j] < A[min_idx])
                min_idx = j;
        }

        if (min_idx != i)
            SWAP(A[i], A[min_idx]);
    }
}


