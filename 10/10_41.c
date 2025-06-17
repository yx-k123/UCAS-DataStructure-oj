#include <stdio.h>

void quicksort(int *list, int left, int right);

int main()
{
    int list[1000];
    int n;
    for (n = 0; n < 1000; n++) {
        scanf("%d", &list[n]);
    }

    quicksort(list, 0, n - 1);

    for (int i = 0; i < n; i++) {
        printf("%d ", list[i]);
    }
    return 0;
}

void quicksort(int *list, int left, int right)
{
    if (left >= right) return;

    int pivot = list[left];
    int i = left + 1;
    int j = right;

    while (i <= j) {
        while (i <= right && list[i] < pivot) i++;
        while (j > left && list[j] > pivot) j--;
        if (i <= j) {
            int temp = list[i];
            list[i] = list[j];
            list[j] = temp;
            i++;
            j--;
        }
    }

    list[left] = list[j];
    list[j] = pivot;

    quicksort(list, left, j - 1);
    quicksort(list, j + 1, right);
}