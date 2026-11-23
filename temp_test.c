#include "my_tree.h"

#include <stdio.h>

/* Generate the integer tree implementation */
TREE_DEFINE(int, IntTree, IntNode)

/* Compare two integers */
int int_compare(const int *a, const int *b) {
    if (*a < *b) {
        return -1;
    }
    if (*a > *b) {
        return 1;
    }

    return 0;
}

/* Print an integer */
void int_print(const int *value) {
    printf("%d", *value);
}

int main(void) {
    IntTree tree;

    IntTree_init(&tree);

    int numbers[] = {50, 30, 70, 20, 40, 60, 80};

    for (size_t i = 0; i < 7; i++) {
        TreeInsertResult result =
            IntTree_insert(&tree, numbers[i], int_compare);

        if (result == TREE_NO_MEMORY) {
            fprintf(stderr, "Memory allocation failed\n");

            IntTree_deinit(&tree);
            return 1;
        }
    }

    printf("Inorder:   ");
    IntTree_print_inorder(&tree, int_print);

    printf("Preorder:  ");
    IntTree_print_preorder(&tree, int_print);

    printf("Postorder: ");
    IntTree_print_postorder(&tree, int_print);

    int target = 40;

    int *found = IntTree_find(&tree, target, int_compare);

    if (found != NULL) {
        printf("Found: %d\n", *found);
    } else {
        printf("Not found\n");
    }

    IntTree_deinit(&tree);

    return 0;
}
