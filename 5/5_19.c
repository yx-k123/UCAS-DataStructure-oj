#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_ROWS 100
#define MAX_COLS 100

void findSaddlePoints(int matrix[MAX_ROWS][MAX_COLS], int m, int n) {
    int row_min[m];    
    int col_max[n];    
    
    for (int i = 0; i < m; i++) {
        row_min[i] = INT_MAX;
    }
    for (int j = 0; j < n; j++) {
        col_max[j] = INT_MIN;
    }
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] < row_min[i]) {
                row_min[i] = matrix[i][j];
            }
            if (matrix[i][j] > col_max[j]) {
                col_max[j] = matrix[i][j];
            }
        }
    }
    
    bool found = false;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == row_min[i] && matrix[i][j] == col_max[j]) {
                printf("%d ", matrix[i][j]);
                found = true;
            }
        }
    }
    return;
}

int main() {
    int m, n;
    int matrix[MAX_ROWS][MAX_COLS];
    
    // 输入矩阵的行数和列数
    scanf("%d %d", &m, &n);
    
    // 输入矩阵元素
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    
    // 查找鞍点
    findSaddlePoints(matrix, m, n);
    
    return 0;
}