/*
 *  Returns index of value.
 */
int BinaryRecursiveSearch (int *A, int i, int j, int v)
{
    int m;

    if (A == NULL) return -1;

    if (i <= j) {

        m = (i + j) / 2;

        if ( A[Midpoint] > v) 
            return BinaryRecursiveSearch(A, i, m - 1, v);

        else if ( A[Midpoint] < v) 
            return BinaryRecursiveSearch(A, m + 1, j, v);

        else
            return m;
    }
    
    return -1;
}

