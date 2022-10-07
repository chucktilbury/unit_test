/*
 * This is a generic list that holds an arbitrary size data element. All
 * of the data elements must be the same size, but the type of element is
 * purely arbitrary.
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "memory.h"

List* createList(size_t size) {

    List* lst = _alloc_ds(List);
    if(lst == NULL)
        return NULL;

    // number of items, not the size of the buffer.
    lst->len = 0;
    lst->cap = 1 << 3;

    // len * size = buffer length
    lst->size = size;
    lst->buffer = _alloc_ds_array_size(uint8_t, lst->size, lst->cap);
    if(lst->buffer == NULL) {
        free(lst);
        return NULL;
    }

    return lst;
}

ListErr destroyList(List* lst) {

    if(lst == NULL || lst->buffer == NULL)
        return LIST_PARAM;

    free(lst->buffer);
    free(lst);

    return LIST_OK;
}

ListErr addList(List* lst, const char* data) {

    if(lst->len + 1 > lst->cap) {
        // double the capacity
        lst->cap <<= 1;

        // allocate new size and clear the unused memory
        uint8_t* tmp = _alloc_ds_array_size(uint8_t, lst->size, lst->cap);
        if(tmp == NULL)
            return LIST_MEM;

        // new list buffer
        memcpy(tmp, lst->buffer, lst->len * lst->size);

        // fix up the new buffer
        free(lst->buffer);
        lst->buffer = tmp;
    }

    // save the data
    memcpy(&lst->buffer[lst->len * lst->size], data, lst->size);
    lst->len++;

    return LIST_OK;
}

ListErr getList(List* lst, int index, void* data) {

    if(lst->len == 0)
        return LIST_EMPTY;

    if(index < 0 || index >= lst->len)
        return LIST_INDEX;

    memcpy(data, &lst->buffer[lst->len * lst->size], lst->size);
    return LIST_OK;
}

ListErr pushList(List* lst, void* data) {

    return addList(lst, data);
}

ListErr popList(List* lst, void* data) {

    if(lst->len <= 0)
        return LIST_STACK; // under run

    lst->len--;
    memcpy(data, &lst->buffer[lst->len * lst->size], lst->size);

    return LIST_OK;
}

ListErr peekList(List* lst, void* data) {

    if(lst->len <= 0)
        return LIST_STACK; // under run

    memcpy(data, &lst->buffer[(lst->len - 1) * lst->size], lst->size);

    return LIST_OK;
}

uint8_t* rawList(List* lst) {

    return lst->buffer;
}

int lenList(List* lst) {

    return lst->len;
}
