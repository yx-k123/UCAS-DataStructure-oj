#include <stdio.h>

#define WHITE 0  
#define GRAY  1  
#define BLACK 2  

void get_array_data(int *array);
int dfs_cycle_check(int *s, int *fst, int *lst, int *color, int n, int v);

int main()
{
    int n;
    scanf("%d", &n);
    int s[100] = {0};
    int fst[n + 1], lst[n + 1];
    get_array_data(s);
    get_array_data(fst);
    get_array_data(lst);
    
    int color[n + 1];
    for (int i = 0; i < n + 1; i++) {
        color[i] = WHITE;
    }

    int cycle_found = 0;
    for (int i = 1; i <= n; i++) {
        if (color[i] == WHITE) {
            if (dfs_cycle_check(s, fst, lst, color, n, i)) {
                cycle_found = 1;
                break;
            }
        }
    }
    if (cycle_found) {
        printf("yes\n");
    } else {
        printf("no\n");
    }

    return 0;
}

void get_array_data(int *array)
{   
    int n = 0;
    char c;
    while (scanf("%d%c", &array[n], &c)) {
        if (c == '\n') {
            break;
        }
        n++;
    }
    return;
}

int dfs_cycle_check(int *s, int *fst, int *lst,  int *color, int n, int v)
{
    color[v] = GRAY;  

    for (int i = fst[v]; i < lst[v]; i++) {
        int w = s[i];
        if (color[w] == WHITE) {
            if (dfs_cycle_check(s, fst, lst, color, n, w)) {
                return 1; 
            }
        } else if (color[w] == GRAY) {
            return 1; 
        }
    }

    color[v] = BLACK;
    return 0;
}