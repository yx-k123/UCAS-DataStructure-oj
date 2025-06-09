#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode {
    char val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode* buildTree(const char* s, int* index) {
    if (s[*index] == '\0' || s[*index] == '^') {
        (*index)++;
        return NULL;
    }
    
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->val = s[*index];
    (*index)++;
    
    node->left = buildTree(s, index);
    node->right = buildTree(s, index);
    
    return node;
}

// 查找路径函数
int findPath(TreeNode* root, char target, TreeNode** path, int* pathLen) {
    if (root == NULL) return 0;
    
    path[*pathLen] = root;
    (*pathLen)++;
    
    if (root->val == target) return 1;
    
    if (findPath(root->left, target, path, pathLen) || 
        findPath(root->right, target, path, pathLen)) {
        return 1;
    }
    
    (*pathLen)--; // 回溯
    return 0;
}

TreeNode* lowestCommonAncestor(TreeNode* root, char p, char q) {
    TreeNode* pathP[100], *pathQ[100];
    int lenP = 0, lenQ = 0;
    
    if (!findPath(root, p, pathP, &lenP) || 
        !findPath(root, q, pathQ, &lenQ)) {
        return NULL;
    }
    
    // 检查是否存在祖先关系
    int minLen = (lenP < lenQ) ? lenP : lenQ;
    int lcaIndex = -1;
    
    // 找到最后一个公共祖先的位置
    for (int i = 0; i < minLen; i++) {
        if (pathP[i] == pathQ[i]) {
            lcaIndex = i;
        } else {
            break;
        }
    }
    
    if (lcaIndex == -1) return NULL;
    
    // 检查是否存在祖先-后代关系
    if (lenP == lcaIndex + 1) {
        // p是q的祖先
        if (lcaIndex == 0) {
            return pathP[0]; // p是根节点
        } else {
            return pathP[lcaIndex - 1]; // p的父节点
        }
    } else if (lenQ == lcaIndex + 1) {
        // q是p的祖先
        if (lcaIndex == 0) {
            return pathQ[0]; // q是根节点
        } else {
            return pathQ[lcaIndex - 1]; // q的父节点
        }
    }
    
    // 正常的LCA情况
    return pathP[lcaIndex];
}

int main() {
    char input[100];
    char p, q;
    
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;
    
    scanf("%c %c", &p, &q);
    
    int index = 0;
    TreeNode* root = buildTree(input, &index);
    
    TreeNode* lca = lowestCommonAncestor(root, p, q);
    if (lca != NULL) {
        printf("%c\n", lca->val);
    }
    
    return 0;
}