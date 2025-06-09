#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode {
    char data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* buildTree(char* preorder, int* index);
void inorderExpression(TreeNode* root, TreeNode* parent, int isLeftChild);
int isOperator(char c);
int getPriority(char op);

int main() {
    char preorder[100];
    scanf("%s", preorder);
    
    int index = 0;
    TreeNode* root = buildTree(preorder, &index);
    
    inorderExpression(root, NULL, 1);
    printf("\n");
    
    return 0;
}

// 判断是否为操作符
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// 获取操作符优先级
int getPriority(char op) {
    switch(op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

// 根据先序序列构建表达式树
TreeNode* buildTree(char* preorder, int* index) {
    if (*index >= strlen(preorder) || preorder[*index] == '#') {
        (*index)++;
        return NULL;
    }
    
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->data = preorder[*index];
    (*index)++;
    
    root->left = buildTree(preorder, index);
    root->right = buildTree(preorder, index);
    
    return root;
}

// 中序遍历输出表达式，根据需要添加括号
void inorderExpression(TreeNode* root, TreeNode* parent, int isLeftChild) {
    if (root == NULL) return;
    
    // 判断是否需要加括号
    int needParentheses = 0;
    if (parent != NULL && isOperator(root->data) && isOperator(parent->data)) {
        int rootPriority = getPriority(root->data);
        int parentPriority = getPriority(parent->data);
        
        // 需要加括号的情况：
        // 1. 子表达式优先级低于父表达式
        // 2. 优先级相同且是右子树且父操作符是左结合的（-、/）
        if (rootPriority < parentPriority || 
            (rootPriority == parentPriority && !isLeftChild && 
             (parent->data == '-' || parent->data == '/'))) {
            needParentheses = 1;
        }
    }
    
    if (needParentheses) printf("(");
    
    // 左子树
    inorderExpression(root->left, root, 1);
    
    // 根节点
    printf("%c", root->data);
    
    // 右子树
    inorderExpression(root->right, root, 0);
    
    if (needParentheses) printf(")");
}

