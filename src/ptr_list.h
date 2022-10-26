#ifndef _PTR_LIST_H_
#define _PTR_LIST_H_

#include <stddef.h>

/*
 * Generic pointer list data structure.
 */
typedef struct {
    void** list; // list of pointers
    int cap;     // capacity of the list
    int len;     // actual number of items
    size_t size; // size of the data that the list element points to
} PtrList;

PtrList* ptrListCreate(size_t size);
void ptrListDestroy(PtrList* lst);
void ptrListAdd(PtrList* lst, void* data);
void* ptrListGet(PtrList* lst, int idx);
void** ptrListGetRaw(PtrList* lst);
int ptrListGetLen(PtrList* lst);

#endif