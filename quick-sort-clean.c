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
    int pivot_index, pivot_value;

    pivot_index = choose_pivot(A, i, j);
    pivot_value = A[pivot_index];

    while (i < j) {

        while (A[i] < pivot_value)
            i++;

        while (A[j] > pivot_value)
            j--;

        if (i < j)
            SWAP(A[i], A[j]);
    }

    return i;   //Return i or j here.
}

void quick_sort(int *A, int i, int j) //Start: quick_sort(A, 0, sizeof(A) - 1)
{
    int p;

    if (i < j){
        p = partition(A, i, j);
        quick_sort(A, i, p - 1);
        quick_sort(A, p + 1, j);
    }
}

