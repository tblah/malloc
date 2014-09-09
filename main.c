#include <stdlib.h>     // exit constants
#include <stdio.h>     // for printf
#include "myMalloc.h"

int main(int argc, char** argv) { // this will do some checking of my malloc function
    printf("Running tests...\n");

    // works the first time
    int* test = myMalloc(sizeof(int));
    *test = 2;
    myFree(test);

    // works a second time
    /*test = myMalloc(sizeof(int));
    *test = 2;
    myFree(test);*/

    // checking conecutive memory is okay
    /*int* x = myMalloc(sizeof(int));
    int* y = myMalloc(sizeof(int));
    int* z = myMalloc(sizeof(int));

    *x = 1;
    *z = 2;
    *y = *x + *y;

    myFree(x);
    myFree(z);

    if (*y = 3) 
        printf("Tests completed succsessfully\n");
    else {
        printf("Oh dear..\n");
        return EXIT_FAILURE;
    }*/

    return EXIT_SUCCESS;
}
