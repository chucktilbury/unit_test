

#include "unit_tests.h"

TestStub* unit_find_stub(TestInstance* ti, int line, const char* name) {

    TestStub** list = stubListGetRaw(ti->stub_list);
    int len = stubListGetLen(ti->stub_list);
    for(int i = 0; i < len; i++) {
        if(strcmp(list[i]->name, name) == 0)
            return list[i];
    }

//     unit_test_add_msg("ERROR", 1, line, ti->name, "stub name \"%s\" does not exist", name);
//     ti->error++;
    unit_test_error(line, ti, "stub name \"%s\" does not exist", name);

    return NULL;
}

void unit_stub_entered(TestInstance* ti, int line, const char* name) {

    TestStub* stub = unit_find_stub(ti, line, name);
    if(stub != NULL)
        stub->entered++;
}

void unit_add_stub(TestInstance* ti, const char* name) {

    TestStub* stub = _alloc_ds(TestStub);
    stub->name = _copy_str(name);
    stub->entered = 0;

    stubListAdd(ti->stub_list, stub);
}
