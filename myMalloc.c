#include <unistd.h> // size_t

#ifdef DEBUG
#include <stdio.h> // do we want printf's?
#endif

void* myMalloc(size_t numBytes) {
    #ifdef DEBUG
    printf("Running my malloc function...\n");
    #endif

    void* ret = 0;

    return ret;
}
