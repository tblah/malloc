#include "freeNode.h"
#include <unistd.h> //size_t

// creates a freeNode at the specified location with the specified properties
//      there is no way for this to check that it is not overwriting anything
//          so please be careful
//
// This might look syntaxicly ugly but all it does is to interprit the
// specified address as the beginning address of the struct and then the layout
// is done for me by the compiler. 
void createFreeNode(void* where, size_t size, void* next) {
    ((struct freeNode*) where)->size = size;
    ((struct freeNode*) where)->next = next;
}
