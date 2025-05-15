#include <stdio.h>

char stack[1000];
int top = -1;

void push(char c) {
    stack[++top] = c;
}

char pop() {
    return stack[top--];
}

int main() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF) {
        if (c == '(')
            push(c);
        else if (c == ')') {
            if (top == -1 || pop() != '(') {
                push('(');
                push(')');
            } 
        }
    }

    if (top == -1) {
        printf("1\n");
    } else {
        printf("0\n");
    }

    return 0;
}