#include <stdlib.h>     // exit constants
#include <stdio.h>     // for printf
#include "myMalloc.h"

int main(int argc, char** argv) { // this will do some checking of my malloc function
    printf("Running tests...\n");

    int* test = myMalloc(sizeof(int));
    //*test = 2;
    myFree(test);

    printf("Test completed :-)\n");

    return EXIT_SUCCESS;
}
