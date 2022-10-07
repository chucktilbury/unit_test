
#ifndef _PTR_LIST_H_
#define _PTR_LIST_H_

typedef struct {
    void** list;
    int len;
    int cap;
} PtrList;

PtrList* ptrListInit();
void ptrListDestroy(PtrList* lst);
void ptrListAdd(PtrList* lst, void* data);
void* ptrListGet(PtrList* lst, int index);
void** ptrListGetRaw(PtrList* lst);
int ptrListGetLen(PtrList* lst);

#endif
