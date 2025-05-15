#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000

int main() {
    char stack[MAX_SIZE];
    int top = -1;
    char temp;

    while ((temp = getchar()) != '&') {
        if (top < MAX_SIZE - 1) {
            stack[++top] = temp;
        }
    }

    int sign = 1;
    while ((temp = getchar()) != '@') {
        if (top < 0 || stack[top] != temp) {
            sign = 0;
            break;
        }
        top--;
    }

    if (top != -1) sign = 0;

    printf("%d\n", sign);
    return 0;
}