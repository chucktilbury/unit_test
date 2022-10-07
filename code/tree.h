#ifndef _TREE_H_
#define _TREE_H_

typedef enum {
    TREE_OK,
    TREE_ERROR,
    TREE_NOT_FOUND,
    TREE_DUP,
    TREE_MEM,
} TreeErr;

typedef struct _tree_struct_ {
    const char* key;
    void* data;
    size_t size;
    struct _tree_struct_* left;
    struct _tree_struct_* right;
} TreeNode;

typedef struct {
    TreeNode* root;
    int num_nodes;
} Tree;

Tree* createTree();
TreeErr destroyTree(Tree* tree);
TreeErr createTreeNode(Tree* tree, const char* key, void* data, size_t size);
TreeErr findTreeNode(Tree* tree, const char* key, void* data, size_t* size);
TreeErr removeTreeNode(Tree* tree, const char* key);
TreeErr rotateTreeLeft(Tree* tree, const char* key);
TreeErr rotateTreeRight(Tree* tree, const char* key);

#endif
