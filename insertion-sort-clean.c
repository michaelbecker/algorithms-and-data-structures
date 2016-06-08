/**
 *  Sorts smallest to largest.
 */ 
void insertion_sort(int *A, int size)
{
    int i, j;
    int tmp;

    if (size < 2)  return;
    if (A == NULL) return;

    for (i = 1; i < size; i++) {
        
        for (j = i; j > 0; j--) {

            if (A[j] < A[j-1])
                SWAP(A[j], A[j-1]);

            else
                break;
        }
    }
}

