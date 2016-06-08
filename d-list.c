#include <stdio.h>
#include <stdlib.h>

#include "d-list.h"

/*
 *  Returns new head
 *  O(1)
 */
struct d_list *add_node_to_head (struct d_list *head, struct d_list *n)
{
    if (head){
        n->next = head;
    }

    return n;
}


/*
 *  Returns new head - only makes sense if head == null at first.
 *  O(n)
 */
struct d_list *add_node_to_tail (struct d_list *head, struct d_list *n)
{
    struct d_list *cur;
    if (!head){
        return n;
    }

    cur = head;

    while (cur->next != NULL){
        cur = cur->next;
    }

    cur->next = n;
    n->next = NULL;

    return head;
}


/*
 *  This is O(1)
 */
void insert_node_after (struct d_list *marker, struct d_list *n)
{
    struct d_list *marker_p1;

    if (!marker)
        return;

    if (!n)
        return;

    marker_p1 = marker->next;
    marker->next = n;
    n->next = marker_p1;
}


/*
 *  Returns new head
 *  This is O(n)
 */
struct d_list *insert_node_before (struct d_list *head, struct d_list *marker, struct d_list *n)
{
    struct d_list *cur_m1;
    struct d_list *cur;

    if (!marker)
        return head;

    if (!n)
        return head;

    if (!head)
        return head;

    if (head == marker){
        n->next = head;
        return n;
    }

    cur_m1 = NULL;
    while (cur != marker){

        if (cur->next == NULL){
            return head;
        }

        cur_m1 = cur;
        cur = cur->next;
    }

    cur_m1->next = n;
    n->next = cur;

    return head;
}


/*
 *  Returns new head
 *  O(n)
 */
struct d_list *remove_node(struct d_list *head, struct d_list *n)
{
    struct d_list *cur;
    struct d_list *prev;

    if (!head)
        return head;

    if (!n)
        return head;

    if (head == n)
        return head->next;

    /* Must have a list of at least 2 here */
    prev = head;
    cur = head->next;
    while (cur != n){

        if (cur->next == NULL)
            return head;

        prev = cur;
        cur = cur->next;
    }

    prev->next = n->next;
    n->next = NULL;

    return head;
}


/*
 *  Helper function
 */
struct d_list *create_node(int d)
{
    struct d_list *n;
    n = malloc(sizeof(struct d_list));

    if (!n)
        return NULL;

    n->next = NULL;
    n->prev = NULL;
    n->data = d;

    return n;
}


/*
 *  Helper function
 */
void free_list(struct d_list *head)
{
    struct d_list *cur;

    while (head != NULL){
        cur = head;
        head = head->next;
        free(cur);
    }
}


/*
 *  Helper function
 */
void print_list(struct d_list *head)
{
    struct d_list *cur;

    cur = head;
    printf("\nPrinting test List\n");
    while (cur != NULL){
        printf("DATA: %d\n", cur->data);
        cur = cur->next;
    }
}



/* gcc -DTEST_SLIST s-list.c */
#ifdef TEST_SLIST 

int main (void)
{
    struct d_list *head;
    struct d_list *n[5];
    struct d_list *cur;
    int i;

    // Test 1 --------------------------------
    head = NULL;
    for (i = 0; i < 5; i++)
        n[i] = create_node(i);

    head = add_node_to_head(head, n[1]);
    head = add_node_to_head(head, n[0]);

    head = add_node_to_tail(head, n[3]);
    head = add_node_to_tail(head, n[4]);

    insert_node_after(n[1], n[2]);

    print_list(head);
    free_list(head);


    // Test 2 --------------------------------
    head = NULL;
    for (i = 0; i < 5; i++)
        n[i] = create_node(i);

    for (i = 0; i < 5; i++)
        head = add_node_to_head(head, n[i]);
    print_list(head);
    free_list(head);


    // Test 3 --------------------------------
    head = NULL;
    for (i = 0; i < 5; i++)
        n[i] = create_node(i);

    for (i = 0; i < 5; i++)
        head = add_node_to_tail(head, n[i]);

    print_list(head);
    free_list(head);


    // Test 4 --------------------------------
    head = NULL;
    for (i = 0; i < 5; i++)
        n[i] = create_node(i);

    head = n[0];
    for (i = 0; i < (5-1); i++)
        insert_node_after(n[i], n[i+1]);

    print_list(head);
    free_list(head);


    // Test 5 --------------------------------
    head = NULL;
    for (i = 0; i < 5; i++)
        n[i] = create_node(i);

    head = n[0];
    for (i = 0; i < (5-1); i++)
        head = insert_node_before(head, n[i], n[i+1]);

    print_list(head);
    free_list(head);



    head = NULL;
    for (i = 0; i < 5; i++)
        n[i] = create_node(i);

    head = n[0];
    for (i = 0; i < (5-1); i++)
        insert_node_after(n[i], n[i+1]);

    print_list(head);


    // Test 6 --------------------------------
    cur = n[0];
    head = remove_node(head, cur);
    print_list(head);
    free(cur);

    // Test 7 --------------------------------
    cur = n[4];
    head = remove_node(head, cur);
    print_list(head);
    free(cur);

    // Test 8 --------------------------------
    cur = n[2];
    head = remove_node(head, cur);
    print_list(head);
    free(cur);

    free_list(head);

    return 0;
}

#endif 


