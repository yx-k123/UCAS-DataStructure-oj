#include <stdio.h>

int main()
{
    int v_num, e_num;
    scanf("%d,%d", &v_num, &e_num);

    int adj_matrix[v_num + 1][v_num + 1];
    for (int i = 0; i < v_num; i++) {
        for (int j = 0; j < v_num; j++) {
            adj_matrix[i][j] = 0;
        }
    }

    int start = 1;
    for (int i = 0; i < e_num; i++) {
        int v1, v2;
        scanf("%d-%d", &v1, &v2);
        adj_matrix[v1][v2] = 1;
        if ( start == 1 && (v1 == 0 || v2 == 0)) {
            start = 0;
        }
        getchar(); 
    }

    for (int i = start; i <= v_num + start - 1; i++) {
        printf("%d", i);
        int index = 0;
        for (int j = v_num; j >= start ; j--) {
            if (adj_matrix[i][j] == 1) {
                if (index == 0) {
                    printf(" ");
                } else {
                    printf(",");
                }
                printf("%d", j);
                index++;
            }
        }
        printf("\n");
    }


    return 0;
}