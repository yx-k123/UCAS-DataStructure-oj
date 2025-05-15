#include <stdio.h>

int F(int n) {
    if (n == 0)
        return 1;
    else
        return n * F(n / 2);
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%d\n", F(n));
    return 0;
}