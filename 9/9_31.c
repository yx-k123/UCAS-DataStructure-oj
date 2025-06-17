#include <stdio.h>
#include <limits.h>

typedef struct binary_tree_node {
    int value;
    struct binary_tree_node *left;
    struct binary_tree_node *right;
} binary_tree_node;

int is_binary_search_tree(binary_tree_node *node, int min, int max);

int main()
{
    binary_tree_node nodes[100];
    int nodecount = 0;
    int value, left, right;
    char c;
    while (scanf("%d %d %d%c", &value, &left, &right, &c) == 4) {
        nodes[nodecount].value = value;
        nodes[nodecount].left = (left == -1) ? NULL : &nodes[left];
        nodes[nodecount].right = (right == -1) ? NULL : &nodes[right];
        nodecount++;
    }

    printf("%d\n", is_binary_search_tree(nodes, INT_MIN,  INT_MAX));
    return 0;
}

int is_binary_search_tree(binary_tree_node *node, int min, int max)
{
    if (node == NULL) {
        return 1; 
    }
    if (node->value <= min || node->value >= max) {
        return 0; 
    }
    return is_binary_search_tree(node->left, min, node->value) &&
           is_binary_search_tree(node->right, node->value, max);
}