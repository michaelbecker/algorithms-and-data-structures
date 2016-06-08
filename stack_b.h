/**
 *  @file
 *
 *  Stack interface using existing singly linked list.
 *
 *  Specifically this uses my sll impl version b, which 
 *  is headless and embeds a data pointer within the s_list_t.
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
#ifndef STACK_B_H__
#define STACK_B_H__


#include "single_list_b.h"


typedef struct stack_t {

    int count;
    s_list_t *head;

}stack;


#define INIT_STACK(_stack)  \
{                           \
    (_stack).count = 0;     \
    (_stack).head = NULL;   \
}

void push_node(stack *stack, s_list_t *node);

s_list_t *pop_node(stack *stack);

int is_empty(stack *stack);

s_list_t *peek_top(stack *stack);

int get_depth(stack *stack);


#endif

