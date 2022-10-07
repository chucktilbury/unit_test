
#ifndef _MOCKS_H_
#define _MOCKS_H_

#define DEF_MOCK(r, n, ...) \
    r n(__VA_ARGS__) {      \
        unit_mock_entered(test, #n);
#define END_MOCK }
#define ADD_MOCK(n) mockListAdd(test->mock_list, #n)

#define mockListInit() (MockList*)ptrListInit()
#define mockListDestroy(lst) ptrListDestroy((PtrList*)lst)
#define mockListAdd(lst, val) ptrListAdd((PtrList*)lst, (void*)(val))
#define mockListGet(lst, idx) (TestMock*)ptrListGet((PtrList*)lst, (idx))
#define mockListGetRaw(lst) (TestMock**)ptrListGetRaw((PtrList*)lst)
#define mockListGetLen(lst) ptrListGetLen((PtrList*)lst)

#include "tests.h"

void unit_mock_entered(TestInstance* ti, int line, const char* name);
void unit_add_mock(TestInstance* ti, const char* name);
TestMock* unit_find_mock(TestInstance* ti, int line, const char* name);

#endif
