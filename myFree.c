#ifdef DEBUG
#include <stdio.h> // do we want printf's?
#include "freeNode.h"
#include "createFreeNode.h"
#endif

extern void* beginningOfHeap;

// note that this implementation of free will not ever reduce the program break
// TO DO: optionally calculate the total memory utilisation after each free
//           and then do very clever things to decide if its worth decreacing
//              the program break.

void myFree(void* p) {
    #ifdef DEBUG
    printf("Running my free function\n");
    #endif

    // the beginning of the free segment (including the "hidden" size counter)
    void* beginning = ((size_t*) p) - 1; 
    size_t size = *((size_t*) beginning);  // the preceding integer
    // This means that the reported size is the number of bytes origionally
    // passed to malloc: i.e. the total size taken by the free segment is
    // size + sizeof(size_t)

    // for performance all new free spaces of memory will be at the beginning
    //      of the list.
    // 
    // This makes frees fast but might slow down a malloc compared to if the
    //      list of free segments was in an ordered list. 
    //
    // Overall this makes this a lot simpler to implement, which is what is 
    //      important for lazy me.
    

    // now we have a copy of the size we can overwrite it
    createFreeNode(beginning, size, beginningOfHeap);

    beginningOfHeap = beginning; // putting it at the beginning of the list
    
}
