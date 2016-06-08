/*
 *  Returns index of value.
 */
int BinarySearch (int *A, int Size, int v)
{
    int m, i, j;
    
    if (Size <= 0) return -1;
    if (A == NULL) return -1;

    i = 0; j = Size - 1;

    while (i <= j){

        m = (i + j) / 2;

        if ( v < A[m] )
            j = m - 1;

        else if ( A[m] < v)
            i = m + 1;

        else
            return m;
    }
    
    return -1;
}

