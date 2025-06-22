#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int data;
    struct ListNode* next;
} ListNode;

ListNode* createNode(int data) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

int getDigit(int num, int pos) {
    for (int i = 0; i < pos; i++) {
        num /= 10;
    }
    return num % 10;
}

int getMax(ListNode* head) {
    int max = 0;
    while (head != NULL) {
        if (head->data > max) {
            max = head->data;
        }
        head = head->next;
    }
    return max;
}

ListNode* radixSort(ListNode* head) {
    if (head == NULL) return NULL;
    
    int max = getMax(head);

    for (int exp = 1; max / exp > 0; exp *= 10) {
        ListNode* buckets[10] = {NULL};
        ListNode* bucketTails[10] = {NULL};
        
        ListNode* current = head;
        while (current != NULL) {
            ListNode* next = current->next;
            int digit = (current->data / exp) % 10;
            
            current->next = NULL;
            if (buckets[digit] == NULL) {
                buckets[digit] = bucketTails[digit] = current;
            } else {
                bucketTails[digit]->next = current;
                bucketTails[digit] = current;
            }
            current = next;
        }

        head = NULL;
        ListNode* tail = NULL;
        for (int i = 0; i < 10; i++) {
            if (buckets[i] != NULL) {
                if (head == NULL) {
                    head = buckets[i];
                } else {
                    tail->next = buckets[i];
                }
                tail = bucketTails[i];
            }
        }
    }
    
    return head;
}

void printList(ListNode* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

void append(ListNode** head, int data) {
    ListNode* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    
    ListNode* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

int main() {
    ListNode* head = NULL;
    int arr[1000] = {0};
    int n = -1;
    while (scanf("%d", &arr[++n]) == 1){}
    
    for (int i = 0; i < n; i++) {
        append(&head, arr[i]);
    }
    
    head = radixSort(head);
    printList(head);
    
    return 0;
}