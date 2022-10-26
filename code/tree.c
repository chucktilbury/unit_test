

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

static void destroy_tree(TreeNode* node) {

    if(node->left != NULL)
        destroy_tree(node->left);
    if(node->right != NULL)
        destroy_tree(node->right);

    _free(node->key);
    _free(node->data);
    _free(node);
}

static TreeErr add_tree_node(TreeNode* tree, TreeNode* node) {

    int x = strcmp(tree->key, node->key);
    if(x > 0) {
        if(tree->right != NULL)
            return tree_add_node(tree->right, node);
        else {
            tree->right = node;
            return TREE_OK;
        }
    }
    else if(x < 0) {
        if(tree->left != NULL)
            return tree_add_node(tree->left, node);
        else {
            tree->left = node;
            return TREE_OK;
        }
    }
    else
        return TREE_DUP;
}

static TreeNode* find_tree_node(TreeNode* tree, const char* key) {

    int x = strcmp(tree->key, key);
    if(x > 0) {
        if(tree->right != NULL)
            return find_tree_node(tree->right, key);
        else
            return NULL;
    }
    else if(x < 0) {
        if(tree->left != NULL)
            return find_tree_node(tree->left, key);
        else
            return NULL;
    }
    else
        return tree;
}

Tree* createTree() {

    Tree* tree = _alloc_ds(Tree);
    tree->num_nodes = 0;
    tree->root = NULL;

    return tree;
}

TreeErr destroyTree(Tree* tree) {

    if(tree != NULL)
        destroy_tree(tree->root);

    return TREE_OK;
}

TreeErr createTreeNode(Tree* tree, const char* key, void* data, size_t size) {

    TreeNode* node = _alloc_ds(TreeNode);
    node->key = _copy_str(key);
    node->data = _copy_data(data, size);
    node->size = size;
    tree->num_nodes++;

    if(tree->root == NULL) {
        tree->root = node;
        return TREE_OK;
    }

    return add_tree_node(tree->root, node);
}

TreeErr findTreeNode(Tree* tree, const char* key, void* data, size_t* size) {

    TreeNode* node = find_tree_node(tree->root, key);
    if(node != NULL) {
        if(data != NULL && size != NULL) {
            if(*size != node->size) {
                if(*size == 0)
                    return TREE_FOUND;
                size_t sz = MIN(*size, node->size);
                memcpy(data, node->data, sz);
                *size = sz;
                return TREE_SIZE;
            }
        }
        else
            return TREE_FOUND;
    }

    return TREE_NOT_FOUND;
}

TreeErr removeTreeNode(Tree* tree, const char* key) {
}

TreeErr rotateTreeLeft(Tree* tree, const char* key) {
}

TreeErr rotateTreeRight(Tree* tree, const char* key) {
}
