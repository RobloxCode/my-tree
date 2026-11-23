#include "my_tree.h"

TREE_DEFINE(int, IntTree)

int int_compare(const int *a, const int *b) {
    if (*a < *b) {
        return -1;
    }
    if (*a > *b) {
        return 1;
    }
    return 0;
}

int main(void) {
    IntTree t;
    IntTree_init(&t);

    IntTree_insert(&t, 60, int_compare);

    return 0;
}
