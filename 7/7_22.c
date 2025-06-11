#include <stdio.h>

#define MAX_VERTEX 100

typedef struct {
    int adjacency_matrix[MAX_VERTEX][MAX_VERTEX];
    int vertex_count;
} Graph;

int is_path(Graph *graph, int u, int v, int *visited);

int main() 
{
    Graph graph;
    scanf("%d", &graph.vertex_count);
    int i, j;
    do {
        scanf("%d-%d", &i, &j);
        graph.adjacency_matrix[i-1][j-1] = 1; // 有向图
    } while (getchar() != '\n'); // Clear the input buffer

    
    int u, v;
    scanf("%d,%d", &u, &v);
    
    int visited[MAX_VERTEX] = {0};

    if (is_path(&graph, u, v, visited)) {
        printf("yes\n");
    } else {
        printf("no\n");
    }
    return 0;
}

int is_path(Graph *graph, int u, int v, int *visited)
{   
    if (u == v) {
        return 1; // 起点等于终点
    }

    visited[u-1] = 1;

    for (int i = 0; i < graph->vertex_count; i++) {
        if (graph->adjacency_matrix[u-1][i] && !visited[i]) {
            if (is_path(graph, i+1, v, visited)) {
                return 1; // 通过中间节点 i 存在路径
            }
        }
    }

    visited[u-1] = 0;
    return 0; // 没有路径
}