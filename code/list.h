#ifndef _LIST_H_
#define _LIST_H_

typedef enum {
    LIST_OK,
    LIST_EMPTY,
    LIST_STACK,
    LIST_PARAM,
    LIST_MEM,
    LIST_INDEX,
} ListErr;

typedef struct {
    uint8_t* buffer;
    int cap;
    int len;
    size_t size;
} List;

List* createList(size_t size);
ListErr destroyList(List* lst);
ListErr addList(List* lst, const char* data);
ListErr getList(List* lst, int index, void* data);
ListErr pushList(List* lst, void* data);
ListErr popList(List* lst, void* data);
ListErr peekList(List* lst, void* data);
uint8_t* rawList(List* lst);
int lenList(List* lst);

#endif
