#include <stdlib.h>     // exit constants
#include <stdio.h>     // for printf
#include "myMalloc.h"

// this will do some checking of my malloc function
int main(int argc, char** argv) { 
    printf("Running tests...\n");

    // works the first time
    int* test = myMalloc(sizeof(int));
    *test = 2;
    myFree(test);

    // works a second time
    long* test2 = myMalloc(sizeof(long));
    *test2 = 2;
    myFree(test2);

    // checking conecutive memory is okay
    int* x = myMalloc(sizeof(int));
    int* y = myMalloc(sizeof(int));
    int* z = myMalloc(sizeof(int));

    *x = 1;
    *z = 2;
    *y = *x + *z;

    myFree(x);
    myFree(z);

    if (*y == 3) { 
        myFree(y);
        printf("Tests completed succsessfully\n");
    }
    else {
        myFree(y);
        printf("Oh dear..final test failed\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
