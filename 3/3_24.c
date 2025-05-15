#include <stdio.h>

int f(int m, int n);

int main()
{
    int m = 0;
    int n = 0;
    scanf("%d,%d", &m, &n);

    printf("%d\n", f(m, n));
    return 0;
}

int f(int m, int n)
{   
    if(m == 1)
        return n;
    if(m == 0)
        return 0;
    return f( m-1, 2*n ) + n;
}