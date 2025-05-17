#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init(int *V, int *B, int m, int n, int *vlen) {
    char line[10000];
    *vlen = 0;
    
    fgets(line, sizeof(line), stdin);
    if (line[0] != '\n') {
        char *token = strtok(line, " \n");
        while (token) {
            V[(*vlen)++] = atoi(token);
            token = strtok(NULL, " \n");
        }
    }
    
    for (int i = 0; i < m * n; i++) {
        scanf("%d", &B[i]);
    }
    getchar(); 
}

void matrix_add(int *V1, int *B1, int vlen1, int *V2, int *B2, int vlen2, int *V3, int *B3, int m, int n, int *vlen3) {
    int idx1 = 0, idx2 = 0, idx3 = 0;
    for (int i = 0; i < m * n; i++) {
        int a = 0, b = 0;
        if (B1[i]) a = V1[idx1++];
        if (B2[i]) b = V2[idx2++];
        int c = a + b;
        if (c != 0) {
            V3[idx3++] = c;
            B3[i] = 1;
        } else {
            B3[i] = 0;
        }
    }
    *vlen3 = idx3;
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    getchar(); 

    int *V1 = (int *)malloc(m * n * sizeof(int));
    int *V2 = (int *)malloc(m * n * sizeof(int));
    int *B1 = (int *)malloc(m * n * sizeof(int));
    int *B2 = (int *)malloc(m * n * sizeof(int));
    int *V3 = (int *)malloc(m * n * sizeof(int));
    int *B3 = (int *)malloc(m * n * sizeof(int));
    int vlen1 = 0, vlen2 = 0, vlen3 = 0;

    init(V1, B1, m, n, &vlen1);
    init(V2, B2, m, n, &vlen2);

    matrix_add(V1, B1, vlen1, V2, B2, vlen2, V3, B3, m, n, &vlen3);

    for (int i = 0; i < vlen3; i++) {
        printf("%d", V3[i]);
        if (i < vlen3 - 1) printf(" ");
    }
    printf("\n");
    
    for (int i = 0; i < m * n; i++) {
        printf("%d", B3[i]);
        if ((i + 1) % n == 0)
            printf("\n");
        else
            printf(" ");
    }

    free(V1); free(V2); free(B1); free(B2); free(V3); free(B3);
    return 0;
}