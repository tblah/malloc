#ifdef DEBUG
#include <stdio.h> // do we want printf's?
#include "freeNode.h"
#endif

extern void* beginningOfHeap;

void myFree(void* p) {
    #ifdef DEBUG
    printf("Running my free function\n");
    #endif

    // the beginning of the free segment (including the "hidden" size counter)
    void* beginning = ((size_t*) p) - 1; 
    size_t size = *((size_t*) beginning);  // the preceding integer

    // now we have a copy of the size we can overwrite it
    ((struct freeNode*) beginning)->size = size + sizeof(size_t);

    // for performance all new free spaces of memory will be at the beginning
    //      of the list.
    // 
    // This makes frees fast but might slow down a malloc compared to if the
    //      list of free segments was in an ordered list. 
    //
    // Overall this makes this a lot simpler to implement, which is what is 
    //      important for lazy me.
    
    ((struct freeNode*) beginning)->next = beginningOfHeap;

    beginningOfHeap = beginning; // putting it at the beginning of the list
    
}
