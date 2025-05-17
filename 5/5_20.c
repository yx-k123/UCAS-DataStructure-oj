#include <stdio.h>
#include <stdlib.h>

int main()
{
    int m, n;
    scanf("%d %d", &m, &n);
    int *matrix = (int *)malloc(m * n * sizeof(int *));

    int first = 1;

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &matrix[i * n + j]);
    
    for (int i = m-1; i > -1; i--)
        for (int j = n-1; j > -1; j--)
        {
            if (matrix[i * n + j] != 0)
            {
                if (!first){
                    printf("+");
                } else {
                    first = 0;
                }
                if (i != 0 || j != 0)
                    if (matrix[i * n + j] != 1)
                        printf("%d", matrix[i * n + j]);
                if (i == 0 && j == 0)
                    printf("%d", matrix[i * n + j]);
                
                if (i != 0)
                    printf("xE%d", i);
                if (j != 0)
                    printf("yE%d", j);
            }
        }
    if(first)
        printf("0");
    free(matrix);
    return 0;
}