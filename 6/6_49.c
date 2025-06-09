#include <stdio.h>

typedef struct BinaryTreeNode {
    char data;
    int left;
    int right;
} BinaryTreeNode;

typedef BinaryTreeNode *BinaryTree;
BinaryTreeNode tree_node[100];

int is_complete_binary_tree(BinaryTree root) {
    if (root == NULL) return 1;

    BinaryTree queue[200]; 
    int front = 0, rear = 0;
    queue[rear++] = root;
    
    int foundNull = 0;

    while (front < rear) {
        BinaryTree current = queue[front++];
        
        if (current == NULL) {
            foundNull = 1;
        } else {
            if (foundNull) {
                return 0; // 在空节点后又遇到非空节点
            }
            
            // 加入左子树
            if (current->left != -1) {
                queue[rear++] = &tree_node[current->left - 1];
            } else {
                queue[rear++] = NULL;
            }
            
            // 加入右子树
            if (current->right != -1) {
                queue[rear++] = &tree_node[current->right - 1];
            } else {
                queue[rear++] = NULL;
            }
        }
    }
    
    return 1;
}

int main()
{   
    BinaryTree tail = tree_node;
    char c;
    
    while (scanf("%c %d %d%c", &tail->data, &tail->left, &tail->right, &c) == 4) {
        if(c != '\n') {
            break;
        }
        tail++;
    }

    BinaryTree root = &tree_node[0];
    
    if (is_complete_binary_tree(root)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}