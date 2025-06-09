#include <stdio.h>

int L[101], R[101];

void reverse_tree_left_right(int root);

int main()
{
    int n = 0;
    char c;
    while(scanf("%d%c", &L[n], &c)) {
        if (c == '\n') {
            break;
        }
        n++;
    }
    n = 0; 
    while(scanf("%d%c", &R[n], &c)) {
        if (c == '\n') {
            break;
        }
        n++;
    }

    // 反转二叉树的左右子树
    reverse_tree_left_right(1);

    // 输出反转后的结果
    for (int i = 0; i <= n; i++) {
        printf("%d", L[i]);
        if (i < n) {
            printf(" ");
        }
    }
    printf("\n");
    for (int i = 0; i <= n; i++) {
        printf("%d", R[i]);
        if (i < n) {
            printf(" ");
        }
    }
    return 0;
}

void reverse_tree_left_right(int root) {
    if (root == 0) return;
    
    // 交换左右孩子
    int temp = L[root];
    L[root] = R[root];
    R[root] = temp;
    
    // 递归处理左子树和右子树
    reverse_tree_left_right(L[root]);
    reverse_tree_left_right(R[root]);
}