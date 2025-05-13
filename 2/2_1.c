#include <stdio.h>

int main() {
    int var[101]; 
    int x, n = 0;
    char temp;

    while (scanf("%d%c", &var[n], &temp) != EOF) {
        n++;
        if (temp == '\n') {
            break;
        }
    }

    scanf("%d", &x);

    int insert_pos = 0;
    for (int i = 0; i < n; i++) {
        if (var[i] >= x) {
            insert_pos = i;
            break;
        }
    }
    if (var[n - 1] < x) {
        insert_pos = n;
    }

    for (int i = n; i > insert_pos; i--) {
        var[i] = var[i - 1];
    }
    var[insert_pos] = x;
    n++;

    for (int i = 0; i < n; i++) {
        printf("%d ", var[i]);
    }
    printf("\n");

    return 0;
}