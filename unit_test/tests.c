
#include "unit_tests.h"

void unit_add_test(TestSection* section, const char* name, TestFunc func) {

    TestInstance* test = _alloc_ds(TestInstance);
    test->name = _copy_str(name);
    test->func = func;
    test->enabled = true;
    // everything else is set to zero

    testListAdd(section->test_list, test);
}
