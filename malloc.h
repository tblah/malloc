#ifndef MALLOC_H
#define MALLOC_H

#include <unistd.h> // size_t

void* malloc(size_t numBytes);
void free(void* p);

#endif
