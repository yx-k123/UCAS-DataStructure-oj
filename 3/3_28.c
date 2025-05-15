#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* initQueue() {
    Node* head = (Node*)malloc(sizeof(Node));
    head->next = head; 
    return head;
}

Node* enqueue(Node* tail, int val) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = val;
    node->next = tail->next; 
    tail->next = node;
    return node; 
}

int dequeue(Node** tailPtr) {
    Node* tail = *tailPtr;
    Node* head = tail->next;
    Node* first = head->next;
    int val = first->data;
    if (first == tail) { 
        head->next = head;
        *tailPtr = head;
    } else {
        head->next = first->next;
    }
    free(first);
    return val;
}

int main() {
    int n;
    char line[1000];
    scanf("%d", &n);
    getchar(); 

    fgets(line, sizeof(line), stdin);
    line[strcspn(line, "\n")] = '\0';

    Node* tail = initQueue();

    char* token = strtok(line, ",");
    while (token) {
        int val = atoi(token);
        tail = enqueue(tail, val);
        token = strtok(NULL, ",");
    }

    Node* head = tail->next;
    for (int i = 0; i < n; i++) {
        int val = dequeue(&tail);
        printf("%d", val);
        if (i != n - 1) printf(",");
    }
    printf("\n");

    free(tail->next);

    return 0;
}