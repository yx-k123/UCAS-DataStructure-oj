#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createList() {
    Node* head = NULL;
    Node* tail = NULL;
    int x;
    while (scanf("%d", &x) == 1) {
        Node* node = (Node*)malloc(sizeof(Node));
        node->data = x;
        node->next = NULL;
        if (!head) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }
    return head;
}

void printList(Node* head) {
    Node* p = head;
    while (p) {
        printf("%d", p->data);
        if (p->next) printf(" ");
        p = p->next;
    }
    printf("\n");
}

void selectionSort(Node* head) {
    for (Node* p = head; p; p = p->next) {
        Node* minNode = p;
        for (Node* q = p->next; q; q = q->next) {
            if (q->data < minNode->data) {
                minNode = q;
            }
        }
        if (minNode != p) {
            int tmp = p->data;
            p->data = minNode->data;
            minNode->data = tmp;
        }
    }
}

void freeList(Node* head) {
    Node* p;
    while (head) {
        p = head;
        head = head->next;
        free(p);
    }
}

int main() {
    Node* head = createList();
    selectionSort(head);
    printList(head);
    freeList(head);
    return 0;
}