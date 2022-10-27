
#include <time.h>

#include "memory.h"
#include "unit_test.cfg"
#include "unit_test.h"

static inline MockEntry* find_mock(MockList* lst, const char* name) {

    MockEntry** list = (MockEntry**)lst->list;
    for(int i = 0; i < lst->len; i++) {
        if(!strcmp(name, list[i]->name))
            return list[i];
    }

    return NULL;
}

static inline StubEntry* find_stub(StubList* lst, const char* name) {

    StubEntry** list = (StubEntry**)lst->list;
    for(int i = 0; i < lst->len; i++) {
        if(!strcmp(name, list[i]->name))
            return list[i];
    }

    return NULL;
}

#if 0
static inline TestEntry* find_test(TestList* lst, const char* name) {

    TestEntry** list = (TestEntry**)lst->list;
    for(int i = 0; i < lst->len; i++) {
        if(!strcmp(name, list[i]->name))
            return list[i];
    }

    return NULL;
}
#endif

static inline void _run_tests(GroupEntry* ge) {

    TestEntry** lst = testListGetRaw(ge->tests);
    int len = testListGetLen(ge->tests);

    for(int i = 0; i < len; i++) {
        TestEntry* ent = lst[i];
        ge->defined++;
        if(ent->enabled) {
            UNIT_TEST_TRACE("test \"%s\" is entered", ent->name);
            ent->entered = true;
            ent->func(ent);
            ge->pass += ent->pass;
            ge->fail += ent->fail;
            ge->error += ent->error;
            ge->ran++;
        }
        else {
            UNIT_TEST_TRACE("test \"%s\" is skipped", ent->name);
            ge->skipped++;
        }
    }
}

static inline void _run_groups(RootEntry* re) {

    GroupEntry** lst = groupListGetRaw(re->groups);
    int len = groupListGetLen(re->groups);

    for(int i = 0; i < len; i++) {
        GroupEntry* ent = lst[i];
        re->defined++;
        if(ent->enabled) {
            UNIT_TEST_TRACE("group \"%s\" is entered", ent->name);
            _run_tests(ent);
            if(ent->error)
                re->error++;
            else if(ent->fail)
                re->fail++;
            else
                re->pass++;
            re->ran++;
        }
        else {
            re->skipped++;
            UNIT_TEST_TRACE("group \"%s\" is skipped", ent->name);
        }
    }
}

int _unit_test_mock_entered(TestEntry* tst, const char* name) {

    MockEntry* ent = find_mock(tst->mocks, name);
    if(ent != NULL)
        return ent->entered;
    else
        return -1;
}

void _unit_test_add_mock(TestEntry* tst, const char* name) {

    MockList* lst = tst->mocks;
    MockEntry* ent = find_mock(lst, name);
    if(ent == NULL) {
        ent = _alloc_ds(MockEntry);
        ent->name = _copy_str(name);
        ent->entered = 0;
        mockListAdd(lst, ent);
    }
    else {
        ent->entered = 0;
    }
}

int _unit_test_stub_entered(TestEntry* tst, const char* name) {

    StubEntry* ent = find_stub(tst->stubs, name);
    if(ent != NULL)
        return ent->entered;
    else
        return -1;
}

void _unit_test_add_stub(TestEntry* tst, const char* name) {

    StubList* lst = tst->stubs;
    StubEntry* ent = find_stub(lst, name);
    if(ent == NULL) {
        ent = _alloc_ds(StubEntry);
        ent->name = _copy_str(name);
        ent->entered = 0;
        stubListAdd(lst, ent);
    }
    else {
        ent->entered = 0;
    }
}

RootEntry* _unit_test_init(int argc, char** argv, const char* name, const char* desc) {

    (void)argc;
    (void)argv;

    msgs = msgListCreate();

    RootEntry* root = _alloc_ds(RootEntry);
    root->name = _copy_str(name);
    root->desc = _copy_str(desc);
    root->pass = 0;
    root->fail = 0;
    root->error = 0;
    root->ran = 0;
    root->skipped = 0;
    root->defined = 0;
    root->groups = groupListCreate();

    _unit_test_make_string(1, "\nRunning test suite: \"%s\"", name);
    time_t t = time(NULL);
    _unit_test_make_string(1, ctime(&t));
    _unit_test_make_string(1, "-- %s\n", desc);

    return root;
}

void _unit_test_run(RootEntry* root) {

    _unit_test_make_string(6, "Running tests: \"%s\"", root->name);
    _run_groups(root);
}

int _unit_test_finish(RootEntry* root) {

    _unit_test_make_string(1, "\nTest Summary: \"%s\"", root->name);
    time_t t = time(NULL);
    _unit_test_make_string(1, ctime(&t));
    _unit_test_make_string(1, "  Groups:");
    _unit_test_make_string(1, "%6d ran", root->ran);
    _unit_test_make_string(1, "%6d skipped", root->skipped);
    _unit_test_make_string(1, "%6d passed", root->pass);
    _unit_test_make_string(1, "%6d failed", root->fail);
    _unit_test_make_string(1, "%6d errors\n", root->error);

    int tran = 0;
    int tskipped = 0;
    int tpassed = 0;
    int tfailed = 0;
    int terrors = 0;

    int apassed = 0;
    int afailed = 0;
    int aerrors = 0;

    GroupEntry** glst = groupListGetRaw(root->groups);
    int glen = groupListGetLen(root->groups);
    for(int i = 0; i < glen; i++) {
        TestEntry** tlst = testListGetRaw(glst[i]->tests);
        int tlen = testListGetLen(glst[i]->tests);
        for(int j = 0; j < tlen; j++) {
            if(!tlst[j]->enabled)
                tskipped++;
            else
                tran++;

            if(tlst[j]->error != 0)
                terrors++;
            else if(tlst[j]->fail != 0)
                tfailed++;
            else
                tpassed++;

            apassed += tlst[j]->pass;
            afailed += tlst[j]->fail;
            aerrors += tlst[j]->error;
        }
    }

    // print the test summary
    _unit_test_make_string(2, "  Tests:");
    _unit_test_make_string(2, "%6d ran", tran);
    _unit_test_make_string(2, "%6d skipped", tskipped);
    _unit_test_make_string(2, "%6d passed", tpassed);
    _unit_test_make_string(2, "%6d failed", tfailed);
    _unit_test_make_string(2, "%6d errors\n", terrors);

    // print the assert summary
    _unit_test_make_string(3, "  Asserts:");
    _unit_test_make_string(3, "%6d total", apassed + afailed + aerrors);
    _unit_test_make_string(3, "%6d passed", apassed);
    _unit_test_make_string(3, "%6d failed", afailed);
    _unit_test_make_string(3, "%6d errors\n", aerrors);

    return terrors;
}

void _unit_test_add_test(GroupEntry* group, const char* name, TestFunc func) {

    TestEntry* tst = _alloc_ds(TestEntry);
    tst->name = _copy_str(name);
    tst->func = func;
    tst->pass = 0;
    tst->fail = 0;
    tst->error = 0;
    tst->enabled = true;
    tst->entered = false;
    tst->mocks = mockListCreate();
    tst->stubs = stubListCreate();
    testListAdd(group->tests, tst);
}

GroupEntry* _unit_test_add_group(const char* name, const char* desc, const char* fname) {

    GroupEntry* group = _alloc_ds(GroupEntry);
    group->name = _copy_str(name);
    group->desc = _copy_str(desc);
    group->fname = _copy_str(fname);
    group->pass = 0;
    group->fail = 0;
    group->error = 0;
    group->ran = 0;
    group->skipped = 0;
    group->defined = 0;
    group->enabled = true;
    group->tests = testListCreate();

    return group;
}