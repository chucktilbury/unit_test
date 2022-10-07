#if 1
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "unit_tests.h"
#endif

MsgList* msg_list;
SectionList* section_list;

static void unit_test_print_result();

int unit_run_tests() {

    int error = 0;

    int num_sections = sectionListGetLen(section_list);
    for(int s = 0; s < num_sections; s++) {
        TestSection* sec = sectionListGet(section_list, s);
        if(sec->enabled) {
            unit_test_section(sec->name, "testing section");
            int num_tests = testListGetLen(sec->test_list);
            for(int t = 0; t < num_tests; t++) {
                TestInstance* tst = testListGet(sec->test_list, t);
                if(tst->enabled) {
                    tst->func(tst);
                    sec->ran++;
                    if(tst->error > 0) {
                        sec->error++;
                        error++;
                    }
                    else if(tst->fail > 0)
                        sec->fail++;
                    else
                        sec->pass++;
                }
                else {
                    // test disabled
                    sec->skipped++;
                }
            }
        }
        else {
            // section disabled
            unit_test_section(sec->name, "section disabled");
        }
    }

    unit_test_print_result();

    msgListDestroy(msg_list);
    sectionListDestroy(section_list);

    return error;
}

static void unit_test_print_result() {

    unit_test_print("\nRESULT:\n");
}

void unit_test_print(const char* fmt, ...) {

    va_list args;
    int len;

    va_start(args, fmt);
    len = vsnprintf(NULL, 0, fmt, args);
    va_end(args);

    char* str = _alloc(len + 2);

    va_start(args, fmt);
    vsnprintf(str, len + 1, fmt, args);
    va_end(args);

    strcat(str, "\n");

    if(1 <= VERBOSITY)
        fprintf(OUTSTREAM, "%s", str);

    msgListAdd(msg_list, str);
}

void unit_test_add_msg(const char* group, int verbo, int line, const char* name, const char* fmt, ...) {

    va_list args;
    const char* format = "%s: %s:\t%d:\t";
    int len1, len2;

    if(line >= 0) {
        format = "%s: %s:\t%d:\t";
        len1 = snprintf(NULL, 0, format, group, name, line);
        va_start(args, fmt);
        len2 = vsnprintf(NULL, 0, fmt, args);
        va_end(args);
    }
    else {
        format = "%s: %s:\t";
        len1 = snprintf(NULL, 0, format, group, name);
        va_start(args, fmt);
        len2 = vsnprintf(NULL, 0, fmt, args);
        va_end(args);
    }

    char* str = _alloc(len1 + len2 + 2);
    snprintf(str, len1 + 1, format, group, name, line);

    va_start(args, fmt);
    vsnprintf(&str[len1], len2 + 2, fmt, args);
    va_end(args);

    strcat(str, "\n");

    if(verbo <= VERBOSITY)
        fprintf(OUTSTREAM, "%s", str);

    msgListAdd(msg_list, str);
}
