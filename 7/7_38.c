#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTEX 100

typedef struct AdjNode {
    int vertex;
    struct AdjNode *next;
} AdjNode;

typedef struct {
    char data;
    AdjNode *head;
} Vertex;

typedef struct {
    Vertex vertices[MAX_VERTEX];
    int vertex_count;
} Graph;

void init_graph(Graph *graph);
void add_vertex(Graph *graph, char data, int index);
void add_edge(Graph *graph, int u, int v);
void print_reverse_polish(Graph *graph);
void push_graph(Graph *graph, int vertex);

int main()
{
    Graph graph;
    init_graph(&graph);
    int v_num;
    scanf("%d", &v_num);
    getchar();

    graph.vertex_count = v_num;
    for (int i = 0; i < v_num; i++) {
        char data;
        scanf("%c", &data);
        add_vertex(&graph, data, i);
        while (getchar() != '\n')
        {
            int v;
            scanf("%d", &v);
            add_edge(&graph, i, v);
        }
    }
    print_reverse_polish(&graph);
    return 0;
}

void init_graph(Graph *graph) {
    graph->vertex_count = 0;
    for (int i = 0; i < MAX_VERTEX; i++) {
        graph->vertices[i].data = '\0';
        graph->vertices[i].head = NULL;
    }
}

void add_vertex(Graph *graph, char data, int index) {
    if (index >= MAX_VERTEX) return;
    graph->vertices[index].data = data;
    graph->vertices[index].head = NULL;
}

void add_edge(Graph *graph, int u, int v) {
    AdjNode *new_node = (AdjNode *)malloc(sizeof(AdjNode));
    new_node->vertex = v;
    new_node->next = graph->vertices[u].head;
    graph->vertices[u].head = new_node;
}

void print_reverse_polish(Graph *graph)
{
    int start = 0;
    push_graph(graph, start);
}

void push_graph(Graph *graph, int vertex) {
    AdjNode *node = graph->vertices[vertex].head;
    while (node != NULL) {
        push_graph(graph, node->vertex);
        node = node->next;
    }
    printf("%c", graph->vertices[vertex].data);
}