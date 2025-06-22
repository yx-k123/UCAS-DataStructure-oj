#include <stdio.h>

void qsort(int *list, int length);

int main()
{
    int i = 0;
    int list[1000] = {0};
    while (scanf("%d", &list[i++]) != EOF){}
    qsort(list, i - 1);
    for (int j = 0; j < i - 1; j++)
    {
        printf("%d ", list[j]);
    }
    printf("\n");
    return 0;
}

void qsort(int *list, int length)
{
    int stack[1000][2];
    int top = -1;
    stack[++top][0] = 0;
    stack[top][1] = length - 1;

    while (top >= 0) {
        int left = stack[top][0];
        int right = stack[top--][1];
        if (left >= right) continue;

        int pivot = list[left];
        int i = left, j = right;
        while (i < j) {
            while (i < j && list[j] >= pivot) j--;
            if (i < j) list[i++] = list[j];
            while (i < j && list[i] <= pivot) i++;
            if (i < j) list[j--] = list[i];
        }
        list[i] = pivot;

        stack[++top][0] = left;
        stack[top][1] = i - 1;
        stack[++top][0] = i + 1;
        stack[top][1] = right;
    }
}