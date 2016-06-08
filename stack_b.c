/**
 *  @file
 *
 *  Implementation of a generic stack in C.
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
 }}} */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack_b.h"



struct stack *create_stack(void)
{
    struct stack *s;

    s = malloc(sizeof(struct stack));

    if (!s)
        return NULL;

    memset(s, 0, sizeof(struct stack));

    return s;
}


void push_node(struct stack *s, int data)
{
    struct s_list *n;

    if (!s)
        return;

    n = create_node(data);
    if (!n)
        return;

    s->head = add_node_to_head(s->head, n);
    s->count++;
}


int pop_node(struct stack *s)
{
    struct s_list *n;
    int data;

    if (!s)
        return -1;

    if (s->count == 0)
        return -1;

    n = s->head;
    s->head = remove_node(s->head, n);
    s->count--;
    data = n->data;
    free(n);

    return data;
}


void destroy_stack(struct stack *s)
{
    struct s_list *n;

    if (!s)
        return;

    while (s->count > 0){
        n = s->head;
        s->head = remove_node(s->head, n);
        free(n);
        s->count--;
    }

    free(s);
}


void print_stack(struct stack *s)
{
    printf("Stack Elements: %d", s->count);
    print_list(s->head);
}


/* gcc -DTEST_STACK stack.c s-list.c */
#ifdef TEST_STACK

int main(void)
{
    struct stack *s;
    int i;

    s = create_stack();
    print_stack(s);

    for (i = 0; i < 5; i++)
        push_on_stack(s, i);

    print_stack(s);

    i = pop_off_stack(s);
    printf("\nPopped %d\n", i);
    print_stack(s);

    i = pop_off_stack(s);
    printf("\nPopped %d\n", i);
    print_stack(s);

    for (i = 10; i < 15; i++)
        push_on_stack(s, i);
    print_stack(s);

    destroy_stack(s);
    
    return 0;
}

#endif


