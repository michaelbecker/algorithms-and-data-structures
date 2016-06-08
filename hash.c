#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct List_ {

    struct List_ *Next;
    int Key;
    int Data;

}List;


typedef struct Hash_ {

    int ArraySize;
    List **DataArray;

}Hash;



Hash *CreateHash (int ArraySize)
{
    Hash *h;

    if (ArraySize <= 0){
        return NULL;
    }

    h = malloc(sizeof(Hash));
    if (h == NULL)
        return NULL;

    h->ArraySize = ArraySize;

    //
    //  Create an array of pointers to "List" structs.
    //
    h->DataArray = malloc(ArraySize * sizeof(List *));
    if (h->DataArray == NULL){
        free (h);
        return NULL;
    }

    memset(h->DataArray, 0, ArraySize * sizeof(List *));

    return h;
}



/**
 *  Simple (and stupid) implementation.
 */
static int HashFunction(Hash *h, int Key)
{
    int index = Key % h->ArraySize;

    return index;
}



int AddToHash(Hash *h, int Key, int Data)
{
    int index;
    List *list;
    List *cur;

    index = HashFunction(h, Key);

    list = malloc(sizeof(List));
    if (list == NULL)
        return -1;

    list->Key = Key;
    list->Data = Data;
    list->Next = NULL;
    
    //
    //  List silliness
    //
    if (h->DataArray[index] == NULL){
        h->DataArray[index] = list;
    }
    else{
        cur = h->DataArray[index];
        while (cur->Next != NULL){
            cur = cur->Next;
        }
        cur->Next = list;
    }

    return 0;
}


/*  @returns 0 = success, -1 failed to find 
 *  Data is returned in *Data
 */
int GetHashValue(Hash *h, int Key, int *Data)
{
    int index;
    List *cur;
    List *Found = NULL;
    
    index = HashFunction(h, Key);
    
    if (h->DataArray[index] == NULL){
        return -1;
    }

    cur = h->DataArray[index];

    do {

        if (cur->Key == Key){
            Found = cur;
            break;
        }
        else{
            cur = cur->Next;
        }

    } while(cur != NULL);

    if (Found == NULL){
        return -1;
    }

    *Data = Found->Data;
    return 0;
}



#ifdef TEST_HASH

/* gcc -DTEST_HASH hash.c */
int main(void)
{
    Hash *h = CreateHash(10);
    int rc;
    int i;
    int Data;

    for (i = 1; i < 10; i++){

        rc = AddToHash(h, i, i+10);

        if (rc != 0){
            printf("Failed!");
            return -1;
        }
    }
    
    for (i = 0; i < 12; i++){

        rc = GetHashValue(h, i, &Data);

        if (rc != 0){
            printf("Not found\n");
        }
        else{
            printf("Found h[%d] = %d\n", i, Data);
        }
    }


    for (i = 100; i < 110; i++){

        rc = AddToHash(h, i, i+1000);

        if (rc != 0){
            printf("Failed!");
            return -1;
        }
    }
    

    for (i = 0; i < 12; i++){

        rc = GetHashValue(h, i, &Data);

        if (rc != 0){
            printf("Not found\n");
        }
        else{
            printf("Found h[%d] = %d\n", i, Data);
        }
    }
    for (i = 98; i < 112; i++){

        rc = GetHashValue(h, i, &Data);

        if (rc != 0){
            printf("Not found\n");
        }
        else{
            printf("Found h[%d] = %d\n", i, Data);
        }
    }


    return 0;
}


#endif

