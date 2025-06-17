#include <stdio.h>
#include <stdlib.h>

typedef struct binary_tree_node {
    int value;
    struct binary_tree_node *left;
    struct binary_tree_node *right;
} binary_tree_node;

void insert(binary_tree_node **root, int value);
void print_in_order(binary_tree_node *node);

int main()
{
    binary_tree_node *root = NULL;

    while (1) {
        int value;
        char c;
        if (scanf("%d%c", &value, &c) != 2) {
            break;
        }
        if (value == -1) continue;
        insert(&root, value);
    }

    print_in_order(root);
    return 0;
}

void insert(binary_tree_node **root, int value)
{
    if (*root == NULL) {
        *root = (binary_tree_node *)malloc(sizeof(binary_tree_node));
        (*root)->value = value;
        (*root)->left = NULL;
        (*root)->right = NULL;
    } else if (value < (*root)->value) {
        insert(&(*root)->left, value);
    } else if (value > (*root)->value) {
        insert(&(*root)->right, value);
    }
}

void print_in_order(binary_tree_node *node)
{
    if (node == NULL) return;
    print_in_order(node->left);
    printf("%d ", node->value);
    print_in_order(node->right);
}