#include <stdio.h>

#define MAX_SIZE 1000

int g[MAX_SIZE][MAX_SIZE];
int m, n;

int dx[]={0,0,-1,1};
int dy[]={1,-1,0,0};

void dfs(int x, int y) {
    if (x < 0 || x >= m || y < 0 || y >= n) return;
    if (g[x][y] == 2 || g[x][y] == 0) return;
    g[x][y] = 2;
    for (int i = 0; i < 4; i++) {
        int new_x = x + dx[i];
        int new_y = y + dy[i];

        dfs(new_x, new_y);
    }
}

int main()
{
    int start_x, start_y, dir;
    scanf("%d %d %d %d %d", &m, &n, &start_x, &start_y, &dir);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &g[i][j]);
        }
    }

    dfs(start_x, start_y);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d", g[i][j]);
        }
        printf("\n");
    }
    return 0;
}