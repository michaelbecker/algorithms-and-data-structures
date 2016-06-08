#ifndef DOUBLE_LINKED_CIRCULAR_LIST__
#define DOUBLE_LINKED_CIRCULAR_LIST__


typedef struct DlcList_ {

    struct DlcList_ *Next;
    struct DlcList_ *Prev;

}DlcList;



//
//  void INIT_NODE(DlcList *node);
//
#define INIT_NODE(node_)            \
    {                               \
        (node_)->Next = (node_);    \
        (node_)->Prev = (node_);    \
    }



//
//  boolean IS_EMPTY(DlcList *Head);
//
#define IS_EMPTY(head_)     \
    (head_->Next == head_)  \



void PushToHead (DlcList *Head, DlcList *Node);
void PushToTail (DlcList *Head, DlcList *Node);

DlcList *PopFromHead (DlcList *Head);
DlcList *PopFromTail (DlcList *Head);

void RemoveNode (DlcList *Node);

void InsertNodeAfter (DlcList *Marker, DlcList *Node);
void InsertNodeBefore (DlcList *Marker, DlcList *Node);


//
//  Helper macros to walk the list:
//  
//  DlcList *YourListHead;
//  DlcList *Node;
//
//  FOR_ALL_ELEMENTS(YourListHead, Node) {
//      ...
//      // use Node here
//      ...
//  }
//
#define FOR_ALL_ELEMENTS(head_, iterator_)  \
    for (   iterator_ = head_->Next;        \
            iterator_ != head_;             \
            iterator_ = iterator_->Next)


#define FOR_ALL_ELEMENTS_REVERSE(head_, iterator_)  \
    for (   iterator_ = head_->Prev;                \
            iterator_ != head_;                     \
            iterator_ = iterator_->Prev)




#endif

