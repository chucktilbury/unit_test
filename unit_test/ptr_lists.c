
#include <assert.h>

#include "memory.h"
#include "ptr_lists.h"

PtrList* ptrListInit() {

    PtrList* lst = _alloc_ds(PtrList);
    lst->len = 0;
    lst->cap = 1;
    lst->list = _alloc_ds_array(void*, lst->cap);

    return lst;
}

void ptrListDestroy(PtrList* lst) {

    assert(lst != NULL);
    _free(lst->list);
    _free(lst);
}

void ptrListAdd(PtrList* lst, void* data) {

    if(lst->len + 1 > lst->cap) {
        lst->cap <<= 1;
        lst->list = _realloc_ds_array(lst->list, void*, lst->cap);
    }

    lst->list[lst->len++] = data;
}

void* ptrListGet(PtrList* lst, int index) {

    assert(lst != NULL);
    assert(lst->len >= 0 && index < lst->len && index >= 0);

    return lst->list[index];
}

void** ptrListGetRaw(PtrList* lst) {

    assert(lst != NULL);
    return lst->list;
}

int ptrListGetLen(PtrList* lst) {

    assert(lst != NULL);
    return lst->len;
}
