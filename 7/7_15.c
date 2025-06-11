#include <stdio.h>
#include <string.h>

#define MAX_VERTEX 100

// 图结构
typedef struct {
    int adjacency_matrix[MAX_VERTEX][MAX_VERTEX];
    int vertex_count;
} Graph;

// 插入顶点
void InsertVex(Graph *G, int v) {
    if (v < 0 || v > G->vertex_count || G->vertex_count >= MAX_VERTEX) return;

    // 行下移
    for (int i = G->vertex_count; i > v; i--) {
        for (int j = 0; j < G->vertex_count; j++) {
            G->adjacency_matrix[i][j] = G->adjacency_matrix[i - 1][j];
        }
    }
    // 列右移
    for (int i = 0; i <= G->vertex_count; i++) {
        for (int j = G->vertex_count; j > v; j--) {
            G->adjacency_matrix[i][j] = G->adjacency_matrix[i][j - 1];
        }
    }
    // 新顶点相关边清零
    for (int i = 0; i <= G->vertex_count; i++) {
        G->adjacency_matrix[v][i] = 0;
        G->adjacency_matrix[i][v] = 0;
    }
    G->vertex_count++;
}

// 插入边
void InsertArc(Graph *G, int v, int w) {
    if (v >= 0 && v < G->vertex_count && w >= 0 && w < G->vertex_count) {
        G->adjacency_matrix[v][w] = 1;
        G->adjacency_matrix[w][v] = 1; // 无向图
    }
}

// 删除顶点
void DeleteVex(Graph *G, int v) {
    if (v < 0 || v >= G->vertex_count) return;
    
    // 将后面的顶点前移
    for (int i = v; i < G->vertex_count - 1; i++) {
        for (int j = 0; j < G->vertex_count; j++) {
            G->adjacency_matrix[i][j] = G->adjacency_matrix[i + 1][j];
        }
    }
    
    for (int i = 0; i < G->vertex_count; i++) {
        for (int j = v; j < G->vertex_count - 1; j++) {
            G->adjacency_matrix[i][j] = G->adjacency_matrix[i][j + 1];
        }
    }
    
    G->vertex_count--;
}

// 删除边
void DeleteArc(Graph *G, int v, int w) {
    if (v >= 0 && v < G->vertex_count && w >= 0 && w < G->vertex_count) {
        G->adjacency_matrix[v][w] = 0;
        G->adjacency_matrix[w][v] = 0; // 无向图
    }
}

// 打印邻接矩阵
void printMatrix(Graph *G) {
    for (int i = 0; i < G->vertex_count; i++) {
        for (int j = 0; j < G->vertex_count; j++) {
            printf("%d", G->adjacency_matrix[i][j]);
            if (j < G->vertex_count - 1) printf(" ");
        }
        printf("\n");
    }
}

int main() {
    Graph G;
    scanf("%d", &G.vertex_count);
    
    // 读取邻接矩阵
    for (int i = 0; i < G.vertex_count; i++) {
        for (int j = 0; j < G.vertex_count; j++) {
            scanf("%d", &G.adjacency_matrix[i][j]);
        }
    }
    
    char operation[3];
    int v, w;
    
    // 处理操作
    while (scanf("%s", operation) == 1) {
        if (strcmp(operation, "IV") == 0) {
            scanf("%d", &v);
            InsertVex(&G, v);
        } else if (strcmp(operation, "IA") == 0) {
            scanf("%d %d", &v, &w);
            InsertArc(&G, v, w);
        } else if (strcmp(operation, "DV") == 0) {
            scanf("%d", &v);
            DeleteVex(&G, v);
        } else if (strcmp(operation, "DA") == 0) {
            scanf("%d %d", &v, &w);
            DeleteArc(&G, v, w);
        }
    }
    
    // 输出最终的邻接矩阵
    printMatrix(&G);
    
    return 0;
}