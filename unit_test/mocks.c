
#include "unit_tests.h"

TestMock* unit_find_mock(TestInstance* ti, int line, const char* name) {

    TestMock** list = mockListGetRaw(ti->mock_list);
    int len = mockListGetLen(ti->mock_list);
    for(int i = 0; i < len; i++) {
        if(strcmp(list[i]->name, name) == 0)
            return list[i];
    }

//     unit_test_add_msg("ERROR", 1, line, ti->name, "mock name \"%s\" does not exist", name);
//     ti->error++;
    unit_test_error(line, ti, "mock name \"%s\" does not exist", name);

    return NULL;
}

void unit_mock_entered(TestInstance* ti, int line, const char* name) {

    TestMock* mock = unit_find_mock(ti, line, name);
    if(mock != NULL)
        mock->entered++;
}

void unit_add_mock(TestInstance* ti, const char* name) {

    TestMock* mock = _alloc_ds(TestMock);
    mock->name = _copy_str(name);
    mock->entered = 0;

    mockListAdd(ti->mock_list, mock);
}
