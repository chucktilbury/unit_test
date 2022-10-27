/*
 * This is the header for all unit tests to link to the unit test library.
 */
#ifndef _UNIT_TEST_H_
#define _UNIT_TEST_H_

#include <stdbool.h>
#include <stddef.h>

#include "ptr_list.h"
#include "unit_test.cfg"

/*
 * Message list.
 */
typedef struct {
    const char* text;
    int verbo;
} MsgEntry;

typedef PtrList MsgList;
#define msgListCreate() (MsgList*)ptrListCreate(sizeof(MsgEntry))
#define msgListDestroy(l) ptrListDestroy((PtrList*)(l))
#define msgListAdd(p, d) ptrListAdd((PtrList*)(p), (MsgEntry*)(d))
#define msgListGet(p, i) (MsgEntry*)ptrListAdd((PtrList*)(p), (i))
#define msgListGetRaw(p) (MsgEntry**)ptrListGetRaw((PtrList*)(p))
#define msgListGetLen(p) ptrListGetLen((PtrList*)(p))
extern MsgList* msgs;

/*
 * Mock list.
 */
typedef struct {
    const char* name;
    int entered;
} MockEntry;

typedef PtrList MockList;
#define mockListCreate() (MockList*)ptrListCreate(sizeof(MockEntry))
#define mockListDestroy(l) ptrListDestroy((PtrList*)(l))
#define mockListAdd(p, d) ptrListAdd((PtrList*)(p), (MockEntry*)(d))
#define mockListGet(p, i) (MockEntry*)ptrListAdd((PtrList*)(p), (i))
#define mockListGetRaw(p) (MockEntry**)ptrListGetRaw((PtrList*)(p))
#define mockListGetLen(p) ptrListGetLen((PtrList*)(p))

/*
 * Stub list.
 */
typedef struct {
    const char* name;
    int entered;
} StubEntry;

typedef PtrList StubList;
#define stubListCreate() (StubList*)ptrListCreate(sizeof(StubEntry))
#define stubListDestroy(l) ptrListDestroy((PtrList*)(l))
#define stubListAdd(p, d) ptrListAdd((PtrList*)(p), (StubEntry*)(d))
#define stubListGet(p, i) (StubEntry*)ptrListAdd((PtrList*)(p), (i))
#define stubListGetRaw(p) (StubEntry**)ptrListGetRaw((PtrList*)(p))
#define stubListGetLen(p) ptrListGetLen((PtrList*)(p))

/*
 * Test data structure.
 */
typedef int (*TestFunc)(void* tst);

typedef struct {
    const char* name;
    const char* desc;

    // function to execute
    TestFunc func;

    int pass;     // asserts that have passed
    int fail;     // asserts that have failed
    int error;    // errors that have happened
    bool entered; // this test has been run
    bool enabled; // this test is enabled

    // list of mocks and stubs that this test is tracking
    MockList* mocks;
    StubList* stubs;
} TestEntry;

/*
 * Test list.
 */
typedef PtrList TestList;
#define testListCreate() (TestList*)ptrListCreate(sizeof(TestEntry))
#define testListDestroy(l) ptrListDestroy((PtrList*)(l))
#define testListAdd(p, d) ptrListAdd((PtrList*)(p), (TestEntry*)(d))
#define testListGet(p, i) (TestEntry*)ptrListAdd((PtrList*)(p), (i))
#define testListGetRaw(p) (TestEntry**)ptrListGetRaw((PtrList*)(p))
#define testListGetLen(p) ptrListGetLen((PtrList*)(p))

/*
 * Test group.
 */
typedef struct {
    const char* name;  // name of this test group
    const char* desc;  // description of the group
    const char* fname; // file name of this test group

    TestList* tests; // list of tests in this group

    int pass;     // tests that have passed
    int fail;     // tests that have failed
    int error;    // errors that have happened
    int ran;      // number of tests that ran
    int skipped;  // number of tests that were skipped
    int defined;  // number of tests that were defined
    bool enabled; // this group is enabled
} GroupEntry;

typedef PtrList GroupList;
#define groupListCreate() (GroupList*)ptrListCreate(sizeof(GroupEntry))
#define groupListDestroy(l) ptrListDestroy((PtrList*)(l))
#define groupListAdd(p, d) ptrListAdd((PtrList*)(p), (GroupEntry*)(d))
#define groupListGet(p, i) (GroupEntry*)ptrListAdd((PtrList*)(p), (i))
#define groupListGetRaw(p) (GroupEntry**)ptrListGetRaw((PtrList*)(p))
#define groupListGetLen(p) ptrListGetLen((PtrList*)(p))

/*
 * This is a list of groups with results tracking.
 */
typedef struct {
    const char* name;
    const char* desc;

    GroupList* groups;

    int pass;    // total passing groups
    int fail;    // total failing groups
    int error;   // total group errors
    int ran;     // total groups that ran
    int skipped; // total groups that were skipped
    int defined; // total groups that were defined.
} RootEntry;

#define UNIT_TEST_ERROR(fmt, ...) _unit_test_add_msg(1, "ERROR", __LINE__, (fmt), ##__VA_ARGS__)
#define UNIT_TEST_MSG(fmt, ...) _unit_test_add_msg(2, "MSG", __LINE__, (fmt), ##__VA_ARGS__)
#define UNIT_TEST_TRACE(fmt, ...) _unit_test_trace((fmt), ##__VA_ARGS__)

#define UNIT_TEST_TEST_PASS(fmt, ...) _unit_test_add_msg(5, "TEST PASS", __LINE__, (fmt), ##__VA_ARGS__)
#define UNIT_TEST_TEST_FAIL(fmt, ...) _unit_test_add_msg(5, "TEST FAIL", __LINE__, (fmt), ##__VA_ARGS__)

#define UNIT_TEST_GROUP_PASS(fmt, ...) _unit_test_add_msg(4, "GROUP PASS", __LINE__, (fmt), ##__VA_ARGS__)
#define UNIT_TEST_GROUP_FAIL(fmt, ...) _unit_test_add_msg(4, "GROUP FAIL", __LINE__, (fmt), ##__VA_ARGS__)


#define DEF_MOCK(r, n, ...) \
    r n(__VA_ARGS__) {      \
        _unit_test_mock_entered(tst, #n);
#define END_MOCK }
#define ADD_MOCK(n) _unit_test_add_mock(tst->mocks, #n)

#define DEF_STUB(r, n, ...) \
    r n(__VA_ARGS__) {      \
        _unit_test_stub_entered(tst, #n);
#define END_STUB }
#define ADD_STUB(n) _unit_test_add_stub(tst->stubs, #n)

/*
 * This defines code that implements the test.
 */
#define DEF_TEST(n, d)                                                  \
    TEST_SCOPE int n##_define_test(void* ptr) {                         \
        TestEntry* tst = (TestEntry*)ptr;                               \
        tst->desc = _copy_str(d);                                       \
        if(!tst->enabled) {                                             \
            UNIT_TEST_MSG("test %s is disabled", #n);                   \
            return -1;                                                  \
        }                                                               \
        else                                                            \
            tst->entered++;                                             \
        _unit_test_add_msg(6, "TEST START", __LINE__, "%s", tst->name); \
        {
// Add testing code and asserts between DEF and END
#define END_TEST                                                       \
    }                                                                  \
    _unit_test_add_msg(6, "TEST FINISH", __LINE__, "%s\n", tst->name); \
    return tst->error;                                                 \
    }
#define ADD_TEST(n)                                                     \
    do {                                                                \
        _unit_test_add_msg(6, "  ADD TEST ENTRY ", __LINE__, "%s", #n); \
        _unit_test_add_test(group, #n, n##_define_test);                \
    } while(0)

/*
 * This code is called from main() to define the test group.
 */
#define DEF_GROUP(n, d)                                                \
    GroupEntry* n##_define_group() {                                   \
        _unit_test_add_msg(6, "ADD GROUP START ", __LINE__, "%s", #n); \
        GroupEntry* group = _unit_test_add_group(#n, d, __FILE__);     \
        {
// ADD_TEST(name) between DEF and END
#define END_GROUP                                                              \
    _unit_test_add_msg(6, "ADD GROUP FINISH ", __LINE__, "%s\n", group->name); \
    }                                                                          \
    return group;                                                              \
    }
#define ADD_GROUP(n) groupListAdd(root->groups, n##_define_group())

/*
 * This defines the main function for all tests. The test groups are added
 * here.
 */
#define DEF_TEST_MAIN(n, d)                                  \
    int main(int argc, char** argv) {                        \
        RootEntry* root = _unit_test_init(argc, argv, n, d); \
        {
// ADD_GROUP(name) between DEF and END.
#define END_TEST_MAIN        \
    }                        \
    _unit_test_run(root);    \
    _unit_test_finish(root); \
    _unit_test_save_msgs();  \
    return root->error;      \
    }

#define ASSERT_INT_ZERO(v) _assert_int_zero(tst, __LINE__, v)
#define ASSERT_INT_NOT_ZERO(v) _assert_int_not_zero(tst, __LINE__, v)
#define ASSERT_INT_EQUAL(v1, v2) _assert_int_equal(tst, __LINE__, v1, v2)
#define ASSERT_INT_NOT_EQUAL(v1, v2) _assert_int_not_equal(tst, __LINE__, v1, v2)
#define ASSERT_INT_LESS(v1, v2) _assert_int_less(tst, __LINE__, v1, v2)
#define ASSERT_INT_GREATER(v1, v2) _assert_int_greater(tst, __LINE__, v1, v2)
#define ASSERT_INT_LESS_OR_EQUAL(v1, v2) _assert_int_less_or_equal(tst, __LINE__, v1, v2)
#define ASSERT_INT_GREATER_OR_EQUAL(v1, v2) _assert_int_greater_or_equal(tst, __LINE__, v1, v2)

#define ASSERT_UINT_ZERO(v) _assert_uint_zero(tst, __LINE__, v)
#define ASSERT_UINT_NOT_ZERO(v) _assert_uint_not_zero(tst, __LINE__, v)
#define ASSERT_UINT_EQUAL(v1, v2) _assert_uint_equal(tst, __LINE__, v1, v2)
#define ASSERT_UINT_NOT_EQUAL(v1, v2) _assert_uint_not_equal(tst, __LINE__, v1, v2)
#define ASSERT_UINT_LESS(v1, v2) _assert_uint_less(tst, __LINE__, v1, v2)
#define ASSERT_UINT_GREATER(v1, v2) _assert_uint_greater(tst, __LINE__, v1, v2)
#define ASSERT_UINT_LESS_OR_EQUAL(v1, v2) _assert_uint_less_or_equal(tst, __LINE__, v1, v2)
#define ASSERT_UINT_GREATER_OR_EQUAL(v1, v2) _assert_uint_greater_or_equal(tst, __LINE__, v1, v2)

#define ASSERT_DOUBLE_ZERO(v) _assert_double_zero(tst, __LINE__, v)
#define ASSERT_DOUBLE_NOT_ZERO(v) _assert_double_not_zero(tst, __LINE__, v)
#define ASSERT_DOUBLE_EQUAL(v1, v2) _assert_double_equal(tst, __LINE__, v1, v2)
#define ASSERT_DOUBLE_NOT_EQUAL(v1, v2) _assert_double_not_equal(tst, __LINE__, v1, v2)
#define ASSERT_DOUBLE_LESS(v1, v2) _assert_double_less(tst, __LINE__, v1, v2)
#define ASSERT_DOUBLE_GREATER(v1, v2) _assert_double_greater(tst, __LINE__, v1, v2)
#define ASSERT_DOUBLE_LESS_OR_EQUAL(v1, v2) _assert_double_less_or_equal(tst, __LINE__, v1, v2)
#define ASSERT_DOUBLE_GREATER_OR_EQUAL(v1, v2) _assert_double_greater_or_equal(tst, __LINE__, v1, v2)

#define ASSERT_PTR_NULL(p) _assert_ptr_null(tst, __LINE__, p)
#define ASSERT_PTR_NOT_NULL(p) _assert_ptr_not_null(tst, __LINE__, p)

#define ASSERT_STRING_EQUAL(p1, p2) _assert_string_equal(tst, __LINE__, p1, p2)
#define ASSERT_STRING_NOT_EQUAL(p1, p2) _assert_string_not_equal(tst, __LINE__, p1, p2)

#define ASSERT_BUFFER_EQUAL(p1, p2, s) _assert_buffer_equal(tst, __LINE__, p1, p2, s)
#define ASSERT_BUFFER_NOT_EQUAL(p1, p2, s) _assert_buffer_not_equal(tst, __LINE__, p1, p2, s)

#define ASSERT_MOCK_ENTERED(n) _assert_mock_entered(tst, __LINE__, n)
#define ASSERT_MOCK_NOT_ENTERED(n) _assert_mock_not_entered(tst, __LINE__, n)
#define ASSERT_MOCK_ENTERED_COUNT(n, c) _assert_mock_entered_count(tst, __LINE__, n, c)

#define ASSERT_STUB_ENTERED(n) _assert_stub_entered(tst, __LINE__, n)
#define ASSERT_STUB_NOT_ENTERED(n) _assert_stub_not_entered(tst, __LINE__, n)
#define ASSERT_STUB_ENTERED_COUNT(n, c) _assert_stub_entered_count(tst, __LINE__, n, c)

/*
 * Asserts to be used in the actual tests. These are called using the macros
 * that are defined above.
 */
bool _assert_int_zero(TestEntry*, int, int);
bool _assert_int_not_zero(TestEntry*, int, int);
bool _assert_int_equal(TestEntry*, int, int, int);
bool _assert_int_not_equal(TestEntry*, int, int, int);
bool _assert_int_less(TestEntry*, int, int, int);
bool _assert_int_greater(TestEntry*, int, int, int);
bool _assert_int_less_or_equal(TestEntry*, int, int, int);
bool _assert_int_greater_or_equal(TestEntry*, int, int, int);

bool _assert_uint_zero(TestEntry*, int, unsigned);
bool _assert_uint_not_zero(TestEntry*, int, unsigned);
bool _assert_uint_equal(TestEntry*, int, unsigned, unsigned);
bool _assert_uint_not_equal(TestEntry*, int, unsigned, unsigned);
bool _assert_uint_less(TestEntry*, int, unsigned, unsigned);
bool _assert_uint_greater(TestEntry*, int, unsigned, unsigned);
bool _assert_uint_less_or_equal(TestEntry*, int, unsigned, unsigned);
bool _assert_uint_greater_or_equal(TestEntry*, int, unsigned, unsigned);

bool _assert_double_zero(TestEntry*, int, double);
bool _assert_double_not_zero(TestEntry*, int, double);
bool _assert_double_equal(TestEntry*, int, double, double);
bool _assert_double_not_equal(TestEntry*, int, double, double);
bool _assert_double_less(TestEntry*, int, double, double);
bool _assert_double_greater(TestEntry*, int, double, double);
bool _assert_double_less_or_equal(TestEntry*, int, double, double);
bool _assert_double_greater_or_equal(TestEntry*, int, double, double);

bool _assert_ptr_null(TestEntry*, int, void*);
bool _assert_ptr_not_null(TestEntry*, int, void*);

bool _assert_string_equal(TestEntry*, int, const char*, const char*);
bool _assert_string_not_equal(TestEntry*, int, const char*, const char*);

bool _assert_buffer_equal(TestEntry*, int, void*, void*, size_t);
bool _assert_buffer_not_equal(TestEntry*, int, void*, void*, size_t);

bool _assert_mock_entered(TestEntry*, int, const char*);
bool _assert_mock_not_entered(TestEntry*, int, const char*);
bool _assert_mock_entered_count(TestEntry*, int, const char*, int);

bool _assert_stub_entered(TestEntry*, int, const char*);
bool _assert_stub_not_entered(TestEntry*, int, const char*);
bool _assert_stub_entered_count(TestEntry*, int, const char*, int);

/*
 * These functions are the backing for the public interface. The actual public
 * interface is implemented with the macros defined above.
 */
int _unit_test_mock_entered(TestEntry* tst, const char* name);
void _unit_test_add_mock(TestEntry* tst, const char* name);
int _unit_test_stub_entered(TestEntry* tst, const char* name);
void _unit_test_add_stub(TestEntry* tst, const char* name);

void _unit_test_add_test(GroupEntry* group, const char* name, TestFunc func);
GroupEntry* _unit_test_add_group(const char* name, const char* desc, const char* fname);

RootEntry* _unit_test_init(int argc, char** argv, const char* name, const char* desc);
void _unit_test_run(RootEntry* root);
int _unit_test_finish(RootEntry* root);
void _unit_test_save_msgs();

void _unit_test_add_msg(int verbosity, const char* name, int line, const char* fmt, ...);
const char* _unit_test_make_string(int verbo, const char* fmt, ...);
void _unit_test_trace(const char*, ...);

#endif

/*
 * Todo:
 * 1. Capture all signals and emulate them. Provide asserts.
 * 2. Track all memory transactions and provide asserts.
 * 3. Override the return and exit calls. (using setjmp)
 * 4. Add debugging spew
 * 5. Add command line parser.
 */