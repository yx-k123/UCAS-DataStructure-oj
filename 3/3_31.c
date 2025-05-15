#include <stdio.h>

#define MAX_SIZE 1000

char stack[MAX_SIZE];
int top = -1;

void push(char c) {
    stack[++top] = c;
}

char pop() {
    return stack[top--];
}

int main()
{   
    char str[MAX_SIZE];
    char c;
    while (1) {
        int i = 0;
        top = -1; 
        while ((c = getchar()) != '@' && c != EOF && c != '\n') {
            push(c);
            str[i++] = c;
        }
        if (c == EOF) break;
        str[i] = '\0';

        int is_palindrome = 1;
        for (int j = 0; j < i; j++) {
            if (str[j] != pop()) {
                is_palindrome = 0;
                break;
            }
        }
        printf("%d\n", is_palindrome);

        while (c != '\n' && c != EOF) c = getchar();
        if (c == EOF) break;
    }
    return 0;
}