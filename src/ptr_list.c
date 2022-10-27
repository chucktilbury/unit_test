
#include "ptr_list.h"
#include "memory.h"

PtrList* ptrListCreate(size_t size) {

    PtrList* list = _alloc_ds(PtrList);

    list->cap = 1 << 3;
    list->len = 0;
    list->size = size;
    list->list = _alloc_ds_array(void*, list->cap);

    return list;
}

void ptrListDestroy(PtrList* lst) {

    if(lst != NULL) {
        for(int i = 0; i < lst->len; i++)
            _free(lst->list[i]);
        _free(lst->list);
        _free(lst);
    }
}

void ptrListAdd(PtrList* lst, void* data) {

    if(lst->len >= lst->cap) {
        lst->cap <<= 1;
        lst->list = _realloc_ds_array(lst->list, void*, lst->cap);
    }

    lst->list[lst->len] = _alloc(lst->size);
    memcpy(lst->list[lst->len], data, lst->size);

    lst->len++;
}

void* ptrListGet(PtrList* lst, int idx) {

    if(idx >= 0 && idx < lst->len) {
        return lst->list[idx];
    }

    return NULL;
}

void** ptrListGetRaw(PtrList* lst) {

    if(lst != NULL)
        return lst->list;

    return NULL;
}

int ptrListGetLen(PtrList* lst) {

    if(lst != NULL)
        return lst->len;

    return -1;
}
