/**
 *  @file
 *
 *  Unit test code of memxxx.c
 *
 *  To compile:
 *  gcc -Wall -std=c99 memxxx.c unit_test_memxxx.c -o unit_test_memxxx
 *
 *  To test:
 *  valgrind ./unit_test_memxxx
 *
 *  MIT License
 *
 *  Copyright (c) 2016, Michael Becker (michael.f.becker@gmail.com)
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
#include <string.h>
#include <ctype.h>


/**
 *  External reference to our custom version of memcpy.
 */
extern void *memcpy_xxx(void *dest_ptr, const void *src_ptr, size_t num_bytes);


/**
 *  Our custom malloc structure for testing.
 */
typedef struct custom_block_t_ {

    /**
     *  The ptr memcpy will use. Lives inside real_ptr buffer.
     */
    unsigned char *ptr;

    /**
     *  The size memcpy will use.
     */
    int size;

    /**
     *  Desired alignment offset:
     *  0 => aligned on 4 bytes
     *  1 => offset by 1 byte
     *  2 => offset by 1 byte
     *  3 => offset by 1 byte
     */
    int alignment_offset;

    /**
     *  The real malloc pointer.
     */
    unsigned char *real_ptr;

    /**
     *  The real size.
     */
    int real_size;

} custom_block_t;


/**
 *  Wrapper around malloc that adds a header, footer, and can misalign memory 
 *  on purpose.
 */
unsigned char *malloc_custom(int size, int alignment_offset, custom_block_t **save_block)
{
    /*
     *  Need a control structure for this.
     */
    custom_block_t *block = (custom_block_t *)malloc(sizeof(custom_block_t));

    //  
    //  Fix up alignment_offset.
    //
    alignment_offset = alignment_offset % 4;

    block->alignment_offset = alignment_offset;
    block->size = size;

    //  
    //  Add an int header and footer at either end, plus the alignment_offset
    //  to skew the alignment if desired.
    //
    block->real_size = block->size + 4 + 4 + block->alignment_offset;

    //
    //  Get our memory.
    //
    block->real_ptr = (unsigned char *)malloc(block->real_size);

    //
    //  Fix up the pointer we are going to give back.
    //
    block->ptr = block->real_ptr + 4 + block->alignment_offset;

    //
    //  Fill everything in with a knowm pattern.
    //
    memset(block->real_ptr, 0xee, block->real_size);

    //
    //  Need to also save the control block.
    //
    *save_block = block;

    return block->ptr;
}


/**
 *  Companion to malloc_custom.
 */
void free_custom(custom_block_t *block)
{
    //
    //  Wipe the memory clean.
    //
    memset(block->real_ptr, 0x11, block->real_size);

    //
    //  And free it.
    //
    free(block->real_ptr);

    //
    //  Wipe the control structure clean.
    //
    memset((unsigned char *)block, 0x22, sizeof(custom_block_t));

    //
    //  And then free it too.
    //
    free(block);
}


/**
 *  Print out a hex dump of the memory and the controlling block.
 */
void print_custom(custom_block_t *block, const char *tag)
{
    int i, j;

    printf("%s : %p\n", tag, block);
    printf("------------------------------------------------------------------------------\n");
    printf("ptr      = %p  size      = %d  alignment_offset = %d\n", 
            block->ptr, block->size, block->alignment_offset);
    printf("real_ptr = %p  real_size = %d\n", 
            block->real_ptr, block->real_size);

    int full_lines = block->real_size / 16;
    unsigned char *ptr = block->real_ptr;

    for (i = 0; i < full_lines; i++){
        printf("%p |", ptr);
        for (j = 0; j < 16; j++) {
            printf(" %02x", ptr[j]);
        }
        printf(" | ");
        for (j = 0; j < 16; j++) {
            if (isgraph(ptr[j]))
                printf("%c", ptr[j]);
            else 
                printf(".");
        }
        printf("\n");
        ptr += 16;
    }

    int remaining_bytes = block->real_size % 16;

    if (remaining_bytes) {
        printf("%p |", ptr);
        for (j = 0; j < remaining_bytes; j++) {
            printf(" %02x", ptr[j]);
        }
        for ( ; j < 16; j++) {
            printf("   ");
        }
        printf(" | ");

        for (j = 0; j < remaining_bytes; j++) {
            if (isgraph(ptr[j]))
                printf("%c", ptr[j]);
            else 
                printf(".");
        }
        printf("\n");
    }

    printf("\n");
}
#define PRINT_CUSTOM(_x) print_custom(_x, #_x)


/**
 *  Check that the src of the memcpy and the dest match, as expected 
 *  with respect to alignment mismatchches. Also check that the header 
 *  and footers are intact, to check for off by one errors. If anything 
 *  is wrong, dump the buffers for debug.
 */
void verify_memcpy_xxx(custom_block_t *a, custom_block_t *b)
{
    for (int i = 0; i < a->size; i++) {
        if (a->ptr[i] != b->ptr[i]){
            printf("DATA DOESN'T MATCH\n");
            PRINT_CUSTOM(a);
            PRINT_CUSTOM(b);
            exit(-1);
        }
    }

    for (int i = 0; i < (4 + a->alignment_offset); i++) {
        if (a->real_ptr[i] != 0xee){
            printf("HEADER CORRUPT\n");
            PRINT_CUSTOM(a);
            PRINT_CUSTOM(b);
            exit(-1);
        }
    }

    for (int i = 0; i < (4 + b->alignment_offset); i++) {
        if (b->real_ptr[i] != 0xee){
            printf("HEADER CORRUPT\n");
            PRINT_CUSTOM(a);
            PRINT_CUSTOM(b);
            exit(-1);
        }
    }

    for (int i = 0; i < 4; i++) {
        if (a->real_ptr[a->real_size - i - 1] != 0xee){
            printf("FOOTER CORRUPT\n");
            PRINT_CUSTOM(a);
            PRINT_CUSTOM(b);
            exit(-1);
        }
        if (b->real_ptr[b->real_size - i - 1] != 0xee){
            printf("FOOTER CORRUPT\n");
            PRINT_CUSTOM(a);
            PRINT_CUSTOM(b);
            exit(-1);
        }
    }
}


/**
 *  Run a single memcpy unit test. The verify function will 
 *  actually exit if it detects an error.
 */
void test_generic(const int size, int src_alignment, int dest_alignment)
{
    custom_block_t *dest_block, *src_block;
    unsigned char *dest, *src;

    dest = malloc_custom(size, dest_alignment, &dest_block);
    src = malloc_custom(size, src_alignment, &src_block);

    for (int i = 0; i < size; i++) {
        src[i] = (i+1);
    }

    memcpy_xxx(dest, src, size);
    verify_memcpy_xxx(src_block, dest_block);

    free_custom(src_block);
    free_custom(dest_block);
}


/**
 *  Iterate over all possible combinations of alignment and size, within 
 *  reason.
 */
void test_all(void)
{
    for (int size = 1; size < 1024; size++) {
        for (int src_alignment = 0; src_alignment < 4; src_alignment++) {
            for (int dest_alignment = 0; dest_alignment < 4; dest_alignment++) {
                test_generic(size, src_alignment, dest_alignment);
            }
        }
    }
}


/**
 *  Small main function to run the test.
 */
int main (void)
{
    printf("\nUnit testing memxxx functions.\n\n");

    test_all();

    printf("Tests passed\n");

    return 0;
}



