#ifndef S_LIST_H__
#define S_LIST_H__

struct d_list {

    struct d_list *next;
    struct d_list *prev;
    int data;

};

/*
 *  Returns new head
 *  O(1)
 */
struct d_list *add_node_to_head (struct d_list *head, struct d_list *n);

/*
 *  May return a new head - only makes sense if head == null at first.
 *  O(n)
 */
struct d_list *add_node_to_tail (struct d_list *head, struct d_list *n);

/*
 *  This is O(1)
 */
void insert_node_after (struct d_list *marker, struct d_list *n);

/*
 *  May returns a new head
 *  This is O(n)
 */
struct d_list *insert_node_before (struct d_list *head, struct d_list *marker, struct d_list *n);

/*
 *  May returns new head
 *  O(n)
 */
struct d_list *remove_node(struct d_list *head, struct d_list *n);

/*
 *  Helper function
 */
struct d_list *create_node(int d);

/*
 *  Helper function
 */
void free_list(struct d_list *head);

/*
 *  Helper function
 */
void print_list(struct d_list *head);


#endif

