/**
 *  @file
 *
 *  Singly linked list interface.
 *
 *  This version does not require a sentinal head element, instead 
 *  implementing the simplest generic data structure possible. As such,
 *  there is no room for optimizing tail accesses so these will 
 *  take O(n) time by default.
 *
 *  This requires C99 or higher.
 *
 *  The naming convention attempts to follow C format, 
 *  which means lower case, underscores, etc.
 *
 *  MIT License
 *
 *  Copyright (c) 2015, Michael Becker (michael.f.becker@gmail.com)
 *  
 *  Permission is hereby granted, free of charge, to any person obtaining a 
 *  copy of this software and associated documentation files (the "Software"),
 *  to deal in the Software without restriction, including without limitation
 *  the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 *  and/or sell copies of the Software, and to permit persons to whom the 
 *  Software is furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included 
 *  in all copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
 *  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 *  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY 
 *  CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT 
 *  OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR 
 *  THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef SINGLE_LIST_B_H__
#define SINGLE_LIST_B_H__


/** 
 *  Since this is a generic implementation of a list, 
 *  void* lets you do anything.  If you know the data 
 *  you want, you can always change the typedef.
 */
typedef void * data_t;

/**
 *  The singly linked list structure.
 */
typedef struct s_list {

    struct s_list *next;
    data_t data;

}s_list_t;

/**
 *  Add a node to the list head.
 *  Runs in O(1) time.
 *
 *  @param head Existing list head, may be NULL.
 *  @param n The node you are adding to the head.
 *  @return The new head (i.e. n).
 */
s_list_t *add_node_to_head (s_list_t *head, s_list_t *n);

/**
 *  Add a node to the list tail.
 *  Runs in O(n) time.
 *  
 *  @param head Existing list head, may be NULL.
 *  @param n The node you are adding to the tail.
 *  @return List's head. Will return a new head if head == null at first.
 */
s_list_t *add_node_to_tail (s_list_t *head, s_list_t *n);

/**
 *  Inserts a new node into the list right after the marker element.
 *  Runs in O(1) time.
 *
 *  @param marker Node you are inserting after. Cannot be NULL.
 *  @param n The node you are inserting. Cannot be NULL.
 */
void insert_node_after (s_list_t *marker, s_list_t *n);

/**
 *  Inserts a new node into the list right before the marker element.
 *  May return a new head if the marker is the head.
 *  Runs in O(n) time.
 *
 *  @param head Existing list head, Cannot be NULL.
 *  @param marker Node you are inserting after. Cannot be NULL.
 *  @param n The node you are inserting. Cannot be NULL.
 *  @return List's head. 
 */
s_list_t *insert_node_before (s_list_t *head, s_list_t *marker, s_list_t *n);

/**
 *  Removes a node from the list.
 *  May return a new head.
 *  Runs in O(n) time.
 *
 *  @param head Existing list head, Cannot be NULL.
 *  @param n The node you are removing. Cannot be NULL.
 */
s_list_t *remove_node(s_list_t *head, s_list_t *n);

/*
 *  Helper function to allocate and initialize memory for a node.
 *
 *  @param d Data you want the node to be initialized with.
 *  @return A new node ready to be used.
 */
s_list_t *allocate_node(data_t d);

/*
 *  Helper macro to free a node's memory.
 *
 *  @param _n The node to be freed.
 */
#define free_node(_n) free(_n)

/**
 *  Helper function to free an entire list.
 *  @param head Existing list head, may be NULL.
 */
void free_list(s_list_t *head);

/**
 *  Macro to ease walking through all of the nodes in a list.
 *  @param _head The List head, cannot be NULL.
 *  @param _node An undefined symbol that will be defined by the macro.
 */ 
#define for_each_slist_node(_head, _node) \
    for (s_list_t *_node = head; _node != NULL; _node = _node->next)


#endif

