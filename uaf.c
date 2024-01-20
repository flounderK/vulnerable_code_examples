
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

/*
 * From
 * Finding the Needle in the Heap: Combining Static Analysis and
 * Dynamic Symbolic Execution to Trigger Use-After-Free
 *
 */
void uaf_example_1 (void) {
    int* p;
    int* p_alias;
    int f = 1;
    char buf[255];
    p= malloc ( sizeof (int) );
    p_alias = p; // p and p_alias points
    // to the same addr
    read (f,buf ,255) ; // buf is tainted

    if( strncmp (buf ,"BAD\n" ,4) ==0) {
        free (p);
        // exit () is missing
    }
    else {
        printf("some computation\n");
        // some computation
    }

    if( strncmp (& buf [4] ,"is a uaf\n" ,9) == 0) {
        p= malloc ( sizeof (int) );
    }
    else {
        p = malloc ( sizeof (int) );
        p_alias = p;
    }

    *p = 42 ; // not a uaf
    *p_alias = 43 ; // uaf if 6 and 14 = true
    return;
}
