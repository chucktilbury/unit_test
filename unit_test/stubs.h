
#ifndef _STUBS_H_
#define _STUBS_H_

#define DEF_STUB(r, n, ...) \
    r n(__VA_ARGS__) {      \
        unit_stub_entered(test, #n);
#define END_STUB }
#define ADD_STUB(n) stubListAdd(test->stub_list, #n)

#define stubListInit() (StubList*)ptrListInit()
#define stubListDestroy(lst) ptrListDestroy((PtrList*)lst)
#define stubListAdd(lst, val) ptrListAdd((PtrList*)lst, (void*)(val))
#define stubListGet(lst, idx) (TestStub*)ptrListGet((PtrList*)lst, (idx))
#define stubListGetRaw(lst) (TestStub**)ptrListGetRaw((PtrList*)lst)
#define stubListGetLen(lst) ptrListGetLen((PtrList*)lst)

#include "tests.h"

void unit_stub_entered(TestInstance* ti, int line, const char* name);
void unit_add_stub(TestInstance* ti, const char* name);
TestStub* unit_find_stub(TestInstance* ti, int line, const char* name);

#endif
