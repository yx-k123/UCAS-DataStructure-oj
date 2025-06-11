#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 100

typedef struct AdjNode {
    int vertex;
    struct AdjNode *next;
} AdjNode;

typedef struct {
    int mpl;
    int in_degree;
    AdjNode *head;
} Vertex;

typedef struct {
    Vertex vertices[MAX_VERTEX];
    int vertex_count;
} Graph;

void init_graph(Graph *graph);
void add_edge(Graph *graph, int u, int v);
void find_max_path_length(Graph *graph, int vertex, int current_length, int *max_length);

int main()
{
    Graph graph;
    int v_num;
    scanf("%d", &v_num);
    init_graph(&graph);
    graph.vertex_count = v_num + 1; // 0号顶点空置

    do {
        int u, v;
        scanf("%d-%d", &u, &v);
        if (u < 0 || u > v_num || v < 0 || v > v_num) {
            continue;
        }
        add_edge(&graph, u, v); 
    } while (getchar() != '\n'); 

    for (int i = 1; i <= v_num; i++) {
        find_max_path_length(&graph, i, 0, &graph.vertices[i].mpl);
    }

    for (int i = 1; i <= v_num; i++) {
        printf("%d", graph.vertices[i].mpl);
        if (i == v_num) {
            printf("\n");
        } else {
            printf(",");
        }
    }
    return 0;
}

void init_graph(Graph *graph) {
    graph->vertex_count = 0;
    for (int i = 0; i < MAX_VERTEX; i++) {
        graph->vertices[i].mpl = 0;
        graph->vertices[i].in_degree = 0;
        graph->vertices[i].head = NULL;
    }
}

void add_edge(Graph *graph, int u, int v) {
    if (u < 0 || u > graph->vertex_count || v < 0 || v > graph->vertex_count) return;

    AdjNode *new_node = (AdjNode *)malloc(sizeof(AdjNode));
    new_node->vertex = v;
    new_node->next = graph->vertices[u].head;
    graph->vertices[u].head = new_node;
    
    graph->vertices[v].in_degree++;
}

void find_max_path_length(Graph *graph, int vertex, int current_length, int *max_length) {
    if (current_length > *max_length) {
        *max_length = current_length;
    }

    AdjNode *node = graph->vertices[vertex].head;
    while (node != NULL) {
        find_max_path_length(graph, node->vertex, current_length + 1, max_length);
        node = node->next;
    }
}

