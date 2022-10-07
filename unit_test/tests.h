
#ifndef _TESTS_H_
#define _TESTS_H_

#define DEF_TEST(n, c)                                                        \
    void n##_def_test(void* ptr) {                                            \
        TestInstance* ti = (TestInstance*)ptr;                                \
        if(!ti->enabled) {                                                    \
            unit_test_add_msg("MSG", 2, __LINE__, ti->name, "test disabled"); \
            return;                                                           \
        }                                                                     \
        else                                                                  \
            ti->entered++;                                                    \
        ti->desc = _copy_str(c);

#define END_TEST }
#define ADD_TEST(n) unit_add_test(section, #n, n##_def_test)

#define testListInit() (TestList*)ptrListInit()
#define testListDestroy(lst) ptrListDestroy((PtrList*)lst)
#define testListAdd(lst, val) ptrListAdd((PtrList*)lst, (void*)(val))
#define testListGet(lst, idx) (TestInstance*)ptrListGet((PtrList*)lst, (idx))
#define testListGetRaw(lst) (TestInstance**)ptrListGetRaw((PtrList*)lst)
#define testListGetLen(lst) ptrListGetLen((PtrList*)lst)

void unit_add_test(TestSection* section, const char* name, TestFunc func);

#endif
