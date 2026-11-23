#ifndef TREE_H
#define TREE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Tree insertion results.
 */
typedef enum {
    TREE_INSERTED,
    TREE_DUPLICATE,
    TREE_NO_MEMORY
} TreeInsertResult;

/*
 * TREE_DEFINE(T, TreeName, NodeName)
 *
 * T        = element type
 * TreeName = generated tree type and function prefix
 * NodeName = generated node type
 *
 * The comparison function must return:
 *   negative if a < b
 *   zero     if a == b
 *   positive if a > b
 *
 * The print function receives a pointer to the value.
 *
 * Example:
 *   TREE_DEFINE(int, IntTree, IntNode)
 *
 *   Generates:
 *     IntTree
 *     IntNode
 *     IntTree_init()
 *     IntTree_insert()
 *     IntTree_find()
 *     IntTree_print_inorder()
 *     IntTree_print_preorder()
 *     IntTree_print_postorder()
 *     IntTree_deinit()
 */

#define TREE_DEFINE(T, TreeName, NodeName)                                     \
                                                                               \
    /* Node structure */                                                       \
    typedef struct NodeName {                                                  \
        T value;                                                               \
        struct NodeName *left;                                                 \
        struct NodeName *right;                                                \
    } NodeName;                                                                \
                                                                               \
    /* Tree structure */                                                       \
    typedef struct TreeName {                                                  \
        NodeName *root;                                                        \
        size_t len;                                                            \
    } TreeName;                                                                \
                                                                               \
    /* Initialize an empty tree */                                             \
    static inline void TreeName##_init(TreeName *tree) {                       \
        tree->root = NULL;                                                     \
        tree->len = 0;                                                         \
    }                                                                          \
                                                                               \
    /* Allocate and initialize a node */                                       \
    static inline NodeName *TreeName##_create_node(T value) {                  \
        NodeName *node = malloc(sizeof(*node));                                \
                                                                               \
        if (node == NULL) {                                                    \
            return NULL;                                                       \
        }                                                                      \
                                                                               \
        node->value = value;                                                   \
        node->left = NULL;                                                     \
        node->right = NULL;                                                    \
                                                                               \
        return node;                                                           \
    }                                                                          \
                                                                               \
    /* Insert a value into the tree */                                         \
    static inline TreeInsertResult TreeName##_insert(                          \
        TreeName *tree, T value, int (*compare)(const T *, const T *)) {       \
        NodeName **link = &tree->root;                                         \
                                                                               \
        while (*link != NULL) {                                                \
            int result = compare(&value, &(*link)->value);                     \
                                                                               \
            if (result == 0) {                                                 \
                return TREE_DUPLICATE;                                         \
            }                                                                  \
                                                                               \
            if (result < 0) {                                                  \
                link = &(*link)->left;                                         \
            } else {                                                           \
                link = &(*link)->right;                                        \
            }                                                                  \
        }                                                                      \
                                                                               \
        NodeName *node = TreeName##_create_node(value);                        \
                                                                               \
        if (node == NULL) {                                                    \
            return TREE_NO_MEMORY;                                             \
        }                                                                      \
                                                                               \
        *link = node;                                                          \
        tree->len++;                                                           \
                                                                               \
        return TREE_INSERTED;                                                  \
    }                                                                          \
                                                                               \
    /* Find a value and return a pointer to it */                              \
    static inline T *TreeName##_find(TreeName *tree, T value,                  \
                                     int (*compare)(const T *, const T *)) {   \
        NodeName *node = tree->root;                                           \
                                                                               \
        while (node != NULL) {                                                 \
            int result = compare(&value, &node->value);                        \
                                                                               \
            if (result == 0) {                                                 \
                return &node->value;                                           \
            }                                                                  \
                                                                               \
            if (result < 0) {                                                  \
                node = node->left;                                             \
            } else {                                                           \
                node = node->right;                                            \
            }                                                                  \
        }                                                                      \
                                                                               \
        return NULL;                                                           \
    }                                                                          \
                                                                               \
    /* Inorder traversal: left, root, right */                                 \
    static inline void TreeName##_print_inorder_node(                          \
        const NodeName *node, void (*print_value)(const T *), bool *first) {   \
        if (node == NULL) {                                                    \
            return;                                                            \
        }                                                                      \
                                                                               \
        TreeName##_print_inorder_node(node->left, print_value, first);         \
                                                                               \
        if (!*first) {                                                         \
            printf(", ");                                                      \
        }                                                                      \
                                                                               \
        print_value(&node->value);                                             \
        *first = false;                                                        \
                                                                               \
        TreeName##_print_inorder_node(node->right, print_value, first);        \
    }                                                                          \
                                                                               \
    static inline void TreeName##_print_inorder(                               \
        const TreeName *tree, void (*print_value)(const T *)) {                \
        bool first = true;                                                     \
                                                                               \
        TreeName##_print_inorder_node(tree->root, print_value, &first);        \
                                                                               \
        printf("\n");                                                          \
    }                                                                          \
                                                                               \
    /* Preorder traversal: root, left, right */                                \
    static inline void TreeName##_print_preorder_node(                         \
        const NodeName *node, void (*print_value)(const T *), bool *first) {   \
        if (node == NULL) {                                                    \
            return;                                                            \
        }                                                                      \
                                                                               \
        if (!*first) {                                                         \
            printf(", ");                                                      \
        }                                                                      \
                                                                               \
        print_value(&node->value);                                             \
        *first = false;                                                        \
                                                                               \
        TreeName##_print_preorder_node(node->left, print_value, first);        \
                                                                               \
        TreeName##_print_preorder_node(node->right, print_value, first);       \
    }                                                                          \
                                                                               \
    static inline void TreeName##_print_preorder(                              \
        const TreeName *tree, void (*print_value)(const T *)) {                \
        bool first = true;                                                     \
                                                                               \
        TreeName##_print_preorder_node(tree->root, print_value, &first);       \
                                                                               \
        printf("\n");                                                          \
    }                                                                          \
                                                                               \
    /* Postorder traversal: left, right, root */                               \
    static inline void TreeName##_print_postorder_node(                        \
        const NodeName *node, void (*print_value)(const T *), bool *first) {   \
        if (node == NULL) {                                                    \
            return;                                                            \
        }                                                                      \
                                                                               \
        TreeName##_print_postorder_node(node->left, print_value, first);       \
                                                                               \
        TreeName##_print_postorder_node(node->right, print_value, first);      \
                                                                               \
        if (!*first) {                                                         \
            printf(", ");                                                      \
        }                                                                      \
                                                                               \
        print_value(&node->value);                                             \
        *first = false;                                                        \
    }                                                                          \
                                                                               \
    static inline void TreeName##_print_postorder(                             \
        const TreeName *tree, void (*print_value)(const T *)) {                \
        bool first = true;                                                     \
                                                                               \
        TreeName##_print_postorder_node(tree->root, print_value, &first);      \
                                                                               \
        printf("\n");                                                          \
    }                                                                          \
                                                                               \
    /* Recursively free every node */                                          \
    static inline void TreeName##_destroy_nodes(NodeName *node) {              \
        if (node == NULL) {                                                    \
            return;                                                            \
        }                                                                      \
                                                                               \
        TreeName##_destroy_nodes(node->left);                                  \
        TreeName##_destroy_nodes(node->right);                                 \
                                                                               \
        free(node);                                                            \
    }                                                                          \
                                                                               \
    /* Free the tree and reset it */                                           \
    static inline void TreeName##_deinit(TreeName *tree) {                     \
        TreeName##_destroy_nodes(tree->root);                                  \
        TreeName##_init(tree);                                                 \
    }

#endif
