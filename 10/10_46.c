#include <stdio.h>

typedef struct {
    int value;
} ListNode;

typedef struct {
    ListNode array[10000];
    int length;
} List;

void quickSort(List *list, int left, int right) {
    if (left >= right) return;

    int i = left, j = right;
    int pivotValue = list->array[left].value;  

    while (i < j) {
        while (i < j && list->array[j].value >= pivotValue) j--;
        if (i < j) {
            ListNode temp = list->array[i];
            list->array[i] = list->array[j];
            list->array[j] = temp;
            i++;
        }
        while (i < j && list->array[i].value < pivotValue) i++;
        if (i < j) {
            ListNode temp = list->array[i];
            list->array[i] = list->array[j];
            list->array[j] = temp;
            j--;
        }
    }

    quickSort(list, left, i - 1);
    quickSort(list, i + 1, right);
}

int main() {   
    List list;
    scanf("%d", &list.length);
    
    for (int i = 0; i < list.length; i++) {
        scanf("%d", &list.array[i].value);
    }
    
    quickSort(&list, 0, list.length - 1);
    
    for (int i = 0; i < list.length; i++) {
        printf("%d ", list.array[i].value);
    }
    printf("\n");
    
    return 0;
}