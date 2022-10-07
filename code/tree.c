

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memory.h"

typedef struct _tree_struct_ {
    const char* key;
    void* data;
    size_t size;
    struct _tree_struct_* left;
    struct _tree_struct_* right;
} TreeNode;

#include "tree.h"

Tree* createTree() {
}

TreeErr destroyTree(Tree* tree) {
}

TreeErr createTreeNode(Tree* tree, const char* key, void* data, size_t size) {
}

TreeErr findTreeNode(Tree* tree, const char* key, void* data, size_t* size) {
}

TreeErr removeTreeNode(Tree* tree, const char* key) {
}

TreeErr rotateTreeLeft(Tree* tree, const char* key) {
}

TreeErr rotateTreeRight(Tree* tree, const char* key) {
}
