#ifndef _UNIT_TEST_ASSERTS_H_
#define _UNIT_TEST_ASSERTS_H_

#include "unit_tests.h"

/*
 * Asserts for use inside tests.
 */
#define assert_int_zero(n) _assert_int_zero(ti, __LINE__, n)
#define assert_int_not_zero(n) _assert_int_not_zero(ti, __LINE__, n)
#define assert_int_equal(l, r) _assert_int_equal(ti, __LINE__, l, r)
#define assert_int_not_equal(l, r) _assert_int_not_equal(ti, __LINE__, l, r)
#define assert_int_less(l, r) _assert_int_less(ti, __LINE__, l, r)
#define assert_int_greater(l, r) _assert_int_greater(ti, __LINE__, l, r)
#define assert_int_less_or_equal(l, r) \
    _assert_int_less_or_equal(ti, __LINE__, l, r)
#define assert_int_greater_or_equal(l, r) \
    _assert_int_greater_or_equal(ti, __LINE__, l, r)

#define assert_uint_zero(n) _assert_uint_zero(ti, __LINE__, n)
#define assert_uint_not_zero(n) _assert_uint_not_zero(ti, __LINE__, n)
#define assert_uint_equal(l, r) _assert_uint_equal(ti, __LINE__, l, r)
#define assert_uint_not_equal(l, r) _assert_uint_not_equal(ti, __LINE__, l, r)
#define assert_uint_less(l, r) _assert_uint_less(ti, __LINE__, l, r)
#define assert_uint_greater(l, r) _assert_uint_greater(ti, __LINE__, l, r)
#define assert_uint_less_or_equal(l, r) \
    _assert_uint_less_or_equal(ti, __LINE__, l, r)
#define assert_uint_greater_or_equal(l, r) \
    _assert_uint_greater_or_equal(ti, __LINE__, l, r)

#define assert_double_zero(n) _assert_double_zero(ti, __LINE__, n)
#define assert_double_not_zero(n) _assert_double_not_zero(ti, __LINE__, n)
#define assert_double_equal(l, r) _assert_double_equal(ti, __LINE__, l, r)
#define assert_double_not_equal(l, r) \
    _assert_double_not_equal(ti, __LINE__, l, r)
#define assert_double_less(l, r) _assert_double_less(ti, __LINE__, l, r)
#define assert_double_greater(l, r) _assert_double_greater(ti, __LINE__, l, r)
#define assert_double_less_or_equal(l, r) \
    _assert_double_less_or_equal(ti, __LINE__, l, r)
#define assert_double_greater_or_equal(l, r) \
    _assert_double_greater_or_equal(ti, __LINE__, l, r)

#define assert_ptr_null(p) _assert_ptr_null(ti, __LINE__, p)
#define assert_ptr_not_null(p) _assert_ptr_not_null(ti, __LINE__, p)

#define assert_string_equal(s1, s2) _assert_string_equal(ti, __LINE__, s1, s2)
#define assert_string_not_equal(s1, s2) \
    _assert_string_not_equal(ti, __LINE__, s1, s2)

#define assert_buffer_equal(s1, s2) _assert_buffer_equal(ti, __LINE__, s1, s2)
#define assert_buffer_not_equal(s1, s2) \
    _assert_buffer_not_equal(ti, __LINE__, s1, s2)

#define assert_mock_entered(n) _assert_mock_entered(ti, __LINE__, n)
#define assert_mock_not_entered(n) _assert_mock_not_entered(ti, __LINE__, n)
#define assert_mock_entered_count(n, c) \
    _assert_mock_entered_count(ti, __LINE__, n, c)

#define assert_stub_entered(n) _assert_stub_entered(ti, __LINE__, n)
#define assert_stub_not_entered(n) _assert_stub_not_entered(ti, __LINE__, n)
#define assert_stub_entered_count(n, c) \
    _assert_stub_entered_count(ti, __LINE__, n, c)

/*
 * Private functions should only be called from the macros.
 */
bool _assert_int_zero(TestInstance* ti, int line, int64_t num);
bool _assert_int_not_zero(TestInstance* ti, int line, int64_t num);
bool _assert_int_equal(TestInstance* ti, int line, int64_t left, int64_t right);
bool _assert_int_not_equal(TestInstance* ti, int line, int64_t left, int64_t right);
bool _assert_int_less(TestInstance* ti, int line, int64_t left, int64_t right);
bool _assert_int_greater(TestInstance* ti, int line, int64_t left, int64_t right);
bool _assert_int_less_or_equal(TestInstance* ti, int line, int64_t left, int64_t right);
bool _assert_int_greater_or_equal(TestInstance* ti, int line, int64_t left, int64_t right);
bool _assert_uint_zero(TestInstance* ti, int line, uint64_t num);
bool _assert_uint_not_zero(TestInstance* ti, int line, uint64_t num);
bool _assert_uint_equal(TestInstance* ti, int line, uint64_t left, uint64_t right);
bool _assert_uint_not_equal(TestInstance* ti, int line, uint64_t left, uint64_t right);
bool _assert_uint_less(TestInstance* ti, int line, uint64_t left, uint64_t right);
bool _assert_uint_greater(TestInstance* ti, int line, uint64_t left, uint64_t right);
bool _assert_uint_less_or_equal(TestInstance* ti, int line, uint64_t left, uint64_t right);
bool _assert_uint_greater_or_equal(TestInstance* ti, int line, uint64_t left, uint64_t right);
bool _assert_double_zero(TestInstance* ti, int line, double num);
bool _assert_double_not_zero(TestInstance* ti, int line, double num);
bool _assert_double_equal(TestInstance* ti, int line, double left, double right);
bool _assert_double_not_equal(TestInstance* ti, int line, double left, double right);
bool _assert_double_less(TestInstance* ti, int line, double left, double right);
bool _assert_double_greater(TestInstance* ti, int line, double left, double right);
bool _assert_double_less_or_equal(TestInstance* ti, int line, double left, double right);
bool _assert_double_greater_or_equal(TestInstance* ti, int line, double left, double right);
bool _assert_ptr_null(TestInstance* ti, int line, void* ptr);
bool _assert_ptr_not_null(TestInstance* ti, int line, void* ptr);
bool _assert_string_equal(TestInstance* ti, int line, const char* s1, const char* s2);
bool _assert_string_not_equal(TestInstance* ti, int line, const char* s1, const char* s2);
bool _assert_buffer_equal(TestInstance* ti, int line, void* left, void* right, size_t size);
bool _assert_buffer_not_equal(TestInstance* ti, int line, void* left, void* right, size_t size);
bool _assert_mock_entered(TestInstance* ti, int line, const char* name);
bool _assert_mock_not_entered(TestInstance* ti, int line, const char* name);
bool _assert_mock_entered_count(TestInstance* ti, int line, const char* name, int count);
bool _assert_stub_entered(TestInstance* ti, int line, const char* name);
bool _assert_stub_not_entered(TestInstance* ti, int line, const char* name);
bool _assert_stub_entered_count(TestInstance* ti, int line, const char* name, int count);

#endif