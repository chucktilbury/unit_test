
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

static inline TestEntry* find_test(TestList* lst, const char* name) {

    TestEntry** list = (TestEntry**)lst->list;
    for(int i = 0; i < lst->len; i++) {
        if(!strcmp(name, list[i]->name))
            return list[i];
    }

    return NULL;
}

static inline void _run_tests(GroupEntry* ge) {

    TestEntry** lst = testListGetRaw(ge->tests);
    int len = testListGetLen(ge->tests);

    for(int i = 0; i < len; i++) {
        TestEntry* ent = lst[i];
        ge->defined++;
        if(ent->enabled) {
            // UNIT_TEST_MSG("test \"%s\" is entered", ent->name);
            ent->entered = true;
            ent->func(ent);
            ge->pass += ent->pass;
            ge->fail += ent->fail;
            ge->error += ent->error;
            ge->ran++;
        }
        else {
            // UNIT_TEST_MSG("test \"%s\" is skipped", ent->name);
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
            UNIT_TEST_TRACE(7, "group \"%s\" is entered", ent->name);
            _run_tests(ent);
            re->pass += ent->pass;
            re->fail += ent->fail;
            re->error += ent->error;
            re->ran++;
        }
        else {
            re->skipped++;
            UNIT_TEST_TRACE(7, "group \"%s\" is skipped", ent->name);
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

void _unit_test_init(int argc, char** argv) {

    (void)argc;
    (void)argv;
}

void _unit_test_run(RootEntry* root) {

    _run_groups(root);
}

int _unit_test_finish(RootEntry* root) {

    return root->error;
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