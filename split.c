/*
 *  split.c 
 *
 *  + Revised to compile clean + fixed indexing bugs.
 *  + Added free function to prevent memory leaks.
 *  + Added additional unit testing.
 *  + mb - 05/07/2015
 */

/*
Write a string split function. 
Inputs: string, char, and an int
Returns: an array of strings, split on char, up to int times. If int is negative, that means infinity

e.g.
split(“192.168.0.10”, ‘.’, -1) == [“192”, “168”, “0”, “10”]
split(“Hey-how-are-you?”, ‘-‘, 2) == [“Hey”, “how”, “are-you?”]
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Corrected declaration for compiler. */
char **split(char *str, char delimiter, int count, int *size_of_array)
{
    int len;
    int i;
    int substr_needed = 1;
    char **substr;
    int real_count;
    char *copy;         /* changed name, too close to strcpy */
    int substr_index;
    
    
    len = strlen(str);
    copy = strdup(str); /* changed to correct call */

    for(i = 0; i < len; i++){
        if (copy[i] == delimiter){
            substr_needed++;
        }
    }
    
    
    if (count < 0){
        real_count = substr_needed;
    }
    else if (count == 0){
        real_count = 1;
    }
    else{
        if (substr_needed < count)
            real_count = substr_needed;
        else
            real_count = count;
    }
    
    substr = malloc(sizeof(char*) * real_count);    

    /* Fixed indexing, and missing first element. */
    substr_index = 0;
    substr[substr_index++] = &copy[0];

    for (i = 0; i < len; i++){

        if (substr_index >= real_count){
            break;
        }

        if (copy[i] == delimiter){
            copy[i] = 0;
            substr[substr_index++] = &copy[i+1];
        }
    }

    *size_of_array = real_count;
    
    return substr;
}


/*
 *  Correctly frees the Array returned from split().
 */
void free_split_array(char **A)
{
    if (A == NULL)
        return;

    free(A[0]);
    free(A);
}



#ifdef UNIT_TEST_SPLIT
/* gcc -DUNIT_TEST_SPLIT -Wall split.c */

#define TEST_CASE(str_, cnt_)                   \
    ans = split(str_, delimiter, cnt_, &cnt);   \
    printf("Split(%s, %d)\n", str_, cnt_);      \
    for (i = 0; i < cnt; i++){                  \
        printf("[%d] = %s\n", i, ans[i]);       \
    }                                           \
    free_split_array(ans);



/* 
 * + Added new unit tests. 
 * + Added TEST_CASE macro.
 * + Freeing memory in macro, valgrind runs clean.
 */
int main (void)
{
    /* fixed declarations */
    char *str1 = "192.168.1.2";
    char *str2 = "192";
    char *str3 = ".192.168.1.2";
    char *str4 = "192.168.1.2.";
    char *str5 = "192.168..1.2";
    char *str6 = "192.168..1.2..";
    char *str7 = "..192.168..1.2..";
    char *str8 = "Hey-how-are-you?";
    char delimiter = '.';
    char **ans;
    int cnt;
    int i;
    
    TEST_CASE(str1, 4);
    TEST_CASE(str1, 3);
    TEST_CASE(str1, 2);
    TEST_CASE(str1, 1);
    TEST_CASE(str1, 0);
    TEST_CASE(str1, -1);
    TEST_CASE(str1, 100);
    

    TEST_CASE(str1, -1);
    TEST_CASE(str2, -1);
    TEST_CASE(str3, -1);
    TEST_CASE(str4, -1);
    TEST_CASE(str5, -1);
    TEST_CASE(str6, -1);
    TEST_CASE(str7, -1);

    delimiter = '-';
    TEST_CASE(str8, 2);

    return 0;
}


#endif


