#define _BSD_SOURCE // sbrk

#include <unistd.h> // size_t sbrk
#include "freeNode.h"

#ifdef DEBUG
#include <stdio.h> // do we want printf's?
#endif

// bool
typedef enum {false, true} bool;

// flag so that we know if malloc has been run yet
int firstRun = true;

// stores where the beginning of the heap is so that we can find it again
void* beginningOfHeap = NULL;

// utility function to errase memory
#ifdef SECURE
void eraiseMemory(void* memory, size_t numBytes) {
    void* max = memory + numBytes;
    for (void* i = memory; i < max; i++)
        *((char *) i) = 0; 
}
#endif

void* myMalloc(size_t numBytes) {
    #ifdef DEBUG
    printf("Running my malloc function...\n");
    #endif

    // MAJOR LIMITATION: we need to be able to fit a whole freeNode struct in
    //  each alloc and so numBytes must be atleast sizeof(void*)
    if (numBytes < sizeof(void*))
        numBytes = sizeof(void*);

    size_t* size = NULL; // will point to where we are putting the length
    void* userMemory = NULL; // pointer to the memory returned to the user

    // check to see if this is the first time we have run malloc
    if (firstRun){
        firstRun = false;
        #ifdef DEBUG
            printf("This is the first time you have run malloc\n");
            printf("Requesting %li bytes\n", sizeof(void*) + sizeof(size_t) + numBytes);
        #endif

        // set the beginning of the heap so that we can find it again
        beginningOfHeap = sbrk(0);

        // space for the starting pointer for the list of free memory,
        //  the length of the stored segment and the requested memory.
        void* newHeap = sbrk(sizeof(void*) + sizeof(size_t) + numBytes); 
        if ((newHeap == (void*)(-1)) | (newHeap == NULL))
            return NULL;    // something went wrong so error out and die

        size = newHeap + sizeof(void*);     // set pointers so I can find things
        userMemory = size + 1;

        *size = numBytes;       // remember how long this segment is

        // so we know that there is no free memory at the moment
        *((void**) newHeap) = NULL; 

        #ifdef SECURE
        eraiseMemory(userMemory, numBytes); // for securityy
        #endif

        return userMemory;
    }

    #ifdef DEBUG
       printf("This is not the first time you have run malloc\n");
    #endif

    return userMemory;
}
