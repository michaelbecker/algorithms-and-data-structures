#include <stdio.h>
#include <stdlib.h>

#include "double-linked-circular-list.h"





void PushToHead (DlcList *Head, DlcList *Node)
{
    DlcList *Temp;

    if (Head == NULL)
        return;

    if (Node == NULL)
        return;

    Temp = Head->Next;

    Node->Next = Temp;
    Node->Prev = Head;

    Head->Next = Node;
    Temp->Prev = Node;
}



DlcList *PopFromHead (DlcList *Head)
{
    DlcList *Node;

    if (Head == NULL)
        return;

    if (IS_EMPTY(Head))
        return NULL;

    Node = Head->Next;
    Head->Next = Node->Next;
    Node->Next->Prev = Head;

    //
    //  Not strictly needed.
    //
    INIT_NODE(Node);

    return Node;
}



void PushToTail (DlcList *Head, DlcList *Node)
{
    DlcList *Temp;

    if (Head == NULL)
        return;

    if (Node == NULL)
        return;

    Temp = Head->Prev;

    Node->Prev = Temp;
    Node->Next = Head;

    Head->Prev = Node;
    Temp->Next = Node;
}



DlcList *PopFromTail (DlcList *Head)
{
    DlcList *Node;

    if (Head == NULL)
        return;

    if (IS_EMPTY(Head))
        return NULL;

    Node = Head->Prev;

    Head->Prev = Node->Prev;
    Node->Prev->Next = Head;

    //
    //  Not strictly needed.
    //
    INIT_NODE(Node);

    return Node;
}



void RemoveNode (DlcList *Node)
{
    if (Node == NULL)
        return;

    if (IS_EMPTY(Node))
        return;

    Node->Prev->Next = Node->Next;
    Node->Next->Prev = Node->Prev;

    //
    //  Not strictly needed.
    //
    INIT_NODE(Node);
}



void InsertNodeAfter (DlcList *Marker, DlcList *Node)
{
    DlcList *Temp;

    if (Node == NULL)
        return;

    if (Marker == NULL)
        return;

    Temp = Marker->Next;

    Node->Next = Temp;
    Node->Prev = Marker;

    Marker->Next = Node;
    Temp->Prev = Node;
}



void InsertNodeBefore (DlcList *Marker, DlcList *Node)
{
    DlcList *Temp;

    if (Node == NULL)
        return;

    if (Marker == NULL)
        return;

    Temp = Marker->Prev;

    Node->Next = Marker;
    Node->Prev = Temp;

    Marker->Prev = Node;
    Temp->Next = Node;
}



/**
 * gcc -DTEST_DLC_LIST double-linked-circular-list.c
 */
#ifdef TEST_DLC_LIST

typedef struct TestData_t_{
    //
    //  If we keep List at the beginning, we can do things 
    //  with typecasting.
    //
    DlcList List;
    int Value;

}TestData_t;



TestData_t *MakeTestData(int value)
{
    TestData_t *Data;

    Data = malloc(sizeof(TestData_t));

    if (Data == NULL)
        return NULL;

    INIT_NODE(&Data->List);
    Data->Value = value;

    return Data;
}



void PrintList(DlcList *Head)
{
    DlcList *Node;
    TestData_t *Data;

    FOR_ALL_ELEMENTS(Head, Node){
        //
        //  Works because we know that Node is at the beginning of 
        //  the structure.
        //
        Data = (TestData_t *)Node;
        printf("%d ", Data->Value);
    }

    printf("\n");
}


void PrintListReverse(DlcList *Head)
{
    DlcList *Node;
    TestData_t *Data;

    FOR_ALL_ELEMENTS_REVERSE(Head, Node){
        //
        //  Works because we know that Node is at the beginning of 
        //  the structure.
        //
        Data = (TestData_t *)Node;
        printf("%d ", Data->Value);
    }

    printf("\n");
}



int main (void)
{
    DlcList Head;
    TestData_t *d;
    DlcList *marker;
    int i;

    INIT_NODE(&Head);

    for (i = 0; i < 5; i++){
        d = MakeTestData(i);
        PushToHead(&Head, &d->List);
        PrintList(&Head);
    }

    for (i = 0; i < 5; i++){
        d = (TestData_t *)PopFromHead(&Head);
        free(d);
        PrintList(&Head);
    }

    for (i = 0; i < 5; i++){
        d = MakeTestData(i);
        PushToTail(&Head, &d->List);
        PrintList(&Head);
    }

    for (i = 0; i < 5; i++){
        d = (TestData_t *)PopFromTail(&Head);
        free(d);
        PrintList(&Head);
    }


    for (i = 0; i < 10; i++){
        d = MakeTestData(i + 100);
        PushToTail(&Head, &d->List);
        if (i == 5)
            marker = &d->List;
        PrintList(&Head);
    }


    d = MakeTestData(222);
    InsertNodeAfter(marker, &d->List);
    PrintList(&Head);

    d = MakeTestData(333);
    InsertNodeBefore(marker, &d->List);
    PrintList(&Head);

    PrintListReverse(&Head);

    return 0;
}



#endif

