
#ifndef _SECTIONS_H_
#define _SECTIONS_H_

#define DEF_SECTION(n, c)                              \
    void n##_def_section() {                           \
        TestSection* section = _alloc_ds(TestSection); \
        section->name = _copy_str(#n);                 \
        section->desc = _copy_str(c);                  \
        section->fname = _copy_str(__FILE__);          \
        section->enabled = true;                       \
        section->test_list = testListInit();

#define END_SECTION                        \
    sectionListAdd(section_list, section); \
    }
#define ADD_SECTION(n) n##_def_section()

#define sectionListInit() (SectionList*)ptrListInit()
#define sectionListDestroy(lst) ptrListDestroy((PtrList*)lst)
#define sectionListAdd(lst, val) ptrListAdd((PtrList*)lst, (void*)(val))
#define sectionListGet(lst, idx) (TestSection*)ptrListGet((PtrList*)lst, (idx))
#define sectionListGetRaw(lst) (TestSection**)ptrListGetRaw((PtrList*)lst)
#define sectionListGetLen(lst) ptrListGetLen((PtrList*)lst)


#endif
