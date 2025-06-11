#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTEX 100

typedef struct AdjNode {
    int vertex;
    int weight;
    struct AdjNode *next;
} AdjNode;

typedef struct {
    AdjNode *head;
} Vertex;

typedef struct {
    Vertex vertices[MAX_VERTEX];
    int vertex_count;
} Graph;

void init_graph(Graph *graph);
void add_edge(Graph *graph, int u, int v, int weight);
int dijkstra(Graph *graph, int start, int end);

int main()
{
    Graph graph;
    init_graph(&graph);
    int v_num, start;
    scanf("%d %d", &v_num, &start);
    graph.vertex_count = v_num;
    int u, v, weight;
    char c;
    while (scanf("%d-%d %d%c", &u, &v, &weight, &c) == 4) {
        add_edge(&graph, u - 1, v - 1, weight);
        if (c != '\n') break; 
    }

    
    // for (int i = 0; i < v_num; i++) {
    //     printf("%d:", i + 1);
    //     AdjNode *node = graph.vertices[i].head;
    //     while (node) {
    //         printf("->%d(%d)", node->vertex + 1, node->weight);
    //         node = node->next;
    //     }
    //     printf("\n");
    // }
    int first = 1;
    for (int i = 0; i < v_num; i++) {
        if (i == start - 1) {
            continue;
        }
        if (first) first = 0;
        else printf(",");
        printf("%d", dijkstra(&graph, start - 1, i));
    }
    return 0;
}

void init_graph(Graph *graph) {
    graph->vertex_count = 0;
    for (int i = 0; i < MAX_VERTEX; i++) {
        graph->vertices[i].head = NULL;
    }
}

void add_edge(Graph *graph, int u, int v, int weight) {
    if (u < 0 || u >= graph->vertex_count || v < 0 || v >= graph->vertex_count) return;

    AdjNode *new_node = (AdjNode *)malloc(sizeof(AdjNode));
    new_node->vertex = v;
    new_node->weight = weight;
    new_node->next = graph->vertices[u].head;
    graph->vertices[u].head = new_node;

    new_node = (AdjNode *)malloc(sizeof(AdjNode));
    new_node->vertex = u;
    new_node->weight = weight;
    new_node->next = graph->vertices[v].head;
    graph->vertices[v].head = new_node;
}

int dijkstra(Graph *graph, int start, int end) {
    int dist[MAX_VERTEX];
    int visited[MAX_VERTEX] = {0};
    for (int i = 0; i < graph->vertex_count; i++) {
        dist[i] = (i == start) ? 0 : INT_MAX;
    }

    for (int i = 0; i < graph->vertex_count - 1; i++) {
        int min_dist = INT_MAX, min_index = -1;
        for (int j = 0; j < graph->vertex_count; j++) {
            if (!visited[j] && dist[j] < min_dist) {
                min_dist = dist[j];
                min_index = j;
            }
        }
        if (min_index == -1) break; // No reachable vertex
        visited[min_index] = 1;

        AdjNode *node = graph->vertices[min_index].head;
        while (node != NULL) {
            if (!visited[node->vertex] && dist[min_index] + node->weight < dist[node->vertex]) {
                dist[node->vertex] = dist[min_index] + node->weight;
            }
            node = node->next;
        }
    }

    return dist[end];
}