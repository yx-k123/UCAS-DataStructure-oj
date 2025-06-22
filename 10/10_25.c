#include <stdio.h>
#include <limits.h>

#define MAXSIZE 100

typedef struct {
    int rc;
    int next;
} SLNode;

typedef struct {
    SLNode r[MAXSIZE + 1];
    int length;
} SLinkListType;

void ListInsertSort(SLinkListType *list);

int main()
{
    SLinkListType list;

    scanf("%d", &list.length);
    for (int  i = 0; i < list.length; i++)
    {
        scanf("%d", &list.r[i+1].rc);
    }
    list.r[0].rc = INT_MAX;
    
    ListInsertSort(&list);
    int k = list.r[0].next;
    for (int i = 0; i < list.length; i++) {
        printf("%d ", list.r[k].rc);
        k = list.r[k].next;
    }
    printf("\n");
    return 0;
}

void ListInsertSort(SLinkListType *list) {
    int i, j, k;
    list->r[0].next = 1;
    for (i = 1; i <= list->length; i++) {
        list->r[i].next = 0;
    }
    for (i = 2; i <= list->length; i++) {
        j = 0;
        k = list->r[0].next;
        while (k != 0 && list->r[k].rc <= list->r[i].rc && k != i) {
            j = k;
            k = list->r[k].next;
        }
        list->r[j].next = i;
        list->r[i].next = k;
    }
    k = list->r[0].next;
    while (list->r[k].next != 0) {
        k = list->r[k].next;
    }
    list->r[k].next = list->r[0].next;
}

