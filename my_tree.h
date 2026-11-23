
#ifndef TREE_H
#define TREE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

/*
 * Tree comparison function:
 *   negative: a < b
 *   zero:     a == b
 *   positive: a > b
 */
typedef enum {
    TREE_INSERTED,
    TREE_DUPLICATE,
    TREE_NO_MEMORY
} TreeInsertResult;

/*
 * TREE_DEFINE(T, Name)
 *
 * T    = element type
 * Name = generated tree type and function prefix
 *
 * Requires a comparison function:
 *     int compare(const T *a, const T *b);
 */
#define TREE_DEFINE(T, Name)                                                   \
                                                                               \
    typedef struct Name##_Node {                                               \
        T value;                                                               \
        struct Name##_Node *left;                                              \
        struct Name##_Node *right;                                             \
    } Name##_Node;                                                             \
                                                                               \
    typedef struct Name {                                                      \
        Name##_Node *root;                                                     \
        size_t len;                                                            \
    } Name;                                                                    \
                                                                               \
    static inline void Name##_init(Name *tree) {                               \
        tree->root = NULL;                                                     \
        tree->len = 0;                                                         \
    }                                                                          \
                                                                               \
    static inline Name##_Node *Name##_create_node(T value) {                   \
        Name##_Node *node = malloc(sizeof(*node));                             \
        if (node == NULL) {                                                    \
            return NULL;                                                       \
        }                                                                      \
        node->value = value;                                                   \
        node->left = NULL;                                                     \
        node->right = NULL;                                                    \
        return node;                                                           \
    }                                                                          \
                                                                               \
    static inline TreeInsertResult Name##_insert(                              \
        Name *tree, T value, int (*compare)(const T *, const T *)) {           \
        Name##_Node **link = &tree->root;                                      \
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
        Name##_Node *node = Name##_create_node(value);                         \
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
    static inline T *Name##_find(Name *tree, T value,                          \
                                 int (*compare)(const T *, const T *)) {       \
        Name##_Node *node = tree->root;                                        \
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
    static inline void Name##_destroy_nodes(Name##_Node *node) {               \
        if (node == NULL) {                                                    \
            return;                                                            \
        }                                                                      \
        Name##_destroy_nodes(node->left);                                      \
        Name##_destroy_nodes(node->right);                                     \
        free(node);                                                            \
    }                                                                          \
                                                                               \
    static inline void Name##_deinit(Name *tree) {                             \
        Name##_destroy_nodes(tree->root);                                      \
        Name##_init(tree);                                                     \
    }

#endif
