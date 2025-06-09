#include <stdio.h>
int is_descendant(int *L, int *R, int ancestor, int node);

int main() {
    int L[1000] = {0};
    int R[1000] = {0};
    int T[1000] = {0};
    int u, v;
    char c;
    int i = 0;

    while (scanf("%d%c", &L[i], &c)) {
        if (c == '\n') break;
        i++;
    }
    
    i = 0;
    while (scanf("%d%c", &L[i], &c)) {
        if (c == '\n') break;
        i++;
    }

    i = 0;
    while (scanf("%d%c", &R[i], &c)) {
        if (c == '\n') break;
        i++;
    }

    scanf("%d %d", &u, &v);

    printf("%d\n", is_descendant(L, R, v, u));
    return 0;
}

int is_descendant(int *L, int *R, int ancestor, int node) {
    if (L[ancestor] == 0 && R[ancestor] == 0) return 0; 
    
    if ((L[ancestor] != 0 && L[ancestor] == node) || 
        (R[ancestor] != 0 && R[ancestor] == node)) {
        return 1;
    }
    
    if (L[ancestor] != 0 && is_descendant(L, R, L[ancestor], node)) return 1;
    if (R[ancestor] != 0 && is_descendant(L, R, R[ancestor], node)) return 1;
    
    return 0;
}