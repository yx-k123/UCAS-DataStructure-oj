#include <stdio.h>

int main() {
    int a[1000];
    int c[1000];
    int n = 0;
    
    while (scanf("%d", &a[n]) == 1) {
        n++;
    }

    for (int i = 0; i < n; i++) {
        c[i] = 0;  
        for (int j = 0; j < n; j++) {
            if (a[j] < a[i]) {
                c[i]++; 
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        printf("%d ", c[i]);
    }
    printf("\n");
    
    return 0;
}