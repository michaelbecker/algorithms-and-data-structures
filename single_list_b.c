/**
 *  @file
 *
 *  Singly linked list implementation.
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
#include <stdlib.h>
#include "single_list_b.h"


s_list_t *add_node_to_head (s_list_t *head, s_list_t *n)
{
    if (head){
        n->next = head;
    }

    return n;
}


s_list_t *add_node_to_tail (s_list_t *head, s_list_t *n)
{
    s_list_t *cur;

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


void insert_node_after (s_list_t *marker, s_list_t *n)
{
    s_list_t *marker_p1;

    if (!marker)
        return;

    if (!n)
        return;

    marker_p1 = marker->next;
    marker->next = n;
    n->next = marker_p1;
}


s_list_t *insert_node_before (s_list_t *head, s_list_t *marker, s_list_t *n)
{
    s_list_t *cur_m1;
    s_list_t *cur;

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


s_list_t *remove_node(s_list_t *head, s_list_t *n)
{
    s_list_t *cur;
    s_list_t *prev;

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


s_list_t *allocate_node(data_t d)
{
    s_list_t *n;

    n = malloc(sizeof(s_list_t));
    if (!n)
        return NULL;

    n->next = NULL;
    n->data = d;

    return n;
}


void free_list(s_list_t *head)
{
    s_list_t *cur;

    while (head != NULL){
        cur = head;
        head = head->next;
        free(cur);
    }
}


