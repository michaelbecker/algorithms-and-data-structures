void merge(int *A, int size, int m)
{
    int *X;
    int i, j, k;

    X = malloc(size * sizeof(int));
    memcpy(X, A, size * sizeof(int));

    i = 0; j = m; k = 0;

    while ( (i < m) && (j < size) ) {

        if (A[j] < X[i])
            A[k++] = A[j++];

        else
            A[k++] = X[i++];
    }

    while (i < m)
        A[k++] = X[i++];


    free(X);
}

void merge_sort(int *A, int size)
{
    int m;

    if (size < 2) return;

    m = size / 2;
    merge_sort(A, m);
    merge_sort(A + m, size - m);
    merge(A, size, m);
}


