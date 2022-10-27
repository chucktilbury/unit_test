
#include "unit_test.h"

// include the file with the units to test
#include "list.c"
#include "tree.c"

// list tests
#include "test_list1.test"
#include "test_list2.test"

// tree tests
#include "test_tree1.test"
#include "test_tree2.test"

// main function
DEF_TEST_MAIN("main test", "This is the main testing test")
ADD_GROUP(list_unit_test_success);
ADD_GROUP(list_section2);
ADD_GROUP(tree_section1);
ADD_GROUP(tree_section2);
END_TEST_MAIN
