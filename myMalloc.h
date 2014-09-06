#ifndef MALLOC_H
#define MALLOC_H

#include <unistd.h> // size_t

void* myMalloc(size_t numBytes);
void myFree(void* p);

#endif
