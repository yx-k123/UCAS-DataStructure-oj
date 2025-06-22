#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int data;
    struct ListNode* next;
} ListNode;

ListNode* createNode(int data) {
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    node->data = data;
    node->next = NULL;
    return node;
}

ListNode* merge(ListNode* a, ListNode* b) {
    if (!a) return b;
    if (!b) return a;
    
    if (a->data <= b->data) {
        a->next = merge(a->next, b);
        return a;
    } else {
        b->next = merge(a, b->next);
        return b;
    }
}

ListNode* naturalMergeSort(ListNode* head) {
    if (!head || !head->next) return head;
    
    ListNode* p = head;
    ListNode* segmentStart = head;
    ListNode* result = NULL;
    ListNode* resultTail = NULL;
    
    while (p) {
        while (p->next && p->data <= p->next->data) {
            p = p->next;
        }
        
        ListNode* nextSegment = p->next;
        p->next = NULL;
        
        if (!result) {
            result = segmentStart;
            resultTail = segmentStart;
        } else {
            result = merge(result, segmentStart);
        }
        
        p = segmentStart = nextSegment;
    }
    
    p = result;
    int sorted = 1;
    while (p && p->next) {
        if (p->data > p->next->data) {
            sorted = 0;
            break;
        }
        p = p->next;
    }
    
    return sorted ? result : naturalMergeSort(result);
}

int main() {
    int n;
    scanf("%d", &n);
    
    ListNode* head = NULL;
    ListNode* tail = NULL;
    
    for (int i = 0; i < n; i++) {
        int data;
        scanf("%d", &data);
        ListNode* node = createNode(data);
        
        if (!head) {
            head = tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }
    
    head = naturalMergeSort(head);
    
    while (head) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
    
    return 0;
}