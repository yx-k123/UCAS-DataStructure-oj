#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* createNode(int data);
TreeNode* insert(TreeNode* root, int data);
void printDescending(TreeNode* root, int x, int* first);

int main() {
    TreeNode* root = NULL;
    int data;
    int x;
    
    while (scanf("%d", &data) == 1) {
        root = insert(root, data);
        
        char c = getchar();
        if (c == '\n') {
            break;
        }
    }
    
    scanf("%d", &x);
    
    int first = 1;
    printDescending(root, x, &first);
    printf("\n");
    
    return 0;
}

TreeNode* createNode(int data) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

TreeNode* insert(TreeNode* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    
    return root;
}

void printDescending(TreeNode* root, int x, int* first) {
    if (root == NULL) {
        return;
    }
    
    printDescending(root->right, x, first);
    
    if (root->data >= x) {
        if (*first) {
            printf("%d", root->data);
            *first = 0;
        } else {
            printf(" %d", root->data);
        }
    }
    
    if (root->data >= x) {
        printDescending(root->left, x, first);
    }
}

