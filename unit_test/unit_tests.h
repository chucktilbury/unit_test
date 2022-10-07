#ifndef _UNITS_H_
#define _UNITS_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "unit_test_config.h"

#include "ptr_lists.h"
typedef PtrList TestList;
typedef PtrList MockList;
typedef PtrList StubList;
typedef PtrList MsgList;
typedef PtrList SectionList;

#define msgListInit() (MsgList*)ptrListInit()
#define msgListDestroy(lst) ptrListDestroy((PtrList*)lst)
#define msgListAdd(lst, val) ptrListAdd((PtrList*)lst, (void*)(val))
#define msgListGet(lst, idx) (char*)ptrListGet((PtrList*)lst, (idx))
#define msgListGetRaw(lst) (char**)ptrListGetRaw((PtrList*)lst)
#define msgListGetLen(lst) ptrListGetLen((PtrList*)lst)

typedef struct {
    const char* name;
    int entered;
} TestMock;

typedef struct {
    const char* name;
    int entered;
} TestStub;

typedef void (*TestFunc)(void* inst);

typedef struct {
    const char* name;
    const char* desc;
    TestFunc func;       // function to execute when this test is run
    MockList* mock_list; // track mocks entered for this function
    StubList* stub_list; // track stubs entered for this function
    int pass;            // number of asserts that pass
    int fail;            // number of asserts that fail
    int error;           // number of errors detected
    int entered;         // this test was run
    bool enabled;        // this test function is enabled
} TestInstance;

typedef struct {
    const char* name;
    const char* desc;
    const char* fname;   // file name of this test section
    TestList* test_list; // list of test functions
    int defined;         // number of test functions defined
    int ran;             // number of test functions that ran
    int skipped;         // number of test functions that were not run
    int pass;            // test functions with zero fails
    int fail;            // test functions with at least one fail
    int error;           // test functions that had an error
    bool enabled;        // this section is enabled
} TestSection;

#define DEF_TEST_MAIN             \
    int main() {                  \
        msg_list = msgListInit(); \
        section_list = sectionListInit();

#define END_TEST_MAIN                 \
    return unit_run_tests();          \
    }

int unit_run_tests();

void unit_test_add_msg(const char* group, // i.e. "TEST", "\tPASS", or "\tMSG"
                       int verbo,         // verbosity level
                       int line,          // line number
                       const char* name,  // name
                       const char* fmt,
                       ...); // the message

void unit_test_print(const char* fmt, ...);

#define unit_test_error(l, t, fmt, ...) \
    do { \
        unit_test_add_msg("ERROR", 1, l, (t)->name, fmt, ##__VA_ARGS__); \
        (t)->error++; \
    } while(0)

#define unit_test_pass(l, t, fmt, ...) \
    do { \
        unit_test_add_msg("\tPASS", 7, l, (t)->name, fmt, ##__VA_ARGS__); \
        (t)->pass++; \
    } while(0)

#define unit_test_fail(l, t, fmt, ...) \
    do { \
        unit_test_add_msg("\tFAIL", 6, l, (t)->name, fmt, ##__VA_ARGS__); \
        (t)->fail++; \
    } while(0)

#define unit_test_msg(n, fmt, ...) \
    do {\
        unit_test_add_msg("MSG", 2, -1, n, fmt, ##__VA_ARGS__); \
    } while(0)

#define unit_test_section(n, fmt, ...) \
    do {\
        unit_test_add_msg("\nSECTION", 6, -1, n, fmt, ##__VA_ARGS__); \
    } while(0)

#include "asserts.h"
#include "memory.h"
#include "mocks.h"
#include "sections.h"
#include "stubs.h"
#include "tests.h"

extern MsgList* msg_list;
extern SectionList* section_list;

#endif
