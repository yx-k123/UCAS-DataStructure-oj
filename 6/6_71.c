#include <stdio.h>

typedef struct {
    char data;
    int first_child;
    int next_sibling;
} ForestNode;

ForestNode forest[100];

void read_forest();
void print_recessed_table(ForestNode root, int depth);

typedef ForestNode *Forest;

int main ()
{
    read_forest();
    print_recessed_table(forest[0], 0);
    return 0;
}

void read_forest()
{   
    int i = 0;
    char c;
    while(scanf("%c %d %d%c", &forest[i].data, &forest[i].first_child, &forest[i].next_sibling, &c) != EOF) {
        i++;
        if (c != '\n') {
            break; 
        }
    }
    return;
}

void print_recessed_table(ForestNode root, int depth)
{
    for (int i = 0; i < depth; i++) {
        printf("-");
    }
    
    printf("%c\n", root.data);
    
    if (root.first_child != -1) {
        print_recessed_table(forest[root.first_child - 1], depth + 1);
    }
    
    if (root.next_sibling != -1) {
        print_recessed_table(forest[root.next_sibling - 1], depth);
    }

    return;
}