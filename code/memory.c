#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void* allocMemory(unsigned int size) {

    void* ptr = malloc(size);
    if(ptr == NULL) {
        fprintf(stderr, "memory  error: cannot allocate %d bytes\n", size);
        exit(1);
    }

    memset(ptr, 0, size);
    return ptr;
}

void* reallocMemory(void* ptr, unsigned int size) {

    void* nptr = realloc(ptr, size);
    if(nptr == NULL) {
        fprintf(stderr, "memory  error: cannot reallocate %d bytes\n", size);
        exit(1);
    }

    return nptr;
}

void freeMemory(void* ptr) {

    if(ptr != NULL)
        free(ptr);
}

void* copyMemory(void* ptr, unsigned int size) {

    void* nptr = allocMemory(size);
    memcpy(nptr, ptr, size);
    return nptr;
}
