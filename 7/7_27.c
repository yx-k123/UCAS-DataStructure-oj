#include <stdio.h>

int normal_path(int edge[][100], int start, int end, int path_length, int visited[], int current_length, int v_num);

int main()
{
    int v_num, path_length;
    scanf("%d,%d", &v_num, &path_length);
    int start, end;
    scanf("%d,%d", &start, &end);
    
    int edge[100][100] = {0};

    do {    
        int u, v;
        scanf("%d-%d", &u, &v);
        edge[u][v] = 1; 
        edge[v][u] = 1; 
    } while (getchar() != '\n'); 
    
    int visited[100] = {0};
    
    if (normal_path(edge, start, end, path_length, visited, 0, v_num)) {
        printf("yes\n");
    } else {
        printf("no\n");
    }

    return 0;
}

int normal_path(int edge[][100], int start, int end, int path_length, int visited[], int current_length, int v_num)
{
    visited[start] = 1;
    
    if (current_length == path_length) {
        visited[start] = 0; 
        return (start == end) ? 1 : 0;
    }

    for (int i = 1; i <= v_num; i++) {
        if (edge[start][i] && !visited[i]) {
            if (normal_path(edge, i, end, path_length, visited, current_length + 1, v_num)) {
                visited[start] = 0; 
                return 1;
            }
        }
    }
    
    visited[start] = 0; 
    return 0;
}