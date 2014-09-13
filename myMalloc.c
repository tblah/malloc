#define _BSD_SOURCE // sbrk

#include <unistd.h> // size_t sbrk
#include "freeNode.h"
#include "createFreeNode.h"

#ifdef DEBUG
#include <stdio.h> // do we want printf's?
#endif

// bool
typedef enum {false, true} bool;

// flag so that we know if malloc has been run yet
int firstRun = true;

// stores where the beginning of the heap is so that we can find it again
void* beginningOfHeap = NULL;

struct freeNode* findPreviousNode(struct freeNode* target) {
    if ((target == NULL) | (beginningOfHeap == NULL))
        return NULL;

    struct freeNode* currentNode = (struct freeNode*) beginningOfHeap;
    
    while (currentNode->next != target) {
        if (currentNode->next == NULL)
            return NULL;   // this means that we are at the end of the list
        currentNode = currentNode->next;
    }

    return currentNode;
}

// recurcive itteration throught the free memory list. If the requested alloc
// can be done in currently in use memory then a pointer to this memory is
// returned. If not then NULL is returned.
void* lookForSpace(struct freeNode* start, size_t numBytes) {
    // if we have to split an existing free segment into this new alloc and
    //  another smaller free segment then we need to have enough space in the
    //  new smaller segment to be able to fit a freeNode.
    // TO DO: no checking for an overflow here!!!!!!!!!!!!!!!!!!!!!!!!!!!
    const size_t threshold = numBytes + sizeof(struct freeNode);

    if (start == NULL) { // a bad has happened
        #ifdef DEBUG
        printf("aquireSuitableNode() hit the end of the list \n");
        #endif
        return NULL;
    }
    else if (start->size == numBytes) { // perfect fit
        #ifdef DEBUG
        printf("Perfect fit for this alloc\n");
        #endif

        // remove this node from the list of free nodes
        struct freeNode* previous = findPreviousNode(start);
        if (previous == NULL)
            return NULL;

        previous->next = start->next;

        return start;
    } else if (start->size > threshold) { // too much space
        // TEST THE SUMMS HERE *THOUGHERLY*
        #ifdef DEBUG
        printf("Splitting a larger memory segment for this alloc\n");
        #endif

        // shrink this freeNode in place
        // doing it in place keeps the pointer in the previous node valid
        //  note: the two sizeof(size_t) cancel
        start->size = (start->size) - numBytes - sizeof(size_t);

        return ((void*) start) + sizeof(size_t) + start->size;

    } // else not enough space lets move on
    #ifdef DEBUG
    printf("Current segment too big: moving on\n");
    #endif

    return lookForSpace(start->next, numBytes);
}

// allocates the new space into new heap space requested from the kernel
void* allocNew(size_t numBytes) {
    #ifdef DEBUG
    printf("Raising brogram break by %li bytes\n", numBytes + sizeof(size_t));
    #endif

    void* freeSegment = sbrk(sizeof(size_t) + numBytes);
    if ((freeSegment == (void*)(-1)) | (freeSegment == NULL))
        return NULL; // something went wrong so do errors

    *((size_t*) freeSegment) = numBytes; // the size is stored at the beginning
    void* userMemory = freeSegment + sizeof(size_t);

    return userMemory;
}

void* myMalloc(size_t numBytes) {
    #ifdef DEBUG
    printf("Running my malloc function...\n");
    #endif

    // MAJOR LIMITATION: we need to be able to fit a whole freeNode struct in
    //  each alloc and so numBytes must be atleast sizeof(void*)
    if (numBytes < sizeof(void*))
        numBytes = sizeof(void*);

    // check to see if this is the first time we have run malloc
    if (firstRun){
        firstRun = false;
        #ifdef DEBUG
            printf("This is the first time you have run malloc\n");
        #endif

        // set the beginning of the heap so that we can find it again
        // this first sbrk will be the space for the pointer to the first
        // free node
        beginningOfHeap = sbrk(sizeof(void*));
        if ((beginningOfHeap == NULL) | (beginningOfHeap == (void*)(-1)))
            return NULL; // something went wrong with sbrk so error

        beginningOfHeap = NULL; // there are no free memory segments yet

        return allocNew(numBytes); // allocates the space requested
    }

    #ifdef DEBUG
    printf("This is not the first time you have run malloc\n");
    #endif

    if (beginningOfHeap == NULL) {
        // there is no free memory so just allocate on the end
        return allocNew(numBytes); // allocates the space requested
    }
    else { // there is free memory
        void* foundSpace = lookForSpace((struct freeNode*) beginningOfHeap,
                numBytes);

        if (foundSpace == NULL) // no suitable free segments exitst
            return allocNew(numBytes); // so lets allocate another
        else { // free segment found for us
            *((size_t*) foundSpace) = numBytes; // the number bit
            return foundSpace + sizeof(size_t); // the user bit
        }
    }

    return NULL; // we shouldnt have made it here
}
