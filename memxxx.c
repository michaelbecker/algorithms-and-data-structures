/**
 *  @file
 *
 *  An implementation of memcpy optimized for a general 32 bit 
 *  architecture written in C.
 *
 *  If this was a simple version and we didn't care about speed, 
 *  we'd just use a loop and copy a byte at a time.
 *  
 *  But because this is an optimized implementation, we use a few gotos, 
 *  fall throughs on case statements, etc. The idea is to be thinking 
 *  of how the assembly code may look and keep this fast. 
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
 *  
 */
#include <string.h>
#include <stdint.h>



void *memcpy_xxx(void *dest_ptr, const void *src_ptr, size_t num_bytes)
{
    //-------------------------------------------------------
    //  Yes, the compiler is free to ignore the register 
    //  keyword, but this is also an indication to us that 
    //  we care how these are opimized.
    register unsigned char *dest = (unsigned char *)dest_ptr;
    register unsigned char *src = (unsigned char *)src_ptr;
    register uint32_t num_blocks;
    register uint32_t n = num_bytes;
    //-------------------------------------------------------

    //
    //  If we are less than a 32 bit word, we don't care about alignment, 
    //  just copy the few bytes.
    //
    if (n < 4) {
        goto COPY_LAST_BYTES;
    }

    //
    //  We need 32 bit aligned pointers for both the src and dest. 
    //  If they cannot be aligned together, default to a byte by byte copy.
    //
    if (((uintptr_t)src & 0x3) != ((uintptr_t)dest & 0x3)) {
        goto COPY_MISALIGNED_BYTES;
    }

    //
    //  If we're here, the buffers can be aligned. 
    //  Then take advantage of it for the rest of the algorithm.
    //
    switch((uintptr_t)src & 0x3) {

        case 3: *dest++ = *src++; n--;
        case 2: *dest++ = *src++; n--;
        case 1: *dest++ = *src++; n--;
    }

    //
    //  An optimized version where we move 32 bit words. We'll also 
    //  unroll the loop as a further optimization.
    //
    if (n >= 16) {

        num_blocks = n >> 4;
        n = n & 0xF;

        while (num_blocks > 0) {

            *(uint32_t *)dest = *(uint32_t *)src; dest += 4; src += 4;
            *(uint32_t *)dest = *(uint32_t *)src; dest += 4; src += 4;
            *(uint32_t *)dest = *(uint32_t *)src; dest += 4; src += 4;
            *(uint32_t *)dest = *(uint32_t *)src; dest += 4; src += 4;
            
            num_blocks--;
        }
    }

    //
    //  Finish up copying the last few words.
    //
    if (n >= 4) {

        num_blocks = n >> 2;
        n = n & 0x3;

        switch (num_blocks) {
            case 3: *(uint32_t *)dest = *(uint32_t *)src; dest += 4; src += 4;
            case 2: *(uint32_t *)dest = *(uint32_t *)src; dest += 4; src += 4;
            case 1: *(uint32_t *)dest = *(uint32_t *)src; dest += 4; src += 4;
        }
    }

    //  
    //  And finish up copying the last few bytes. 
    //
    switch(n){
        case 3: *dest++ = *src++;
        case 2: *dest++ = *src++;
        case 1: *dest++ = *src++;
        default: return dest;
    }


    /////////////////////////////////////////////////////////////////////////
    //
    //  Special Case - Copy Misaligned Bytes
    //
    //  If we fall through to here, the src and dest are misaligned and we 
    //  are stuck doing a byte by byte copy.
    //
    /////////////////////////////////////////////////////////////////////////
COPY_MISALIGNED_BYTES:

    num_blocks = n >> 2;

    while (num_blocks > 0) {
        *dest = *src; dest++; src++;
        *dest = *src; dest++; src++;
        *dest = *src; dest++; src++;
        *dest = *src; dest++; src++;
        num_blocks--;
    }

    n = n & 3;

    /////////////////////////////////////////////////////////////////////////
    //
    //  Special Case - Copy Last Bytes
    //  Finish up with the last 3 - 0 bytes.
    //
    /////////////////////////////////////////////////////////////////////////
COPY_LAST_BYTES:

    switch(n) {
        case 3: *dest++ = *src++;
        case 2: *dest++ = *src++;
        case 1: *dest++ = *src++;
        default: return dest;
    }
}


