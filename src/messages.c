
#include <stdarg.h>
#include <stdio.h>

#include "unit_test.cfg"
#include "unit_test.h"

#include "memory.h"

#if USE_TIME
#include <time.h>
#endif

MsgList* msgs = NULL;

void _unit_test_add_msg(int verbosity, const char* name, int line, const char* fmt, ...) {

    // build the string
    int len1, len2, tlen;
#if USE_TIME
    time_t t;
    time(&t);
    char* tbuf = ctime(&t);
    tbuf[strlen(tbuf) - 1] = 0;
    len1 = snprintf(NULL, 0, "[%s] %s: %d: ", tbuf, name, line);
#else
    len1 = snprintf(NULL, 0, "%s: %d: ", name, line);
#endif

    va_list args;

    va_start(args, fmt);
    len2 = vsnprintf(NULL, 0, fmt, args);
    va_end(args);

    tlen = len1 + len2 + 3;
    char* buf = _alloc(tlen);

#if USE_TIME
    snprintf(buf, tlen, "[%s] %s: %d: ", tbuf, name, line);
#else
    snprintf(buf, tlen, "%s: %d: ", name, line);
#endif

    va_start(args, fmt);
    vsnprintf(&buf[len1], len2 + 2, fmt, args);
    va_end(args);

    strcat(buf, "\n");

    // Add the string to the list
    MsgEntry* msg = _alloc_ds(MsgEntry);
    msg->text = _copy_str(buf);
    msg->verbo = verbosity;
    msgListAdd(msgs, msg);

    // print it out according to the current verbosity
    if(verbosity <= VERBOSITY)
        fprintf(OUTSTREAM, "%s", buf);
}

void _unit_test_save_msgs() {

    if(OUTFILE != NULL) {
        FILE* fp = fopen(OUTFILE, "w");

        MsgEntry** rm = msgListGetRaw(msgs);
        int len = msgListGetLen(msgs);

        for(int i = 0; i < len; i++) {
            fprintf(fp, "%s", rm[i]->text);
        }

        fclose(fp);
    }
}
