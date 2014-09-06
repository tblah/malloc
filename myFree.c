#ifdef DEBUG
#include <stdio.h> // do we want printf's?
#endif

void myFree(void* p) {
    #ifdef DEBUG
    printf("Running my free function\n");
    #endif

}
