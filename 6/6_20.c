#include <stdio.h>
#include <stdlib.h>

typedef struct BinaryTreeNode {
    int data;
    int left;
    int right;
} BinaryTreeNode;

typedef BinaryTreeNode *BinaryTree;

typedef struct ForestNode {
    int data;
    int first_child;
    int next_sibling;
} ForestNode;

typedef ForestNode *Forest;

BinaryTreeNode tree[100];
ForestNode forest[100];
ForestNode forest_root[100];

int L[101] = {1};
int R[101] = {1};
int pre_node;

void preorder_threading(int root);
void inorder_threading(int root);
void postorder_threading(int root);
void find_all_root(Forest forest, int n);
BinaryTree forest_to_binarytree(Forest forest, BinaryTree tree, int n);
void print_array(int arr[], int n);


int main() 
{
    int n = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &forest[i].data, &forest[i].first_child, &forest[i].next_sibling);
    }
    // 转换为二叉树
    forest_to_binarytree(forest, tree, n);

    // printf("Binary Tree:\n");
    // for (int i = 0; i < n; i++) {
    //     printf("Node %d: data=%d, left=%d, right=%d\n", i + 1, tree[i].data, tree[i].left, tree[i].right);
    // }
    // printf("Forest:\n");
    // for (int i = 0; i < n; i++) {
    //     printf("Node %d: data=%d, first_child=%d, next_sibling=%d\n", i + 1, forest[i].data, forest[i].first_child, forest[i].next_sibling);
    // }
    
    // 获取根节点
    int root = forest_root[0].data;
    
    // 1. 先序前驱线索化
    for (int i = 1; i <= n; i++) {
        L[i] = R[i] = 0;
    }
    pre_node = 0;
    preorder_threading(root);
    print_array(L, n);
    print_array(R, n);
    
    // 2. 中序全线索化
    for (int i = 1; i <= n; i++) {
        L[i] = R[i] = 0;
    }
    pre_node = 0;
    inorder_threading(root);
    print_array(L, n);
    print_array(R, n);
    
    // 3. 后序后继线索化
    for (int i = 1; i <= n; i++) {
        L[i] = R[i] = 0;
    }
    pre_node = 0;
    postorder_threading(root);
    print_array(L, n);
    print_array(R, n);
    
    return 0;
}

BinaryTree forest_to_binarytree(Forest forest, BinaryTree tree, int n) {
    for (int i = 0; i < 100; i++) {
        tree[i].data = 0;
        tree[i].left = 0;
        tree[i].right = 0;
    }

    for (int i = 0; i < n; i++) {
        int idx = forest[i].data - 1;  
        tree[idx].data = forest[i].data;
        tree[idx].left = forest[i].first_child;
        tree[idx].right = forest[i].next_sibling;
    }
    
    find_all_root(forest, n);
    
    if (forest_root[0].data != 0) {
        int current = forest_root[0].data - 1;
        for (int i = 1; forest_root[i].data != 0; i++) {
            while (tree[current].right != 0) {
                current = tree[current].right - 1;
            }
            tree[current].right = forest_root[i].data;
            current = forest_root[i].data - 1;
        }
    }
    
    return tree;
}

void find_all_root(Forest forest, int n) {
    int is_root[100];
    
    for (int i = 0; i < 100; i++) {
        is_root[i] = 1;
    }
    
    for (int i = 0; i < n; i++) {
        if (forest[i].first_child != 0) {
            is_root[forest[i].first_child - 1] = 0;
        }
        if (forest[i].next_sibling != 0) {
            is_root[forest[i].next_sibling - 1] = 0;
        }
    }
    
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (is_root[forest[i].data - 1]) {
            forest_root[j].data = forest[i].data;
            forest_root[j].first_child = forest[i].first_child;
            forest_root[j].next_sibling = forest[i].next_sibling;
            j++;
        }
    }

    // if (j > 0) {
    //     forest_root[j].data = 0; // 结束标志
    // }
    // printf("Root(s): ");
    // for (int k = 0; k < j; k++) {
    //     printf("%d ", forest_root[k].data);
    // }
    // printf("\n");
}

// 先序前驱线索化
void preorder_threading(int root) {
    if (root == 0) return;
    
    // 设置前驱线索
    if (tree[root - 1].left == 0 && pre_node != 0) {
        L[root] = pre_node;
    } else {
        L[root] = tree[root - 1].left;
    }
    
    // 保持原有右孩子
    R[root] = tree[root - 1].right;
    
    pre_node = root;
    
    if (tree[root - 1].left != 0) {
        preorder_threading(tree[root - 1].left);
    }
    if (tree[root - 1].right != 0) {
        preorder_threading(tree[root - 1].right);
    }
}

// 中序全线索化
void inorder_threading(int root) {
    if (root == 0) return;
    
    if (tree[root - 1].left != 0) {
        inorder_threading(tree[root - 1].left);
    }
    
    // 设置前驱线索
    if (tree[root - 1].left == 0 && pre_node != 0) {
        L[root] = pre_node;
    } else {
        L[root] = tree[root - 1].left;
    }
    
    // 设置后继线索
    if (pre_node != 0 && tree[pre_node - 1].right == 0) {
        R[pre_node] = root;
    } else if (pre_node != 0) {
        R[pre_node] = tree[pre_node - 1].right;
    }
    
    pre_node = root;
    
    if (tree[root - 1].right != 0) {
        inorder_threading(tree[root - 1].right);
    } else {
        R[root] = 0; // 最后一个节点
    }
}

// 后序后继线索化
void postorder_threading(int root) {
    if (root == 0) return;
    
    if (tree[root - 1].left != 0) {
        postorder_threading(tree[root - 1].left);
    }
    if (tree[root - 1].right != 0) {
        postorder_threading(tree[root - 1].right);
    }
    
    // 保持原有左孩子
    L[root] = tree[root - 1].left;
    
    // 如果有右孩子，保持原有右孩子；否则暂时设为0
    if (tree[root - 1].right != 0) {
        R[root] = tree[root - 1].right;
    } else {
        R[root] = 0;  // 暂时设为0，后面可能被设置为后继
    }
    
    // 为前一个访问的节点设置后继线索
    if (pre_node != 0 && tree[pre_node - 1].right == 0) {
        R[pre_node] = root;  // 前一个节点的后继是当前节点
    }
    
    pre_node = root;
}

// 输出数组
void print_array(int arr[], int n) {
    for (int i = 0; i <= n; i++) {
        printf("%d", arr[i]);
        if (i < n) printf(" ");
    }
    printf("\n");
}