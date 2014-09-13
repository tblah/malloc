#ifndef FREENODE_H
#define FREENODE_H

#include <unistd.h> // size_t

struct freeNode {
    void* next;
    size_t size;
};

#endif
