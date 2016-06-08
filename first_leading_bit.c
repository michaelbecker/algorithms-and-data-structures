/*
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


/**
 *  Provides a count of the leading zeros in an integer.
 *
 *  @param mask we are counting zero bits in.
 *  @returns number of leading zeros
 */
int
count_leading_zeros(unsigned int mask)
{
    int count = 0;

    if (mask == 0){
        return 32;
    }

    if (mask <= 0x0000FFFF) {
        count += 16;
        mask <<= 16;
    }

    if (mask <= 0x00FFFFFF) {
        count += 8;
        mask <<= 8;
    }

    if (mask <= 0x0FFFFFFF) {
        count += 4;
        mask <<= 4;
    }

    if (mask <= 0x3FFFFFFF) {
        count += 2;
        mask <<= 2;
    }

    if (mask <= 0x7FFFFFFF) {
        count += 1;
    }

    return count;
}


/**
 *  Provides a zero based index of the first MSb set 
 *  in the given mask.
 *
 *  @param index Pointer where we will return the zero based 
 *  index of the first MSb set.
 *  @param mask where we are searching.
 *  @returns zero if no bits are set. one of there is 
 *  some bit set.
 */
int
first_leading_bit(  int *index,         /* [out] */
                    unsigned int mask)  /* [in]  */
{
    int num_leading_zeros = count_leading_zeros(mask);

    if (num_leading_zeros == 32){  
        return 0;
    }

    *index = 31 - num_leading_zeros;

    return 1;
}


void run_test(unsigned int mask)
{
    int index;
    int rc;

    rc = first_leading_bit(&index, mask);
    if (rc)
        printf("rc: %d  mask: %08x  index: %d\n", rc, mask, index);
    else 
        printf("rc: %d  mask: %08x  index: --\n", rc, mask);
}


int main (void)
{
    unsigned int mask = 1;
    unsigned int i;

    printf("first_leading_bit unit test \n\n");
    
    run_test(0);

    for (i = 0; i < 32; i++) {
        run_test(mask);
        mask <<= 1;
    }

    mask = 1;
    for (i = 0; i < 33; i++) {
        run_test(mask-1);
        mask <<= 1;
    }

    return 0;
}


