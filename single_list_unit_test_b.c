/**
 *  @file
 *
 *  Unit test for Singly linked list.
 *
 *  This requires C99 or higher.
 *
 *  To compile:
 *  gcc -std=c99 -Wall single_list_b.c single_list_unit_test_b.c -o single_list_unit_test_b
 *  
 *  To test:
 *  valgrind single_list_unit_test_b
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
#include <stdio.h>
#include <stdlib.h>

#include "single_list_b.h"

/**
 *  We are unit testing using simple code that treats the data_t as 
 *  an integer.
 */
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"



void print_list(s_list_t *head)
{
    printf("\nPrinting test List\n");
    for_each_slist_node(head, n){
        printf("DATA: %p\n", n->data);
    }
}


int main (void)
{
    s_list_t *head;
    s_list_t *n[5];
    s_list_t *cur;
    int i;

    // Test 1 --------------------------------
    head = NULL;
    for (i = 0; i < 5; i++)
        n[i] = allocate_node((data_t)i);

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
        n[i] = allocate_node((data_t)i);

    for (i = 0; i < 5; i++)
        head = add_node_to_head(head, n[i]);
    print_list(head);
    free_list(head);


    // Test 3 --------------------------------
    head = NULL;
    for (i = 0; i < 5; i++)
        n[i] = allocate_node((data_t)i);

    for (i = 0; i < 5; i++)
        head = add_node_to_tail(head, n[i]);

    print_list(head);
    free_list(head);


    // Test 4 --------------------------------
    head = NULL;
    for (i = 0; i < 5; i++)
        n[i] = allocate_node((data_t)i);

    head = n[0];
    for (i = 0; i < (5-1); i++)
        insert_node_after(n[i], n[i+1]);

    print_list(head);
    free_list(head);


    // Test 5 --------------------------------
    head = NULL;
    for (i = 0; i < 5; i++)
        n[i] = allocate_node((data_t)i);

    head = n[0];
    for (i = 0; i < (5-1); i++)
        head = insert_node_before(head, n[i], n[i+1]);

    print_list(head);
    free_list(head);



    head = NULL;
    for (i = 0; i < 5; i++)
        n[i] = allocate_node((data_t)i);

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


