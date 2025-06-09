#include <stdio.h>
#include <stdlib.h>

typedef struct BinaryTreeNode {
    char data;
    int left;
    int right;
} BinaryTreeNode;

typedef BinaryTreeNode *BinaryTree;

typedef struct Stack {
    BinaryTreeNode *data[100];
    int top;
} Stack;

void push(BinaryTreeNode *node);
BinaryTreeNode *pop();

Stack stack = { .top = -1 };
BinaryTreeNode tree_node[100];

int main()
{   
    BinaryTree tail = tree_node;
    BinaryTree root = tree_node;
    char c;

    while (scanf("%c %d %d%c", &tail->data, &tail->left, &tail->right, &c) == 4) {
        if(c != '\n') {
            break;
        }
        tail++;
    }

    push(root); 
    while (stack.top >= 0) {
        BinaryTreeNode *current = pop(); 
        printf("%c ", current->data); 

        if (current->right != -1) {
            push(&tree_node[current->right - 1]);
        }
        if (current->left != -1) {
            push(&tree_node[current->left - 1]);
        }
    }

    return 0;
}

void push(BinaryTreeNode *node) {
    if (stack.top < 99) {
        stack.data[++stack.top] = node;
    }
}

BinaryTreeNode *pop() {
    if (stack.top >= 0) {
        return stack.data[stack.top--];
    }
    return NULL; // Stack underflow
}