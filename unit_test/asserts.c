
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "unit_tests.h"

#define evaluate(e, s, ...) _evaluate(ti, line, e, s, ##__VA_ARGS__)
#define CHECK_MOCK(n, line) unit_check_mock(ti, line, n)
#define CHECK_STUB(n, line) unit_check_stub(ti, line, n)

static int unit_check_mock(TestInstance* ti, int line, const char* name) {

    TestMock* mock = unit_find_mock(ti, line, name);
    if(mock != NULL)
        return mock->entered;

    return -1;
}

static int unit_check_stub(TestInstance* ti, int line, const char* name) {

    TestStub* stub = unit_find_stub(ti, line, name);
    if(stub != NULL)
        return stub->entered;

    return -1;
}


static bool _evaluate(TestInstance* ti, int line, bool expr, const char* fmt, ...) {

    va_list args;

    va_start(args, fmt);
    int len = vsnprintf(NULL, 0, fmt, args);
    va_end(args);

    char* msg = _alloc(len + 1);
    va_start(args, fmt);
    vsnprintf(msg, len + 1, fmt, args);
    va_end(args);

    if(expr)
        unit_test_pass(line, ti, "%s", msg);
    else
        unit_test_fail(line, ti, "%s", msg);

    _free(msg);
    return expr;
}

bool _assert_int_zero(TestInstance* ti, int line, int64_t num) {

    return evaluate(num == 0, "assert int is zero (%ld)", num);
}

bool _assert_int_not_zero(TestInstance* ti, int line, int64_t num) {

    return evaluate(num != 0, "assert int is not zero (%ld)", num);
}

bool _assert_int_equal(TestInstance* ti, int line, int64_t left, int64_t right) {

    return evaluate(left == right, "assert int is equal (%ld == %ld)", left, right);
}

bool _assert_int_not_equal(TestInstance* ti, int line, int64_t left, int64_t right) {

    return evaluate(left != right, "assert int is not equal (%ld != %ld)", left, right);
}

bool _assert_int_less(TestInstance* ti, int line, int64_t left, int64_t right) {

    return evaluate(left < right, "assert int is less (%ld < %ld)", left, right);
}

bool _assert_int_greater(TestInstance* ti, int line, int64_t left, int64_t right) {

    return evaluate(left > right, "assert int is greater (%ld > %ld)", left, right);
}

bool _assert_int_less_or_equal(TestInstance* ti, int line, int64_t left, int64_t right) {

    return evaluate(left <= right, "assert int is less or equal (%ld <= %ld)", left, right);
}

bool _assert_int_greater_or_equal(TestInstance* ti, int line, int64_t left, int64_t right) {

    return evaluate(left >= right, "assert int is greater or equal (%ld >= %ld)", left, right);
}

bool _assert_uint_zero(TestInstance* ti, int line, uint64_t num) {

    return evaluate(num == 0, "assert unsigned is zero (%lu)", num);
}

bool _assert_uint_not_zero(TestInstance* ti, int line, uint64_t num) {

    return evaluate(num != 0, "assert unsigned is not zero (%lu)", num);
}

bool _assert_uint_equal(TestInstance* ti, int line, uint64_t left, uint64_t right) {

    return evaluate(left == right, "assert unsigned is equal (%lu == %lu)", left, right);
}

bool _assert_uint_not_equal(TestInstance* ti, int line, uint64_t left, uint64_t right) {

    return evaluate(left != right, "assert unsigned is not equal (%lu != %lu)", left, right);
}

bool _assert_uint_less(TestInstance* ti, int line, uint64_t left, uint64_t right) {

    return evaluate(left < right, "assert unsigned is less (%lu < %lu)", left, right);
}

bool _assert_uint_greater(TestInstance* ti, int line, uint64_t left, uint64_t right) {

    return evaluate(left > right, "assert unsigned is greater (%lu > %lu)", left, right);
}

bool _assert_uint_less_or_equal(TestInstance* ti, int line, uint64_t left, uint64_t right) {

    return evaluate(left <= right,
                    "assert unsigned is less or equal (%lu <= %lu)", left, right);
}

bool _assert_uint_greater_or_equal(TestInstance* ti, int line, uint64_t left, uint64_t right) {

    return evaluate(left >= right, "assert unsigned is greater or equal (%lu >= %lu)",
                    left, right);
}

bool _assert_double_zero(TestInstance* ti, int line, double num) {

    return evaluate(num == 0.0, "assert double is zero (%f)", num);
}

bool _assert_double_not_zero(TestInstance* ti, int line, double num) {

    return evaluate(num != 0.0, "assert double is not zero (%f)", num);
}

bool _assert_double_equal(TestInstance* ti, int line, double left, double right) {

    return evaluate(left == right, "assert double is equal (%f == %f)", left, right);
}

bool _assert_double_not_equal(TestInstance* ti, int line, double left, double right) {

    return evaluate(left != right, "assert double is equal (%f != %f)", left, right);
}

bool _assert_double_less(TestInstance* ti, int line, double left, double right) {

    return evaluate(left < right, "assert double is equal (%f < %f)", left, right);
}

bool _assert_double_greater(TestInstance* ti, int line, double left, double right) {

    return evaluate(left > right, "assert double is equal (%f > %f)", left, right);
}

bool _assert_double_less_or_equal(TestInstance* ti, int line, double left, double right) {

    return evaluate(left <= right, "assert double is equal (%f <= %f)", left, right);
}

bool _assert_double_greater_or_equal(TestInstance* ti, int line, double left, double right) {

    return evaluate(left >= right, "assert double is equal (%f >= %f)", left, right);
}

bool _assert_ptr_null(TestInstance* ti, int line, void* ptr) {

    return evaluate(ptr == NULL, "assert pointer is NULL");
}

bool _assert_ptr_not_null(TestInstance* ti, int line, void* ptr) {

    return evaluate(ptr != NULL, "assert pointer is not NULL");
}

bool _assert_string_equal(TestInstance* ti, int line, const char* s1, const char* s2) {

    return evaluate(strcmp(s1, s2) == 0, "assert strings are equal");
}

bool _assert_string_not_equal(TestInstance* ti, int line, const char* s1, const char* s2) {

    return evaluate(strcmp(s1, s2) != 0, "assert strings are not equal");
}

bool _assert_buffer_equal(TestInstance* ti, int line, void* left, void* right, size_t size) {

    return evaluate(memcmp(left, right, size) == 0, "assert buffers are equal");
}

bool _assert_buffer_not_equal(TestInstance* ti, int line, void* left, void* right, size_t size) {

    return evaluate(memcmp(left, right, size) != 0, "assert buffers are not equal");
}

bool _assert_mock_entered(TestInstance* ti, int line, const char* name) {

    return evaluate(CHECK_MOCK(name, line) != 0,
                    "assert that mock \"%s\" has been entered", name);
}

bool _assert_mock_not_entered(TestInstance* ti, int line, const char* name) {

    return evaluate(CHECK_MOCK(name, line) == 0,
                    "assert that mock \"%s\" has not been entered", name);
}

bool _assert_mock_entered_count(TestInstance* ti, int line, const char* name, int count) {

    return evaluate(CHECK_MOCK(name, line) == count,
                    "assert that mock \"%s\" has been entered %d times", name, count);
}

bool _assert_stub_entered(TestInstance* ti, int line, const char* name) {

    return evaluate(CHECK_STUB(name, line) != 0,
                    "assert that stub \"%s\" has been entered", name);
}

bool _assert_stub_not_entered(TestInstance* ti, int line, const char* name) {

    return evaluate(CHECK_STUB(name, line) == 0,
                    "assert that stub \"%s\" has not been entered", name);
}

bool _assert_stub_entered_count(TestInstance* ti, int line, const char* name, int count) {

    return evaluate(CHECK_STUB(name, line) == count,
                    "assert that stub \"%s\" has been entered %d times", name);
}
