
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>

#include "memory.h"
#include "unit_test.cfg"
#include "unit_test.h"

#define evaluate(e, s, ...) _evaluate(tst, line, e, s, ##__VA_ARGS__)

static bool _evaluate(TestEntry* tst, int line, bool expr, const char* fmt, ...) {

    va_list args;

    va_start(args, fmt);
    int len = vsnprintf(NULL, 0, fmt, args);
    va_end(args);

    char* msg = _alloc(len + 1);
    va_start(args, fmt);
    vsnprintf(msg, len + 1, fmt, args);
    va_end(args);

    if(expr) {
        _unit_test_add_msg(7, "ASSERT PASS", line, msg);
        tst->pass++;
    }
    else {
        _unit_test_add_msg(6, "ASSERT FAIL", line, msg);
        tst->fail++;
    }

    _free(msg);
    return expr;
}

bool _assert_int_zero(TestEntry* tst, int line, int val) {
    return evaluate((val == 0), "int(%d) == 0", val);
}

bool _assert_int_not_zero(TestEntry* tst, int line, int val) {
    return evaluate((val != 0), "int(%d) != 0", val);
}

bool _assert_int_equal(TestEntry* tst, int line, int val1, int val2) {
    return evaluate((val1 == val2), "int(%d) == int(%d)", val1, val2);
}

bool _assert_int_not_equal(TestEntry* tst, int line, int val1, int val2) {
    return evaluate((val1 != val2), "int(%d) != int(%d)", val1, val2);
}

bool _assert_int_less(TestEntry* tst, int line, int val1, int val2) {
    return evaluate((val1 < val2), "int(%d) < int(%d)", val1, val2);
}

bool _assert_int_greater(TestEntry* tst, int line, int val1, int val2) {
    return evaluate((val1 > val2), "int(%d) > int(%d)", val1, val2);
}

bool _assert_int_less_or_equal(TestEntry* tst, int line, int val1, int val2) {
    return evaluate((val1 <= val2), "int(%d) <= int(%d)", val1, val2);
}

bool _assert_int_greater_or_equal(TestEntry* tst, int line, int val1, int val2) {
    return evaluate((val1 >= val2), "int(%d) >= int(%d)", val1, val2);
}

bool _assert_uint_zero(TestEntry* tst, int line, unsigned val) {
    return evaluate((val == 0), "unsigned(%d) == 0", val);
}

bool _assert_uint_not_zero(TestEntry* tst, int line, unsigned val) {
    return evaluate((val != 0), "unsigned(%d) != 0", val);
}

bool _assert_uint_equal(TestEntry* tst, int line, unsigned val1, unsigned val2) {
    return evaluate((val1 == val2), "unsigned(%d) == unsigned(%d)", val1, val2);
}

bool _assert_uint_not_equal(TestEntry* tst, int line, unsigned val1, unsigned val2) {
    return evaluate((val1 != val2), "unsigned(%d) != unsigned(%d)", val1, val2);
}

bool _assert_uint_less(TestEntry* tst, int line, unsigned val1, unsigned val2) {
    return evaluate((val1 < val2), "unsigned(%d) < unsigned(%d)", val1, val2);
}

bool _assert_uint_greater(TestEntry* tst, int line, unsigned val1, unsigned val2) {
    return evaluate((val1 > val2), "unsigned(%d) > unsigned(%d)", val1, val2);
}

bool _assert_uint_less_or_equal(TestEntry* tst, int line, unsigned val1, unsigned val2) {
    return evaluate((val1 <= val2), "unsigned(%d) <= unsigned(%d)", val1, val2);
}

bool _assert_uint_greater_or_equal(TestEntry* tst, int line, unsigned val1, unsigned val2) {
    return evaluate((val1 >= val2), "unsigned(%d) >= unsigned(%d)", val1, val2);
}

bool _assert_double_zero(TestEntry* tst, int line, double val) {
    return evaluate((val == 0.0), "double(%f) == 0", val);
}

bool _assert_double_not_zero(TestEntry* tst, int line, double val) {
    return evaluate((val != 0.0), "double(%f) != 0", val);
}

bool _assert_double_equal(TestEntry* tst, int line, double val1, double val2) {
    return evaluate((val1 == val2), "double(%f) == double(%f)", val1, val2);
}

bool _assert_double_not_equal(TestEntry* tst, int line, double val1, double val2) {
    return evaluate((val1 != val2), "double(%f) != double(%f)", val1, val2);
}

bool _assert_double_less(TestEntry* tst, int line, double val1, double val2) {
    return evaluate((val1 < val2), "double(%f) < double(%f)", val1, val2);
}

bool _assert_double_greater(TestEntry* tst, int line, double val1, double val2) {
    return evaluate((val1 > val2), "double(%f) > double(%f)", val1, val2);
}

bool _assert_double_less_or_equal(TestEntry* tst, int line, double val1, double val2) {
    return evaluate((val1 <= val2), "double(%f) <= double(%f)", val1, val2);
}

bool _assert_double_greater_or_equal(TestEntry* tst, int line, double val1, double val2) {
    return evaluate((val1 >= val2), "double(%f) >= double(%f)", val1, val2);
}

bool _assert_ptr_null(TestEntry* tst, int line, void* ptr) {
    return evaluate((ptr == NULL), "void*(%p) == NULL", ptr);
}

bool _assert_ptr_not_null(TestEntry* tst, int line, void* ptr) {
    return evaluate((ptr != NULL), "void*(%p) != NULL", ptr);
}

bool _assert_string_equal(TestEntry* tst, int line, const char* ptr1, const char* ptr2) {
    return evaluate((strcmp(ptr1, ptr2) == 0), "string(%s) == string(%s)", ptr1, ptr2);
}

bool _assert_string_not_equal(TestEntry* tst, int line, const char* ptr1, const char* ptr2) {
    return evaluate((strcmp(ptr1, ptr2) == 0), "string(%s) == string(%s)", ptr1, ptr2);
}

bool _assert_buffer_equal(TestEntry* tst, int line, void* ptr1, void* ptr2, size_t size) {
    return evaluate((memcmp(ptr1, ptr2, size) == 0), "ptr(%p) == ptr(%p) size = %lu", ptr1, ptr2, size);
}

bool _assert_buffer_not_equal(TestEntry* tst, int line, void* ptr1, void* ptr2, size_t size) {
    return evaluate((memcmp(ptr1, ptr2, size) != 0), "ptr(%p) != ptr(%p) size = %lu", ptr1, ptr2, size);
}

/*
 * Mock and stub asserts.
 */
bool _assert_mock_entered(TestEntry* tst, int line, const char* name) {

    int mock_entered = _unit_test_mock_entered(tst, name);

    if(mock_entered >= 0)
        return evaluate((mock_entered != 0), "mock \"%s\" is entered", name);
    else {
        UNIT_TEST_ERROR("mock \"%s\" has not been defined", name);
        tst->error++;
    }
    return false;
}

bool _assert_mock_not_entered(TestEntry* tst, int line, const char* name) {

    int mock_entered = _unit_test_mock_entered(tst, name);

    if(mock_entered >= 0)
        return evaluate((mock_entered == 0), "mock \"%s\" is not entered", name);
    else {
        UNIT_TEST_ERROR("mock \"%s\" has not been defined", name);
        tst->error++;
    }
    return false;
}

bool _assert_mock_entered_count(TestEntry* tst, int line, const char* name, int count) {

    int mock_entered = _unit_test_mock_entered(tst, name);

    if(mock_entered >= 0)
        return evaluate((mock_entered == count), "mock \"%s\" is entered %d times", name, count);
    else {
        UNIT_TEST_ERROR("mock \"%s\" has not been defined", name);
        tst->error++;
    }
    return false;
}

bool _assert_stub_entered(TestEntry* tst, int line, const char* name) {

    int stub_entered = _unit_test_stub_entered(tst, name);

    if(stub_entered >= 0)
        return evaluate((stub_entered != 0), "stub \"%s\" is entered", name);
    else {
        UNIT_TEST_ERROR("stub \"%s\" has not been defined", name);
        tst->error++;
    }
    return false;
}

bool _assert_stub_not_entered(TestEntry* tst, int line, const char* name) {

    int stub_entered = _unit_test_stub_entered(tst, name);

    if(stub_entered >= 0)
        return evaluate((stub_entered == 0), "stub \"%s\" is not entered", name);
    else {
        UNIT_TEST_ERROR("stub \"%s\" has not been defined", name);
        tst->error++;
    }
    return false;
}

bool _assert_stub_entered_count(TestEntry* tst, int line, const char* name, int count) {

    int stub_entered = _unit_test_stub_entered(tst, name);

    if(stub_entered >= 0)
        return evaluate((stub_entered == count), "stub \"%s\" is entered %d times", name, count);
    else {
        UNIT_TEST_ERROR("stub \"%s\" has not been defined", name);
        tst->error++;
    }
    return false;
}
